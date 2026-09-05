Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
Friend Class frmAttributes
	Inherits System.Windows.Forms.Form

	Public objInventorApp As Inventor.Application
	Public objPartDocument As Inventor.PartDocument
	Dim objHighlightSet As Inventor.HighlightSet

	'clear the current highlight set
	Private Sub Clear_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Clear_Command.Click
		On Error Resume Next
		If Not objHighlightSet Is Nothing Then
			objHighlightSet.Clear()
			Err.Clear()
		End If
		On Error GoTo 0
	End Sub

	'save the document with attributes and close the view
	Private Sub Save_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Save_Command.Click
		Call objInventorApp.ActiveDocument.Save()
		Dim sFullDocumentName As String
		sFullDocumentName = objInventorApp.ActiveDocument.FullDocumentName
		Call objInventorApp.ActiveDocument.Close()
		objPartDocument = objInventorApp.Documents.Open(sFullDocumentName, True)
	End Sub

	'create an attribute set "AttribSet" and an attribute "Attrib" for the selected entity if it doesn't already exist and set its value
	Private Sub SetAttribute_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles SetAttribute_Command.Click

		'make sure an entity in the part document is selected
		If objPartDocument.SelectSet.Count <> 1 Then
			MsgBox("An entity in the part document must be selected.")
			Exit Sub
		End If

		'get the selected entity from the select set
		Dim objSelectedObject As Object
		objSelectedObject = objInventorApp.ActiveDocument.SelectSet.Item(1)

		'make sure the selected object supports attributes
		On Error Resume Next
		Dim objAttributeSets As Inventor.AttributeSets
		objAttributeSets = objSelectedObject.AttributeSets
		If Err.Number Then
			MsgBox("The selected object does not support attributes")
			Exit Sub
		End If
		On Error GoTo 0

		'check if attribute value has been specified
		If SetAttribute_Text.Text = "" Then
			MsgBox("Enter an attribute value in the text box")
			Exit Sub
		End If

		Dim objAttributeSet As Inventor.AttributeSet
		Dim objAttribute As Inventor.Attribute
		If SetAttribute_Text.Text <> "" Then

			On Error Resume Next

			'access the attribute set "AttribTest" if it already exists
			objAttributeSet = objAttributeSets.Item("AttribTest")

			'if it does not exist, create it
			If Err.Number Or objAttributeSet Is Nothing Then
				objAttributeSet = objAttributeSets.Add("AttribTest")
			End If

			'access the attribute "Attrib" if it already exists
			objAttribute = objAttributeSet.Item("Attrib")

			'if it does not exist, create it
			If Err.Number Or objAttribute Is Nothing Then
				objAttribute = objAttributeSet.Add("Attrib", Inventor.ValueTypeEnum.kStringType, SetAttribute_Text.Text)
			End If

			'assign a new value to the attribute
			objAttribute.Value = SetAttribute_Text.Text

			On Error GoTo 0

		End If
	End Sub

	'deletes the attribute set "AttribSet" and the attribute "Attrib" on the selected entity
	Private Sub DeleteAttribute_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles DeleteAttribute_Command.Click

		'first check if an entity has been selected
		If objPartDocument.SelectSet.Count <> 1 Then
			MsgBox("An entity must be selected first")
			Exit Sub
		End If

		'if an entity has been selected, get it from the select set
		Dim objSelectedObject As Object
		objSelectedObject = objInventorApp.ActiveDocument.SelectSet.Item(1)

		'make sure the selected object supports attributes
		On Error Resume Next

		'try to get the attributesets from the object
		Dim objAttributeSets As Inventor.AttributeSets
		objAttributeSets = objSelectedObject.AttributeSets

		'if there's an error, then the object does not support attributes
		If Err.Number Then
			MsgBox("The selected object does not support attributes")
			Exit Sub
		End If

		On Error GoTo 0

		'check if the attribute set "AttribTest" exists, if so access it
		Dim objAttributeSet As Inventor.AttributeSet
		Dim objAttribute As Inventor.Attribute
		If objAttributeSets.NameIsUsed("AttribTest") Then

			'get the attribute set "AttribTest"
			objAttributeSet = objAttributeSets.Item("AttribTest")

			'check if the attribute "Attrib" exists, if so access it
			If objAttributeSet.NameIsUsed("Attrib") Then

				'get the attribute "Attrib"
				objAttribute = objAttributeSet.Item("Attrib")

				'first delete the attribute
				objAttribute.Delete()
			End If

			'delete the attribute set
			objAttributeSet.Delete()

			GetAttribute_Text.Text = ""
		Else
			MsgBox("the selected entity does not have the attribute")
		End If

	End Sub

	'exit the application
	Private Sub Close_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Close_Command.Click
		Me.Close()
	End Sub

	Private Sub frmAttributes_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load

		On Error Resume Next

		'get an active session of Inventor
		objInventorApp = Win32.GetActiveObject("Inventor.Application")
		If Err.Number Then
			MsgBox("Inventor must be running.")
			End
		End If

		On Error GoTo 0

		Call DrawBlockWithPocket()

	End Sub

	Public Sub DrawBlockWithPocket()

		'create a new part document, using the default part template
		objPartDocument = objInventorApp.Documents.Add(Inventor.DocumentTypeEnum.kPartDocumentObject, objInventorApp.FileManager.GetTemplateFile(Inventor.DocumentTypeEnum.kPartDocumentObject))
		objPartDocument.DisplayName = "Attribute Sample.ipt"

		'set a reference to the component definition
		Dim objPartCompDef As Inventor.PartComponentDefinition
		objPartCompDef = objPartDocument.ComponentDefinition

		'create a new sketch on the X-Y work plane.  Since it's being created on
		'one of the base workplanes we know the orientation it will be created in
		'and don't need to worry about controlling it.  Because of this we also
		'know the origin of the sketch plane will be at (0,0,0) in model space.
		Dim objPlanarSketch As Inventor.PlanarSketch
		objPlanarSketch = objPartCompDef.Sketches.Add(objPartCompDef.WorkPlanes(3))

		'set a reference to the transient geometry object
		Dim objTransGeom As Inventor.TransientGeometry
		objTransGeom = objInventorApp.TransientGeometry

		'draw a 4cm x 3cm rectangle with the corner at (0,0)
		Dim objRectangleLines As Inventor.SketchEntitiesEnumerator
		objRectangleLines = objPlanarSketch.SketchLines.AddAsTwoPointRectangle(objTransGeom.CreatePoint2d(0, 0), objTransGeom.CreatePoint2d(4, 3))

		'create a profile
		Dim objProfile As Inventor.Profile
		objProfile = objPlanarSketch.Profiles.AddForSolid

		'create a base extrusion 1cm thick
		Dim objExtrudeFeat As Inventor.ExtrudeFeature
		objExtrudeFeat = objPartCompDef.Features.ExtrudeFeatures.AddByDistanceExtent(objProfile, 1, Inventor.PartFeatureExtentDirectionEnum.kNegativeExtentDirection, Inventor.PartFeatureOperationEnum.kJoinOperation)


	End Sub

	'gets the attribute set "AttribSet" and then the attribute "Attrib", then its value for the selected entity
	Public Sub GetAttribute_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles GetAttribute_Command.Click

		'first check if an entity has been selected
		If objPartDocument.SelectSet.Count <> 1 Then
			MsgBox("An entity must be selected first")
			Exit Sub
		End If

		'if an entity has been selected, get it from the select set
		Dim objSelectedObject As Object
		objSelectedObject = objInventorApp.ActiveDocument.SelectSet.Item(1)

		'make sure the selected object supports attributes
		On Error Resume Next

		'try to get the attributesets from the object
		Dim objAttributeSets As Inventor.AttributeSets
		objAttributeSets = objSelectedObject.AttributeSets

		'if there's an error, then the object does not support attributes
		If Err.Number Then
			MsgBox("The selected object does not support attributes")
			Exit Sub
		End If

		On Error GoTo 0

		'check if the attribute set "AttribTest" exists, if so access it
		Dim objAttributeSet As Inventor.AttributeSet
		Dim objAttribute As Inventor.Attribute
		If objAttributeSets.NameIsUsed("AttribTest") Then

			'get the attribute set "AttribTest"
			objAttributeSet = objAttributeSets.Item("AttribTest")

			'check if the attribute "Attrib" exists, if so access it
			If objAttributeSet.NameIsUsed("Attrib") Then

				'get the attribute "Attrib"
				objAttribute = objAttributeSet.Item("Attrib")

				'get the attribute value
				GetAttribute_Text.Text = objAttribute.Value
			End If

		Else
			MsgBox("the selected entity does not have the attribute")
		End If

	End Sub

	'search all the faces for the  attribute value specifed in the Query Entities text box
	'and highight all the faces whose attribute values match
	Private Sub QueryEntities_Command_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles QueryEntities_Command.Click

		'first check if the attribute value to search for has been specified
		If QueryEntities_Text.Text = "" Then
			MsgBox("please enter a attribute value in the text box")
			Exit Sub
		End If

		Dim colObject As Inventor.ObjectCollection
		colObject = objPartDocument.AttributeManager.FindObjects("AttribTest", "Attrib", QueryEntities_Text.Text)

		If colObject.Count = 0 Then
			MsgBox("No entities were found with the given attribute value")
			Exit Sub
		End If

		'clear the current highlight set
		On Error Resume Next
		If Not objHighlightSet Is Nothing Then
			objHighlightSet.Clear()
			Err.Clear()
		End If
		On Error GoTo 0

		'create a new highlight set for the entities
		objHighlightSet = objPartDocument.HighlightSets.Add

		'set the highlight color for the set to red
		Dim oTransientObjects As Inventor.TransientObjects
		oTransientObjects = objInventorApp.TransientObjects

		Dim oColor As Inventor.Color
		oColor = oTransientObjects.CreateColor(255, 0, 0)
		objHighlightSet.Color = oColor

		'add all entities to the highlight set
		Dim objObject As Object
		For Each objObject In colObject
			objHighlightSet.AddItem(objObject)
		Next objObject
	End Sub

	Private Sub QueryTextBox_Change()
		QueryEntities_Command.Enabled = True
	End Sub
End Class

Public Class Win32
	<DllImport("ole32")>
	Private Shared Function CLSIDFromProgIDEx(
		<MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
	End Function
	<DllImport("ole32")>
	Private Shared Function CLSIDFromProgID(
		<MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
	End Function
	<DllImport("oleaut32")>
	Private Shared Function GetActiveObject(
		<MarshalAs(UnmanagedType.LPStruct)> ByVal rclsid As Guid, ByVal pvReserved As IntPtr, <Out>
		<MarshalAs(UnmanagedType.IUnknown)> ByRef ppunk As Object) As Integer
	End Function

	Public Shared Function GetActiveObject(ByVal progID As String) As Object
		Dim obj As Object = Nothing
		Dim clsid As Guid

		' Call CLSIDFromProgIDEx first then fall back on CLSIDFromProgID if
		' CLSIDFromProgIDEx doesn't exist.
		Try
			CLSIDFromProgIDEx(progID, clsid)
		Catch ex As Exception
			CLSIDFromProgID(progID, clsid)
		End Try

		Dim hr = GetActiveObject(clsid, IntPtr.Zero, obj)
		If hr < 0 Then
			Err.Raise(0)
		End If
		Return obj
	End Function
End Class