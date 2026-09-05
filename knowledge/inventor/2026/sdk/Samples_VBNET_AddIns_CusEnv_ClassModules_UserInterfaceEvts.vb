Option Strict Off
Option Explicit On
<System.Runtime.InteropServices.ProgId("CustomEnv.UserInterfaceEvts")> Public Class clsUserInterfaceEvts

    Private mobjInventorApp As Inventor.Application
    Private mstrClientID As String

    Private WithEvents mobjUserInterfaceEvents As Inventor.UserInterfaceEvents

    Public Sub New(ByVal objInventorApp As Inventor.Application, ByVal strClientID As String)
        MyBase.New()

        mobjInventorApp = objInventorApp
        mstrClientID = strClientID

        On Error Resume Next

        'get the user interface manager
        Dim objUserInterfaceMgr As Inventor.UserInterfaceManager
        objUserInterfaceMgr = mobjInventorApp.UserInterfaceManager

        'initialize user interface events
        mobjUserInterfaceEvents = objUserInterfaceMgr.UserInterfaceEvents

    End Sub

    Private Sub mobjUserInterfaceEvents_OnEnvironmentChange(ByVal Environment As Inventor.Environment, ByVal EnvironmentState As Inventor.EnvironmentStateEnum, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles mobjUserInterfaceEvents.OnEnvironmentChange

        On Error Resume Next

        Dim objAnalyzeBodyEnv As Inventor.Environment
        objAnalyzeBodyEnv = mobjInventorApp.UserInterfaceManager.Environments("AnalyzeBodyEnv")

        Dim objParallelEnvs As Inventor.EnvironmentList
        Dim lngEnvIndex As Integer
        Dim blnEnvExists As Boolean
        Dim objEnvironment As Inventor.Environment
        Dim objCustomBrowserPane As New clsCustomBrowserPane(mobjInventorApp, mstrClientID)

        Dim lngNewEnvIndex As Integer
        If Environment.InternalName = "PMxPartEnvironment" Then

            If (EnvironmentState = Inventor.EnvironmentStateEnum.kActivateEnvironmentState Or EnvironmentState = Inventor.EnvironmentStateEnum.kResumeEnvironmentState) And BeforeOrAfter = Inventor.EventTimingEnum.kAfter Then

                objParallelEnvs = mobjInventorApp.UserInterfaceManager.ParallelEnvironments


                For lngEnvIndex = 1 To objParallelEnvs.Count
                    objEnvironment = objParallelEnvs(lngEnvIndex)

                    If objEnvironment.InternalName = objAnalyzeBodyEnv.InternalName Then
                        blnEnvExists = True
                        Exit For
                    End If
                Next

                If blnEnvExists = False Then
                    Call mobjInventorApp.UserInterfaceManager.ParallelEnvironments.Add(objAnalyzeBodyEnv)
                End If
            End If

        Else

            If Environment.InternalName = objAnalyzeBodyEnv.InternalName Then

                If (EnvironmentState = Inventor.EnvironmentStateEnum.kActivateEnvironmentState Or EnvironmentState = Inventor.EnvironmentStateEnum.kResumeEnvironmentState) And BeforeOrAfter = Inventor.EventTimingEnum.kAfter Then
                    Call objCustomBrowserPane.ActivateBrepTree(mobjInventorApp.ActiveDocument)
                End If

                If (EnvironmentState = Inventor.EnvironmentStateEnum.kTerminateEnvironmentState Or EnvironmentState = Inventor.EnvironmentStateEnum.kSuspendEnvironmentState) And BeforeOrAfter = Inventor.EventTimingEnum.kAfter Then
                    Call objCustomBrowserPane.ActivateDefaultTree(mobjInventorApp.ActiveDocument)
                End If

            Else

                If (EnvironmentState = Inventor.EnvironmentStateEnum.kActivateEnvironmentState Or EnvironmentState = Inventor.EnvironmentStateEnum.kResumeEnvironmentState) And BeforeOrAfter = Inventor.EventTimingEnum.kAfter Then

                    objParallelEnvs = mobjInventorApp.UserInterfaceManager.ParallelEnvironments


                    For lngEnvIndex = 1 To objParallelEnvs.Count
                        objEnvironment = objParallelEnvs(lngEnvIndex)

                        If objEnvironment.InternalName = objAnalyzeBodyEnv.InternalName Then
                            blnEnvExists = True
                            lngNewEnvIndex = lngEnvIndex
                            Exit For
                        End If
                    Next

                    If blnEnvExists = True Then
                        Call mobjInventorApp.UserInterfaceManager.ParallelEnvironments.Remove(lngNewEnvIndex)
                    End If

                End If
            End If
        End If

    End Sub

    Protected Overrides Sub Finalize()

        'set the user interface events to Nothing
        mobjUserInterfaceEvents = Nothing

        MyBase.Finalize()

    End Sub

    Private Sub mobjUserInterfaceEvents_OnResetCommandBars(ByVal CommandBars As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles mobjUserInterfaceEvents.OnResetCommandBars

        Dim objCommandBar As Inventor.CommandBar
        For Each objCommandBar In CommandBars
            If objCommandBar.InternalName = "AnalyzeBodyFaceCmdBar" Then

                'add buttons to analyze body toolbar
                objCommandBar.Controls.AddButton(mobjInventorApp.CommandManager.ControlDefinitions.Item("MeasureSurfaceBodyCmd"))
                objCommandBar.Controls.AddButton(mobjInventorApp.CommandManager.ControlDefinitions.Item("MeasureFaceCmd"))
                objCommandBar.Controls.AddButton(mobjInventorApp.CommandManager.ControlDefinitions.Item("MeasureEdgeCmd"))

                Exit Sub
            End If
        Next objCommandBar

    End Sub

    Private Sub mobjUserInterfaceEvents_OnResetEnvironments(ByVal Environments As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles mobjUserInterfaceEvents.OnResetEnvironments

        'make the analyze body command bar accessible in the panel menu for the analyze body environment
        Dim objCommandBar As Inventor.CommandBar
        Dim objEnvironment As Inventor.Environment
        For Each objCommandBar In mobjInventorApp.UserInterfaceManager.CommandBars

            'get the analyze body command bar
            If objCommandBar.InternalName = "AnalyzeBodyFaceCmdBar" Then

                For Each objEnvironment In Environments
                    'get the analyze body environment
                    If objEnvironment.InternalName = "AnalyzeBodyEnv" Then

                        'add the command bar to the panel bar of the custom environment
                        Call objEnvironment.PanelBar.CommandBarList.Add(objCommandBar)

                        'make the command bar the default command bar on the panel bar
                        objEnvironment.PanelBar.DefaultCommandBar = objCommandBar

                        'set the default tool bar to the part standard tool bar
                        objEnvironment.DefaultToolBar = mobjInventorApp.UserInterfaceManager.CommandBars.Item("PMxPartStandardCmdBar")

                        'make the command bar available on the context menu list
                        Call objEnvironment.ContextMenuList.Add(objCommandBar)

                        Exit Sub
                    End If
                Next objEnvironment
            End If
        Next objCommandBar

    End Sub

    Private Sub mobjUserInterfaceEvents_OnResetRibbonInterface(ByVal Context As Inventor.NameValueMap) Handles mobjUserInterfaceEvents.OnResetRibbonInterface
        Dim objUIManager As Inventor.UserInterfaceManager
        objUIManager = mobjInventorApp.UserInterfaceManager

        Dim objAnalyzeBodyEnv As Inventor.Environment
        objAnalyzeBodyEnv = mobjInventorApp.UserInterfaceManager.Environments("AnalyzeBodyEnv")

        Dim objPartRibbon As Inventor.Ribbon
        objPartRibbon = objUIManager.Ribbons("Part")

        Dim objAnalyzeBodyTab As Inventor.RibbonTab
        objAnalyzeBodyTab = objPartRibbon.RibbonTabs.Add("Analyze Body", "AnalyzeBodyTab", clsCustomEnvAddIn.mstrAddInCLSID, , , True)

        Dim objAnalyzeBodyPanel As Inventor.RibbonPanel
        objAnalyzeBodyPanel = objAnalyzeBodyTab.RibbonPanels.Add("AnalyzeBody", "AnalyzeBodyPanel", clsCustomEnvAddIn.mstrAddInCLSID)

        objAnalyzeBodyPanel.CommandControls.AddButton(mobjInventorApp.CommandManager.ControlDefinitions.Item("MeasureSurfaceBodyCmd"), True)
        objAnalyzeBodyPanel.CommandControls.AddButton(mobjInventorApp.CommandManager.ControlDefinitions.Item("MeasureFaceCmd"), True)
        objAnalyzeBodyPanel.CommandControls.AddButton(mobjInventorApp.CommandManager.ControlDefinitions.Item("MeasureEdgeCmd"), True)

        Dim sTabs(0) As String
        sTabs(0) = "AnalyzeBodyTab"

        objAnalyzeBodyEnv.AdditionalVisibleRibbonTabs = sTabs
        objAnalyzeBodyEnv.DefaultRibbonTab = objAnalyzeBodyTab
    End Sub
End Class