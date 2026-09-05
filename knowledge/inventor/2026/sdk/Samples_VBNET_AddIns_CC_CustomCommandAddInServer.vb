Imports Inventor
Imports System.Drawing
Imports System.Windows.Forms
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

<ProgIdAttribute("CustomCommand.AddInServer"), _
GuidAttribute("D7D54695-7FBE-4968-A0DD-B86FA4D59AE5")> _
Public Class CustomCommandAddInServer
    Implements Inventor.ApplicationAddInServer

#Region "Data Member"
    'Inventor application object
    Private m_inventorApp As Inventor.Application

    'Rack Face command
    Private m_rackFaceCmd As RackFaceCmd

    Private m_addInCLSIDString As String

    ' Events
    Private m_userInterfaceEvents As UserInterfaceEvents

#End Region

    Public Sub New()
        m_inventorApp = Nothing
        m_rackFaceCmd = Nothing
    End Sub

#Region "ApplicationAddinServer Member"

    Public Sub Activate(ByVal addInSiteObject As ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate
        Try
            'The Activate method is called by Inventor when it loads the addin
            'the AddInSiteObject provides access to the Inventor Application object
            'the FirstTime flag indicates if the addin is loaded for the first time

            'Initialize AddIn members
            m_inventorApp = addInSiteObject.Application

            'initialize event handlers
            m_userInterfaceEvents = m_inventorApp.UserInterfaceManager.UserInterfaceEvents

            AddHandler m_userInterfaceEvents.OnResetCommandBars, AddressOf Me.UserInterfaceEvents_OnResetCommandBars
            AddHandler m_userInterfaceEvents.OnEnvironmentChange, AddressOf Me.UserInterfaceEvents_OnEnvironmentChange
            AddHandler m_userInterfaceEvents.OnResetRibbonInterface, AddressOf Me.UserInterfaceEvents_OnResetRibbonInterface


            'Retrieve the GUID for this class
            Dim addInCLSID As GuidAttribute
            addInCLSID = CType(System.Attribute.GetCustomAttribute(GetType(CustomCommandAddInServer), GetType(GuidAttribute)), GuidAttribute)

            m_addInCLSIDString = "{" & addInCLSID.Value & "}"

            'Create the command button(s)
            'Create instance of the "Rack Face" command class
            m_rackFaceCmd = New CustomCommand.RackFaceCmd()

            'Create the "Fack face" button
            m_rackFaceCmd.CreateButton(m_inventorApp, False, "Rack Face", "Autodesk:CustomCommand:RackFaceCmd", CommandTypesEnum.kShapeEditCmdType, m_addInCLSIDString, "Create a rack feature", "Create a rack feature")

            'Create change definition
            'Get the change manager
            Dim changeManager As ChangeManager
            changeManager = m_inventorApp.ChangeManager

            'Create the change definitions collection for this AddIn
            Dim changeDefinitions As ChangeDefinitions
            changeDefinitions = changeManager.Add(m_addInCLSIDString)

            'Create the "Rack Face" change definition
            Dim rackFaceChangeDefinition As ChangeDefinition
            rackFaceChangeDefinition = changeDefinitions.Add("Autodesk:CustomCommand:RackFaceChgDef", "Rack Face")

            ' Create the "Rack Face" command category
            Dim rackFaceCmdCategory As CommandCategory = m_inventorApp.CommandManager.CommandCategories.Add("Rack Face", "Autodesk:CustomCommand:RackFaceCmdCat", m_addInCLSIDString)
            rackFaceCmdCategory.Add(m_rackFaceCmd.ButtonDefinition)

            If firstTime Then
                'Add the button to the part features toolbar
                Dim userInterfaceMgr As UserInterfaceManager
                userInterfaceMgr = m_inventorApp.UserInterfaceManager

                Dim interfaceStyle As InterfaceStyleEnum = userInterfaceMgr.InterfaceStyle

                'Create the UI for classic interface
                If interfaceStyle = InterfaceStyleEnum.kClassicInterface Then

                    'Get the commandbars collection
                    Dim commandBars As CommandBars
                    commandBars = userInterfaceMgr.CommandBars

                    'Get the part features toolbar
                    Dim partFeaturesToolbar As Inventor.CommandBar
                    partFeaturesToolbar = commandBars("PMxPartFeatureCmdBar")

                    'Add the "Rack Face" button to the toolbar
                    partFeaturesToolbar.Controls.AddButton(m_rackFaceCmd.ButtonDefinition, 0)

                    'Create the UI for the ribbon interface
                Else
                    'Get the ribbons associated with part documents
                    Dim ribbons As Ribbons = userInterfaceMgr.Ribbons
                    Dim partRibbon As Ribbon = ribbons("Part")

                    'Get the tabs associated with part ribbon
                    Dim ribbonTabs As RibbonTabs = partRibbon.RibbonTabs
                    Dim modelRibbonTab As RibbonTab = ribbonTabs("id_TabModel")

                    'Get the panels within Model tab
                    Dim ribbonPanels As RibbonPanels = modelRibbonTab.RibbonPanels
                    Dim modifyRibbonPanel As RibbonPanel = ribbonPanels("id_PanelP_ModelModify")

                    'Add controls to the Modify panel
                    Dim modifyRibbonPanelCtrls As CommandControls = modifyRibbonPanel.CommandControls

                    'Add button to the Modify panel
                    modifyRibbonPanelCtrls.AddButton(m_rackFaceCmd.ButtonDefinition)

                End If

            End If

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.ToString())
        End Try
    End Sub

    Public ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation
        'if you want to return an interface to another client of this addin,
        'implement that interface in a class and return that class object 
        'through this property

        Get
            Return Nothing
        End Get
    End Property

    Public Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate
        'The Deactiveate method is called by Inventor when the AddIn is unloaded
        'the AddIn will be unloaded either manually by the user or
        'when the Inventor session is terminated

        'disconnect events
        RemoveHandler m_userInterfaceEvents.OnResetCommandBars, AddressOf Me.UserInterfaceEvents_OnResetCommandBars
        RemoveHandler m_userInterfaceEvents.OnEnvironmentChange, AddressOf Me.UserInterfaceEvents_OnEnvironmentChange
        RemoveHandler m_userInterfaceEvents.OnResetRibbonInterface, AddressOf Me.UserInterfaceEvents_OnResetRibbonInterface

        m_userInterfaceEvents = Nothing

        'Remove the command button(s)
        'Remove the "Rack Face" button
        m_rackFaceCmd.RemoveButton()
        m_rackFaceCmd = Nothing

        'Delete change definition(s)
        'Get the change manager
        Dim changeManager As ChangeManager
        changeManager = m_inventorApp.ChangeManager

        'Get the change definition collection
        Dim changeDefinitions As ChangeDefinitions
        changeDefinitions = changeManager(m_addInCLSIDString)

        'Get the "Rack Face" change definition
        Dim rackFaceChangeDefinition As ChangeDefinition
        rackFaceChangeDefinition = changeDefinitions("Autodesk:CustomCommand:RackFaceChgDef")

        'Delete the "Rack Face" change definition
        rackFaceChangeDefinition.Delete()

        Marshal.ReleaseComObject(m_inventorApp)
        m_inventorApp = Nothing

        GC.WaitForPendingFinalizers()
        GC.Collect()

    End Sub

    Public Sub ExecuteCommand(ByVal commandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand
        'this method was used to notify when an AddIn command was executed
        'the CommandID parameter identifies the command that was executed

        'Note:this method is now obsolete, you should use the new
        'ControlDefinition objects to implement commands, they have
        'their own event sinks to notify when the command is executed
    End Sub

    Public Sub UserInterfaceEvents_OnResetCommandBars(ByVal commandBars As ObjectsEnumerator, ByVal context As NameValueMap)

        Try
            Dim commandBar As CommandBar
            For Each commandBar In commandBars
                If commandBar.InternalName = "PMxPartFeatureCmdBar" Then

                    'Add "Rack Face" button back to the part features toolbar
                    commandBar.Controls.AddButton(m_rackFaceCmd.ButtonDefinition)

                    Exit Sub
                End If
            Next

        Catch
        End Try

    End Sub

    Public Sub UserInterfaceEvents_OnEnvironmentChange(ByVal environment As Environment, ByVal environmentState As EnvironmentStateEnum, ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)

        Try
            Dim envInternalName As String
            envInternalName = environment.InternalName

            If envInternalName = "PMxPartEnvironment" Then

                ' Enable the "Rack Face" button when the part environment is activated or resumed
                If environmentState = EnvironmentStateEnum.kActivateEnvironmentState Or environmentState = EnvironmentStateEnum.kResumeEnvironmentState Then
                    m_rackFaceCmd.ButtonDefinition.Enabled = True
                End If

                ' Disable the "Rack Face" button when the part environment is terminated or suspended
                If environmentState = EnvironmentStateEnum.kTerminateEnvironmentState Or environmentState = EnvironmentStateEnum.kSuspendEnvironmentState Then
                    m_rackFaceCmd.ButtonDefinition.Enabled = False
                End If
            End If

            handlingCode = HandlingCodeEnum.kEventNotHandled

        Catch
        End Try

    End Sub

    Public Sub UserInterfaceEvents_OnResetRibbonInterface(ByVal context As NameValueMap)

        Try
            Dim userInterfaceMgr As UserInterfaceManager = m_inventorApp.UserInterfaceManager

            'Get the ribbons associated with part documents
            Dim ribbons As Ribbons = userInterfaceMgr.Ribbons
            Dim partRibbon As Ribbon = ribbons("Part")

            'Get the tabs associated with part ribbon
            Dim ribbonTabs As RibbonTabs = partRibbon.RibbonTabs
            Dim modelRibbonTab As RibbonTab = ribbonTabs("id_TabModel")

            'Get the panels within Model tab
            Dim ribbonPanels As RibbonPanels = modelRibbonTab.RibbonPanels
            Dim modifyRibbonPanel As RibbonPanel = ribbonPanels("id_PanelP_ModelModify")

            'Add controls to the Modify panel
            Dim modifyRibbonPanelCtrls As CommandControls = modifyRibbonPanel.CommandControls

            'Add button to the Modify panel
            Dim rackFaceCmdBtnDefObj As ButtonDefinitionObject = m_rackFaceCmd.ButtonDefinition
            modifyRibbonPanelCtrls.AddButton(rackFaceCmdBtnDefObj)

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.ToString())
        End Try

    End Sub

#End Region

End Class



