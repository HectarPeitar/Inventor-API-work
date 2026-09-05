Imports Inventor
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

Namespace TextClientGraphics
    <ProgIdAttribute("TextClientGraphics.StandardAddInServer"), _
    GuidAttribute("13b1419e-168c-4634-9475-af21bc2f36e7")> _
    Public Class StandardAddInServer
        Implements Inventor.ApplicationAddInServer

        ' Inventor application object.
        Private m_inventorApplication As Inventor.Application
        Private WithEvents objButtonDefAddTextGraphics As Inventor.ButtonDefinition
        Private WithEvents objUserInterfaceEvents As Inventor.UserInterfaceEvents
        Private oRibbonPanel As RibbonPanel
        Private objCommandCategory As Inventor.CommandCategory

#Region "ApplicationAddInServer Members"

        Public Sub Activate(ByVal addInSiteObject As Inventor.ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

            ' This method is called by Inventor when it loads the AddIn.
            ' The AddInSiteObject provides access to the Inventor Application object.
            ' The FirstTime flag indicates if the AddIn is loaded for the first time.

            ' Initialize AddIn members.
            m_inventorApplication = addInSiteObject.Application

            'set a reference to the user interface events.
            objUserInterfaceEvents = m_inventorApplication.UserInterfaceManager.UserInterfaceEvents

            'create the button definition to create the text graphics
            objButtonDefAddTextGraphics = m_inventorApplication.CommandManager.ControlDefinitions.AddButtonDefinition("AddTextGraphics", "AddTextGraphicsCmdIntName", Inventor.CommandTypesEnum.kShapeEditCmdType, "{64B357C8-44F4-4DCB-85EC-87AB79EA1AF2}", "Add Text Graphics", "Add Text Graphics")

            'enable the button
            objButtonDefAddTextGraphics.Enabled = True

            'create the command category
            objCommandCategory = m_inventorApplication.CommandManager.CommandCategories.Add("Text Graphics", "AddTextGraphicsCmdCatIntName", "{64B357C8-44F4-4DCB-85EC-87AB79EA1AF2}")

            objCommandCategory.Add(objButtonDefAddTextGraphics)

            'if AddIn is called first time, create ribbon panel and add button to it.
            If firstTime = True Then

                Dim oRibbon As Ribbon
                oRibbon = m_inventorApplication.UserInterfaceManager.Ribbons("Assembly")

                Dim oRibbonTab As RibbonTab
                oRibbonTab = oRibbon.RibbonTabs.Item("id_TabTools")

                oRibbonPanel = oRibbonTab.RibbonPanels.Add("Text Graphics", "AddTextGraphicsToolbarIntName", "{64B357C8-44F4-4DCB-85EC-87AB79EA1AF2}")

                oRibbonPanel.CommandControls.AddButton(objButtonDefAddTextGraphics)

            End If

        End Sub

        Public Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

            ' This method is called by Inventor when the AddIn is unloaded.
            ' The AddIn will be unloaded either manually by the user or
            ' when the Inventor session is terminated.

            objButtonDefAddTextGraphics.Delete()

            If (oRibbonPanel IsNot Nothing) Then
                oRibbonPanel.Delete()
                oRibbonPanel = Nothing
            End If

            objCommandCategory.Delete()

            ' Release objects.
            Marshal.ReleaseComObject(m_inventorApplication)
            m_inventorApplication = Nothing

            System.GC.WaitForPendingFinalizers()
            System.GC.Collect()

        End Sub

        Public ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation

            ' This property is provided to allow the AddIn to expose an API 
            ' of its own to other programs. Typically, this  would be done by
            ' implementing the AddIn's API interface in a class and returning 
            ' that class object through this property.

            Get
                Return Nothing
            End Get

        End Property

        Public Sub ExecuteCommand(ByVal commandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand

            ' Note:this method is now obsolete, you should use the 
            ' ControlDefinition functionality for implementing commands.

        End Sub


        Private Sub objButtonDefAddTextGraphics_OnExecute(ByVal Context As Inventor.NameValueMap) Handles objButtonDefAddTextGraphics.OnExecute

            'obtain current document
            Dim objDocument As Inventor.Document
            objDocument = m_inventorApplication.ActiveDocument

            'obtain the component definition
            Dim objCompDef As Inventor.ComponentDefinition
            objCompDef = objDocument.ComponentDefinition

            'obtain client graphics collection
            Dim colClientGraphics As Inventor.ClientGraphicsCollection
            colClientGraphics = objCompDef.ClientGraphicsCollection

            'add new Client Graphics item, but delete it first if already exists
            On Error Resume Next
            Dim objClientGraphics As Inventor.ClientGraphics
            objClientGraphics = colClientGraphics.Item("TextGraphicsSample")
            If Err.Number = 0 Then
                objClientGraphics.Delete()
                Err.Clear()
                m_inventorApplication.ActiveView.Update()
                On Error GoTo 0
                Exit Sub
            End If

            objClientGraphics = colClientGraphics.Add("TextGraphicsSample")

            'create new Client Graphics node
            Dim objGraphicsNode As Inventor.GraphicsNode
            objGraphicsNode = objClientGraphics.AddNode(objClientGraphics.Count + 1)

            'add Text Graphics to node
            Dim objTextGraphics As Inventor.TextGraphics
            objTextGraphics = objGraphicsNode.AddTextGraphics

            'create Transient Geometry for text anchor point
            Dim objTransGeom As Inventor.TransientGeometry
            objTransGeom = m_inventorApplication.TransientGeometry

            'create Anchor point of 0,0
            Dim objPoint As Inventor.Point
            objPoint = objTransGeom.CreatePoint(0.0#, 0.0#)

            'add attributes such as anchor point, font, size, and content.
            objTextGraphics.Anchor = objPoint
            objTextGraphics.Bold = True
            objTextGraphics.Font = "Arial"
            objTextGraphics.Text = "This is Client Graphics Text."
            objTextGraphics.FontSize = 28

            'specify a color for the text - here it is cyan
            Call objTextGraphics.PutTextColor(0, 255, 255)

            'update the view
            m_inventorApplication.ActiveView.Update()

        End Sub

        Public Sub UserInterfaceEvents_OnResetRibbonInterface(ByVal Context As Inventor.NameValueMap) Handles objUserInterfaceEvents.OnResetRibbonInterface

            Dim oRibbon As Ribbon
            oRibbon = m_inventorApplication.UserInterfaceManager.Ribbons("Assembly")

            Dim oRibbonTab As RibbonTab
            oRibbonTab = oRibbon.RibbonTabs.Item("id_TabTools")

            oRibbonPanel = oRibbonTab.RibbonPanels.Add("Text Graphics", "AddTextGraphicsToolbarIntName", "{64B357C8-44F4-4DCB-85EC-87AB79EA1AF2}")

            oRibbonPanel.CommandControls.AddButton(objButtonDefAddTextGraphics)
        End Sub

#End Region

    End Class

End Namespace

