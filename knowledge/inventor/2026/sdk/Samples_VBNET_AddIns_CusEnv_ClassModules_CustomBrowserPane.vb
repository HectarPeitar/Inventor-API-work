Option Strict Off
Option Explicit On
<System.Runtime.InteropServices.ProgId("clsCustomBrowserPane_NET.clsCustomBrowserPane")> Public Class clsCustomBrowserPane

    Private mobjInventorApp As Inventor.Application
    Private mstrClientID As String

	'constants
	Private Const mlngBodyNodePictureId As Short = 1
	Private Const mlngFaceNodePictureId As Short = 2
	Private Const mlngEdgeLoopNodePictureId As Short = 3
	Private Const mlngEdgeNodePictureId As Short = 4
	
	'data members
	Private mlngBrowserNodeId As Integer
	
	Private mobjBrowserPanes As Inventor.BrowserPanes
	
    Private WithEvents mobjBrowserPanesEvents As Inventor.BrowserPanesEvents

    Public Sub New(ByVal objInventorApp As Inventor.Application, ByVal strClientID As String)

        MyBase.New()

        mobjInventorApp = objInventorApp
        mstrClientID = strClientID

    End Sub
	
	Public Sub CreateBrepTree(ByRef objPartDoc As Inventor.PartDocument)
		
		On Error Resume Next
		
		mobjBrowserPanes = objPartDoc.BrowserPanes
		
		mobjBrowserPanesEvents = mobjBrowserPanes.BrowserPanesEvents
		
		'first, check if the browser pane already exists
		Dim objBrowserPane As Inventor.BrowserPane
		For	Each objBrowserPane In mobjBrowserPanes
			
            If objBrowserPane.InternalName = "BrepTree" & mstrClientID Then
                Call objBrowserPane.Activate()
                Exit Sub
            End If
			
		Next objBrowserPane
		
		'create the node resources
		Call CreateNodeResources()
		
		'create the root node
		Dim objRootNodeDef As Inventor.ClientBrowserNodeDefinition
		objRootNodeDef = CreateRootNode((objPartDoc.DisplayName))
		
		Dim objActiveBrowserPane As Inventor.BrowserPane
		Dim objRootNode As Inventor.BrowserNode
		Dim objSurfaceBody As Inventor.SurfaceBody
		If Not objRootNodeDef Is Nothing Then
			
			objActiveBrowserPane = mobjBrowserPanes.ActivePane
			
			'create the BrowserPane tree
            objBrowserPane = mobjBrowserPanes.AddTreeBrowserPane("Brep Tree", "BrepTree" & mstrClientID, objRootNodeDef)
			
			Call objActiveBrowserPane.Activate()
			
			'add child nodes to the tree
			objRootNode = objBrowserPane.TopNode
			
			objSurfaceBody = objPartDoc.ComponentDefinition.SurfaceBodies(1)
			
			If Not objSurfaceBody Is Nothing Then
				Call CreateTreeNodes(objPartDoc.ComponentDefinition.SurfaceBodies(1), objRootNode)
			End If
			
		End If
		
	End Sub
	
	Public Sub ActivateBrepTree(ByRef objPartDoc As Inventor.PartDocument)
		
		On Error Resume Next
		
		mobjBrowserPanes = objPartDoc.BrowserPanes
		
		'first, check if the browser pane already exists
		Dim objBrowserPane As Inventor.BrowserPane
		For	Each objBrowserPane In mobjBrowserPanes
			
            If objBrowserPane.InternalName = "BrepTree" & mstrClientID Then
                Call objBrowserPane.Activate()
                Exit Sub
            End If
			
		Next objBrowserPane
		
	End Sub
	
	Public Sub ActivateDefaultTree(ByRef objPartDoc As Inventor.PartDocument)
		
		On Error Resume Next
		
		mobjBrowserPanes = objPartDoc.BrowserPanes
		
		'first, check if the browser pane already exists
		Dim objBrowserPane As Inventor.BrowserPane
		For	Each objBrowserPane In mobjBrowserPanes
			
			If objBrowserPane.BuiltIn = True Then
				If objBrowserPane.Default = True Then
					Call objBrowserPane.Activate()
					Exit Sub
				End If
			End If
			
		Next objBrowserPane
		
	End Sub
	
	Private Sub CreateNodeResources()
		
		On Error Resume Next
		
		' load the icons from a resource
		Dim objBodyPicture As System.Drawing.Image
		objBodyPicture = My.Resources.bmp11
		
		Dim objFacePicture As System.Drawing.Image
		objFacePicture = My.Resources.bmp12
		
		Dim objEdgeLoopPicture As System.Drawing.Image
		objEdgeLoopPicture = My.Resources.bmp13
		
		Dim objEdgePicture As System.Drawing.Image
		objEdgePicture = My.Resources.bmp14
		
        Call mobjBrowserPanes.ClientNodeResources.Add(mstrClientID, mlngBodyNodePictureId, objBodyPicture)
        Call mobjBrowserPanes.ClientNodeResources.Add(mstrClientID, mlngFaceNodePictureId, objFacePicture)
        Call mobjBrowserPanes.ClientNodeResources.Add(mstrClientID, mlngEdgeLoopNodePictureId, objEdgeLoopPicture)
        Call mobjBrowserPanes.ClientNodeResources.Add(mstrClientID, mlngEdgeNodePictureId, objEdgePicture)
		
	End Sub
	
	Private Function CreateRootNode(ByRef strBrowserNodeName As String) As Inventor.ClientBrowserNodeDefinition
		On Error Resume Next
		
		mlngBrowserNodeId = 1
		CreateRootNode = CreateNode(strBrowserNodeName, mlngBodyNodePictureId)
	End Function
	
	'get the brep information and add it to the tree
	Private Sub CreateTreeNodes(ByRef objSurfaceBody As Inventor.SurfaceBody, ByRef objParentNode As Inventor.BrowserNode)
		
		On Error Resume Next
		
		'get the Faces collection from the SurfaceBody
		Dim objFaces As Inventor.Faces
		objFaces = objSurfaceBody.Faces
		
		'iterate through the faces in the current body
		Dim objFace As Inventor.Face
		Dim objFaceNodeDef As Inventor.ClientBrowserNodeDefinition
		Dim objFaceNode As Inventor.BrowserNode
		Dim objEdgeLoops As Inventor.EdgeLoops
		Dim objEdgeLoop As Inventor.EdgeLoop
		Dim objEdgeLoopNodeDef As Inventor.ClientBrowserNodeDefinition
		Dim objEdgeLoopNode As Inventor.BrowserNode
		Dim objEdges As Inventor.Edges
		Dim objEdge As Inventor.Edge
		Dim objEdgeNodeDef As Inventor.ClientBrowserNodeDefinition
		Dim objEdgeNode As Inventor.BrowserNode
		For	Each objFace In objFaces
			
			'add a node to the tree view for the face
			objFaceNodeDef = CreateNode("Face", mlngFaceNodePictureId)
			
			If Not objFaceNodeDef Is Nothing Then
				
                objFaceNode = objParentNode.AddChild(objFaceNodeDef)
				
				'get the EdgeLoops collection from the Face
				objEdgeLoops = objFace.EdgeLoops
				
				'iterate through the loops of the current face
				For	Each objEdgeLoop In objEdgeLoops
					
					'add a node to the tree view for the edge loop
					objEdgeLoopNodeDef = CreateNode("EdgeLoop", mlngEdgeLoopNodePictureId)
					
					If Not objEdgeLoopNodeDef Is Nothing Then
						
                        objEdgeLoopNode = objFaceNode.AddChild(objEdgeLoopNodeDef)
						
						'get the Edges collection from the EdgeLoop
						objEdges = objEdgeLoop.Edges
						
						'iterate through the edges of the current loop
						For	Each objEdge In objEdges
							
							'add a node to the tree view for the edge
							objEdgeNodeDef = CreateNode("Edge", mlngEdgeNodePictureId)
							
							If Not objEdgeNodeDef Is Nothing Then
								
                                objEdgeNode = objEdgeLoopNode.AddChild(objEdgeNodeDef)
								
							End If
							
						Next objEdge
						
					End If
					
				Next objEdgeLoop
				
			End If
		Next objFace
		
	End Sub
	
	Private Function CreateNode(ByRef strBrowserNodeName As String, ByRef lngNodePictureId As Integer) As Inventor.ClientBrowserNodeDefinition
		
		On Error Resume Next
		
		Dim objClientNodeRescs As Inventor.ClientNodeResources
		objClientNodeRescs = mobjBrowserPanes.ClientNodeResources
		
        CreateNode = mobjBrowserPanes.CreateBrowserNodeDefinition(strBrowserNodeName, mlngBrowserNodeId, objClientNodeRescs.ItemById(mstrClientID, lngNodePictureId))
		mlngBrowserNodeId = mlngBrowserNodeId + 1
		
	End Function
	
	Private Function GetBrepEntity(ByRef objPartDoc As Inventor.PartDocument, ByRef lngBrowserNodeId As Integer) As Object
		
        On Error Resume Next

        GetBrepEntity = Nothing
		
		Dim objPartCompDef As Inventor.PartComponentDefinition
		objPartCompDef = objPartDoc.ComponentDefinition
		
		Dim objSurfaceBody As Inventor.SurfaceBody
		Dim lngBrepEntityId As Integer
		Dim objFaces As Inventor.Faces
		Dim objFace As Inventor.Face
		Dim objEdgeLoops As Inventor.EdgeLoops
		Dim objEdgeLoop As Inventor.EdgeLoop
		Dim objEdges As Inventor.Edges
		Dim objEdge As Inventor.Edge
		If Not objPartCompDef Is Nothing Then
			
			objSurfaceBody = objPartDoc.ComponentDefinition.SurfaceBodies(1)
			
			If Not objSurfaceBody Is Nothing Then
				
				lngBrepEntityId = 1
				
				If lngBrepEntityId = lngBrowserNodeId Then
					GetBrepEntity = objSurfaceBody
					Exit Function
				End If
				
				'get the Faces collection from the SurfaceBody
				objFaces = objSurfaceBody.Faces
				
				'iterate through the faces in the current body
				For	Each objFace In objFaces
					
					lngBrepEntityId = lngBrepEntityId + 1
					
					If lngBrepEntityId = lngBrowserNodeId Then
						GetBrepEntity = objFace
						Exit Function
					End If
					
					'get the EdgeLoops collection from the Face
					objEdgeLoops = objFace.EdgeLoops
					
					'iterate through the loops of the current face
					For	Each objEdgeLoop In objEdgeLoops
						
						lngBrepEntityId = lngBrepEntityId + 1
						
						If lngBrepEntityId = lngBrowserNodeId Then
							GetBrepEntity = objEdgeLoop
							Exit Function
						End If
						
						'get the Edges collection from the EdgeLoop
						objEdges = objEdgeLoop.Edges
						
						'iterate through the edges of the current loop
						For	Each objEdge In objEdges
							
							lngBrepEntityId = lngBrepEntityId + 1
							
							If lngBrepEntityId = lngBrowserNodeId Then
								GetBrepEntity = objEdge
                                Exit Function
                            End If
						Next objEdge
					Next objEdgeLoop
				Next objFace
			End If
		End If
	End Function
	
	Private Sub mobjBrowserPanesEvents_OnBrowserNodeActivate(ByVal BrowserNodeDefinition As Object, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles mobjBrowserPanesEvents.OnBrowserNodeActivate
		
		On Error Resume Next
		
        Dim objPartDoc As Inventor.PartDocument
		Dim objBrepEntity As Object
		Dim frmEntityInfo As New frmEntityInformation
		If BrowserNodeDefinition.Type = Inventor.ObjectTypeEnum.kClientBrowserNodeDefinitionObject Then
			
            objPartDoc = mobjInventorApp.ActiveDocument
			
            objBrepEntity = GetBrepEntity(objPartDoc, BrowserNodeDefinition.Id)
			
			If Not objBrepEntity Is Nothing Then
				
                If objBrepEntity.Type = Inventor.ObjectTypeEnum.kSurfaceBodyObject Then
                    Call frmEntityInfo.DisplaySurfaceBodyInformation(objBrepEntity)
                End If
				
                If objBrepEntity.Type = Inventor.ObjectTypeEnum.kFaceObject Then
                    Call frmEntityInfo.DisplayFaceInformation(objBrepEntity)
                End If
				
                If objBrepEntity.Type = Inventor.ObjectTypeEnum.kEdgeObject Then
                    Call frmEntityInfo.DisplayEdgeInformation(objBrepEntity)
                End If
				
			End If
			
		End If
		
	End Sub
	
	Private Sub mobjBrowserPanesEvents_OnBrowserNodeGetDisplayObjects(ByVal BrowserNodeDefinition As Object, ByRef Objects As Inventor.ObjectCollection, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles mobjBrowserPanesEvents.OnBrowserNodeGetDisplayObjects
		
		On Error Resume Next
		
        Dim objPartDoc As Inventor.PartDocument
		Dim objBrepEntity As Object
		If BrowserNodeDefinition.Type = Inventor.ObjectTypeEnum.kClientBrowserNodeDefinitionObject Then
			
            objPartDoc = mobjInventorApp.ActiveDocument
			
            objBrepEntity = GetBrepEntity(objPartDoc, BrowserNodeDefinition.Id)
			
            If Not objBrepEntity Is Nothing And (objBrepEntity.Type = Inventor.ObjectTypeEnum.kFaceObject Or objBrepEntity.Type = Inventor.ObjectTypeEnum.kEdgeObject) Then

                Objects = mobjInventorApp.TransientObjects.CreateObjectCollection
                Call Objects.Add(objBrepEntity)

                HandlingCode = Inventor.HandlingCodeEnum.kEventHandled
            End If
			
		End If
		
	End Sub
	
    Protected Overrides Sub Finalize()

        mobjBrowserPanes = Nothing

        mobjBrowserPanesEvents = Nothing

        MyBase.Finalize()

    End Sub
End Class