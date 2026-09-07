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
' - F3: BO rechthoek O-kolom
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


					Dim angleDeg As Double = _
						Math.Atan2( _
							c2.Y - c1.Y, _
							c2.X - c1.X) * _
						180.0 / Math.PI


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
						Fmt(centerDistMm + widthMm) & " " & _
						Fmt(0.0) & _
						"l " & _
						Fmt(centerDistMm + widthMm) & " " & _
						Fmt(0.0) & " " & _
						Fmt(angleDeg)


					AddHoleLineUnique( _
						holeLines, _
						sHoleLine, _
						holeToleranceMm)

				End If


			' =====================================================
			' RECTANGLE
			' =====================================================

			ElseIf lineCount = 4 AndAlso _
				arcCount = 0 AndAlso _
				circleCount = 0 Then


				Dim rectPoints As New List(Of Point2d)


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
					Dim rectWidthMm As Double = sizeXmm
					Dim rectHeightMm As Double = sizeYmm
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


					' DEBUG: per-opening face decision (rectangle)
					If DebugMode Then
						debugSb.AppendLine("  OPENING (rect): face=" + sFace + " facePos=" + Fmt(facePos) + " holeX=" + Fmt(holeX) + GetDstvXref(sFace) + " holeY=" + Fmt(holeY) + " holeZ=" + Fmt(holeZ) + " sizeX=" + Fmt(sizeXmm) + " sizeY=" + Fmt(sizeYmm))
					End If


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
	sb.AppendLine("  " & Fmt(0.0))
	sb.AppendLine("  " & Fmt(0.0))
	sb.AppendLine("  " & Fmt(0.0))
	sb.AppendLine("  " & Fmt(0.0))


	' =============================================================
	' TEXT INFO ON PIECE
	'
	' DSTV 7e editie:
	' Text info 1
	' Text info 2
	' Text info 3
	' Text info 4
	'
	' Voorlopig leeg.
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
