' =====================================================================
' EXPORT_DSTV_ST_BO
' =====================================================================

Sub Main()

	' -------------------------------------------------------------
	' Configuratie
	' -------------------------------------------------------------
	Dim ORDER_ID As String = "ORDER-1"
	Dim DRAWING_ID As String = "TEK-1"
	Dim PHASE_ID As String = "1"


	' -------------------------------------------------------------
	' Onderdeel ophalen
	' -------------------------------------------------------------
	Dim oDoc As Document = ThisApplication.ActiveDocument
	Dim oPartDoc As PartDocument = Nothing

	If oDoc.DocumentType = DocumentTypeEnum.kAssemblyDocumentObject Then

		Dim oAsmDoc As AssemblyDocument = oDoc

		If oAsmDoc.SelectSet.Count = 0 Then
			MessageBox.Show( _
				"Selecteer eerst één Frame Generator-lid in de assembly.", _
				"Geen selectie")
			Return
		End If

		Dim oOcc As ComponentOccurrence = _
			oAsmDoc.SelectSet.Item(1)

		oPartDoc = oOcc.Definition.Document

	ElseIf oDoc.DocumentType = DocumentTypeEnum.kPartDocumentObject Then

		oPartDoc = oDoc

	Else

		MessageBox.Show( _
			"Open of selecteer een onderdeel (part).", _
			"Verkeerd documenttype")
		Return

	End If


	' -------------------------------------------------------------
	' Headergegevens
	' -------------------------------------------------------------
	Dim oDT As PropertySet = _
		oPartDoc.PropertySets.Item("Design Tracking Properties")

	Dim sPieceId As String = _
		oDT.Item("Part Number").Value

	If sPieceId = "" Then
		sPieceId = oPartDoc.DisplayName
	End If

	Dim sSteelGrade As String = _
		oDT.Item("Material").Value

	Dim sProfileName As String = _
		oDT.Item("Stock Number").Value

	If sProfileName = "" Then
		sProfileName = oDT.Item("Part Number").Value
	End If

	If sProfileName = "" Then
		sProfileName = oDT.Item("Description").Value
	End If

	If sProfileName = "" Then
		MessageBox.Show( _
			"Kon geen profielnaam vinden.", _
			"Profielnaam ontbreekt")
		Return
	End If

	sProfileName = _
		CleanProfileDesignation(sProfileName)

	Dim sProfileCode As String = _
		GetDstvProfileCode(sProfileName)


	' -------------------------------------------------------------
	' Component definition en body
	' -------------------------------------------------------------
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


	' -------------------------------------------------------------
	' Profielparameters
	' -------------------------------------------------------------
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


	' -------------------------------------------------------------
	' DSTV coördinatensysteem bepalen
	' -------------------------------------------------------------
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


	' -------------------------------------------------------------
	' Hoogte- en breedterichting bepalen
	' -------------------------------------------------------------
	Dim heightVec As Vector = Nothing
	Dim widthVec As Vector = Nothing

	If dHeightMm > 0.0 AndAlso dWidthMm > 0.0 Then

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


	' -------------------------------------------------------------
	' DSTV X-as richting geven
	' -------------------------------------------------------------
	Dim xUnit As UnitVector = _
		GetOrientedAxis(lengthVec, _
			ThisApplication.TransientGeometry.CreateUnitVector(1, 0, 0), _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 1, 0), _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 0, 1))


	' -------------------------------------------------------------
	' DSTV Z-as richting geven
	' -------------------------------------------------------------
	Dim zUnit As UnitVector = _
		GetOrientedAxis(heightVec, _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 0, 1), _
			ThisApplication.TransientGeometry.CreateUnitVector(0, 1, 0), _
			ThisApplication.TransientGeometry.CreateUnitVector(1, 0, 0))


	' -------------------------------------------------------------
	' Y-as uit Z x X
	' -------------------------------------------------------------
	Dim yVector As Vector = _
		zUnit.AsVector.CrossProduct( _
			xUnit.AsVector)

	yVector.Normalize()

	Dim yUnit As UnitVector = _
		yVector.AsUnitVector


	' -------------------------------------------------------------
	' Controleer rechtsdraaiend stelsel
	' -------------------------------------------------------------
	Dim checkVector As Vector = _
		xUnit.AsVector.CrossProduct( _
			yUnit.AsVector)

	If DotVector( _
		checkVector, _
		zUnit.AsVector) < 0.0 Then

		yVector.ScaleBy(-1.0)
		yUnit = yVector.AsUnitVector

	End If


	' -------------------------------------------------------------
	' Lokale min/max waarden bepalen
	' -------------------------------------------------------------
	Dim oRefPoint As Point = _
		oBody.Vertices.Item(1).Point.Copy

	Dim minX As Double = Double.MaxValue
	Dim maxY As Double = Double.MinValue
	Dim minZ As Double = Double.MaxValue

	For Each oVertex As Vertex In oBody.Vertices

		Dim p As Point = oVertex.Point

		Dim rel As Vector = _
			oRefPoint.VectorTo(p)

		Dim px As Double = _
			DotVector(rel, xUnit.AsVector)

		Dim py As Double = _
			DotVector(rel, yUnit.AsVector)

		Dim pz As Double = _
			DotVector(rel, zUnit.AsVector)

		If px < minX Then
			minX = px
		End If

		If py > maxY Then
			maxY = py
		End If

		If pz < minZ Then
			minZ = pz
		End If

	Next


	' -------------------------------------------------------------
	' Massa en oppervlakte
	' -------------------------------------------------------------
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
				2)

		dAreaPerMeter = _
			Math.Round( _
				(oMassProps.Area / 10000.0) / _
				lengthMeters, _
				3)

	End If


	' -------------------------------------------------------------
	' Gaten detecteren
	' -------------------------------------------------------------
	Dim holeLines As New List(Of String)

	Dim holeToleranceMm As Double = 0.05

	For Each oSurfBody As SurfaceBody In _
		oCompDef.SurfaceBodies

		For Each oFace As Face In oSurfBody.Faces

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


			' -----------------------------------------------------
			' Cirkelcentrum bepalen
			' -----------------------------------------------------
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


			' -----------------------------------------------------
			' Lokale gatcoördinaten
			' -----------------------------------------------------
			Dim relHole As Vector = _
				oRefPoint.VectorTo(oHoleCenter)

			Dim holeX As Double = _
				DotVector(relHole, xUnit.AsVector)

			Dim holeY As Double = _
				DotVector(relHole, yUnit.AsVector)

			Dim holeZ As Double = _
				DotVector(relHole, zUnit.AsVector)


			' -----------------------------------------------------
			' DSTV absolute X/Y
			' -----------------------------------------------------
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


			' -----------------------------------------------------
			' Gatvlak bepalen
			' -----------------------------------------------------
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


			' -----------------------------------------------------
			' Flensgat
			' -----------------------------------------------------
			If axisAlongHeight >= axisAlongWidth Then

				If zPos >= dHeightMm / 2.0 Then
					sFace = "o"
				Else
					sFace = "u"
				End If

				faceY = yPos


			' -----------------------------------------------------
			' Lijfgat
			' -----------------------------------------------------
			Else

				sFace = _
					GetWebFace( _
						oFace, _
						yUnit)

				faceY = zPos

			End If


			If vPos > -0.05 AndAlso vPos < 0.05 Then
				vPos = 0.0
			End If

			If faceY > -0.05 AndAlso faceY < 0.05 Then
				faceY = 0.0
			End If


			' -----------------------------------------------------
			' BO-regel
			' -----------------------------------------------------
			Dim sHoleLine As String = _
				"  " & _
				sFace & " " & _
				Fmt(vPos) & " " & _
				Fmt(faceY) & " " & _
				Fmt(dDiameterMm)


			' -----------------------------------------------------
			' Dubbele gaten verwijderen
			' -----------------------------------------------------
			Dim bExists As Boolean = False

			For Each existingLine As String In holeLines

				If HoleLinesEquivalent( _
					existingLine, _
					sFace, _
					vPos, _
					faceY, _
					dDiameterMm, _
					holeToleranceMm) Then

					bExists = True
					Exit For

				End If

			Next

			If Not bExists Then
				holeLines.Add(sHoleLine)
			End If

		Next

	Next


	' -------------------------------------------------------------
	' DSTV bestand opbouwen
	' -------------------------------------------------------------
	Dim sb As New System.Text.StringBuilder

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
	sb.AppendLine("  " & Fmt(dWeightPerMeter))
	sb.AppendLine("  " & Fmt(dAreaPerMeter))
	sb.AppendLine("  0.00")
	sb.AppendLine("  0.00")
	sb.AppendLine("  0.00")
	sb.AppendLine("  0.00")

	If holeLines.Count > 0 Then

		sb.AppendLine("BO")

		For Each sLine As String In holeLines
			sb.AppendLine(sLine)
		Next

	End If

	sb.AppendLine("EN")


	' -------------------------------------------------------------
	' Bestand opslaan
	' -------------------------------------------------------------
	Dim OUTPUT_FOLDER As String = _
		System.IO.Path.GetDirectoryName( _
			oPartDoc.FullFileName)

	If Not System.IO.Directory.Exists(OUTPUT_FOLDER) Then
		System.IO.Directory.CreateDirectory(OUTPUT_FOLDER)
	End If

	Dim sSafeName As String = sPieceId

	For Each c As Char In _
		System.IO.Path.GetInvalidFileNameChars()

		sSafeName = _
			sSafeName.Replace(c, "_")

	Next

	Dim sOutPath As String = _
		System.IO.Path.Combine( _
			OUTPUT_FOLDER, _
			sSafeName & ".nc1")

	System.IO.File.WriteAllText( _
		sOutPath, _
		sb.ToString())


	' -------------------------------------------------------------
	' Resultaat
	' -------------------------------------------------------------
	MessageBox.Show( _
		"Weggeschreven:" & vbCrLf & _
		sOutPath & vbCrLf & vbCrLf & _
		"Profiel: " & _
		sProfileName & _
		" (" & sProfileCode & ")" & vbCrLf & _
		"Lengte: " & _
		Fmt(dLengthMm) & " mm" & vbCrLf & _
		"Hoogte: " & _
		Fmt(dHeightMm) & " mm" & vbCrLf & _
		"Breedte: " & _
		Fmt(dWidthMm) & " mm" & vbCrLf & _
		"Aantal boorgaten: " & _
		holeLines.Count, _
		"DSTV export klaar")

End Sub


' =====================================================================
' Kies richting met teken volgens referentie-as
' =====================================================================
Function GetOrientedAxis( _
	ByVal source As Vector, _
	ByVal ref1 As UnitVector, _
	ByVal ref2 As UnitVector, _
	ByVal ref3 As UnitVector) As UnitVector

	Dim a1 As Double = _
		Math.Abs(DotVector(source, ref1.AsVector))

	Dim a2 As Double = _
		Math.Abs(DotVector(source, ref2.AsVector))

	Dim a3 As Double = _
		Math.Abs(DotVector(source, ref3.AsVector))

	Dim result As Vector = source.Copy

	If a1 >= a2 AndAlso a1 >= a3 Then

		If DotVector(source, ref1.AsVector) < 0.0 Then
			result.ScaleBy(-1.0)
		End If

	ElseIf a2 >= a1 AndAlso a2 >= a3 Then

		If DotVector(source, ref2.AsVector) < 0.0 Then
			result.ScaleBy(-1.0)
		End If

	Else

		If DotVector(source, ref3.AsVector) < 0.0 Then
			result.ScaleBy(-1.0)
		End If

	End If

	Return result.AsUnitVector

End Function


' =====================================================================
' Dot product
' =====================================================================
Function DotVector( _
	ByVal a As Vector, _
	ByVal b As Vector) As Double

	Return _
		a.X * b.X + _
		a.Y * b.Y + _
		a.Z * b.Z

End Function


' =====================================================================
' Grootste richting
' =====================================================================
Function GetLargestIndex( _
	ByVal a As Double, _
	ByVal b As Double, _
	ByVal c As Double) As Integer

	If a >= b AndAlso a >= c Then
		Return 1
	ElseIf b >= a AndAlso b >= c Then
		Return 2
	Else
		Return 3
	End If

End Function


' =====================================================================
' Webzijde V/H bepalen
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


' =====================================================================
' Lengte cm naar mm
' =====================================================================
Function CmToMm(ByVal v As Double) As Double

	Return Math.Round(v * 10.0, 2)

End Function


' =====================================================================
' Getal formatteren
' =====================================================================
Function Fmt(ByVal v As Double) As String

	Return _
		v.ToString( _
			"0.00", _
			System.Globalization.CultureInfo.InvariantCulture)

End Function


' =====================================================================
' Profielparameter zoeken
' =====================================================================
Function GetProfileParam( _
	ByVal oPartDoc As PartDocument, _
	ByVal paramNames() As String, _
	ByVal defaultValue As Double) As Double

	Dim oParams As Parameters = _
		oPartDoc.ComponentDefinition.Parameters

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
' Profielnaam opschonen
' =====================================================================
Function CleanProfileDesignation( _
	ByVal sRaw As String) As String

	Dim s As String = _
		sRaw.Trim()

	Dim idx As Integer = _
		s.LastIndexOf(" - ")

	If idx >= 0 Then

		s = _
			s.Substring(idx + 3).Trim()

	End If

	s = _
		System.Text.RegularExpressions.Regex.Replace( _
			s, _
			"-\d+(\.\d+)?$", _
			"").Trim()

	Return s

End Function


' =====================================================================
' DSTV profielcode bepalen
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
' Dubbele BO-regels controleren
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
				parts(1), _
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
