Imports System
Imports System.Collections.Generic
Imports System.Windows.Forms
Imports Inventor

Module DstvRule
' =====================================================================
' EXPORT_DSTV2
'
' DSTV export
'
' Fase 1 (geconsolideerd):
' - ST header (24 velden)
' - OBB-gebaseerde DSTV-assen, rechtsdraaiend stelsel,
'   referentiepunt + extremen
' - massa / oppervlakte per meter (MassProperties)
' - ronde gaten via B-Rep cilindervlak-detectie (primaire bron)
'   met profile-path fallback voor cirkelvormige cuts
' - SLOT / RECTANGLE via profile-path contourdetectie
'   (geometrische betekenis: fase 2)
' - BO met numerieke duplicaat-detectie
' - EN + schrijven naar <PartFolder>\<PieceId>.nc1
'
' Fase 2 (Np + X-referentieletter):
' - Np: kleinste X = 0.0 (minX-referentie); pins/pins-start aan de
'   minX-zijde (standaardaanzicht-default; figuur p. 7-8 = PENDING)
' - X-referentieletter 'u' op alle vlakken (F1-default, p. 12)
' - t-diepteveld 0.00 toegevoegd aan ronde-gat BO-regels
'
' Open punten:
' - F1-rest: pins-start per profieltype + per-vlak ref-letter
'   (figuur p. 7-8 is een afbeelding, PENDING)
' - F2: BO slot breedte (hart-tot-hart vs totale lengte)
'   RESOLVED: centre-to-centre = correct; slotvelden niet gewijzigd'
' - F3: BO rechthoek O-kolom
'   RESOLVED voor scherpe rechthoeken: BO d=0.00 wordt door de
'   target-viewer geweigerd (1 validatiewaarschuwing, geverifieerd
'   2026-09). Scherpe rechthoekige openingen worden nu als gesloten,
'   clockwise IK-contour (radius 0.0) geexport. Zie
'   knowledge/dstv/nc1/7th-edition/blocks/BO.md en AK-IK.md.
'   Ronde gaten, slots en vierhoeken die geen rechthoek zijn
'   behouden het bestaande BO-gedrag.
'   3D-fillet (Fillet-tool na de cut): de cut-sketch blijft dan
'   scherp; de werkelijke gatrandloop op het vlak wordt geprobeerd
'   (ProbeHoleBoundaryLoop). 4 lijnen + 4 uniforme bogen -> BO met
'   d = 2 x boogstraal; 4 lijnen -> IK.
'
' Belangrijk:
' Inventor collections zijn 1-based
' .NET Lists zijn 0-based
' =====================================================================

Sub Main()

	' -------------------------------------------------------------
	' Configuratie
	' -------------------------------------------------------------
	Dim ORDER_ID As String = "ORDER-1"
	Dim DRAWING_ID As String = "TEK-1"
	Dim PHASE_ID As String = "1"

	' -------------------------------------------------------------
	' DebugMode: when True, writes a coordinate-system diagnostic
	' report to scratch\ and shows it in the MessageBox. Production
	' output (the .nc1 file) is NOT changed. Set to False after
	' verification. See .clinerules/10-coding-standards.md section 20.
	' -------------------------------------------------------------
	Const DebugMode As Boolean = True
	Const DebugOutputFile As String = "C:\Users\ricog\3D Modeling\Inventor API work\scratch\DSTV_Debug_Report.txt"

	Dim debugSb As New System.Text.StringBuilder

	' =============================================================
	' ONDERDEEL OPHALEN
	' =============================================================

	Dim oDoc As Document = ThisApplication.ActiveDocument
	Dim oPartDoc As PartDocument = Nothing

	If oDoc.DocumentType = DocumentTypeEnum.kAssemblyDocumentObject Then

		Dim oAsmDoc As AssemblyDocument = oDoc

		If oAsmDoc.SelectSet.Count = 0 Then
			MessageBox.Show( _
				"Selecteer eerst Ã©Ã©n Frame Generator-lid in de assembly.", _
				"Geen selectie")
			Return
		End If

		Dim oOcc As ComponentOccurrence = _
			oAsmDoc.SelectSet.Item(1)

		Try
			oPartDoc = oOcc.Definition.Document
		Catch
			MessageBox.Show( _
				"Het geselecteerde object is geen geldig onderdeel.", _
				"Ongeldige selectie")
			Return
		End Try

	ElseIf oDoc.DocumentType = DocumentTypeEnum.kPartDocumentObject Then

		oPartDoc = CType(oDoc, PartDocument)

	Else

		MessageBox.Show( _
			"Open of selecteer een onderdeel (part).", _
			"Verkeerd documenttype")
		Return

	End If


	' =============================================================
	' HEADERGEGEVENS
	' =============================================================

	Dim oDT As PropertySet = _
		oPartDoc.PropertySets.Item("Design Tracking Properties")


	' =============================================================
	' PIECE IDENTIFICATION
	'
	' Voorkeur:
	'   bestandsnaam zonder .ipt
	'
	' Fallback:
	'   DisplayName zonder extensie
	'
	' Part Number wordt hier bewust NIET gebruikt.
	' =============================================================

	Dim sPieceId As String = ""

	Try

		If Not String.IsNullOrWhiteSpace(oPartDoc.FullFileName) Then

			sPieceId = _
				System.IO.Path.GetFileNameWithoutExtension( _
					oPartDoc.FullFileName)

		End If

	Catch

		sPieceId = ""

	End Try


	If String.IsNullOrWhiteSpace(sPieceId) Then

		Try

			sPieceId = _
				System.IO.Path.GetFileNameWithoutExtension( _
					oPartDoc.DisplayName)

		Catch

			sPieceId = oPartDoc.DisplayName

		End Try

	End If


	If String.IsNullOrWhiteSpace(sPieceId) Then

		MessageBox.Show( _
			"Kan geen Piece Identification bepalen." & _
			vbCrLf & _
			"Controleer de bestandsnaam van het onderdeel.", _
			"Piece Identification ontbreekt")

		Return

	End If


	' =============================================================
	' STEEL GRADE
	' =============================================================

	Dim sSteelGrade As String = ""

	Try
		sSteelGrade = CStr(oDT.Item("Material").Value)
	Catch
		sSteelGrade = ""
	End Try


	' =============================================================
	' PROFIELNAAM
	' =============================================================

	Dim sProfileName As String = ""

	Try
		sProfileName = CStr(oDT.Item("Stock Number").Value)
	Catch
		sProfileName = ""
	End Try


	If String.IsNullOrWhiteSpace(sProfileName) Then

		Try
			sProfileName = CStr(oDT.Item("Part Number").Value)
		Catch
			sProfileName = ""
		End Try

	End If


	If String.IsNullOrWhiteSpace(sProfileName) Then

		Try
			sProfileName = CStr(oDT.Item("Description").Value)
		Catch
			sProfileName = ""
		End Try

	End If


	If String.IsNullOrWhiteSpace(sProfileName) Then

		MessageBox.Show( _
			"Kon geen profielnaam vinden.", _
			"Profielnaam ontbreekt")
		Return

	End If


	sProfileName = _
		CleanProfileDesignation(sProfileName)


	Dim sProfileCode As String = _
		GetDstvProfileCode(sProfileName)


	' =============================================================
	' COMPONENT DEFINITION EN BODY
	' =============================================================

	Dim oCompDef As PartComponentDefinition = _
		oPartDoc.ComponentDefinition

	Dim oBody As SurfaceBody = Nothing

	If oCompDef.SurfaceBodies.Count > 0 Then
		oBody = oCompDef.SurfaceBodies.Item(1)
	End If


	If oBody Is Nothing Then

		MessageBox.Show( _
			"Geen SurfaceBody gevonden.", _
			"Geen geometrie")
		Return

	End If


	' =============================================================
	' PROFIELPARAMETERS
	' =============================================================

	Dim dHeightMm As Double = _
		GetProfileParam( _
			oPartDoc, _
			{"ParH", "height", "G_H", "H", "h"}, _
			0.0)


	Dim dWidthMm As Double = _
		GetProfileParam( _
			oPartDoc, _
			{"b", "width", "G_B", "B"}, _
			0.0)


	Dim dFlangeThickMm As Double = _
		GetProfileParam( _
			oPartDoc, _
			{"t2", "tf", "G_TF", "TF", "t_f"}, _
			0.0)


	Dim dWebThickMm As Double = _
		GetProfileParam( _
			oPartDoc, _
			{"t1", "tw", "G_TW", "TW", "t_w", "s"}, _
			0.0)


	Dim dRadiusMm As Double = _
		GetProfileParam( _
			oPartDoc, _
			{"R1", "r", "G_R", "R"}, _
			0.0)


	' =============================================================
	' DSTV COORDINATENSYSTEEM
	' =============================================================

	Dim oOBB As OrientedBox = _
		oBody.OrientedMinimumRangeBox


	Dim obbV1 As Vector = _
		oOBB.DirectionOne.Copy


	Dim obbV2 As Vector = _
		oOBB.DirectionTwo.Copy


	Dim obbV3 As Vector = _
		oOBB.DirectionThree.Copy


	Dim obbLen1Mm As Double = _
		obbV1.Length * 10.0


	Dim obbLen2Mm As Double = _
		obbV2.Length * 10.0


	Dim obbLen3Mm As Double = _
		obbV3.Length * 10.0


	Dim lengthIndex As Integer = _
		GetLargestIndex( _
			obbLen1Mm, _
			obbLen2Mm, _
			obbLen3Mm)


	Dim lengthVec As Vector = Nothing
	Dim crossVecA As Vector = Nothing
	Dim crossVecB As Vector = Nothing


	Dim crossLenA As Double = 0.0
	Dim crossLenB As Double = 0.0


	If lengthIndex = 1 Then

		lengthVec = obbV1
		crossVecA = obbV2
		crossVecB = obbV3

		crossLenA = obbLen2Mm
		crossLenB = obbLen3Mm

	ElseIf lengthIndex = 2 Then

		lengthVec = obbV2
		crossVecA = obbV1
		crossVecB = obbV3

		crossLenA = obbLen1Mm
		crossLenB = obbLen3Mm

	Else

		lengthVec = obbV3
		crossVecA = obbV1
		crossVecB = obbV2

		crossLenA = obbLen1Mm
		crossLenB = obbLen2Mm

	End If


	Dim dLengthMm As Double = _
		lengthVec.Length * 10.0


	' =============================================================
	' HOOGTE EN BREEDTE
	' =============================================================

	Dim heightVec As Vector = Nothing
	Dim widthVec As Vector = Nothing


	If dHeightMm > 0.0 AndAlso _
		dWidthMm > 0.0 Then

		Dim errAH As Double = _
			Math.Abs(crossLenA - dHeightMm)


		Dim errAW As Double = _
			Math.Abs(crossLenA - dWidthMm)


		If errAH <= errAW Then

			heightVec = crossVecA
			widthVec = crossVecB

		Else

			heightVec = crossVecB
			widthVec = crossVecA

		End If

	Else

		If crossLenA >= crossLenB Then

			heightVec = crossVecA
			widthVec = crossVecB

		Else

			heightVec = crossVecB
			widthVec = crossVecA

		End If

	End If


	If dHeightMm <= 0.0 Then
		dHeightMm = heightVec.Length * 10.0
	End If


	If dWidthMm <= 0.0 Then
		dWidthMm = widthVec.Length * 10.0
	End If


	' =============================================================
	' DSTV X-AS
	' =============================================================

	Dim xUnit As UnitVector = _
		GetOrientedAxis( _
			lengthVec, _
			ThisApplication.TransientGeometry.CreateUnitVector(1, 0, 0), _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 1, 0), _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 0, 1))


	' =============================================================
	' DSTV Z-AS
	' =============================================================

	Dim zUnit As UnitVector = _
		GetOrientedAxis( _
			heightVec, _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 0, 1), _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 1, 0), _
			ThisApplication.TransientGeometry.CreateUnitVector(1, 0, 0))


	' =============================================================
	' Y-AS = Z x X
	' =============================================================

	Dim yVector As Vector = _
		zUnit.AsVector.CrossProduct( _
			xUnit.AsVector)


	yVector.Normalize()


	Dim yUnit As UnitVector = _
		yVector.AsUnitVector


	' =============================================================
	' RECHTSDRAAIEND STELSEL
	' =============================================================

	Dim checkVector As Vector = _
		xUnit.AsVector.CrossProduct( _
			yUnit.AsVector)


	If DotVector( _
		checkVector, _
		zUnit.AsVector) < 0.0 Then

		yVector.ScaleBy(-1.0)
		yUnit = yVector.AsUnitVector

	End If


	' =============================================================
	' REFERENTIEPUNT
	' =============================================================

	If oBody.Vertices.Count = 0 Then

		MessageBox.Show( _
			"De SurfaceBody bevat geen vertices.", _
			"Geen geometrie")
		Return

	End If


	Dim oRefPoint As Point = _
		oBody.Vertices.Item(1).Point.Copy


	Dim minX As Double = Double.MaxValue
	Dim maxY As Double = Double.MinValue
	Dim minZ As Double = Double.MaxValue
	Dim maxX As Double = Double.MinValue
	Dim minY As Double = Double.MaxValue
	Dim maxZ As Double = Double.MinValue


	For Each oVertex As Vertex In oBody.Vertices

		Dim pVertex As Point = _
			oVertex.Point


		Dim relVertex As Vector = _
			oRefPoint.VectorTo(pVertex)


		Dim px As Double = _
			DotVector(relVertex, xUnit.AsVector)


		Dim py As Double = _
			DotVector(relVertex, yUnit.AsVector)


		Dim pz As Double = _
			DotVector(relVertex, zUnit.AsVector)


		If px < minX Then
			minX = px
		End If

		If px > maxX Then
			maxX = px
		End If

		If py > maxY Then
			maxY = py
		End If

		If py < minY Then
			minY = py
		End If

		If pz < minZ Then
			minZ = pz
		End If

		If pz > maxZ Then
			maxZ = pz
		End If

	Next


	' -------------------------------------------------------------
	' Np / nulpunt (fase 2):
	' - Kleinste X = 0.0: alle BO-X-coordinaten worden verminderd met
	'   minX (zie de BO-regelbouw). Np/pins liggen daarmee aan de
	'   minX-zijde van het werkstuk (default; de exacte pins-start
	'   regel per profieltype uit figuur p. 7-8 is PENDING).
	' - Theoretische omhullende: voor rechte prismatische profielen
	'   (I/U/L, platen) vallen de OBB-extremen samen met de
	'   theoretische envelope. Voor gekromde werkstukken (kromme
	'   balken / gebogen onderdelen) wijkt de ruwe OBB daarvan af;
	'   dat blijft een open punt in deze fase.
	' -------------------------------------------------------------
	' =============================================================
	' DEBUG: coordinate-system diagnostic dump (DebugMode only)
	' =============================================
	If DebugMode Then
		debugSb.AppendLine("=== COORDINATE SYSTEM DIAGNOSTIC ===")
		debugSb.AppendLine("Piece ID: " + sPieceId)
		debugSb.AppendLine("Profile: " + sProfileName + " (" + sProfileCode + ")")
		debugSb.AppendLine("dHeightMm=" + Fmt(dHeightMm) + " dWidthMm=" + Fmt(dWidthMm) + " dLengthMm=" + Fmt(dLengthMm))
		debugSb.AppendLine("")
		debugSb.AppendLine("OBB direction lengths (mm): " + Fmt(obbLen1Mm) + " / " + Fmt(obbLen2Mm) + " / " + Fmt(obbLen3Mm))
		debugSb.AppendLine("lengthIndex (1/2/3): " + lengthIndex.ToString())
		debugSb.AppendLine("")
		debugSb.AppendLine("xUnit (length axis): " + Fmt(xUnit.AsVector.X) + ", " + Fmt(xUnit.AsVector.Y) + ", " + Fmt(xUnit.AsVector.Z))
		debugSb.AppendLine("yUnit (width axis):  " + Fmt(yUnit.AsVector.X) + ", " + Fmt(yUnit.AsVector.Y) + ", " + Fmt(yUnit.AsVector.Z))
		debugSb.AppendLine("zUnit (height axis): " + Fmt(zUnit.AsVector.X) + ", " + Fmt(zUnit.AsVector.Y) + ", " + Fmt(zUnit.AsVector.Z))
		debugSb.AppendLine("")
		debugSb.AppendLine("Right-handed check (x cross y dot z): " + Fmt(DotVector(xUnit.AsVector.CrossProduct(yUnit.AsVector), zUnit.AsVector)))
		debugSb.AppendLine("")
		debugSb.AppendLine("Reference point (model coords): " + Fmt(oRefPoint.X) + ", " + Fmt(oRefPoint.Y) + ", " + Fmt(oRefPoint.Z))
		debugSb.AppendLine("Extremes (DSTV frame, mm): minX=" + Fmt(minX * 10.0) + " maxX=" + Fmt(maxX * 10.0) + " minY=" + Fmt(minY * 10.0) + " maxY=" + Fmt(maxY * 10.0) + " minZ=" + Fmt(minZ * 10.0) + " maxZ=" + Fmt(maxZ * 10.0))
		debugSb.AppendLine("Computed piece size (mm): X=" + Fmt(maxX * 10.0 - minX * 10.0) + " Y=" + Fmt(maxY * 10.0 - minY * 10.0) + " Z=" + Fmt(maxZ * 10.0 - minZ * 10.0))
		debugSb.AppendLine("SurfaceBody vertex count: " + oBody.Vertices.Count.ToString())
		debugSb.AppendLine("=====================================")
		debugSb.AppendLine("")
	End If

	' =============================================================
	' MASSA EN OPPERVLAKTE
	' =============================================================

	Dim oMassProps = _
		oCompDef.MassProperties


	oMassProps.Accuracy = _
		MassPropertiesAccuracyEnum.k_Low


	Dim lengthMeters As Double = _
		dLengthMm / 1000.0


	Dim dWeightPerMeter As Double = 0.0
	Dim dAreaPerMeter As Double = 0.0


	If lengthMeters > 0.0 Then

		dWeightPerMeter = _
			Math.Round( _
				oMassProps.Mass / lengthMeters, _
				3)


		dAreaPerMeter = _
			Math.Round( _
				(oMassProps.Area / 10000.0) / _
				lengthMeters, _
				3)

	End If


	' =============================================================
	' OPENINGEN
	' =============================================================

	Dim holeLines As New List(Of String)

	' IK internal-contour blocks (scherpe rechthoekige openingen).
	' Elk element is een compleet blok: "IK"-kop + puntdatalijnen.
	' De target-viewer weigert scherpe rechthoeken als BO d=0.00
	' maar accepteert ze als gesloten clockwise IK-contour
	' (geverifieerd 2026-09; zie knowledge/dstv/nc1/7th-edition/).
	Dim ikBlocks As New List(Of String)

	Dim holeToleranceMm As Double = 0.05


	Dim oFeatures As PartFeatures = _
		oCompDef.Features


	' -------------------------------------------------------------
	' DEBUG: feature-type census counters
	' -------------------------------------------------------------
	Dim censusTotal As Integer = 0
	Dim censusNotExtrude As Integer = 0
	Dim censusNotCut As Integer = 0
	Dim censusCutProcessed As Integer = 0

	For Each oFeature As PartFeature In oFeatures

		censusTotal += 1

		If Not TypeOf oFeature Is ExtrudeFeature Then
			censusNotExtrude += 1
			If DebugMode Then
				debugSb.AppendLine("  FEATURE (not extrude): " + oFeature.Name + " type=" + oFeature.Type.ToString())
			End If

			' Ronde gaten worden hier NIET meer via feature-objecten
			' opgezocht: de B-Rep cilindervlak-detectie (verderop) is de
			' primaire bron. Deze features worden daarom overgeslagen.

			Continue For
		End If


		Dim oExtrude As ExtrudeFeature = _
			CType(oFeature, ExtrudeFeature)


		If oExtrude.Operation <> _
			PartFeatureOperationEnum.kCutOperation Then

			censusNotCut += 1
			Continue For

		End If

		censusCutProcessed += 1
		If DebugMode Then
			debugSb.AppendLine("  FEATURE (cut extrude): " + oFeature.Name)
		End If


		' ---------------------------------------------------------
		' PROFILE
		' ---------------------------------------------------------

		Dim oProfile As Profile = Nothing


		Try

			oProfile = oExtrude.Profile

		Catch

			oProfile = Nothing

		End Try


		If oProfile Is Nothing Then
			Continue For
		End If


		' ---------------------------------------------------------
		' PROFILE PATHS
		' ---------------------------------------------------------

		For pathIndex As Integer = 1 To oProfile.Count

			Dim oPath As ProfilePath = Nothing


			Try

				oPath = oProfile.Item(pathIndex)

			Catch

				Continue For

			End Try


			If oPath Is Nothing Then
				Continue For
			End If


			If Not oPath.Closed Then
				Continue For
			End If


			If oPath.Count <= 0 Then
				Continue For
			End If


			' -----------------------------------------------------
			' GEOMETRIE TELLEN
			' -----------------------------------------------------

			Dim lineCount As Integer = 0
			Dim arcCount As Integer = 0
			Dim circleCount As Integer = 0


			Dim sketchObj As Object = Nothing


			For entityIndex As Integer = 1 To oPath.Count

				Dim oProfileEntity As ProfileEntity = Nothing


				Try

					oProfileEntity = _
						oPath.Item(entityIndex)

				Catch

					Continue For

				End Try


				If oProfileEntity Is Nothing Then
					Continue For
				End If


				Dim oSketchEntity As SketchEntity = Nothing


				Try

					oSketchEntity = _
						oProfileEntity.SketchEntity

				Catch

					Continue For

				End Try


				If oSketchEntity Is Nothing Then
					Continue For
				End If


				If sketchObj Is Nothing Then

					Try

						sketchObj = _
							oSketchEntity.Parent

					Catch

						sketchObj = Nothing

					End Try

				End If


				If TypeOf oSketchEntity Is SketchLine Then

					lineCount += 1

				ElseIf TypeOf oSketchEntity Is SketchArc Then

					arcCount += 1

				ElseIf TypeOf oSketchEntity Is SketchCircle Then

					circleCount += 1

				End If

			Next


			' -----------------------------------------------------
			' SKETCH
			' -----------------------------------------------------

			Dim oSketch As PlanarSketch = Nothing


			Try

				oSketch = CType( _
					sketchObj, _
					PlanarSketch)

			Catch

				oSketch = Nothing

			End Try


			If oSketch Is Nothing Then
				Continue For
			End If


			' =====================================================
			' ROUND
			' =====================================================

			If circleCount = 1 AndAlso _
				lineCount = 0 AndAlso _
				arcCount = 0 Then


				For entityIndex As Integer = 1 To oPath.Count

					Dim pe As ProfileEntity = Nothing


					Try

						pe = oPath.Item(entityIndex)

					Catch

						Continue For

					End Try


					Dim se As SketchEntity = Nothing


					Try

						se = pe.SketchEntity

					Catch

						Continue For

					End Try


					If TypeOf se Is SketchCircle Then

						Dim sc As SketchCircle = _
							CType(se, SketchCircle)


						Dim circle2d As Circle2d = Nothing


						Try

							circle2d = _
								CType(sc.Geometry, circle2d)

						Catch

							Continue For

						End Try


						If circle2d Is Nothing Then
							Continue For
						End If


						Dim sketchCenter As Point2d = _
							circle2d.Center


						Dim modelCenter As Point = _
							oSketch.SketchToModelSpace( _
								sketchCenter)


						Dim diameterMm As Double = _
							circle2d.Radius * 20.0


						Dim holeX As Double = _
							GetDstvX( _
								modelCenter, _
								oRefPoint, _
								xUnit, _
								minX)


						Dim holeY As Double = _
							GetDstvY( _
								modelCenter, _
								oRefPoint, _
								yUnit, _
								maxY)


						Dim holeZ As Double = _
							GetDstvZ( _
								modelCenter, _
								oRefPoint, _
								zUnit, _
								minZ)


						Dim sFace As String = _
							GetOpeningFace( _
								oSketch, _
								modelCenter, _
								oBody, _
								xUnit, _
								yUnit, _
								zUnit, _
								dHeightMm, _
								holeY, _
								holeZ)


						Dim facePos As Double = _
							GetFacePosition( _
								sFace, _
								holeY, _
								holeZ)


						' -------------------------------------------------
						' RONDE OPENING - canonieke vorm (geen referentieletter)
						'
						'   face X Y diameter
						'
						' B-Rep detectie (verderop) is de primaire bron voor
						' ronde gaten; deze profile-path tak is de fallback
						' voor cirkelvormige extrude-cuts en schrijft dezelfde
						' regelinvoer. Numerieke dedupe combineert overlaps.
						' -------------------------------------------------

						If DebugMode Then
							debugSb.AppendLine("  OPENING: face=" + sFace + " facePos=" + Fmt(facePos) + " holeX=" + Fmt(holeX) + GetDstvXref(sFace) + " holeY=" + Fmt(holeY) + " holeZ=" + Fmt(holeZ) + " dia=" + Fmt(diameterMm))
						End If

						Dim sHoleLine As String = _
							"  " & _
							sFace & " " & _
							Fmt(holeX) & GetDstvXref(sFace) & " " & _
							Fmt(facePos) & " " & _
							Fmt(diameterMm) & " " & _
							Fmt(0.0)


						AddHoleLineUnique( _
							holeLines, _
							sHoleLine, _
							holeToleranceMm)


						Exit For

					End If

				Next


			' =====================================================
			' SLOT
			' =====================================================

			ElseIf lineCount = 2 AndAlso _
				arcCount = 2 AndAlso _
				circleCount = 0 Then


				Dim arcCenters As New List(Of Point2d)

				Dim slotRadiusMm As Double = 0.0


				For entityIndex As Integer = 1 To oPath.Count

					Dim pe As ProfileEntity = Nothing


					Try

						pe = oPath.Item(entityIndex)

					Catch

						Continue For

					End Try


					Dim se As SketchEntity = Nothing


					Try

						se = pe.SketchEntity

					Catch

						Continue For

					End Try


					If TypeOf se Is SketchArc Then

						Dim sa As SketchArc = _
							CType(se, SketchArc)


						Dim arc2d As Arc2d = Nothing


						Try

							arc2d = _
								CType(sa.Geometry, arc2d)

						Catch

							Continue For

						End Try


						If arc2d Is Nothing Then
							Continue For
						End If


						arcCenters.Add( _
							arc2d.Center)


						slotRadiusMm = _
							arc2d.Radius * 10.0

					End If

				Next


				If arcCenters.Count = 2 Then

					' -------------------------------------------------
					' BELANGRIJK:
					' List(Of Point2d) is 0-based
					' -------------------------------------------------

					Dim c1 As Point2d = _
						arcCenters(0)


					Dim c2 As Point2d = _
						arcCenters(1)


					Dim centerSketch As Point2d = _
						ThisApplication.TransientGeometry.CreatePoint2d( _
							(c1.X + c2.X) / 2.0, _
							(c1.Y + c2.Y) / 2.0)


					Dim modelCenter As Point = _
						oSketch.SketchToModelSpace( _
							centerSketch)


					Dim widthMm As Double = _
						slotRadiusMm * 2.0


					Dim centerDistMm As Double = _
						c1.DistanceTo(c2) * 10.0


					' Compute slot direction in sketch coordinates
					Dim dirSketch As Point2d = _
						ThisApplication.TransientGeometry.CreatePoint2d( _
							c2.X - c1.X, _
							c2.Y - c1.Y)

					' Compute angle in face frame (relative to piece X)
					' NOTE: face type (sFace) is determined later in the code.
					' We compute the angle here using a placeholder and refine
					' after sFace is known.
					Dim angleDeg As Double = _
						Math.Atan2( _
							c2.Y - c1.Y, _
							c2.X - c1.X) * _
						180.0 / Math.PI

					' Normalize to [0, 180) for now
					If angleDeg < 0.0 Then
						angleDeg += 180.0
					End If

					If angleDeg >= 180.0 Then
						angleDeg -= 180.0
					End If


					Dim holeX As Double = _
						GetDstvX( _
							modelCenter, _
							oRefPoint, _
							xUnit, _
							minX)


					Dim holeY As Double = _
						GetDstvY( _
							modelCenter, _
							oRefPoint, _
							yUnit, _
							maxY)


					Dim holeZ As Double = _
						GetDstvZ( _
							modelCenter, _
							oRefPoint, _
							zUnit, _
							minZ)


					Dim sFace As String = _
						GetOpeningFace( _
							oSketch, _
							modelCenter, _
							oBody, _
							xUnit, _
							yUnit, _
							zUnit, _
							dHeightMm, _
							holeY, _
							holeZ)


					Dim facePos As Double = _
						GetFacePosition( _
							sFace, _
							holeY, _
							holeZ)

					' Compute slot angle in face frame (relative to piece X)
					angleDeg = ComputeFaceFrameAngle( _
						oSketch, _
						dirSketch, _
						sFace, _
						xUnit, _
						yUnit, _
						zUnit)
				' Compute slot angle in face frame (relative to piece X)
				angleDeg = ComputeFaceFrameAngle( _
					oSketch, _
					dirSketch, _
					sFace, _
					xUnit, _
					yUnit, _
					zUnit)

				' Normalize to [0, 180) — slot is symmetric under 180° rotation
				If angleDeg < 0.0 Then
					angleDeg += 180.0
				End If

				If angleDeg >= 180.0 Then
					angleDeg -= 180.0
				End If




					' DEBUG: per-opening face decision (slot)
					If DebugMode Then
						debugSb.AppendLine("  OPENING (slot): face=" + sFace + " facePos=" + Fmt(facePos) + " holeX=" + Fmt(holeX) + GetDstvXref(sFace) + " holeY=" + Fmt(holeY) + " holeZ=" + Fmt(holeZ) + " width=" + Fmt(widthMm) + " centerDist=" + Fmt(centerDistMm) + " angle=" + Fmt(angleDeg))
					End If


					' -------------------------------------------------
					' SLOT
					'
					' Structuur:
					'
					' face X Y diameter t l
					'      width length angle
					'
					' Geen referentieletter (F1, fase 2).
					' De geometrische betekenis van de slot-afmetingen
					' wordt in fase 2 verbeterd (F2).
					' -------------------------------------------------

					Dim sHoleLine As String = _
						"  " & _
						sFace & " " & _
						Fmt(holeX) & GetDstvXref(sFace) & " " & _
											Fmt(facePos) & " " & _
					Fmt(widthMm) & " " & _
						Fmt(0.0) & _
						"l " & _
						Fmt(centerDistMm) & " " & _
						Fmt(0.0) & " " & _
						Fmt(angleDeg)


					AddHoleLineUnique( _
						holeLines, _
						sHoleLine, _
						holeToleranceMm)

					' ---------------------------------------------
					' DOORGESTOKEN SLOTS: hetzelfde cut-prisma kan
					' naast de schets-vlak ook parallelle vlakken
					' doorsteken (bijv. een slot door BEIDE flenzen).
					' De feature levert slechts EEN profile-path op;
					' zoek de overige doorstoken vlakken via hun
					' binnenloop en emit per vlak een record.
					' (Test G 2026-09: flens-slot door o en u.)
					' ---------------------------------------------
					If DebugMode Then
						Dim peObj As Object = oSketch.PlanarEntity
						debugSb.AppendLine("  SLOT through-face probe: planarEntity=" + If(peObj IsNot Nothing, peObj.GetType().Name, "Nothing"))
					End If

					Dim otherFaces As List(Of String) = _
						GetOtherPiercedFaces( _
							oBody, oSketch, modelCenter, _
							xUnit, yUnit, zUnit, debugSb)

					For Each sOther As String In otherFaces

						If sOther = sFace Then
							Continue For
						End If

						Dim facePosOther As Double = _
							GetFacePosition( _
								sOther, holeY, holeZ)

						Dim sOtherLine As String = _
							"  " & _
							sOther & " " & _
							Fmt(holeX) & GetDstvXref(sOther) & " " & _
							Fmt(facePosOther) & " " & _
							Fmt(widthMm) & " " & _
							Fmt(0.0) & _
							"l " & _
							Fmt(centerDistMm) & " " & _
							Fmt(0.0) & " " & _
							Fmt(angleDeg)

						If DebugMode Then
							debugSb.AppendLine("  OPENING (slot, through-face): face=" + sOther + " facePos=" + Fmt(facePosOther))
						End If

						AddHoleLineUnique( _
							holeLines, _
							sOtherLine, _
							holeToleranceMm)

					Next

				End If


			' =====================================================
			' RECTANGLE
			' =====================================================

			ElseIf lineCount = 4 AndAlso _
				arcCount = 0 AndAlso _
				circleCount = 0 Then


				Dim rectPoints As New List(Of Point2d)
				Dim rectSegments As New List(Of LineSegment2d)
				Dim rectLongestEdgeLen As Double = 0.0
				Dim rectDirSketch As Point2d = _
					ThisApplication.TransientGeometry.CreatePoint2d(1.0, 0.0)


				For entityIndex As Integer = 1 To oPath.Count

					Dim pe As ProfileEntity = Nothing


					Try

						pe = oPath.Item(entityIndex)

					Catch

						Continue For

					End Try


					Dim se As SketchEntity = Nothing


					Try

						se = pe.SketchEntity

					Catch

						Continue For

					End Try


					If TypeOf se Is SketchLine Then

						Dim sl As SketchLine = _
							CType(se, SketchLine)


						Dim line2d As LineSegment2d = Nothing


						Try

							line2d = _
								CType(sl.Geometry, LineSegment2d)

						Catch

							Continue For

						End Try


						If line2d Is Nothing Then
							Continue For
						End If


						rectPoints.Add( _
							line2d.StartPoint)


						rectPoints.Add( _
							line2d.EndPoint)

						' Segmenten bewaren voor de hoekpuntketen
						' (IK-classificatie uit de werkelijke geometrie).
						rectSegments.Add(line2d)
					' Track longest edge for angle computation
					Dim edgeLen As Double = line2d.StartPoint.DistanceTo(line2d.EndPoint)
					If edgeLen > rectLongestEdgeLen Then
						rectLongestEdgeLen = edgeLen
						rectDirSketch = ThisApplication.TransientGeometry.CreatePoint2d( _
							line2d.EndPoint.X - line2d.StartPoint.X, _
							line2d.EndPoint.Y - line2d.StartPoint.Y)
					End If



					End If

				Next


				If rectPoints.Count >= 4 Then

					Dim minSX As Double = Double.MaxValue
					Dim maxSX As Double = Double.MinValue
					Dim minSY As Double = Double.MaxValue
					Dim maxSY As Double = Double.MinValue


					For Each rp As Point2d In rectPoints

						If rp.X < minSX Then
							minSX = rp.X
						End If


						If rp.X > maxSX Then
							maxSX = rp.X
						End If


						If rp.Y < minSY Then
							minSY = rp.Y
						End If


						If rp.Y > maxSY Then
							maxSY = rp.Y
						End If

					Next


					Dim centerSketch As Point2d = _
						ThisApplication.TransientGeometry.CreatePoint2d( _
							(minSX + maxSX) / 2.0, _
							(minSY + maxSY) / 2.0)


					Dim modelCenter As Point = _
						oSketch.SketchToModelSpace( _
							centerSketch)


					Dim sizeXmm As Double = _
						(maxSX - minSX) * 10.0


					Dim sizeYmm As Double = _
						(maxSY - minSY) * 10.0

					'' F3: rectangle edge lengths (bounding box; refined later)
					Dim rectWidthMm As Double = sizeYmm
					Dim rectHeightMm As Double = sizeXmm
					Dim rectODiamMm As Double = 0.0
					Dim rectAngleDeg As Double = 0.0


					Dim holeX As Double = _
						GetDstvX( _
							modelCenter, _
							oRefPoint, _
							xUnit, _
							minX)


					Dim holeY As Double = _
						GetDstvY( _
							modelCenter, _
							oRefPoint, _
							yUnit, _
							maxY)


					Dim holeZ As Double = _
						GetDstvZ( _
							modelCenter, _
							oRefPoint, _
							zUnit, _
							minZ)


					Dim sFace As String = _
						GetOpeningFace( _
							oSketch, _
							modelCenter, _
							oBody, _
							xUnit, _
							yUnit, _
							zUnit, _
							dHeightMm, _
							holeY, _
							holeZ)


					Dim facePos As Double = _
						GetFacePosition( _
							sFace, _
							holeY, _
							holeZ)

					' -------------------------------------------------
					' Scherpe rechthoek vs overige vierhoek
					'
					' De target-viewer weigert een scherpe rechthoekige
					' opening als BO met d=0.00 (geverifieerd 2026-09,
					' zie knowledge/dstv/nc1/7th-edition/blocks/BO.md)
					' en accepteert dezelfde geometrie als gesloten,
					' clockwise IK-contour. De classificatie komt uit
					' de werkelijke geometrie: dit profile-path heeft
					' 4 lijnen en 0 bogen (branchvoorwaarde hierboven),
					' dus de hoeken zijn scherp; BuildOrderedCornerChain
					' + IsRectangleFromCorners bepalen uit de sketch-
					' geometrie of het een echte rechthoek is. Alleen
					' een echte scherpe rechthoek gaat naar IK; elke
					' andere vierhoek behoudt het bestaande BO-gedrag.
					' -------------------------------------------------
					Dim rectCorners As New List(Of Point2d)
					Dim isSharpRectangle As Boolean = _
						BuildOrderedCornerChain(rectSegments, rectCorners) AndAlso _
						IsRectangleFromCorners(rectCorners, 0.01)

					' -------------------------------------------------
					' 3D-FILLET-PROBE
					'
					' De sketch beschrijft een scherpe rechthoek, maar de
					' WERKELIJKE gatrand op het vlak kan door een latere
					' 3D-fillet (Fillet-tool) afgerond zijn: de cut-sketch
					' verandert dan niet, alleen de body. De binnenrandloop
					' van het sketch-vlak bevat de echte gatcontour na alle
					' features (ProbeHoleBoundaryLoop):
					'   4 lijnen + 4 uniforme bogen -> afgeronde rechthoek
					'     -> BO met d = 2 x boogstraal (viewer-geverifieerd);
					'   4 lijnen -> werkelijk scherp -> IK;
					'   anders -> IK (bestaand gedrag) met debug-regel.
					' -------------------------------------------------
					Dim exportMode As String = "BO-QUAD"
					Dim probeStatus As String = ""
					Dim probeFilletCm As Double = 0.0
					Dim probeLines As New List(Of LineSegment)
					Dim probeArcs As New List(Of Arc3d)
					Dim fullLenMm(3) As Double
					Dim edgeAngleDeg(3) As Double
					Dim parallelIdx3 As Integer = -1
					Dim perpIdx3 As Integer = -1

					If isSharpRectangle Then

						probeStatus = ProbeHoleBoundaryLoop(oSketch, modelCenter, probeLines, probeArcs)

						If probeStatus = "FACE" AndAlso _
							probeLines.Count = 4 AndAlso probeArcs.Count = 4 Then

							Dim uniformOk As Boolean = True

							For Each pa As Arc3d In probeArcs
								If Math.Abs(pa.Radius - probeArcs(0).Radius) > 0.0001 Then
									uniformOk = False
								End If
							Next

							If uniformOk Then

								' Per rand: volledige lengte (mm) en hoek in
								' het DSTV-vlakframe (zelfde transformatie als
								' de IK-hoekpunten). Volledige randlengte =
								' lijnlengte + 2 x straal.
								Dim pairOk As Boolean = True
								Dim perpCount3 As Integer = 0

								For i As Integer = 0 To 3

									Dim ln3d As LineSegment = probeLines(i)

									Dim vEx As Double = ln3d.EndPoint.X - ln3d.StartPoint.X
									Dim vEy As Double = ln3d.EndPoint.Y - ln3d.StartPoint.Y
									Dim vEz As Double = ln3d.EndPoint.Z - ln3d.StartPoint.Z

									Dim lenCm As Double = Math.Sqrt(vEx * vEx + vEy * vEy + vEz * vEz)

									fullLenMm(i) = (lenCm + 2.0 * probeArcs(0).Radius) * 10.0

									Dim axDstv As Double = GetDstvX(ln3d.StartPoint, oRefPoint, xUnit, minX)
									Dim ayDstv As Double

									If sFace = "v" OrElse sFace = "h" Then
										ayDstv = GetDstvZ(ln3d.StartPoint, oRefPoint, zUnit, minZ)
									Else
										ayDstv = GetDstvY(ln3d.StartPoint, oRefPoint, yUnit, maxY)
									End If

									Dim bxDstv As Double = GetDstvX(ln3d.EndPoint, oRefPoint, xUnit, minX)
									Dim byDstv As Double

									If sFace = "v" OrElse sFace = "h" Then
										byDstv = GetDstvZ(ln3d.EndPoint, oRefPoint, zUnit, minZ)
									Else
										byDstv = GetDstvY(ln3d.EndPoint, oRefPoint, yUnit, maxY)
									End If

									Dim aDeg As Double = Math.Atan2(byDstv - ayDstv, bxDstv - axDstv) * 180.0 / Math.PI

									If aDeg < 0 Then
										aDeg = aDeg + 180.0
									End If

									If aDeg >= 180.0 Then
										aDeg = aDeg - 180.0
									End If

									edgeAngleDeg(i) = aDeg

								Next

								For i As Integer = 1 To 3

									Dim dAng As Double = Math.Abs(edgeAngleDeg(0) - edgeAngleDeg(i))
									If dAng > 90.0 Then
										dAng = 180.0 - dAng
									End If

									If dAng < 0.01 Then
										If parallelIdx3 < 0 Then
											parallelIdx3 = i
										Else
											pairOk = False
										End If
									ElseIf Math.Abs(dAng - 90.0) < 0.01 Then
										perpCount3 = perpCount3 + 1
										perpIdx3 = i
									Else
										pairOk = False
									End If

								Next

								If pairOk AndAlso parallelIdx3 >= 0 AndAlso perpCount3 = 2 Then

									If Math.Abs(fullLenMm(0) - fullLenMm(parallelIdx3)) > 0.01 Then
										pairOk = False
									End If

									Dim otherIdx3 As Integer = -1

									For i As Integer = 1 To 3
										If i <> parallelIdx3 Then
											If otherIdx3 < 0 Then
												otherIdx3 = i
											ElseIf Math.Abs(fullLenMm(otherIdx3) - fullLenMm(i)) > 0.01 Then
												pairOk = False
											End If
										End If
									Next

								Else
									pairOk = False
								End If

								If pairOk Then
									exportMode = "BO-3DFILLET"
									probeFilletCm = probeArcs(0).Radius
								Else
									exportMode = "IK"
								End If

							Else
								exportMode = "IK"
							End If

						ElseIf probeStatus = "FACE" AndAlso _
							probeLines.Count = 4 AndAlso probeArcs.Count = 0 Then

							exportMode = "IK"

						Else

							exportMode = "IK"

						End If

					End If

					' DEBUG: per-opening face decision (rectangle)
					If DebugMode Then
						debugSb.AppendLine("  OPENING (rect): face=" + sFace + " facePos=" + Fmt(facePos) + " holeX=" + Fmt(holeX) + GetDstvXref(sFace) + " holeY=" + Fmt(holeY) + " holeZ=" + Fmt(holeZ) + " sizeX=" + Fmt(sizeXmm) + " sizeY=" + Fmt(sizeYmm) + " angle=" + Fmt(rectAngleDeg) + " repr=" + exportMode + " probe=" + probeStatus + " probeLines=" + probeLines.Count.ToString() + " probeArcs=" + probeArcs.Count.ToString())
					End If


					If exportMode = "IK" Then

						' ---------------------------------------------
						' IK internal contour (scherpe rechthoek)
						'
						' Puntopbouw volgens DSTV 7e editie p. 13-14 en
						' het HEB400-voorbeeld (p. 22):
						'   face X[ref] Y radius
						' radius 0.0 bij scherpe hoeken; het eerste punt
						' wordt als laatste punt herhaald (gesloten
						' contour, p. 13); interne contouren clockwise.
						' ---------------------------------------------

						' Hoekpunten naar het DSTV-vlakframe. De Y-as
						' volgt dezelfde mapping als de BO-records van
						' dit vlak (zie GetFacePosition): GetDstvY voor
						' o/u-vlakken, GetDstvZ voor v/h-vlakken.
						Dim cornerX As New List(Of Double)
						Dim cornerY As New List(Of Double)

						For Each rectCorner As Point2d In rectCorners

							Dim cornerModel As Point = _
								oSketch.SketchToModelSpace(rectCorner)

							Dim cDstvX As Double = _
								GetDstvX( _
									cornerModel, _
									oRefPoint, _
									xUnit, _
									minX)

							Dim cDstvY As Double

							If sFace = "v" OrElse sFace = "h" Then
								cDstvY = GetDstvZ( _
									cornerModel, _
									oRefPoint, _
									zUnit, _
									minZ)
							Else
								cDstvY = GetDstvY( _
									cornerModel, _
									oRefPoint, _
									yUnit, _
									maxY)
							End If

							cornerX.Add(cDstvX)
							cornerY.Add(cDstvY)

						Next

						' Interne contouren clockwise (DSTV p. 13).
						' Shoelace getekende oppervlakte: positief =
						' wiskundige (CCW) orientatie -> volgorde
						' omkeren; het eerste hoekpunt blijft anker.
						Dim signedArea As Double = 0.0

						For ci As Integer = 0 To cornerX.Count - 1
							Dim cj As Integer = (ci + 1) Mod cornerX.Count
							signedArea += cornerX(ci) * cornerY(cj) - _
								cornerX(cj) * cornerY(ci)
						Next

						If signedArea > 0 Then
							cornerX.Reverse(1, cornerX.Count - 1)
							cornerY.Reverse(1, cornerY.Count - 1)
						End If

						Dim ikSb As New System.Text.StringBuilder

						ikSb.AppendLine("IK")

						For ci As Integer = 0 To cornerX.Count - 1

							ikSb.AppendLine( _
								"  " & sFace & " " & _
								Fmt(cornerX(ci)) & GetDstvXref(sFace) & " " & _
								Fmt(cornerY(ci)) & " " & _
								Fmt(0.0))

						Next

						' Sluitpunt = eerste punt (gesloten contour).
						ikSb.AppendLine( _
							"  " & sFace & " " & _
							Fmt(cornerX(0)) & GetDstvXref(sFace) & " " & _
							Fmt(cornerY(0)) & " " & _
							Fmt(0.0))

						ikBlocks.Add(ikSb.ToString())

						If DebugMode Then
							Dim ikDbg As New System.Text.StringBuilder
							For ci As Integer = 0 To cornerX.Count - 1
								ikDbg.Append("(" + Fmt(cornerX(ci)) + "," + Fmt(cornerY(ci)) + ")")
							Next
							debugSb.AppendLine("    IK contour: face=" + sFace + " corners=" + ikDbg.ToString() + " closed=yes radius=0.00")
						End If

					ElseIf exportMode = "BO-3DFILLET" Then

						' ---------------------------------------------
						' BO-record vanaf de werkelijke gatrandloop
						' (3D-fillet op de gatranden). d = 2 x boogstraal;
						' width/height = volledige randlengten uit de loop;
						' hoek in het DSTV-vlakframe. Toewijzing: de rand
						' met de kleinste hoek t.o.v. stuk-X is de breedte
						' (viewer-geverifieerde conventie bij hoek 0).
						' Alle validatie is al gedaan in de probe-fase;
						' hier is geen faalpad meer.
						' ---------------------------------------------

						Dim fillet3dDiamMm As Double = probeFilletCm * 20.0

						Dim filletAngleDeg As Double
						Dim filletWidthMm As Double
						Dim filletHeightMm As Double

						If edgeAngleDeg(0) <= edgeAngleDeg(perpIdx3) Then
							filletAngleDeg = edgeAngleDeg(0)
							filletWidthMm = fullLenMm(0)
							filletHeightMm = fullLenMm(perpIdx3)
						Else
							filletAngleDeg = edgeAngleDeg(perpIdx3)
							filletWidthMm = fullLenMm(perpIdx3)
							filletHeightMm = fullLenMm(0)
						End If

						If DebugMode Then
							debugSb.AppendLine("  OPENING (rect-3dfillet): face=" + sFace + " holeX=" + Fmt(holeX) + GetDstvXref(sFace) + " facePos=" + Fmt(facePos) + " d=" + Fmt(fillet3dDiamMm) + " width=" + Fmt(filletWidthMm) + " height=" + Fmt(filletHeightMm) + " angle=" + Fmt(filletAngleDeg) + " repr=BO")
						End If

						Dim sHoleLine As String = _
							"  " & _
							sFace & " " & _
							Fmt(holeX) & GetDstvXref(sFace) & " " & _
							Fmt(facePos) & " " & _
							Fmt(fillet3dDiamMm) & " " & _
							Fmt(0.0) & _
							"l " & _
							Fmt(filletWidthMm) & " " & _
							Fmt(filletHeightMm) & " " & _
							Fmt(filletAngleDeg)

						AddHoleLineUnique( _
							holeLines, _
							sHoleLine, _
							holeToleranceMm)

					Else

						' ---------------------------------------------
						' BO-record (bestaand gedrag voor een vierhoek
						' die geen rechthoek is). Onveranderd gelaten.
						' ---------------------------------------------

						' Compute rectangle angle in face frame (relative to piece X)
					rectAngleDeg = ComputeFaceFrameAngle( _
						oSketch, _
						rectDirSketch, _
						sFace, _
						xUnit, _
						yUnit, _
						zUnit)



								' Rectangle angle: set to 0 (axis-aligned with piece).
				' The edge-vector angle computation is unreliable for
				' sketches where axes don't align with piece axes.
				rectAngleDeg = 0.0






					' (legacy per-rectangle debug removed 2026-09; superseded by the
'  repr= debug line above)


					' -------------------------------------------------
					' RECTANGLE
					'
					' Structuur:
					'
					' face X Y diameter t l
					'      width height angle
					'
					' Geen referentieletter (F1, fase 2).
					' Voor deze eerste versie gebruiken we 0 voor
					' diameter en t. Rotatie van de rechthoek wordt
					' in fase 2 toegevoegd.
					'
					' NB (2026-09): dit BO-pad geldt alleen nog voor
					' vierhoeken die geen rechthoek zijn; echte scherpe
					' rechthoeken gaan naar IK (zie hierboven).
					' -------------------------------------------------

					Dim sHoleLine As String = _
						"  " & _
						sFace & " " & _
						Fmt(holeX) & GetDstvXref(sFace) & " " & _
						Fmt(facePos) & " " & _
						Fmt(rectODiamMm) & " " & _
						Fmt(0.0) & _
						"l " & _
						Fmt(rectWidthMm) & " " & _
						Fmt(rectHeightMm) & " " & _
						Fmt(rectAngleDeg)


					AddHoleLineUnique( _
						holeLines, _
						sHoleLine, _
						holeToleranceMm)

					End If

				End If

				ElseIf lineCount = 4 AndAlso arcCount = 4 AndAlso circleCount = 0 Then

					' =====================================================
					' FILLETED RECTANGLE (4 lijnen + 4 hoekbogen)
					'
					' De target-viewer accepteert een rechthoekige opening
					' met een geldige, niet-nul hoekdiameter als BO
					' (geverifieerd: d = 1.00/10.00/20.00 -> PASS; zie
					' knowledge/dstv/nc1/7th-edition/blocks/BO.md). Zonder
					' deze branch valt een gejilletteerde rechthoek door
					' alle classificatie-branches heen en verdwijnt de
					' opening volledig uit het NC-bestand.
					'
					' Classificatie uit de werkelijke geometrie. Gevallen
					' die niet als een enkele BO-rechthoek representeerbaar
					' zijn (niet-uniforme hoekstralen, geen rechthoek)
					' worden overgeslagen met een debug-regel.
					' =====================================================

					Dim filletLines As New List(Of LineSegment2d)
					Dim filletArcs As New List(Of Arc2d)

					For entityIndex As Integer = 1 To oPath.Count

						Dim peF As ProfileEntity = Nothing

						Try
							peF = oPath.Item(entityIndex)
						Catch
							Continue For
						End Try

						If peF Is Nothing Then
							Continue For
						End If

						Dim seF As SketchEntity = Nothing

						Try
							seF = peF.SketchEntity
						Catch
							Continue For
						End Try

						If seF Is Nothing Then
							Continue For
						End If

						If TypeOf seF Is SketchLine Then

							Dim slF As SketchLine = CType(seF, SketchLine)
							Dim lineF As LineSegment2d = Nothing

							Try
								lineF = CType(slF.Geometry, LineSegment2d)
							Catch
								lineF = Nothing
							End Try

							If lineF IsNot Nothing Then
								filletLines.Add(lineF)
							End If

						ElseIf TypeOf seF Is SketchArc Then

							Dim saF As SketchArc = CType(seF, SketchArc)
							Dim arcF As Arc2d = Nothing

							Try
								arcF = CType(saF.Geometry, Arc2d)
							Catch
								arcF = Nothing
							End Try

							If arcF IsNot Nothing Then
								filletArcs.Add(arcF)
							End If

						End If

					Next

					Dim filletSkipReason As String = ""
					Dim cornerRadiusCm As Double = 0.0

					If filletLines.Count <> 4 OrElse filletArcs.Count <> 4 Then

						filletSkipReason = "profile is not 4 lines + 4 arcs"

					Else

						cornerRadiusCm = filletArcs(0).Radius

						For Each fa As Arc2d In filletArcs
							If Math.Abs(fa.Radius - cornerRadiusCm) > 0.0001 Then
								filletSkipReason = "corner radii are not uniform"
							End If
						Next

					End If

					Dim edgeDx(3) As Double
					Dim edgeDy(3) As Double
					Dim edgeLenCm(3) As Double

					If filletSkipReason = "" Then

						For i As Integer = 0 To 3

							Dim vEx As Double = filletLines(i).EndPoint.X - filletLines(i).StartPoint.X
							Dim vEy As Double = filletLines(i).EndPoint.Y - filletLines(i).StartPoint.Y

							edgeLenCm(i) = Math.Sqrt(vEx * vEx + vEy * vEy)

							If edgeLenCm(i) > 0.00001 Then
								edgeDx(i) = vEx / edgeLenCm(i)
								edgeDy(i) = vEy / edgeLenCm(i)
							Else
								filletSkipReason = "degenerate (zero-length) edge"
							End If

						Next

					End If

					Dim parallelIdx As Integer = -1
					Dim perpIdx As Integer = -1

					If filletSkipReason = "" Then

						Dim perpCount As Integer = 0

						For i As Integer = 1 To 3

							Dim dotVal As Double = Math.Abs(edgeDx(0) * edgeDx(i) + edgeDy(0) * edgeDy(i))

							If dotVal >= 0.999 Then

								If parallelIdx < 0 Then
									parallelIdx = i
								Else
									filletSkipReason = "edges do not form a rectangle"
								End If

							ElseIf dotVal <= 0.01 Then
								perpCount = perpCount + 1
								perpIdx = i
							Else
								filletSkipReason = "edges do not form a rectangle"
							End If

						Next

						If filletSkipReason = "" Then

							If parallelIdx < 0 OrElse perpCount <> 2 Then

								filletSkipReason = "edges do not form a rectangle"

							ElseIf Math.Abs(edgeLenCm(0) - edgeLenCm(parallelIdx)) > 0.001 Then

								filletSkipReason = "opposite edges differ in length"

							Else

								Dim otherIdx As Integer = -1

								For i As Integer = 1 To 3
									If i <> parallelIdx Then
										If otherIdx < 0 Then
											otherIdx = i
										ElseIf Math.Abs(edgeLenCm(otherIdx) - edgeLenCm(i)) > 0.001 Then
											filletSkipReason = "opposite edges differ in length"
										End If
									End If
								Next

							End If

						End If

					End If

					If filletSkipReason <> "" Then

						If DebugMode Then
							debugSb.AppendLine("  OPENING (rect-fillet): SKIPPED (" + filletSkipReason + ")")
						End If

					Else

						' Hoekdiameter d = 2 x filletraadius (sketch cm -> mm).
						Dim filletDiamMm As Double = cornerRadiusCm * 20.0

						' Volledige randlengte = lijnlengte + 2 x straal
						' (de fillet kortt elk randeinde met r in).
						Dim fullLenA_Mm As Double = (edgeLenCm(0) + 2.0 * cornerRadiusCm) * 10.0
						Dim fullLenB_Mm As Double = (edgeLenCm(perpIdx) + 2.0 * cornerRadiusCm) * 10.0

						' Rechthoekcentrum = gemiddelde van de vier
						' boogmiddelpunten (exact voor een gejilletteerde
						' rechthoek; de bbox van lijneindpunten zou door de
						' tangentpunten naar binnen trekken).
						Dim sumCx As Double = 0.0
						Dim sumCy As Double = 0.0

						For Each fa As Arc2d In filletArcs
							sumCx = sumCx + fa.Center.X
							sumCy = sumCy + fa.Center.Y
						Next

						Dim centerSketchF As Point2d = _
							ThisApplication.TransientGeometry.CreatePoint2d( _
								sumCx / 4.0, _
								sumCy / 4.0)

						Dim modelCenterF As Point = _
							oSketch.SketchToModelSpace(centerSketchF)

						Dim holeX As Double = _
							GetDstvX(modelCenterF, oRefPoint, xUnit, minX)

						Dim holeY As Double = _
							GetDstvY(modelCenterF, oRefPoint, yUnit, maxY)

						Dim holeZ As Double = _
							GetDstvZ(modelCenterF, oRefPoint, zUnit, minZ)

						Dim sFace As String = _
							GetOpeningFace(oSketch, modelCenterF, oBody, xUnit, yUnit, zUnit, dHeightMm, holeY, holeZ)

						Dim facePos As Double = _
							GetFacePosition(sFace, holeY, holeZ)

						' Randrichtingen naar het DSTV-vlakframe
						' (zelfde transformatie als de IK-hoekpunten).
						Dim angleA As Double = GetDstvFaceFrameAngle(oSketch, centerSketchF, edgeDx(0), edgeDy(0), sFace, oRefPoint, xUnit, yUnit, zUnit, minX, maxY, minZ)
						Dim angleB As Double = GetDstvFaceFrameAngle(oSketch, centerSketchF, edgeDx(perpIdx), edgeDy(perpIdx), sFace, oRefPoint, xUnit, yUnit, zUnit, minX, maxY, minZ)

						Dim filletAngleDeg As Double
						Dim filletWidthMm As Double
						Dim filletHeightMm As Double

						If angleA <= angleB Then
							filletAngleDeg = angleA
							filletWidthMm = fullLenA_Mm
							filletHeightMm = fullLenB_Mm
						Else
							filletAngleDeg = angleB
							filletWidthMm = fullLenB_Mm
							filletHeightMm = fullLenA_Mm
						End If

						If DebugMode Then
							debugSb.AppendLine("  OPENING (rect-fillet): face=" + sFace + " holeX=" + Fmt(holeX) + GetDstvXref(sFace) + " facePos=" + Fmt(facePos) + " d=" + Fmt(filletDiamMm) + " width=" + Fmt(filletWidthMm) + " height=" + Fmt(filletHeightMm) + " angle=" + Fmt(filletAngleDeg) + " repr=BO")
						End If

						Dim sHoleLine As String = _
							"  " & _
							sFace & " " & _
							Fmt(holeX) & GetDstvXref(sFace) & " " & _
							Fmt(facePos) & " " & _
							Fmt(filletDiamMm) & " " & _
							Fmt(0.0) & _
							"l " & _
							Fmt(filletWidthMm) & " " & _
							Fmt(filletHeightMm) & " " & _
							Fmt(filletAngleDeg)

						AddHoleLineUnique( _
							holeLines, _
							sHoleLine, _
							holeToleranceMm)

					End If

			End If

		Next

	Next

	If DebugMode Then
		debugSb.AppendLine("")
		debugSb.AppendLine("=== FEATURE CENSUS ===")
		debugSb.AppendLine("Total features: " + censusTotal.ToString())
		debugSb.AppendLine("Not extrude (skipped): " + censusNotExtrude.ToString())
		debugSb.AppendLine("Extrude but not cut (skipped): " + censusNotCut.ToString())
		debugSb.AppendLine("Cut extrudes processed: " + censusCutProcessed.ToString())
		debugSb.AppendLine("======================")
	End If

	' =============================================================
	' GATEN DETECTEREN (B-Rep)
	'
	' Gebaseerd op de gevalideerde aanpak uit EXPORT_DSTV_ST_BO:
	' elke cilindrische B-Rep face = binnenwand van een gat.
	' - diameter via oCyl.Radius * 2 (cm -> mm)
	' - centrum via de cirkeledge van de face
	' - as via oCyl.AxisVector -> flensgat (o/u) of lijfgat (v/h)
	' =============================================================

	Dim holeCountDetected As Integer = 0

	For Each oSurfBody As SurfaceBody In oCompDef.SurfaceBodies

		For Each oFace As Face In oSurfBody.Faces

			' Alleen cilindervlakken (binnenzijde van een gat)
			If oFace.SurfaceType <> _
				SurfaceTypeEnum.kCylinderSurface Then

				Continue For

			End If

			Dim oCyl As Cylinder = _
				oFace.Geometry

			Dim dDiameterMm As Double = _
				CmToMm(oCyl.Radius * 2.0)

			If dDiameterMm <= 0.0 OrElse _
				dDiameterMm > 100.0 Then

				Continue For

			End If

			Dim oHoleAxis As UnitVector = _
				oCyl.AxisVector

			Dim dotLength As Double = _
				Math.Abs( _
					DotVector( _
						oHoleAxis.AsVector, _
						xUnit.AsVector))

			If dotLength > 0.85 Then
				Continue For
			End If

			' -------------------------------------------------
			' Cirkelcentrum bepalen
			' -------------------------------------------------
			Dim oCircle As Circle = Nothing

			For Each oEdge As Edge In oFace.Edges

				Try

					Dim oGeom As Object = _
						oEdge.Geometry

					If TypeOf oGeom Is Circle Then

						oCircle = _
							CType(oGeom, Circle)

						Exit For

					End If

				Catch

				End Try

			Next

			If oCircle Is Nothing Then
				Continue For
			End If

			Dim oHoleCenter As Point = _
				oCircle.Center

			' -------------------------------------------------
			' Lokale gatcoordinaten
			' -------------------------------------------------
			Dim relHole As Vector = _
				oRefPoint.VectorTo(oHoleCenter)

			Dim holeX As Double = _
				DotVector(relHole, xUnit.AsVector)

			Dim holeY As Double = _
				DotVector(relHole, yUnit.AsVector)

			Dim holeZ As Double = _
				DotVector(relHole, zUnit.AsVector)

			' -------------------------------------------------
			' DSTV absolute X/Y
			' -------------------------------------------------
			Dim vPos As Double = _
				Math.Round( _
					(holeX - minX) * 10.0, _
					2)

			Dim yPos As Double = _
				Math.Round( _
					(maxY - holeY) * 10.0, _
					2)

			Dim zPos As Double = _
				Math.Round( _
					(holeZ - minZ) * 10.0, _
					2)

			' -------------------------------------------------
			' Gatvlak bepalen
			' -------------------------------------------------
			Dim axisAlongHeight As Double = _
				Math.Abs( _
					DotVector( _
						oHoleAxis.AsVector, _
						zUnit.AsVector))

			Dim axisAlongWidth As Double = _
				Math.Abs( _
					DotVector( _
						oHoleAxis.AsVector, _
						yUnit.AsVector))

			Dim sFace As String = ""
			Dim faceY As Double = 0.0

			' Flensgat
			If axisAlongHeight >= axisAlongWidth Then

				If zPos >= dHeightMm / 2.0 Then
					sFace = "o"
				Else
					sFace = "u"
				End If

				faceY = yPos

			' Lijfgat
			Else

				sFace = _
					GetWebFace( _
						oFace, _
						yUnit)

				faceY = zPos

			End If

			If vPos > -0.05 AndAlso _
				vPos < 0.05 Then

				vPos = 0.0

			End If

			If faceY > -0.05 AndAlso _
				faceY < 0.05 Then

				faceY = 0.0

			End If

			' -------------------------------------------------
			' BO-regel
			' -------------------------------------------------
			Dim sHoleLine As String = _
				"  " & _
				sFace & " " & _
				Fmt(vPos) & GetDstvXref(sFace) & " " & _
				Fmt(faceY) & " " & _
				Fmt(dDiameterMm) & " " & _
				Fmt(0.0)

			AddHoleLineUnique( _
				holeLines, _
				sHoleLine, _
				holeToleranceMm)

			holeCountDetected += 1

			If DebugMode Then
				debugSb.AppendLine( _
					"  Hole: face=" & sFace & _
					" X=" & Fmt(vPos) & GetDstvXref(sFace) & _
					" Y=" & Fmt(faceY) & _
					" D=" & Fmt(dDiameterMm) & " mm")
			End If

		Next

	Next

	If DebugMode Then
		debugSb.AppendLine("")
		debugSb.AppendLine("=== B-REP HOLE DETECTION ===")
		debugSb.AppendLine("Holes detected: " & holeCountDetected.ToString())
		debugSb.AppendLine("Total BO records: " & holeLines.Count.ToString())
		debugSb.AppendLine("")
	End If
' =============================================================
	' END-CUT DETECTION (ST skew-angle fields 17-20)
	'
	' Doel:  een SIMPEL, enkel-vlakkig eindeinde (schuin zaagsneden)
	'        detecteren uit de werkelijke body-geometrie en de vier
	'        ST-skew-hoeken berekenen. Dit is fase 1 van de
	'        end-cut-ondersteuning; SC/AK worden hier NIET gebruikt.
	'
	' Werkwijze (geometrie, geen feature-history):
	'   1. Alle vlakken van body 1 doorlopen (het stuk; een eventuele
	'      tweede body - Split-sliver - hoort niet bij het stuk).
	'   2. Een "eindvlak" is een planair vlak waarvan de normaal
	'      hoofdzakelijk langs de lengte-as (xUnit) staat en waarvan
	'      de ECHTE X-extent (bepaald uit de face-vertices) de
	'      uiterste X (minX of maxX) raakt. NB: Face.Evaluator.RangeBox
	'      geeft de box van het ONderliggende ongetrimde vlak en is
	'      daarmee onbruikbaar voor face-positie.
	'      - de vlakpositie (vertex-extent) bepaalt START (minX =
	'        Np-eind) versus END (maxX);
	'      - de vlaknormaal wordt daarna genormaliseerd naar NAAR
	'        BUITEN gericht (start: -X-component, end: +X-component),
	'        zodat de lean-tekens consequent zijn.
	'   3. Start-end en end-end apart groeperen.
	'   4. Als een eind ALLE vlakken met dezelfde normaal heeft
	'      (enkele kopse plane), is het een SIMPELE rechte schuine
	'      snede: hoekgrootte uit de normaal.
	'      - Web-Start/End-Cut: hoek in het vooraanzicht (X-Z vlak),
	'        via de Z-component van de normaal.
	'      - Flens-Start/End-Cut: hoek in het onderaanzicht (X-Y vlak),
	'        via de Y-component van de normaal.
	'   5. ST-signaal: de hoekgrootte is positief; het teken volgt de
	'      GEVERIFIEERDE conventie (viewer 2026-09): START-eind
	'      +lean, END-eind -lean. Vastgelegd in blocks/ST.md als
	'      EXPORTER/VIEWER VERIFIED CONVENTION.
	'   6. Als een eind NIET als één enkel vlak beschrijfbaar is
	'      (meerdere niet-coplanaire vlakken, special cut), dan
	'      worden de ST-waarden NIET berekend en blijft 0.00 staan;
	'      de debug meldt "UNSUPPORTED (special end cut)".
	'
	' NB: Alleen de vier ST-hoeken worden aangepast. Veld 9
	'     (dLengthMm) blijft ongewijzigd (maxX - minX) - zie het
	'     apart geregistreerde item "DSTV length semantics for skew
	'     cuts".
	' =============================================================

	Dim webStartCutDeg As Double = 0.0
	Dim webEndCutDeg As Double = 0.0
	Dim flangeStartCutDeg As Double = 0.0
	Dim flangeEndCutDeg As Double = 0.0

	' Kopse vlakken groeperen per eind (parallel: vlak + genormaliseerde
	' naar-buiten gerichte normaal)
	Dim startEndFaces As New List(Of Face)
	Dim endEndFaces As New List(Of Face)
	Dim startFaceNormals As New List(Of Vector)
	Dim endFaceNormals As New List(Of Vector)

	' Tolerantie voor "raakt de extreem-X": 0.05 cm = 0.5 mm
	Dim endFaceTolCm As Double = 0.05

	' Minimale paralelliteit van de eindvlak-normaal met de
	' lengte-as (|cos|). 0.7 = tot ~45 graden scheefstand.
	Dim endNormalMinCos As Double = 0.7

	' Alleen body 1 doorlopen: het stuk waarop ook de extremen en het
	' referentiepunt gebaseerd zijn. Een eventuele tweede body (een
	' Split-sliver) hoort niet bij het stuk en mag de classificatie
	' niet vervuilen.
	For Each oFace2 As Face In oBody.Faces

		If oFace2.SurfaceType <> SurfaceTypeEnum.kPlaneSurface Then
			Continue For
		End If

		Dim oPlane2 As Plane = Nothing

		Try
			oPlane2 = CType(oFace2.Geometry, Plane)
		Catch
			oPlane2 = Nothing
		End Try

		If oPlane2 Is Nothing Then
			Continue For
		End If

		Dim oNormal2 As Vector = oPlane2.Normal.AsVector.Copy
		oNormal2.Normalize()

		' Normaal langs de lengte-as?
		Dim dotLen As Double = Math.Abs(DotVector(oNormal2, xUnit.AsVector))
			

		' Echte X-extent uit de FACE-VERTICES (DSTV-frame, cm).
		' NB: Face.Evaluator.RangeBox geeft de box van het onderliggende
		' (ongetrimde) vlak en is onbruikbaar voor face-positie; de
		' vertices geven de werkelijke begrenzing. Zelfde projectie
		' (referentiepunt + xUnit) als bij de extremen hierboven.
		Dim nrm2X As Double = DotVector(oNormal2, xUnit.AsVector)

		If dotLen < endNormalMinCos Then
			Continue For
		End If

		Dim faceMinX As Double = Double.MaxValue
		Dim faceMaxX As Double = Double.MinValue

		For Each oVtx2 As Vertex In oFace2.Vertices

			Dim relV As Vector = oRefPoint.VectorTo(oVtx2.Point)
			Dim vx As Double = DotVector(relV, xUnit.AsVector)

			If vx < faceMinX Then
				faceMinX = vx
			End If

			If vx > faceMaxX Then
				faceMaxX = vx
			End If

		Next

		' Positie bepaalt START vs END (de rauwe vlaknormaal mag naar
		' binnen of naar buiten wijzen): een eindvlak dat de minX-zijde
		' raakt is een START-vlak, een eindvlak dat de maxX-zijde raakt
		' is een END-vlak. De normaal wordt daarna genormaliseerd naar
		' NAAR BUITEN gericht (start: -X-component, end: +X-component),
		' zodat de lean-tekens consequent zijn.
		If faceMinX <= minX + endFaceTolCm Then

			If nrm2X > 0 Then
				oNormal2 = ThisApplication.TransientGeometry.CreateVector( _
					-oNormal2.X, -oNormal2.Y, -oNormal2.Z)
			End If

			startEndFaces.Add(oFace2)
			startFaceNormals.Add(oNormal2)

			If DebugMode Then
				debugSb.AppendLine("    [endcut] START-face: faceMinX=" + Fmt(faceMinX) + " faceMaxX=" + Fmt(faceMaxX) + " outwardN=(" + Fmt(DotVector(oNormal2, xUnit.AsVector)) + "," + Fmt(DotVector(oNormal2, yUnit.AsVector)) + "," + Fmt(DotVector(oNormal2, zUnit.AsVector)) + ")")
			End If

		ElseIf faceMaxX >= maxX - endFaceTolCm Then

			If nrm2X < 0 Then
				oNormal2 = ThisApplication.TransientGeometry.CreateVector( _
					-oNormal2.X, -oNormal2.Y, -oNormal2.Z)
			End If

			endEndFaces.Add(oFace2)
			endFaceNormals.Add(oNormal2)

			If DebugMode Then
				debugSb.AppendLine("    [endcut] END-face: faceMinX=" + Fmt(faceMinX) + " faceMaxX=" + Fmt(faceMaxX) + " outwardN=(" + Fmt(DotVector(oNormal2, xUnit.AsVector)) + "," + Fmt(DotVector(oNormal2, yUnit.AsVector)) + "," + Fmt(DotVector(oNormal2, zUnit.AsVector)) + ")")
			End If

		End If
		Next


	' -------------------------------------------------------------
	' Klassificeer elk eind: enkel vlak (simpele snede) of speciaal
	' -------------------------------------------------------------
Dim startNormal As Vector = Nothing
	Dim endNormal As Vector = Nothing

	Dim startIsSingle As Boolean = False
	Dim endIsSingle As Boolean = False

	' --- START-end ---
	If startEndFaces.Count > 0 Then

		' Genormaliseerde NAAR BUITEN gerichte normaal van het eerste
		' start-vlak; die bepaalt de lean-tekens. De rauwe vlaknormaal
		' kan ook naar binnen wijzen.
		Dim firstNormal As Vector = startFaceNormals(0)

		Dim bSingle As Boolean = True

		For iSn As Integer = 0 To startEndFaces.Count - 1

			Dim pn As Plane = CType(startEndFaces(iSn).Geometry, Plane)
			Dim sn As Vector = startFaceNormals(iSn)

			If Math.Abs(DotVector(sn, firstNormal)) < 0.9995 Then
				' Niet-coplanaire normaal -> meerdere vlakken
				bSingle = False
			Else
				' Ook de vlak-afstand controleren (parallel maar
				' verschoven vlakken = getrapte snede). |distDiff|
				' is teken-onafhankelijk.
				Dim sp As Point = pn.RootPoint
				Dim root0 As Point = CType(startEndFaces(0).Geometry, Plane).RootPoint
				Dim distDiff As Double = _
					(sn.X * sp.X + sn.Y * sp.Y + sn.Z * sp.Z) - _
					(sn.X * root0.X + sn.Y * root0.Y + sn.Z * root0.Z)

				If Math.Abs(distDiff) > 0.01 Then
					bSingle = False
				End If

			End If

		Next

		startIsSingle = bSingle
		startNormal = firstNormal

		If DebugMode Then
			debugSb.AppendLine("  END-CUT START (minX): faces=" + startEndFaces.Count.ToString() + " singlePlane=" + startIsSingle.ToString())
		End If

	End If


	' --- END-end ---
	If endEndFaces.Count > 0 Then

		Dim firstNormal As Vector = endFaceNormals(0)

		Dim bSingle As Boolean = True

		For iEn As Integer = 0 To endEndFaces.Count - 1

			Dim pn As Plane = CType(endEndFaces(iEn).Geometry, Plane)
			Dim sn As Vector = endFaceNormals(iEn)

			If Math.Abs(DotVector(sn, firstNormal)) < 0.9995 Then
				bSingle = False
			Else
				Dim sp As Point = pn.RootPoint
				Dim root0 As Point = CType(endEndFaces(0).Geometry, Plane).RootPoint
				Dim distDiff As Double = _
					(sn.X * sp.X + sn.Y * sp.Y + sn.Z * sp.Z) - _
					(sn.X * root0.X + sn.Y * root0.Y + sn.Z * root0.Z)

				If Math.Abs(distDiff) > 0.01 Then
					bSingle = False
				End If

			End If

		Next

		endIsSingle = bSingle
		endNormal = firstNormal

		If DebugMode Then
			debugSb.AppendLine("  END-CUT END (maxX): faces=" + endEndFaces.Count.ToString() + " singlePlane=" + endIsSingle.ToString())
		End If

	End If

	' -------------------------------------------------------------
	' TRAPGEZUURDE EINDEN (staircase / multi-level) - Test G regel
	' (HEB400 werkvoorbeeld p. 21-22, 2026-09)
	'
	' Een eind waarvan ANDERE sectie-delen op kleinere/grotere X
	' eindigen dan de lengte-tip (getrapte einden: bijv. web tot
	' 1952, bovenflens tot 1750, diagonale flens-tip tot 2000) is
	' GEEN skew cut: de hoek behoort tot de vlak-contour (AK), de
	' ST-hoekvelden blijven 0.00 en er komt geen SC voor (AK heeft
	' prioriteit). Alleen een snede die de HELE sectie in één vlak
	' doorsnijdt is een ST skew cut (viewer-geverifieerd Test B/C).
	'
	' Indicatie: een lengte-gericht planair vlak (|n.x| >=
	' endNormalMinCos) dat de tip NIET raakt en een aanzienlijke
	' Y- of Z-uitbreiding heeft (>= helft van de sectie-breedte
	' respectievelijk -hoogte; onderscheidt een sectie-eindvlak van
	' een kleine zakwand). Toewijzing aan START/END via nabijheid.
	' -------------------------------------------------------------
	Dim startIsStaircase As Boolean = False
	Dim endIsStaircase As Boolean = False

	Dim halfHeightCm As Double = dHeightMm / 20.0
	Dim halfWidthCm As Double = dWidthMm / 20.0

	For Each oFace3 As Face In oBody.Faces

		If oFace3.SurfaceType <> SurfaceTypeEnum.kPlaneSurface Then
			Continue For
		End If

		Dim oPlane3 As Plane = Nothing

		Try
			oPlane3 = CType(oFace3.Geometry, Plane)
		Catch
			oPlane3 = Nothing
		End Try

		If oPlane3 Is Nothing Then
			Continue For
		End If

		Dim oNormal3 As Vector = oPlane3.Normal.AsVector.Copy
		oNormal3.Normalize()

		If Math.Abs(DotVector(oNormal3, xUnit.AsVector)) < endNormalMinCos Then
			Continue For
		End If

		Dim fMinX As Double = Double.MaxValue
		Dim fMaxX As Double = Double.MinValue
		Dim fMinY As Double = Double.MaxValue
		Dim fMaxY As Double = Double.MinValue
		Dim fMinZ As Double = Double.MaxValue
		Dim fMaxZ As Double = Double.MinValue

		For Each oVtx3 As Vertex In oFace3.Vertices

			Dim relV3 As Vector = oRefPoint.VectorTo(oVtx3.Point)

			Dim vx3 As Double = DotVector(relV3, xUnit.AsVector)
			Dim vy3 As Double = DotVector(relV3, yUnit.AsVector)
			Dim vz3 As Double = DotVector(relV3, zUnit.AsVector)

			If vx3 < fMinX Then fMinX = vx3
			If vx3 > fMaxX Then fMaxX = vx3
			If vy3 < fMinY Then fMinY = vy3
			If vy3 > fMaxY Then fMaxY = vy3
			If vz3 < fMinZ Then fMinZ = vz3
			If vz3 > fMaxZ Then fMaxZ = vz3

		Next

		' Vlak raakt de tip niet (ook niet het tegenoverliggende
		' eind) en heeft sectie-aanzienlijke uitbreiding.
		If fMaxX < maxX - endFaceTolCm AndAlso _
			fMinX > minX + endFaceTolCm Then

			If (fMaxY - fMinY) >= halfWidthCm OrElse _
				(fMaxZ - fMinZ) >= halfHeightCm Then

				Dim midX3 As Double = (fMinX + fMaxX) / 2.0

				If (maxX - midX3) <= (midX3 - minX) Then
					endIsStaircase = True
				Else
					startIsStaircase = True
				End If

			End If

		End If

	Next

	If DebugMode Then
		If startIsStaircase Then
			debugSb.AppendLine("  STAIRCASE START: multi-level end detected - ST skew fields stay 0.00 (contour material, AK)")
		End If
		If endIsStaircase Then
			debugSb.AppendLine("  STAIRCASE END: multi-level end detected - ST skew fields stay 0.00 (contour material, AK)")
		End If
	End If
' -------------------------------------------------------------
	' Hoekgrootte en teken (GEVERIFIEERDE conventie 2026-09)
	' -------------------------------------------------------------

	' ST-tekenconventie: EXPORTER/VIEWER VERIFIED CONVENTION
	' (Inventor 2026 + target-viewer, HE 400 B, 2026-09):
	'   - hoekgrootte = hellingshoek van het eindvlak t.o.v. de
	'     loodrende eindplane (0.00 bij een haaks einde), in graden;
	'   - lean = teken van de transversale component van de NAAR
	'     BUITEN gerichte eindvlaknormaal (web: Z-component in het
	'     vooraanzicht; flens: Y-component in het onderaanzicht);
	'   - tekens per veld (flens en web zijn TEGENGESTELD, want het
	'     vooraanzicht en het onderaanzicht hebben een tegengestelde
	'     draairichting in de DSTV-projectie):
	'       veld 17 web-start:    -lean x grootte
	'       veld 18 web-end:      +lean x grootte
	'       veld 19 flens-start:  +lean x grootte
	'       veld 20 flens-end:    -lean x grootte
	'     Identieke (parallelle) schuine sneden krijgen aan beide
	'     einden TEGENGESTELDE tekens - consistent met de +15/-15
	'     labels in de p. 9-10 figuur.
	'   - Viewer-bevestiging: flens start 15 graden (beide
	'     richtingen) + flens end 10 graden correct; een web-snede
	'     met de oude uniforme regel rendert gespiegeld ->
	'     web-correctie doorgevoerd (web = spiegelbeeld van flens).
	'   - Vastgelegd in knowledge/dstv/nc1/7th-edition/blocks/ST.md.

	If startIsSingle AndAlso startNormal IsNot Nothing AndAlso Not startIsStaircase Then

		' Web-Start-Cut: hoek in vooraanzicht (X-Z)
		Dim nxS As Double = DotVector(startNormal, xUnit.AsVector)
		Dim nzS As Double = DotVector(startNormal, zUnit.AsVector)
		Dim nyS As Double = DotVector(startNormal, yUnit.AsVector)

		Dim webStartMag As Double = Math.Atan2(Math.Abs(nzS), Math.Abs(nxS)) * 180.0 / Math.PI
		Dim flangeStartMag As Double = Math.Atan2(Math.Abs(nyS), Math.Abs(nxS)) * 180.0 / Math.PI

		webStartMag = Math.Round(webStartMag, 2)
		flangeStartMag = Math.Round(flangeStartMag, 2)

		' Leunrichting: het teken van de transversale component
		Dim webLeanSign As Integer = 0
		If nzS > 0.0001 Then webLeanSign = 1
		If nzS < -0.0001 Then webLeanSign = -1

		Dim flangeLeanSign As Integer = 0
		If nyS > 0.0001 Then flangeLeanSign = 1
		If nyS < -0.0001 Then flangeLeanSign = -1

		' GEVERIFIEERDE conventie (viewer 2026-09): het START-eind
		' krijgt +lean voor de flens (onderaanzicht) maar -lean voor
		' het web (vooraanzicht): vooraanzicht en onderaanzicht
		' hebben een tegengestelde draairichting in de DSTV-
		' projectie; het web is het spiegelbeeld van de flens.
		webStartCutDeg = -webLeanSign * webStartMag
		flangeStartCutDeg = flangeLeanSign * flangeStartMag

		If DebugMode Then
			debugSb.AppendLine("    START: normal=(" + Fmt(nxS) + "," + Fmt(nyS) + "," + Fmt(nzS) + ")")
			debugSb.AppendLine("      webStart magnitude=" + Fmt(webStartMag) + " lean=(" + webLeanSign.ToString() + ") => field=" + Fmt(webStartCutDeg))
			debugSb.AppendLine("      flangeStart magnitude=" + Fmt(flangeStartMag) + " lean=(" + flangeLeanSign.ToString() + ") => field=" + Fmt(flangeStartCutDeg))
		End If

	ElseIf startIsStaircase Then

		If DebugMode Then
			debugSb.AppendLine("    START: STAIRCASE end (multi-level) - ST skew fields stay 0.00 (contour material, AK)")
		End If

	ElseIf startEndFaces.Count > 0 Then

		If DebugMode Then
			debugSb.AppendLine("    START: UNSUPPORTED (special end cut) - cannot be represented as one planar cut")
		End If

	End If


	If endIsSingle AndAlso endNormal IsNot Nothing AndAlso Not endIsStaircase Then

		Dim nxE As Double = DotVector(endNormal, xUnit.AsVector)
		Dim nzE As Double = DotVector(endNormal, zUnit.AsVector)
		Dim nyE As Double = DotVector(endNormal, yUnit.AsVector)

		Dim webEndMag As Double = Math.Atan2(Math.Abs(nzE), Math.Abs(nxE)) * 180.0 / Math.PI
		Dim flangeEndMag As Double = Math.Atan2(Math.Abs(nyE), Math.Abs(nxE)) * 180.0 / Math.PI

		webEndMag = Math.Round(webEndMag, 2)
		flangeEndMag = Math.Round(flangeEndMag, 2)

		Dim webLeanSign As Integer = 0
		If nzE > 0.0001 Then webLeanSign = 1
		If nzE < -0.0001 Then webLeanSign = -1

		Dim flangeLeanSign As Integer = 0
		If nyE > 0.0001 Then flangeLeanSign = 1
		If nyE < -0.0001 Then flangeLeanSign = -1

		' GEVERIFIEERDE conventie (viewer 2026-09): het END-eind
		' krijgt het TEGENGESTELDE teken van het START-eind:
		' flens -lean (bevestigd, 10 graden end), web +lean
		' (spiegelbeeld van de flens; zonder deze web-correctie
		' rendert een web-snede gespiegeld - gebruikerstest 2026-09).
		webEndCutDeg = webLeanSign * webEndMag
		flangeEndCutDeg = -flangeLeanSign * flangeEndMag

		If DebugMode Then
			debugSb.AppendLine("    END: normal=(" + Fmt(nxE) + "," + Fmt(nyE) + "," + Fmt(nzE) + ")")
			debugSb.AppendLine("      webEnd magnitude=" + Fmt(webEndMag) + " lean=(" + webLeanSign.ToString() + ") => field=" + Fmt(webEndCutDeg))
			debugSb.AppendLine("      flangeEnd magnitude=" + Fmt(flangeEndMag) + " lean=(" + flangeLeanSign.ToString() + ") => field=" + Fmt(flangeEndCutDeg))
		End If

	ElseIf endIsStaircase Then

		If DebugMode Then
			debugSb.AppendLine("    END: STAIRCASE end (multi-level) - ST skew fields stay 0.00 (contour material, AK)")
		End If

	ElseIf endEndFaces.Count > 0 Then

		If DebugMode Then
			debugSb.AppendLine("    END: UNSUPPORTED (special end cut) - cannot be represented as one planar cut")
		End If

	End If

	If DebugMode Then
		debugSb.AppendLine("  SKEW FIELDS (ST 17-20): webStart=" + Fmt(webStartCutDeg) + " webEnd=" + Fmt(webEndCutDeg) + " flangeStart=" + Fmt(flangeStartCutDeg) + " flangeEnd=" + Fmt(flangeEndCutDeg))
		debugSb.AppendLine("")
	End If

	' =============================================================
	' DSTV BESTAND OPBOUWEN
	' =============================================================

	Dim sb As New System.Text.StringBuilder


	' =============================================================
	' ST
	' =============================================================

	sb.AppendLine("ST")

	sb.AppendLine("  " & ORDER_ID)
	sb.AppendLine("  " & DRAWING_ID)
	sb.AppendLine("  " & PHASE_ID)
	sb.AppendLine("  " & sPieceId)
	sb.AppendLine("  " & sSteelGrade)
	sb.AppendLine("  1")
	sb.AppendLine("  " & sProfileName)
	sb.AppendLine("  " & sProfileCode)
	sb.AppendLine("  " & Fmt(dLengthMm))
	sb.AppendLine("  " & Fmt(dHeightMm))
	sb.AppendLine("  " & Fmt(dWidthMm))
	sb.AppendLine("  " & Fmt(dFlangeThickMm))
	sb.AppendLine("  " & Fmt(dWebThickMm))
	sb.AppendLine("  " & Fmt(dRadiusMm))
	sb.AppendLine("  " & Fmt3(dWeightPerMeter))
	sb.AppendLine("  " & Fmt3(dAreaPerMeter))
	sb.AppendLine("  " & Fmt(webStartCutDeg))
	sb.AppendLine("  " & Fmt(webEndCutDeg))
	sb.AppendLine("  " & Fmt(flangeStartCutDeg))
	sb.AppendLine("  " & Fmt(flangeEndCutDeg))


	' =============================================================
	' TEXT INFO ON PIECE
	'
	' DSTV 7e editie:
	' Text info 1
	' Text info 2
	' Text info 3
	' Text info 4
	'
	' Text info left blank per DSTV spec (F4 pending).
	' =============================================================

	sb.AppendLine("  ")
	sb.AppendLine("  ")
	sb.AppendLine("  ")
	sb.AppendLine("  ")


	' =============================================================
	' BO
	' =============================================================

	If holeLines.Count > 0 Then

		sb.AppendLine("BO")

		For Each sLine As String In holeLines

			sb.AppendLine(sLine)

		Next

	End If


	' =============================================================
	' IK - internal contours (scherpe rechthoekige openingen)
	'
	' Elke scherpe rechthoekige opening levert 1 IK-blok: "IK"-kop
	' + puntdatalijnen (2 spaties inspringing). Geplaatst na het
	' BO-blok, voor EN. DSTV staat een willekeurige blokvolgorde
	' toe (p. 9); het HEB400-voorbeeld (p. 22) groepeert de
	' contourblokken per vlak na de BO-blokken.
	' =============================================================

	For Each sIkBlock As String In ikBlocks

		sb.Append(sIkBlock)

	Next


	' =============================================================
	' EN
	' =============================================================

	sb.AppendLine("EN")


	' =============================================================
	' BESTAND OPSLAAN
	' =============================================================

	Dim OUTPUT_FOLDER As String = _
		System.IO.Path.GetDirectoryName( _
			oPartDoc.FullFileName)


	If String.IsNullOrWhiteSpace(OUTPUT_FOLDER) Then

		MessageBox.Show( _
			"Kan de uitvoermap van het onderdeel niet bepalen.", _
			"Opslaan mislukt")

		Return

	End If


	If Not System.IO.Directory.Exists(OUTPUT_FOLDER) Then

		System.IO.Directory.CreateDirectory( _
			OUTPUT_FOLDER)

	End If


	Dim sSafeName As String = sPieceId


	For Each c As Char In _
		System.IO.Path.GetInvalidFileNameChars()

		sSafeName = _
			sSafeName.Replace(c, "_"c)

	Next


	Dim sOutPath As String = _
		System.IO.Path.Combine( _
			OUTPUT_FOLDER, _
			sSafeName & ".nc1")


	System.IO.File.WriteAllText( _
		sOutPath, _
		sb.ToString())

	' -------------------------------------------------------------
	' DEBUG report output (DebugMode only)
	' -------------------------------------------------------------
	If DebugMode Then
		Try
			System.IO.File.WriteAllText(DebugOutputFile, debugSb.ToString())
		Catch
			' Ignore file write failures
		End Try
		MessageBox.Show(debugSb.ToString(), "DSTV Debug")
	End If

	' =============================================================
	' RESULTAAT
	' =============================================================

	MessageBox.Show( _
		"Weggeschreven:" & vbCrLf & _
		sOutPath & vbCrLf & vbCrLf & _
		"Piece ID: " & _
		sPieceId & vbCrLf & _
		"Profiel: " & _
		sProfileName & _
		" (" & sProfileCode & ")" & vbCrLf & _
		"Lengte: " & _
		Fmt(dLengthMm) & " mm" & vbCrLf & _
		"Hoogte: " & _
		Fmt(dHeightMm) & " mm" & vbCrLf & _
		"Breedte: " & _
		Fmt(dWidthMm) & " mm" & vbCrLf & _
		"Openingen: " & _
		holeLines.Count, _
		"DSTV export klaar")

End Sub


' =====================================================================
' DSTV X POSITIE
' =====================================================================

Function GetDstvX( _
	ByVal oPoint As Point, _
	ByVal oRefPoint As Point, _
	ByVal xUnit As UnitVector, _
	ByVal minX As Double) As Double

	Dim rel As Vector = _
		oRefPoint.VectorTo(oPoint)

	Return Math.Round( _
		(DotVector(rel, xUnit.AsVector) - minX) * 10.0, _
		2)

End Function


' =====================================================================
' DSTV Y POSITIE
' =====================================================================

Function GetDstvY( _
	ByVal oPoint As Point, _
	ByVal oRefPoint As Point, _
	ByVal yUnit As UnitVector, _
	ByVal maxY As Double) As Double

	Dim rel As Vector = _
		oRefPoint.VectorTo(oPoint)

	Return Math.Round( _
		(maxY - DotVector(rel, yUnit.AsVector)) * 10.0, _
		2)

End Function


' =====================================================================
' DSTV Z POSITIE
' =====================================================================

Function GetDstvZ( _
	ByVal oPoint As Point, _
	ByVal oRefPoint As Point, _
	ByVal zUnit As UnitVector, _
	ByVal minZ As Double) As Double

	Dim rel As Vector = _
		oRefPoint.VectorTo(oPoint)

	Return Math.Round( _
		(DotVector(rel, zUnit.AsVector) - minZ) * 10.0, _
		2)

End Function


' =====================================================================
' OPENING FACE BEPALEN
'
' o/u = flens
' v/h = lijf
'
' Let op:
' De precieze lokale vlak-/referentiebepaling wordt in een volgende
' fase verder verbeterd.
' =====================================================================

Function GetOpeningFace( _
	ByVal oSketch As PlanarSketch, _
	ByVal oModelPoint As Point, _
	ByVal oBody As SurfaceBody, _
	ByVal xUnit As UnitVector, _
	ByVal yUnit As UnitVector, _
	ByVal zUnit As UnitVector, _
	ByVal dHeightMm As Double, _
	ByVal holeY As Double, _
	ByVal holeZ As Double) As String

	Try

		Dim planarObject As Object = _
			oSketch.PlanarEntity


		If TypeOf planarObject Is Face Then

			Dim oFace As Face = _
				CType(planarObject, Face)


			If oFace.SurfaceType = _
				SurfaceTypeEnum.kPlaneSurface Then

				Dim oPlane As Plane = _
					CType(oFace.Geometry, Plane)


				Dim normal As Vector = _
					oPlane.Normal.AsVector.Copy


				normal.Normalize()


				Dim dotX As Double = _
					Math.Abs( _
						DotVector( _
							normal, _
							xUnit.AsVector))


				Dim dotY As Double = _
					Math.Abs( _
						DotVector( _
							normal, _
							yUnit.AsVector))


				Dim dotZ As Double = _
					Math.Abs( _
						DotVector( _
							normal, _
							zUnit.AsVector))


				' -------------------------------------------------
				' WEB
				' -------------------------------------------------

				If dotY >= dotZ AndAlso _
					dotY >= dotX Then

					If DotVector( _
						normal, _
						yUnit.AsVector) >= 0.0 Then

						Return "v"

					Else

						Return "h"

					End If

				End If


				' -------------------------------------------------
				' FLENS
				' -------------------------------------------------

				If dotZ >= dotY AndAlso _
					dotZ >= dotX Then

					If DotVector( _
						normal, _
						zUnit.AsVector) >= 0.0 Then

						Return "o"

					Else

						Return "u"

					End If

				End If

			End If

		End If

	Catch

	End Try


	' -------------------------------------------------------------
	' FALLBACK
	' -------------------------------------------------------------

	If dHeightMm > 0.0 Then

		If holeZ >= dHeightMm / 2.0 Then

			Return "o"

		Else

			Return "u"

		End If

	End If


	Return "v"

End Function


' =====================================================================
' DSTV X-REFERENTIELETTER (Fase 2)
'
' De referentieletter na X in een BO-regel is een DIMENSIE-referentie
' (o = bovenrand, leeg = vorige, s = as, u = onderrand), NIET de
' vlakletter (v/h).
'
' Fase 2: default 'u' (onderrand) op ALLE vlakken - PENDING-item F1,
' p. 12 voorbeelden. Differentiatie per vlak/profieltype volgt uit
' figuur p. 7-8 (afbeelding; PENDING in de digest).
' =====================================================================

Function GetDstvXref(ByVal sFace As String) As String

	' F1-default: onderrand-referentie op elk vlak.
	Return "u"

End Function


' =====================================================================
' X-REF-LETTER STRIPPEN (numerieke duplicaatdetectie)
'
' Een BO-X-waarde kan een trailende referentieletter bevatten
' ("888.78u"). Double.Parse faalt daarop; deze helper haalt een
' trailende letter eraf voordat geparseerd wordt.
' =====================================================================

Function StripRefLetter(ByVal s As String) As String

	If s.Length > 0 AndAlso Char.IsLetter(s(s.Length - 1)) Then
		Return s.Substring(0, s.Length - 1)
	End If

	Return s

End Function


' =====================================================================
' POSITIE OP DSTV VLAK
' =====================================================================

Function GetFacePosition( _
	ByVal sFace As String, _
	ByVal holeY As Double, _
	ByVal holeZ As Double) As Double

	If sFace = "v" OrElse _
		sFace = "h" Then

		Return holeZ

	End If


	Return holeY

End Function


' =====================================================================
' VLAKLETTER UIT NORMAAL
'
' Bepaalt de DSTV-vlakletter (o/u/v/h) uit de vlaknormaal t.o.v. het
' stuk-coordinatensysteem (zelfde logica als GetOpeningFace, maar
' herbruikbaar voor vlakken die niet de schets-vlak zijn).
' Lege string als de normaal geen standaardvlak bepaalt.
' =====================================================================

Function GetFaceLetterFromNormal( _
	ByVal n As Vector, _
	ByVal xUnit As UnitVector, _
	ByVal yUnit As UnitVector, _
	ByVal zUnit As UnitVector) As String

	Dim dotX As Double = Math.Abs(DotVector(n, xUnit.AsVector))
	Dim dotY As Double = Math.Abs(DotVector(n, yUnit.AsVector))
	Dim dotZ As Double = Math.Abs(DotVector(n, zUnit.AsVector))

	' WEB
	If dotY >= dotZ AndAlso dotY >= dotX Then

		If DotVector(n, yUnit.AsVector) >= 0.0 Then
			Return "v"
		Else
			Return "h"
		End If

	End If

	' FLENS
	If dotZ >= dotY AndAlso dotZ >= dotX Then

		If DotVector(n, zUnit.AsVector) >= 0.0 Then
			Return "o"
		Else
			Return "u"
		End If

	End If

	Return ""

End Function


' =====================================================================
' DOORGESTOKEN OPENINGEN - OVERIGE VLAKKEN
'
' Een cut-extrude steekt naast de schets-vlak ook parallelle vlakken
' door (bijv. een slot door BEIDE flenzen). De profile-path detectie
' levert per feature slechts EEN record (de schets-vlak); deze helper
' vindt de overige doorstoken vlakken:
'
'   - planair vlak parallel aan de schets-vlak (|dot(n, nSketch)| ~ 1)
'     en niet coplanair met de schets-vlak;
'   - met een binnenloop (>= 2 entiteiten; ronde loops = 1 entiteit
'     worden genegeerd) waarvan het hoekpunt-middelpunt, geprojecteerd
'     langs de schetsnormaal op de schets-vlak, op het opening-centrum
'     valt.
'
' Toleranties in model-eenheden (cm): projectie-match 1.0 cm = 10 mm
' (gaten liggen honderden mm verder); coplanariteit 0.01 cm = 0.1 mm.
' =====================================================================

Function GetOtherPiercedFaces( _
	ByVal oBody As SurfaceBody, _
	ByVal oSketch As PlanarSketch, _
	ByVal modelCenter As Point, _
	ByVal xUnit As UnitVector, _
	ByVal yUnit As UnitVector, _
	ByVal zUnit As UnitVector, _
	ByVal dbg As System.Text.StringBuilder) As List(Of String)

	Dim result As New List(Of String)

	Try

		Dim planarObject As Object = oSketch.PlanarEntity

		' Het planaire entiteit van de schets kan een Face zijn MAAR
		' ook een WorkPlane (bijv. offset-werkvlak). In beide gevallen
		' is een Plane afleidbaar; zonder Face is er alleen geen
		' sketchFace om over te slaan (coplanariteitscheck vangt dat af
		' via de vlakafstand).

		Dim sketchPlane As Plane = Nothing
		Dim sketchFace As Face = Nothing

		If TypeOf planarObject Is Face Then

			sketchFace = CType(planarObject, Face)
			sketchPlane = CType(sketchFace.Geometry, Plane)

			If dbg IsNot Nothing Then
				dbg.AppendLine("    [pierce] plane source=Face")
			End If

		ElseIf TypeOf planarObject Is WorkPlane Then

			Dim wp As WorkPlane = CType(planarObject, WorkPlane)
			sketchPlane = wp.Plane

			If dbg IsNot Nothing Then
				dbg.AppendLine("    [pierce] plane source=WorkPlane")
			End If

		Else

			If dbg IsNot Nothing Then
				dbg.AppendLine("    [pierce] plane source=OTHER (" + planarObject.GetType().FullName + ")")
			End If

		End If

		If sketchPlane Is Nothing Then
			Return result
		End If

		Dim sketchN As Vector = sketchPlane.Normal.AsVector.Copy
		sketchN.Normalize()

		Dim pierceToleranceCm As Double = 1.0
		Dim parallelMinDot As Double = 0.999

		For Each oFace As Face In oBody.Faces

			If oFace Is sketchFace Then
				Continue For
			End If

			If oFace.SurfaceType <> SurfaceTypeEnum.kPlaneSurface Then
				Continue For
			End If

			Dim oPlane As Plane = Nothing

			Try
				oPlane = CType(oFace.Geometry, Plane)
			Catch
				oPlane = Nothing
			End Try

			If oPlane Is Nothing Then
				Continue For
			End If

			Dim nF As Vector = oPlane.Normal.AsVector.Copy
			nF.Normalize()

			Dim dotPar As Double = Math.Abs(DotVector(nF, sketchN))

			' Alleen bijna-parallelle vlakken loggen (anders vloedt de
			' debug met alle web/flens-vlakken).
			If dotPar < 0.9 Then
				Continue For
			End If

			Dim sCandLetter As String = _
				GetFaceLetterFromNormal( _
					nF, xUnit, yUnit, zUnit)

			' Coplanair met de schets-vlak? Dan geen doorgestoken vlak.
			Dim rel As Vector = sketchPlane.RootPoint.VectorTo(oPlane.RootPoint)
			Dim coplanarDist As Double = Math.Abs(DotVector(rel, sketchN))

			If dbg IsNot Nothing Then
				dbg.AppendLine("    [pierce] candidate face=" + sCandLetter + " dot=" + Fmt(dotPar) + " planeDistCm=" + Fmt(coplanarDist))
			End If

			If dotPar < parallelMinDot Then
				Continue For
			End If

			If coplanarDist < 0.01 Then
				Continue For
			End If

			' Inventor 2026 API (interop verified): Face.EdgeLoops
			' (NOT Face.Loops) en EdgeLoop.IsOuterEdgeLoop (NOT
			' IsOuter). Zie Autodesk SDK BRepTraversal-sample.
			For Each oLoop As EdgeLoop In oFace.EdgeLoops

				If oLoop.IsOuterEdgeLoop Then
					Continue For
				End If

				If oLoop.Edges.Count < 2 Then
					Continue For
				End If

				' Middelpunt van de loop-vertexpunten; elk hoekpunt
				' wordt door 2 randen gedeeld -> uniforme weegfactor.
				Dim sumX As Double = 0.0
				Dim sumY As Double = 0.0
				Dim sumZ As Double = 0.0
				Dim vtxCount As Double = 0.0

				For Each oEdge As Edge In oLoop.Edges

					Try
						Dim p1 As Point = oEdge.StartVertex.Point
						sumX += p1.X
						sumY += p1.Y
						sumZ += p1.Z
						vtxCount += 1.0

						Dim p2 As Point = oEdge.StopVertex.Point
						sumX += p2.X
						sumY += p2.Y
						sumZ += p2.Z
						vtxCount += 1.0
					Catch
					End Try

				Next

				If vtxCount < 1.0 Then
					Continue For
				End If

				Dim loopCenter As Point = _
					ThisApplication.TransientGeometry.CreatePoint( _
						sumX / vtxCount, _
						sumY / vtxCount, _
						sumZ / vtxCount)

				' Projecteer langs de schetsnormaal op de schets-vlak
				Dim relC As Vector = _
					sketchPlane.RootPoint.VectorTo(loopCenter)
				Dim dist As Double = DotVector(relC, sketchN)

				Dim projected As Point = _
					ThisApplication.TransientGeometry.CreatePoint( _
						loopCenter.X - sketchN.X * dist, _
						loopCenter.Y - sketchN.Y * dist, _
						loopCenter.Z - sketchN.Z * dist)

				Dim matchDist As Double = projected.DistanceTo(modelCenter)

				If dbg IsNot Nothing Then
					dbg.AppendLine("    [pierce] candidate=" + sCandLetter + " innerLoop edges=" + oLoop.Edges.Count.ToString() + " projDistCm=" + Fmt(matchDist))
				End If

				If matchDist <= pierceToleranceCm Then

					If dbg IsNot Nothing Then
						dbg.AppendLine("    [pierce] MATCH face=" + sCandLetter)
					End If

					If sLetter_Check(sCandLetter) AndAlso _
						Not result.Contains(sCandLetter) Then

						result.Add(sCandLetter)

					End If

					Exit For

				End If

			Next

		Next

	Catch ex As Exception

		If dbg IsNot Nothing Then
			dbg.AppendLine("    [pierce] EXCEPTION: " + ex.Message)
		End If

	End Try

	Return result

End Function

' Lege-letters are already filtered by GetFaceLetterFromNormal; kept as
' a tiny guard so result never receives "".
Private Function sLetter_Check(ByVal s As String) As Boolean
	Return s <> ""
End Function


' =====================================================================
' ORDERED CORNER CHAIN FROM PROFILE SEGMENTS
'
' Loopt de lijnsegmenten van een gesloten profile-path af en geeft
' de unieke hoekpunten in traversatievolgorde terug. Geeft False als
' de segmenten geen gesloten keten vormen (gat of vertakking).
'
' Tolerantie in sketch-eenheden (cm): 1e-5 cm = 1e-4 mm.
' =====================================================================

Function BuildOrderedCornerChain( _
	ByVal oSegments As List(Of LineSegment2d), _
	ByRef oCorners As List(Of Point2d)) As Boolean

	oCorners = New List(Of Point2d)

	If oSegments.Count < 3 Then
		Return False
	End If

	Dim chainTol As Double = 0.00001

	Dim segUsed(oSegments.Count - 1) As Boolean

	Dim walkPt As Point2d = oSegments(0).EndPoint

	segUsed(0) = True
	oCorners.Add(oSegments(0).StartPoint)

	For stepIndex As Integer = 1 To oSegments.Count - 1

		Dim nextIndex As Integer = -1
		Dim nextIsStart As Boolean = False

		For si As Integer = 0 To oSegments.Count - 1

			If segUsed(si) Then
				Continue For
			End If

			If walkPt.DistanceTo(oSegments(si).StartPoint) <= chainTol Then
				nextIndex = si
				nextIsStart = False
				Exit For
			End If

			If walkPt.DistanceTo(oSegments(si).EndPoint) <= chainTol Then
				nextIndex = si
				nextIsStart = True
				Exit For
			End If

		Next

		If nextIndex < 0 Then
			oCorners = New List(Of Point2d)
			Return False
		End If

		segUsed(nextIndex) = True
		oCorners.Add(walkPt)

		If nextIsStart Then
			walkPt = oSegments(nextIndex).StartPoint
		Else
			walkPt = oSegments(nextIndex).EndPoint
		End If

	Next

	If walkPt.DistanceTo(oCorners(0)) > chainTol Then
		oCorners = New List(Of Point2d)
		Return False
	End If

	Return True

End Function


' =====================================================================
' RECTANGLE CHECK FROM CORNER CHAIN
'
' True als de vier hoekpunten een rechthoek vormen: alle vier de
' binnenhoeken zijn rechte hoeken (een gesloten vierhoek met vier
' rechte hoeken is een rechthoek). dCosTol = maximaal toegestane
' |cos(hoek)| (0 = perfect haaks). Nul-lengte randen worden
' geweigerd (degenereerde keten).
' =====================================================================

Function IsRectangleFromCorners( _
	ByVal oCorners As List(Of Point2d), _
	ByVal dCosTol As Double) As Boolean

	If oCorners.Count <> 4 Then
		Return False
	End If

	For i As Integer = 0 To 3

		Dim prevIdx As Integer = (i + 3) Mod 4
		Dim nextIdx As Integer = (i + 1) Mod 4

		Dim vx As Double = oCorners(prevIdx).X - oCorners(i).X
		Dim vy As Double = oCorners(prevIdx).Y - oCorners(i).Y
		Dim wx As Double = oCorners(nextIdx).X - oCorners(i).X
		Dim wy As Double = oCorners(nextIdx).Y - oCorners(i).Y

		Dim lenV As Double = Math.Sqrt(vx * vx + vy * vy)
		Dim lenW As Double = Math.Sqrt(wx * wx + wy * wy)

		If lenV <= 0.00001 OrElse lenW <= 0.00001 Then
			Return False
		End If

		Dim dCos As Double = Math.Abs((vx * wx + vy * wy) / (lenV * lenW))

		If dCos > dCosTol Then
			Return False
		End If

	Next

	Return True

End Function


' =====================================================================
' DSTV FACE-FRAME ANGLE OF A SKETCH DIRECTION
'
' Transformeert het middelpunt en een punt verschoven in de
' randrichting naar het DSTV-vlakframe (zelfde mapping als de
' IK-hoekpunten: GetDstvY voor o/u-vlakken, GetDstvZ voor v/h)
' en geeft de richtingshoek in dat frame terug, genormaliseerd
' naar [0, 180). De rechthoek is symmetrisch onder 180 graden.
' NB: de hoekteken-conventie in het DSTV-vlakframe is voor
' werkelijk gedraaide rechthoeken nog niet viewer-geverifieerd
' (PENDING-item F3); voor vlakke-uitgelijnde gevallen is de
' hoek 0.00.
' =====================================================================

Function GetDstvFaceFrameAngle( _
	ByVal oSketch As PlanarSketch, _
	ByVal oCenterSketch As Point2d, _
	ByVal dDirX As Double, _
	ByVal dDirY As Double, _
	ByVal sFace As String, _
	ByVal oRefPoint As Point, _
	ByVal xUnit As UnitVector, _
	ByVal yUnit As UnitVector, _
	ByVal zUnit As UnitVector, _
	ByVal dMinX As Double, _
	ByVal dMaxY As Double, _
	ByVal dMinZ As Double) As Double

	Dim ptA As Point = oSketch.SketchToModelSpace(oCenterSketch)

	Dim ptB As Point = oSketch.SketchToModelSpace( _
		ThisApplication.TransientGeometry.CreatePoint2d( _
			oCenterSketch.X + dDirX, _
			oCenterSketch.Y + dDirY))

	Dim axDstv As Double = GetDstvX(ptA, oRefPoint, xUnit, dMinX)
	Dim ayDstv As Double

	If sFace = "v" OrElse sFace = "h" Then
		ayDstv = GetDstvZ(ptA, oRefPoint, zUnit, dMinZ)
	Else
		ayDstv = GetDstvY(ptA, oRefPoint, yUnit, dMaxY)
	End If

	Dim bxDstv As Double = GetDstvX(ptB, oRefPoint, xUnit, dMinX)
	Dim byDstv As Double

	If sFace = "v" OrElse sFace = "h" Then
		byDstv = GetDstvZ(ptB, oRefPoint, zUnit, dMinZ)
	Else
		byDstv = GetDstvY(ptB, oRefPoint, yUnit, dMaxY)
	End If

	Dim dAng As Double = Math.Atan2(byDstv - ayDstv, bxDstv - axDstv) * 180.0 / Math.PI

	If dAng < 0 Then
		dAng = dAng + 180.0
	End If

	If dAng >= 180.0 Then
		dAng = dAng - 180.0
	End If

	Return dAng

End Function



' =====================================================================
' HOLE BOUNDARY LOOP PROBE (3D-fillet detectie)
'
' Zoekt op het vlak waarin de opening is gesneden de binnenrandloop
' (EdgeLoop, IsOuterEdgeLoop = False) die het dichtst bij het
' gatmiddelpunt ligt en classificeert de randen daarvan. De loop is
' de WERKELIJKE gatcontour na alle features: een 3D-fillet (Fillet-
' tool) op de gatranden geeft hier 4 lijnen + 4 bogen, terwijl de
' cut-sketch nog een scherpe rechthoek beschrijft.
'
' Statuswaarden:
'   "FACE"              - planaire face gevonden; de dichtstbijzijnde
'                         binnenloop staat in oBoundaryLines /
'                         oBoundaryArcs
'   "NO-FACE"           - sketch staat niet op een body-face
'                         (bijv. werkvlak) -> geen probe mogelijk
'   "NO-LOOP"           - geen binnenloop binnen de afstandstolerantie
'   "UNRECOGNIZED-EDGE" - loop bevat een ander randtype dan lijn/boog
'
' Toleranties: loop-matching 0.05 cm (0.5 mm) op het RangeBox-
' middelpunt; boogstraal-uniformiteit 0.0001 cm.
' =====================================================================

Function ProbeHoleBoundaryLoop( _
	ByVal oSketch As PlanarSketch, _
	ByVal oModelCenter As Point, _
	ByRef oBoundaryLines As List(Of LineSegment), _
	ByRef oBoundaryArcs As List(Of Arc3d)) As String

	oBoundaryLines = New List(Of LineSegment)
	oBoundaryArcs = New List(Of Arc3d)

	Dim planarObject As Object = Nothing

	Try
		planarObject = oSketch.PlanarEntity
	Catch
		planarObject = Nothing
	End Try

	If Not (TypeOf planarObject Is Face) Then
		Return "NO-FACE"
	End If

	Dim oFace As Face = CType(planarObject, Face)

	Dim matchTolCm As Double = 0.05

	Dim bestLoop As EdgeLoop = Nothing
	Dim bestDist As Double = 0.0

	For Each oEdgeLoop As EdgeLoop In oFace.EdgeLoops

		If oEdgeLoop.IsOuterEdgeLoop Then
			Continue For
		End If

		Dim rb As Box = oEdgeLoop.RangeBox

		Dim cx As Double = (rb.MinPoint.X + rb.MaxPoint.X) / 2.0
		Dim cy As Double = (rb.MinPoint.Y + rb.MaxPoint.Y) / 2.0
		Dim cz As Double = (rb.MinPoint.Z + rb.MaxPoint.Z) / 2.0

		Dim dx As Double = cx - oModelCenter.X
		Dim dy As Double = cy - oModelCenter.Y
		Dim dz As Double = cz - oModelCenter.Z

		Dim dist As Double = Math.Sqrt(dx * dx + dy * dy + dz * dz)

		If bestLoop Is Nothing OrElse dist < bestDist Then
			bestDist = dist
			bestLoop = oEdgeLoop
		End If

	Next

	If bestLoop Is Nothing OrElse bestDist > matchTolCm Then
		Return "NO-LOOP"
	End If

	For Each oEdge As Edge In bestLoop.Edges

		Dim oGeom As Object = Nothing

		Try
			oGeom = oEdge.Geometry
		Catch
			oGeom = Nothing
		End Try

		If TypeOf oGeom Is LineSegment Then

			oBoundaryLines.Add(CType(oGeom, LineSegment))

		ElseIf TypeOf oGeom Is Arc3d Then

			oBoundaryArcs.Add(CType(oGeom, Arc3d))

		Else
			Return "UNRECOGNIZED-EDGE"
		End If

	Next

	Return "FACE"

End Function



' =====================================================================
' DUBBELE OPENING VOORKOMEN (numeriek)
'
' Een BO-regel is 'dezelfde opening' als face, X, Y en eerste maat
' binnen de tolerantie overeenkomen. Dit verenigt:
' - B-Rep cilinder-detectie en de profile-path fallback;
' - meervoudige coaxiale cilindervlakken (bijv. verzinkte gaten);
' - regels die vanuit verschillende paden geregistreerd worden.
'
' NB: voor slots/rechthoeken wordt dit in fase 2-afhankelijk verfijnd.
' =====================================================================

Sub AddHoleLineUnique( _
	ByVal holeLines As List(Of String), _
	ByVal newLine As String, _
	ByVal tolerance As Double)

	Dim parts() As String = _
		newLine.Trim().Split( _
			New Char() {" "c}, _
			StringSplitOptions.RemoveEmptyEntries)

	If parts.Length < 4 Then

		holeLines.Add(newLine)
		Return

	End If

	Dim sFace As String = parts(0)
	Dim xPos As Double = 0.0
	Dim yPos As Double = 0.0
	Dim size As Double = 0.0

	Try

		xPos = _
			Double.Parse( _
				StripRefLetter(parts(1)), _
				System.Globalization.CultureInfo.InvariantCulture)

		yPos = _
			Double.Parse( _
				parts(2), _
				System.Globalization.CultureInfo.InvariantCulture)

		size = _
			Double.Parse( _
				parts(3), _
				System.Globalization.CultureInfo.InvariantCulture)

	Catch

		holeLines.Add(newLine)
		Return

	End Try

	For Each existingLine As String In holeLines

		If HoleLinesEquivalent( _
			existingLine, _
			sFace, _
			xPos, _
			yPos, _
			size, _
			tolerance) Then

			Return

		End If

	Next


	holeLines.Add(newLine)

End Sub


' =====================================================================
' BO-REGELS VERGELIJKEN (numeriek)
' =====================================================================

Function HoleLinesEquivalent( _
	ByVal existingLine As String, _
	ByVal sFace As String, _
	ByVal vPos As Double, _
	ByVal yPos As Double, _
	ByVal diameter As Double, _
	ByVal tolerance As Double) As Boolean

	Try

		Dim parts() As String = _
			existingLine.Trim().Split( _
				New Char() {" "c}, _
				StringSplitOptions.RemoveEmptyEntries)

		If parts.Length < 4 Then
			Return False
		End If

		Dim existingFace As String = _
			parts(0)

		Dim existingX As Double = _
			Double.Parse( _
				StripRefLetter(parts(1)), _
				System.Globalization.CultureInfo.InvariantCulture)

		Dim existingY As Double = _
			Double.Parse( _
				parts(2), _
				System.Globalization.CultureInfo.InvariantCulture)

		Dim existingD As Double = _
			Double.Parse( _
				parts(3), _
				System.Globalization.CultureInfo.InvariantCulture)

		If existingFace <> sFace Then
			Return False
		End If

		If Math.Abs(existingX - vPos) > tolerance Then
			Return False
		End If

		If Math.Abs(existingY - yPos) > tolerance Then
			Return False
		End If

		If Math.Abs(existingD - diameter) > tolerance Then
			Return False
		End If

		Return True

	Catch

		Return False

	End Try

End Function


' =====================================================================
' KIES RICHTING MET TEKEN
' =====================================================================

Function GetOrientedAxis( _
	ByVal source As Vector, _
	ByVal ref1 As UnitVector, _
	ByVal ref2 As UnitVector, _
	ByVal ref3 As UnitVector) As UnitVector

	Dim a1 As Double = _
		Math.Abs( _
			DotVector( _
				source, _
				ref1.AsVector))


	Dim a2 As Double = _
		Math.Abs( _
			DotVector( _
				source, _
				ref2.AsVector))


	Dim a3 As Double = _
		Math.Abs( _
			DotVector( _
				source, _
				ref3.AsVector))


	Dim result As Vector = _
		source.Copy


	If a1 >= a2 AndAlso _
		a1 >= a3 Then

		If DotVector( _
			source, _
			ref1.AsVector) < 0.0 Then

			result.ScaleBy(-1.0)

		End If


	ElseIf a2 >= a1 AndAlso _
		a2 >= a3 Then

		If DotVector( _
			source, _
			ref2.AsVector) < 0.0 Then

			result.ScaleBy(-1.0)

		End If


	Else

		If DotVector( _
			source, _
			ref3.AsVector) < 0.0 Then

			result.ScaleBy(-1.0)

		End If

	End If


	Return result.AsUnitVector

End Function


' =====================================================================
' DOT PRODUCT
' =====================================================================

Function DotVector( _
	ByVal a As Vector, _
	ByVal vecB As Vector) As Double

	Return _
		a.X * vecB.X + _
		a.Y * vecB.Y + _
		a.Z * vecB.Z

End Function


' =====================================================================
' FACE NORMAL (outward)
' =====================================================================
' Returns the outward-pointing normal for a given DSTV face letter.
' o = top flange (+Z), u = bottom flange (-Z),
' v = front web (+Y), h = back web (-Y).
' =====================================================================

Function GetFaceNormal( _
	ByVal sFace As String, _
	ByVal xUnit As UnitVector, _
	ByVal yUnit As UnitVector, _
	ByVal zUnit As UnitVector) As Vector

	Select Case sFace
		Case "o"
			Return zUnit.AsVector.Copy
		Case "u"
			Dim v As Vector = zUnit.AsVector.Copy
			v.ScaleBy(-1.0)
			Return v
		Case "v"
			Return yUnit.AsVector.Copy
		Case "h"
			Dim v2 As Vector = yUnit.AsVector.Copy
			v2.ScaleBy(-1.0)
			Return v2
		Case Else
			Return zUnit.AsVector.Copy
	End Select

End Function


' =====================================================================
' FACE-FRAME ANGLE
' =====================================================================
' Computes the angle of a feature direction in the DSTV face frame.
'
' The direction is given in sketch coordinates (dirSketch). This
' function:
'   1. Transforms the direction from sketch to model coordinates
'   2. Projects onto the face plane (removes normal component)
'   3. Computes the angle relative to the piece X axis (xUnit)
'
' The angle is in degrees, range (-180, 180]:
'   0   = aligned with piece X (longitudinal)
'   90  = perpendicular to piece X in face plane
' =====================================================================

Function ComputeFaceFrameAngle( _
	ByVal oSketch As PlanarSketch, _
	ByVal dirSketch As Point2d, _
	ByVal sFace As String, _
	ByVal xUnit As UnitVector, _
	ByVal yUnit As UnitVector, _
	ByVal zUnit As UnitVector) As Double

	' Transform direction from sketch to model coordinates
	Dim originSketch As Point2d = _
		ThisApplication.TransientGeometry.CreatePoint2d(0.0, 0.0)
	Dim dirPointSketch As Point2d = _
		ThisApplication.TransientGeometry.CreatePoint2d( _
			dirSketch.X, dirSketch.Y)

	Dim originModel As Point = _
		oSketch.SketchToModelSpace(originSketch)
	Dim dirPointModel As Point = _
		oSketch.SketchToModelSpace(dirPointSketch)

	Dim dirModel As Vector = originModel.VectorTo(dirPointModel)

	' Get the face normal
	Dim faceNormal As Vector = GetFaceNormal(sFace, xUnit, yUnit, zUnit)

	' Project direction onto face plane (remove normal component)
	Dim dot As Double = DotVector(dirModel, faceNormal)
	Dim projected As Vector = dirModel.Copy
	Dim normalComponent As Vector = faceNormal.Copy
	normalComponent.ScaleBy(dot)
	projected = ThisApplication.TransientGeometry.CreateVector(projected.X - normalComponent.X, projected.Y - normalComponent.Y, projected.Z - normalComponent.Z)

	' If projected direction is degenerate, return 0
	If projected.Length < 0.0001 Then
		Return 0.0
	End If

	projected.Normalize()

	' Project piece X axis onto face plane
	Dim xDot As Double = DotVector(xUnit.AsVector, faceNormal)
	Dim xProjected As Vector = xUnit.AsVector.Copy
	Dim xNormalComponent As Vector = faceNormal.Copy
	xNormalComponent.ScaleBy(xDot)
	xProjected = ThisApplication.TransientGeometry.CreateVector(xProjected.X - xNormalComponent.X, xProjected.Y - xNormalComponent.Y, xProjected.Z - xNormalComponent.Z)

	If xProjected.Length < 0.0001 Then
		Return 0.0
	End If

	xProjected.Normalize()

	' Compute face Y axis (perpendicular to xProjected in face plane)
	Dim yProjected As Vector = _
		CrossVector(faceNormal, xProjected)
	yProjected.Normalize()

	' Compute angle relative to xProjected
	Dim angleDeg As Double = _
		Math.Atan2( _
			DotVector(projected, yProjected), _
			DotVector(projected, xProjected)) * _
		180.0 / Math.PI

	Return angleDeg

End Function


' =====================================================================
' CROSS PRODUCT
' =====================================================================

Function CrossVector( _
	ByVal a As Vector, _
	ByVal vecB As Vector) As Vector

	Dim result As Vector = _
		ThisApplication.TransientGeometry.CreateVector( _
			a.Y * vecB.Z - a.Z * vecB.Y, _
			a.Z * vecB.X - a.X * vecB.Z, _
			a.X * vecB.Y - a.Y * vecB.X)

	Return result

End Function


' =====================================================================
' GROOTSTE RICHTING
' =====================================================================

Function GetLargestIndex( _
	ByVal a As Double, _
	ByVal bVal As Double, _
	ByVal c As Double) As Integer

	If a >= bVal AndAlso _
		a >= c Then

		Return 1

	ElseIf bVal >= a AndAlso _
		bVal >= c Then

		Return 2

	Else

		Return 3

	End If

End Function


' =====================================================================
' CM -> MM
' =====================================================================

Function CmToMm( _
	ByVal v As Double) As Double

	Return Math.Round( _
		v * 10.0, _
		2)

End Function


' =====================================================================
' GETAL FORMATTEREN - 2 DECIMALEN
' =====================================================================

Function Fmt( _
	ByVal v As Double) As String

	Return _
		v.ToString( _
			"0.00", _
			System.Globalization.CultureInfo.InvariantCulture)

End Function


' =====================================================================
' GETAL FORMATTEREN - 3 DECIMALEN
' =====================================================================

Function Fmt3( _
	ByVal v As Double) As String

	Return _
		v.ToString( _
			"0.000", _
			System.Globalization.CultureInfo.InvariantCulture)

End Function


' =====================================================================
' PROFIELPARAMETER ZOEKEN
' =====================================================================

Function GetProfileParam( _
	ByVal oPartDoc As PartDocument, _
	ByVal paramNames() As String, _
	ByVal defaultValue As Double) As Double

	Dim oParams As Parameters = _
		oPartDoc.ComponentDefinition.Parameters


	' -------------------------------------------------------------
	' USER PARAMETERS
	' -------------------------------------------------------------

	For Each pName As String In paramNames

		For Each p As UserParameter In _
			oParams.UserParameters

			If String.Equals( _
				p.Name, _
				pName, _
				StringComparison.OrdinalIgnoreCase) Then

				Return Math.Round( _
					p.Value * 10.0, _
					2)

			End If

		Next

	Next


	' -------------------------------------------------------------
	' ALLE PARAMETERS
	' -------------------------------------------------------------

	For Each pName As String In paramNames

		For Each p As Parameter In oParams

			If String.Equals( _
				p.Name, _
				pName, _
				StringComparison.OrdinalIgnoreCase) Then

				Return Math.Round( _
					p.Value * 10.0, _
					2)

			End If

		Next

	Next


	Return defaultValue

End Function


' =====================================================================
' PROFIELNAAM OPSCHONEN
' =====================================================================

Function CleanProfileDesignation( _
	ByVal sRaw As String) As String

	Dim s As String = _
		sRaw.Trim()


	Dim idx As Integer = _
		s.LastIndexOf(" - ")


	If idx >= 0 Then

		s = _
			s.Substring( _
				idx + 3).Trim()

	End If


	s = _
		System.Text.RegularExpressions.Regex.Replace( _
			s, _
			"-\d+(\.\d+)?$", _
			"").Trim()


	Return s

End Function


' =====================================================================
' DSTV PROFIELCODE
' =====================================================================

Function GetDstvProfileCode( _
	ByVal sFamilyOrDesc As String) As String

	Dim s As String = _
		sFamilyOrDesc.ToUpper()


	Dim reHE As New System.Text.RegularExpressions.Regex( _
		"^HE\s*\d+\s*[ABM]\b")


	Dim reL As New System.Text.RegularExpressions.Regex( _
				"^L\s*\d")

	Dim rePL As New System.Text.RegularExpressions.Regex( _
		"^PL\b")

	Dim reC As New System.Text.RegularExpressions.Regex( _
		"^C\s*\d")

	Dim reT As New System.Text.RegularExpressions.Regex( _
		"^T\s*\d")

	Dim reRU As New System.Text.RegularExpressions.Regex( _
		"^R\s*\d")


	If reHE.IsMatch(s) OrElse _
		s.Contains("HEA") OrElse _
		s.Contains("HEB") OrElse _
		s.Contains("HEM") OrElse _
		s.Contains("IPE") Then

		Return "I"


	ElseIf reL.IsMatch(s) OrElse _
		s.Contains("HOEK") OrElse _
		s.Contains("EQUAL ANGLE") OrElse _
		s.Contains("UNEQUAL ANGLE") Then

		Return "L"


	ElseIf s.Contains("UNP") OrElse _
		s.Contains("UPN") OrElse _
		s.Contains("UPE") Then

		Return "U"


	ElseIf rePL.IsMatch(s) OrElse _
		s.Contains("PLATE") OrElse _
		s.Contains("SHEET") OrElse _
		s.Contains("BLECH") Then
		Return "B"


	ElseIf s.Contains("ROHR") OrElse _
		s.Contains("ROUND TUBE") OrElse _
		s.Contains("CHS") OrElse _
		s.Contains("BUIS") Then
		Return "RO"


	ElseIf reRU.IsMatch(s) OrElse _
		s.Contains("RND") OrElse _
		s.Contains("RUND") OrElse _
		s.Contains("ROUND") OrElse _
		s.Contains("CIRCLE") Then
		Return "RU"


	ElseIf s.Contains("RHS") OrElse _
		s.Contains("SHS") OrElse _
		s.Contains("KOK") OrElse _
		s.Contains("RECTANGULAR") OrElse _
		s.Contains("RECTANGLE") OrElse _
		s.Contains("SQUARE") Then
		Return "M"


	ElseIf reC.IsMatch(s) Then
		Return "C"


	ElseIf reT.IsMatch(s) Then
		Return "T"


	Else

		Return "SO"

	End If

End Function
' =====================================================================
' WEBZIJDE V/H BEPALEN
'
' Bepaalt of een lijfgat op de v-zijde (v) of de h-zijde (h)
' van het lijf zit, door naar de normale van het aangrenzende
' platte vlak te kijken en die te vergelijken met de Y-as.
' =====================================================================

Function GetWebFace( _
	ByVal oHoleFace As Face, _
	ByVal oYUnit As UnitVector) As String

	Try

		For Each oEdge As Edge In oHoleFace.Edges

			For Each oAdjacentFace As Face In oEdge.Faces

				If oAdjacentFace Is oHoleFace Then
					Continue For
				End If

				If oAdjacentFace.SurfaceType <> _
					SurfaceTypeEnum.kPlaneSurface Then

					Continue For

				End If

				Dim oPoint As Point = _
					oAdjacentFace.PointOnFace

				Dim points(2) As Double

				points(0) = oPoint.X
				points(1) = oPoint.Y
				points(2) = oPoint.Z

				Dim normals(2) As Double

				oAdjacentFace.Evaluator.GetNormalAtPoint( _
					points, _
					normals)

				Dim oNormal As Vector = _
					ThisApplication.TransientGeometry.CreateVector( _
						normals(0), _
						normals(1), _
						normals(2))

				If oNormal.Length < 0.000001 Then
					Continue For
				End If

				oNormal.Normalize()

				Dim d As Double = _
					DotVector( _
						oNormal, _
						oYUnit.AsVector)

				If d > 0.5 Then
					Return "v"
				End If

				If d < -0.5 Then
					Return "h"
				End If

			Next

		Next

	Catch

	End Try

	Return "v"

End Function
End Module

Module ILogicHost
    Public ThisApplication As Inventor.Application = Nothing
End Module
