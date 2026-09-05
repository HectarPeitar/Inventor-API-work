Option Strict Off
Option Explicit On
Module Module1
	
	Public Sub Main()
		' Set a reference to a running instance of Inventor.
		Dim oApp As Inventor.Application
		oApp = GetObject( , "Inventor.Application")
		If Err.Number Then
			MsgBox("Inventor must be running.")
			Exit Sub
		End If
		On Error GoTo 0
		
		' Check to make sure a document is open.
		If oApp.Documents.Count = 0 Then
			MsgBox("A document must be open.")
			Exit Sub
		End If
		
		' Set a reference to the select set.
		Dim oSelectSet As Inventor.SelectSet
		oSelectSet = oApp.ActiveDocument.SelectSet
		
		' Check to see that a single item is in the select set.
		Dim oEdge As Inventor.Edge
		Dim oAttribSets As Inventor.AttributeSetsEnumerator
		Dim oAttribSet As Inventor.AttributeSet
		Dim oHighlightSet As Inventor.HighlightSet
		If oSelectSet.Count = 1 Then
			' Check to see that an edge is selected.
			If TypeOf oSelectSet.Item(1) Is Inventor.Edge Then
				' Set a reference to the edge in the select set.
				oEdge = oSelectSet.Item(1)
				
				' Clear the select set.
				oSelectSet.Clear()
				
				' Check to make sure the selected edge is a circle or arc.
				If oEdge.CurveType = Inventor.CurveTypeEnum.kCircleCurve Or oEdge.CurveType = Inventor.CurveTypeEnum.kCircularArcCurve Then
					' Check to see if the attribute set has already been assigned.
					oAttribSets = oApp.ActiveDocument.AttributeManager.FindAttributeSets("AutoBolts")
					If oAttribSets.Count = 0 Then
						' Add the attribute set to the selected edge.
						oAttribSet = oEdge.AttributeSets.Add("AutoBolts")
						
						Call oAttribSet.Add("AutoBolts", Inventor.ValueTypeEnum.kIntegerType, 1)
					Else
						' An existing attribute set already exists so highlight the edge
						' that has the attribute.
						oHighlightSet = oApp.ActiveDocument.HighlightSets.Add
                        oHighlightSet.AddItem(oAttribSets.Item(1).Parent.Parent)
						If MsgBox("The attribute is already assigned to the highlighted edge.  Do you want to overwrite it?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
							' Clear the highlight set.
							oHighlightSet.Clear()
							
							' Remove the attribute set from the current item.
							oAttribSets.Item(1).Delete()
							
							' Add the attribute set to the selected edge.
							Call oEdge.AttributeSets.Add("AutoBolts")
						Else
							oHighlightSet.Clear()
							Exit Sub
						End If
					End If
				Else
					MsgBox("A circular edge must be selected.")
				End If
			Else
				MsgBox("A circular edge must be selected.")
			End If
		Else
			MsgBox("A single circular edge must be selected.")
		End If
	End Sub
End Module