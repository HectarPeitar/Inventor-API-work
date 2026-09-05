Imports Inventor
Imports System.Drawing
Imports System.Windows.Forms
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

Namespace SimpleAddIn
    <ProgIdAttribute("SimpleAddIn.StandardAddInServer"), _
    GuidAttribute("E6EA2F87-0494-4C0D-9E05-63DEB55637FB")> _
    Public Class StandardAddInServer
        Implements Inventor.ApplicationAddInServer

#Region "Data Members"

        Private m_inventorApplication As Inventor.Application

        'buttons
        Private m_addSlotOptionButton As AddSlotOptionButton
        Private m_drawSlotButton As DrawSlotButton
        Private m_toggleSlotStateButton As ToggleSlotStateButton

        'combo-boxes
        Private m_slotWidthComboBoxDefinition As ComboBoxDefinition
        Private m_slotHeightComboBoxDefinition As ComboBoxDefinition

        'events
        Private m_userInterfaceEvents As UserInterfaceEvents

        ' ribbon panel
        Private m_partSketchSlotRibbonPanel As RibbonPanel

#End Region

#Region "ApplicationAddInServer Members"

        Public Sub Activate(ByVal addInSiteObject As Inventor.ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

            Try
                'the Activate method is called by Inventor when it loads the addin
                'the AddInSiteObject provides access to the Inventor Application object
                'the FirstTime flag indicates if the addin is loaded for the first time

                'initialize AddIn members
                m_inventorApplication = addInSiteObject.Application
                Button.InventorApplication = m_inventorApplication

                'initialize event handlers
                m_userInterfaceEvents = m_inventorApplication.UserInterfaceManager.UserInterfaceEvents

                AddHandler m_userInterfaceEvents.OnResetCommandBars, AddressOf Me.UserInterfaceEvents_OnResetCommandBars
                AddHandler m_userInterfaceEvents.OnResetEnvironments, AddressOf Me.UserInterfaceEvents_OnResetEnvironments
                AddHandler m_userInterfaceEvents.OnResetRibbonInterface, AddressOf Me.UserInterfaceEvents_OnResetRibbonInterface

                'load image icons for UI items
                Dim addSlotOptionImageStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("SimpleAddIn.AddSlotOption.ico")
                Dim addSlotOptionIcon As Icon = New Icon(addSlotOptionImageStream)

                Dim drawSlotImageStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("SimpleAddIn.DrawSlot.ico")
                Dim drawSlotIcon As Icon = New Icon(drawSlotImageStream)

                Dim toggleSlotStateImageStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("SimpleAddIn.ToggleSlotState.ico")
                Dim toggleSlotStateIcon As Icon = New Icon(toggleSlotStateImageStream)

                'retrieve the GUID for this class
                Dim addInCLSID As GuidAttribute
                addInCLSID = CType(System.Attribute.GetCustomAttribute(GetType(StandardAddInServer), GetType(GuidAttribute)), GuidAttribute)
                Dim addInCLSIDString As String
                addInCLSIDString = "{" & addInCLSID.Value & "}"

                'create the comboboxes
                m_slotWidthComboBoxDefinition = m_inventorApplication.CommandManager.ControlDefinitions.AddComboBoxDefinition("Slot Width", "Autodesk:SimpleAddIn:SlotWidthCboBox", CommandTypesEnum.kShapeEditCmdType, 100, addInCLSIDString, "Specifies slot width", "Slot width")
                m_slotHeightComboBoxDefinition = m_inventorApplication.CommandManager.ControlDefinitions.AddComboBoxDefinition("Slot Height", "Autodesk:SimpleAddIn:SlotHeightCboBox", CommandTypesEnum.kShapeEditCmdType, 100, addInCLSIDString, "Specifies slot height", "Slot height")

                'add some initial items to the comboboxes
                m_slotWidthComboBoxDefinition.AddItem("1 cm", 0)
                m_slotWidthComboBoxDefinition.AddItem("2 cm", 0)
                m_slotWidthComboBoxDefinition.AddItem("3 cm", 0)
                m_slotWidthComboBoxDefinition.AddItem("4 cm", 0)
                m_slotWidthComboBoxDefinition.AddItem("5 cm", 0)
                m_slotWidthComboBoxDefinition.ListIndex = 1

                m_slotHeightComboBoxDefinition.AddItem("1 cm", 0)
                m_slotHeightComboBoxDefinition.AddItem("2 cm", 0)
                m_slotHeightComboBoxDefinition.AddItem("3 cm", 0)
                m_slotHeightComboBoxDefinition.AddItem("4 cm", 0)
                m_slotHeightComboBoxDefinition.AddItem("5 cm", 0)
                m_slotHeightComboBoxDefinition.ListIndex = 1

                'create buttons
                m_addSlotOptionButton = New AddSlotOptionButton("Add Slot width/height", "Autodesk:SimpleAddIn:AddSlotOptionCmdBtn", CommandTypesEnum.kShapeEditCmdType, _
                 addInCLSIDString, "Adds option for slot width/height", "Add slot option", addSlotOptionIcon, addSlotOptionIcon)

                m_drawSlotButton = New DrawSlotButton("Draw Slot", "Autodesk:SimpleAddIn:DrawSlotCmdBtn", CommandTypesEnum.kShapeEditCmdType, _
                 addInCLSIDString, "Create slot sketch graphics", "Draw Slot", drawSlotIcon, drawSlotIcon)

                m_toggleSlotStateButton = New ToggleSlotStateButton("Toggle Slot State", "Autodesk:SimpleAddIn:ToggleSlotStateCmdBtn", CommandTypesEnum.kShapeEditCmdType, _
                 addInCLSIDString, "Enables/Disables state of slot command", "Toggle Slot State", toggleSlotStateIcon, toggleSlotStateIcon)

                'create the command category
                Dim slotCmdCategory As CommandCategory = m_inventorApplication.CommandManager.CommandCategories.Add("Slot", "Autodesk:SimpleAddIn:SlotCmdCat", addInCLSIDString)

                slotCmdCategory.Add(m_slotWidthComboBoxDefinition)
                slotCmdCategory.Add(m_slotHeightComboBoxDefinition)
                slotCmdCategory.Add(m_addSlotOptionButton.ButtonDefinition)
                slotCmdCategory.Add(m_drawSlotButton.ButtonDefinition)
                slotCmdCategory.Add(m_toggleSlotStateButton.ButtonDefinition)
               
                If firstTime = True Then

                    'access user interface manager
                    Dim userInterfaceManager As UserInterfaceManager
                    userInterfaceManager = m_inventorApplication.UserInterfaceManager

                    Dim interfaceStyle As InterfaceStyleEnum
                    interfaceStyle = userInterfaceManager.InterfaceStyle

                    m_partSketchSlotRibbonPanel = Nothing

                    ' create the UI for classic interface
                    If interfaceStyle = InterfaceStyleEnum.kClassicInterface Then
                        'create toolbar
                        Dim slotCommandBar As CommandBar
                        slotCommandBar = userInterfaceManager.CommandBars.Add("Slot", "Autodesk:SimpleAddIn:SlotToolbar", , addInCLSIDString)

                        'add comboboxes to toolbar
                        slotCommandBar.Controls.AddComboBox(m_slotWidthComboBoxDefinition)
                        slotCommandBar.Controls.AddComboBox(m_slotHeightComboBoxDefinition)

                        'add buttons to toolbar
                        slotCommandBar.Controls.AddButton(m_addSlotOptionButton.ButtonDefinition)
                        slotCommandBar.Controls.AddButton(m_drawSlotButton.ButtonDefinition)
                        slotCommandBar.Controls.AddButton(m_toggleSlotStateButton.ButtonDefinition)

                        'get the 2d sketch environment base object
                        Dim partSketchEnvironment As Inventor.Environment
                        partSketchEnvironment = userInterfaceManager.Environments.Item("PMxPartSketchEnvironment")

                        'make this command bar accessible in the panel menu for the 2d sketch environment
                        partSketchEnvironment.PanelBar.CommandBarList.Add(slotCommandBar)

                        'create UI for ribbon interface
                    Else
                        ' get the ribbon associated with part document
                        Dim ribbons As Ribbons
                        ribbons = userInterfaceManager.Ribbons

                        Dim partRibbon As Ribbon
                        partRibbon = ribbons.Item("Part")

                        ' get the tabs associated with part ribbon
                        Dim ribbonTabs As RibbonTabs
                        ribbonTabs = partRibbon.RibbonTabs

                        Dim partSketchRibbonTab As RibbonTab
                        partSketchRibbonTab = ribbonTabs.Item("id_TabSketch")

                        ' create a new panel within the tab
                        Dim ribbonPanels As RibbonPanels
                        ribbonPanels = partSketchRibbonTab.RibbonPanels

                        'Dim m_partSketchSlotRibbonPanel As RibbonPanel
                        m_partSketchSlotRibbonPanel = ribbonPanels.Add("Slot", "Autodesk:SimpleAddIn:SlotRibbonPanel", "{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}", "", False)

                        ' add controls to the slot panel
                        Dim partSketchSlotRibbonPanelCtrls As CommandControls
                        partSketchSlotRibbonPanelCtrls = m_partSketchSlotRibbonPanel.CommandControls

                        ' add the combo boxes to the ribbon panel
                        Dim slotWidthCmdCboBoxCmdCtrl As CommandControl
                        slotWidthCmdCboBoxCmdCtrl = partSketchSlotRibbonPanelCtrls.AddComboBox(m_slotWidthComboBoxDefinition, "", False)

                        Dim slotHeightCmdCboBoxCmdCtrl As CommandControl
                        slotHeightCmdCboBoxCmdCtrl = partSketchSlotRibbonPanelCtrls.AddComboBox(m_slotHeightComboBoxDefinition, "", False)

                        ' add the buttons to the ribbon panel
                        Dim drawSlotCmdBtnCmdCtrl As CommandControl
                        drawSlotCmdBtnCmdCtrl = partSketchSlotRibbonPanelCtrls.AddButton(m_drawSlotButton.ButtonDefinition, False, True, "", False)


                        Dim slotOptionCmdBtnCmdCtrl As CommandControl
                        slotOptionCmdBtnCmdCtrl = partSketchSlotRibbonPanelCtrls.AddButton(m_addSlotOptionButton.ButtonDefinition, False, True, "", False)

                        Dim toggleSlotStateCmdBtnCmdCtrl As CommandControl
                        toggleSlotStateCmdBtnCmdCtrl = partSketchSlotRibbonPanelCtrls.AddButton(m_toggleSlotStateButton.ButtonDefinition, False, True, "", False)



                    End If
                End If
                MessageBox.Show("To access the commands of the sample addin, activate a 2d sketch of a part" & vbNewLine & _
                                "document and select the ""AddInSlot"" toolbar within the panel menu")

            Catch ex As Exception
                MessageBox.Show(ex.ToString)
            End Try

        End Sub

        Public Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

            'the Deactivate method is called by Inventor when the AddIn is unloaded
            'the AddIn will be unloaded either manually by the user or
            'when the Inventor session is terminated

            Try
                'release objects
                RemoveHandler m_userInterfaceEvents.OnResetCommandBars, AddressOf Me.UserInterfaceEvents_OnResetCommandBars
                RemoveHandler m_userInterfaceEvents.OnResetEnvironments, AddressOf Me.UserInterfaceEvents_OnResetEnvironments

                m_addSlotOptionButton = Nothing
                m_drawSlotButton = Nothing
                m_toggleSlotStateButton = Nothing
                If Not m_partSketchSlotRibbonPanel Is Nothing Then m_partSketchSlotRibbonPanel.Delete()
                m_userInterfaceEvents = Nothing

                Marshal.ReleaseComObject(m_inventorApplication)
                m_InventorApplication = Nothing

                System.GC.WaitForPendingFinalizers()
                System.GC.Collect()

            Catch ex As Exception
                MessageBox.Show(ex.ToString)
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

        Public Sub ExecuteCommand(ByVal CommandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand

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
                    If commandBar.InternalName = "Autodesk:SimpleAddIn:SlotToolbar" Then

                        'add comboboxes to toolbar
                        commandBar.Controls.AddComboBox(m_slotWidthComboBoxDefinition)
                        commandBar.Controls.AddComboBox(m_slotHeightComboBoxDefinition)

                        'add buttons to toolbar
                        commandBar.Controls.AddButton(m_addSlotOptionButton.ButtonDefinition)
                        commandBar.Controls.AddButton(m_drawSlotButton.ButtonDefinition)
                        commandBar.Controls.AddButton(m_toggleSlotStateButton.ButtonDefinition)

                        Exit Sub
                    End If
                Next

            Catch
            End Try

        End Sub

        Public Sub UserInterfaceEvents_OnResetEnvironments(ByVal environments As ObjectsEnumerator, ByVal context As NameValueMap)

            Try
                Dim environment As Environment
                For Each environment In environments
                    'get the 2d sketch environment
                    If environment.InternalName = "PMxPartSketchEnvironment" Then

                        'make the command bar accessible in the panel menu for the 2d sketch environment
                        environment.PanelBar.CommandBarList.Add(m_inventorApplication.UserInterfaceManager.CommandBars.Item("Autodesk:SimpleAddIn:SlotToolbar"))

                        Exit Sub
                    End If
                Next
            Catch
            End Try

        End Sub

        Public Sub UserInterfaceEvents_OnResetRibbonInterface(ByVal Context As Inventor.NameValueMap)
            ' get UserInterfaceManager
            Dim userInterfaceManager As UserInterfaceManager
            userInterfaceManager = m_inventorApplication.UserInterfaceManager

            ' get the ribbon associated with part documents
            Dim ribbons As Ribbons
            ribbons = userInterfaceManager.Ribbons

            Dim partRibbon As Ribbon
            partRibbon = ribbons.Item("Part")

            ' get the tabs associated with part ribbon
            Dim ribbonTabs As RibbonTabs
            ribbonTabs = partRibbon.RibbonTabs

            Dim partSketchRibbonTab As RibbonTab
            partSketchRibbonTab = ribbonTabs.Item("id_TabSketch")

            ' create a new panel within the tab
            Dim ribbonPanels As RibbonPanels
            ribbonPanels = partSketchRibbonTab.RibbonPanels

            Dim partSketchSlotRibbonPanel As RibbonPanel
            partSketchSlotRibbonPanel = ribbonPanels.Add("Slot", "Autodesk:SimpleAddIn:SlotRibbonPanel", "{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}", "", False)

            ' add controls to the slot panel
            Dim partSketchSlotRibbonPanelCtrls As CommandControls
            partSketchSlotRibbonPanelCtrls = partSketchSlotRibbonPanel.CommandControls

            ' add the combo boxes to the ribbon panel
            Dim slotWidthCmdCboBoxCmdCtrl As CommandControl
            slotWidthCmdCboBoxCmdCtrl = partSketchSlotRibbonPanelCtrls.AddComboBox(m_slotWidthComboBoxDefinition, "", False)

            Dim slotHeightCmdCboBoxCmdCtrl As CommandControl
            slotHeightCmdCboBoxCmdCtrl = partSketchSlotRibbonPanelCtrls.AddComboBox(m_slotHeightComboBoxDefinition, "", False)

            ' add the buttons to the ribbon panel
            Dim drawSlotCmdBtnCmdCtrl As CommandControl
            drawSlotCmdBtnCmdCtrl = partSketchSlotRibbonPanelCtrls.AddButton(m_drawSlotButton.ButtonDefinition, False, True, "", False)


            Dim slotOptionCmdBtnCmdCtrl As CommandControl
            slotOptionCmdBtnCmdCtrl = partSketchSlotRibbonPanelCtrls.AddButton(m_addSlotOptionButton.ButtonDefinition, False, True, "", False)

            Dim toggleSlotStateCmdBtnCmdCtrl As CommandControl
            toggleSlotStateCmdBtnCmdCtrl = partSketchSlotRibbonPanelCtrls.AddButton(m_toggleSlotStateButton.ButtonDefinition, False, True, "", False)
        End Sub
#End Region


    End Class

End Namespace

