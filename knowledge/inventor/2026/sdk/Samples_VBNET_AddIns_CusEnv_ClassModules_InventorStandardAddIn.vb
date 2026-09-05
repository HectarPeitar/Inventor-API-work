Imports System.Runtime.InteropServices
<ProgId("CustomEnvAddIn.StandardAddInServer"), _
GuidAttribute("A0CC5D86-D345-461f-9E9D-35C5F699D2CB")> _
Public Class clsCustomEnvAddIn
    Implements Inventor.ApplicationAddInServer

#Region "Data Member"
    Private mobjInventorApp As Inventor.Application
    Private WithEvents mobjMeasureSurfaceBodyCmd As Inventor.ButtonDefinition
    Private WithEvents mobjMeasureFaceCmd As Inventor.ButtonDefinition
    Private WithEvents mobjMeasureEdgeCmd As Inventor.ButtonDefinition

    Private mobjUserInterfaceEvts As clsUserInterfaceEvts
    Private mobjUserInputEvts As clsUserInputEvts
    Private mobjApplicationEvts As clsApplicationEvts

    Public Shared mstrAddInCLSID As String
#End Region

    Private Sub Activate(ByVal AddInSiteObject As Inventor.ApplicationAddInSite, ByVal FirstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

        On Error Resume Next

        'get the Inventor application object
        mobjInventorApp = AddInSiteObject.Application

        'Retrieve the GUID for this class
        Dim AddInCLSID As GuidAttribute
        AddInCLSID = CType(System.Attribute.GetCustomAttribute(GetType(clsCustomEnvAddIn), GetType(GuidAttribute)), GuidAttribute)

        mstrAddInCLSID = "{" & AddInCLSID.Value & "}"

        'connect user interface event sinks
        mobjUserInterfaceEvts = New clsUserInterfaceEvts(mobjInventorApp, mstrAddInCLSID)

        'connect user input event sinks
        mobjUserInputEvts = New clsUserInputEvts(mobjInventorApp)

        'connect application event sinks
        mobjApplicationEvts = New clsApplicationEvts(mobjInventorApp, mstrAddInCLSID)

        'get the control definitions collection
        Dim objControlDefs As Inventor.ControlDefinitions
        objControlDefs = mobjInventorApp.CommandManager.ControlDefinitions

        'load the icons for the commands
        Dim MeasureBodyIconIPictureDisp As Object = System.Type.Missing

        Dim MeasureBodyIconStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("CustomEnvironment.MeasureBody.bmp")
        Dim MeasureBodyIconImage As System.Drawing.Image = New System.Drawing.Bitmap(MeasureBodyIconStream)

        MeasureBodyIconIPictureDisp = ImageToPictureConverter.Convert(MeasureBodyIconImage)

        Dim MeasureFaceIconIPictureDisp As Object = System.Type.Missing

        Dim MeasureFaceIconStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("CustomEnvironment.MeasureFace.bmp")
        Dim MeasureFaceIconImage As System.Drawing.Image = New System.Drawing.Bitmap(MeasureFaceIconStream)

        MeasureFaceIconIPictureDisp = ImageToPictureConverter.Convert(MeasureFaceIconImage)


        Dim MeasureEdgeIconIPictureDisp As Object = System.Type.Missing

        Dim MeasureEdgeIconStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("CustomEnvironment.MeasureEdge.bmp")
        Dim MeasureEdgeIconImage As System.Drawing.Image = New System.Drawing.Bitmap(MeasureEdgeIconStream)

        MeasureEdgeIconIPictureDisp = ImageToPictureConverter.Convert(MeasureEdgeIconImage)

        'create the commands for the environment
        mobjMeasureSurfaceBodyCmd = objControlDefs.AddButtonDefinition("Measure Surface Body", "MeasureSurfaceBodyCmd", Inventor.CommandTypesEnum.kQueryOnlyCmdType, mstrAddInCLSID, , , MeasureBodyIconIPictureDisp, MeasureBodyIconIPictureDisp)
        mobjMeasureFaceCmd = objControlDefs.AddButtonDefinition("Measure Face", "MeasureFaceCmd", Inventor.CommandTypesEnum.kQueryOnlyCmdType, mstrAddInCLSID, , , MeasureFaceIconIPictureDisp, MeasureFaceIconIPictureDisp)
        mobjMeasureEdgeCmd = objControlDefs.AddButtonDefinition("Measure Edge", "MeasureEdgeCmd", Inventor.CommandTypesEnum.kQueryOnlyCmdType, mstrAddInCLSID, , , MeasureEdgeIconIPictureDisp, MeasureEdgeIconIPictureDisp)

        'create the command category
        Dim objCommandCategory As Inventor.CommandCategory
        objCommandCategory = mobjInventorApp.CommandManager.CommandCategories.Add("Analyze Body", "AnalyzeBodyFaceCmdCat", mstrAddInCLSID)

        objCommandCategory.Add(mobjMeasureSurfaceBodyCmd)
        objCommandCategory.Add(mobjMeasureFaceCmd)
        objCommandCategory.Add(mobjMeasureEdgeCmd)

        Dim objUserInterfaceMgr As Inventor.UserInterfaceManager
        Dim objEnvironments As Inventor.Environments
        Dim objAnalyzeBodyEnv As Inventor.Environment
        Dim objCommandBars As Inventor.CommandBars
        Dim objAnalyzeBodyCmdBar As Inventor.CommandBar
        If FirstTime = True Then

            'get the user interface manager
            objUserInterfaceMgr = mobjInventorApp.UserInterfaceManager

            'create the new environment
            objEnvironments = objUserInterfaceMgr.Environments
            objAnalyzeBodyEnv = objEnvironments("AnalyzeBodyEnv")
            If objAnalyzeBodyEnv Is Nothing Then
                objAnalyzeBodyEnv = objEnvironments.Add("AnalyzeBody", "AnalyzeBodyEnv", mstrAddInCLSID)
            End If

            If objUserInterfaceMgr.InterfaceStyle = Inventor.InterfaceStyleEnum.kRibbonInterface Then
                Dim objPartRibbon As Inventor.Ribbon
                objPartRibbon = objUserInterfaceMgr.Ribbons("Part")

                Dim objAnalyzeBodyTab As Inventor.RibbonTab
                objAnalyzeBodyTab = objPartRibbon.RibbonTabs.Add("Analyze Body", "AnalyzeBodyTab", mstrAddInCLSID, , , True)

                Dim objAnalyzeBodyPanel As Inventor.RibbonPanel
                objAnalyzeBodyPanel = objAnalyzeBodyTab.RibbonPanels.Add("Analyze Body", "AnalyzeBodyPanel", mstrAddInCLSID)

                objAnalyzeBodyPanel.CommandControls.AddButton(mobjMeasureSurfaceBodyCmd, True)
                objAnalyzeBodyPanel.CommandControls.AddButton(mobjMeasureFaceCmd, True)
                objAnalyzeBodyPanel.CommandControls.AddButton(mobjMeasureEdgeCmd, True)

                Dim sTabs(0) As String
                sTabs(0) = "AnalyzeBodyTab"

                objAnalyzeBodyEnv.AdditionalVisibleRibbonTabs = sTabs
                objAnalyzeBodyEnv.DefaultRibbonTab = "AnalyzeBodyTab"
                objAnalyzeBodyEnv.ContextMenuList.Add(objAnalyzeBodyCmdBar)
            Else
                'create the command bar for the environment
                objCommandBars = objUserInterfaceMgr.CommandBars

                objAnalyzeBodyCmdBar = objCommandBars.Add("Analyze Body", "AnalyzeBodyFaceCmdBar", Inventor.CommandBarTypeEnum.kRegularCommandBar, mstrAddInCLSID)

                'add the commands to the command bar
                Call objAnalyzeBodyCmdBar.Controls.AddButton(mobjMeasureSurfaceBodyCmd)
                Call objAnalyzeBodyCmdBar.Controls.AddButton(mobjMeasureFaceCmd)
                Call objAnalyzeBodyCmdBar.Controls.AddButton(mobjMeasureEdgeCmd)

                If Not objAnalyzeBodyEnv Is Nothing Then

                    'add the command bar to the panel bar of the custom environment
                    Call objAnalyzeBodyEnv.PanelBar.CommandBarList.Add(objAnalyzeBodyCmdBar)

                    'make the command bar the default command bar on the panel bar
                    objAnalyzeBodyEnv.PanelBar.DefaultCommandBar = objAnalyzeBodyCmdBar

                    'set the default tool bar to the part standard tool bar
                    objAnalyzeBodyEnv.DefaultToolBar = objCommandBars.Item("PMxPartStandardCmdBar")

                    'make the command bar available on the context menu list
                    Call objAnalyzeBodyEnv.ContextMenuList.Add(objAnalyzeBodyCmdBar)

                End If

            End If

        End If
        'make the commands available on the context menu in the graphics window
        Call mobjUserInputEvts.AddCmdToEnvContextMenu(mobjMeasureSurfaceBodyCmd, "AnalyzeBodyEnv")
        Call mobjUserInputEvts.AddCmdToEnvContextMenu(mobjMeasureFaceCmd, "AnalyzeBodyEnv")
        Call mobjUserInputEvts.AddCmdToEnvContextMenu(mobjMeasureEdgeCmd, "AnalyzeBodyEnv")

    End Sub

    Private ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation
        Get

            Automation = Nothing

        End Get
    End Property

    Private Sub ExecuteCommand(ByVal CommandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand
        '
    End Sub


    'implementation of the commands
    Private Sub mobjMeasureSurfaceBodyCmd_OnExecute(ByVal Context As Inventor.NameValueMap) Handles mobjMeasureSurfaceBodyCmd.OnExecute

        On Error Resume Next

        Dim objInteraction As New clsInteraction(mobjInventorApp)

        Dim objSurfaceBody As Inventor.SurfaceBody
        objSurfaceBody = objInteraction.SelectEntity(Inventor.SelectionFilterEnum.kPartBodyFilter)

        Dim frmEntityInfo As New frmEntityInformation
        If Not objSurfaceBody Is Nothing Then
            Call frmEntityInfo.DisplaySurfaceBodyInformation(objSurfaceBody)
        End If

    End Sub

    Private Sub mobjMeasureFaceCmd_OnExecute(ByVal Context As Inventor.NameValueMap) Handles mobjMeasureFaceCmd.OnExecute

        On Error Resume Next

        Dim objInteraction As New clsInteraction(mobjInventorApp)

        Dim objSelectedFace As Inventor.Face
        objSelectedFace = objInteraction.SelectEntity(Inventor.SelectionFilterEnum.kPartFaceFilter)

        Dim frmEntityInfo As New frmEntityInformation
        If Not objSelectedFace Is Nothing Then
            Call frmEntityInfo.DisplayFaceInformation(objSelectedFace)
        End If

    End Sub

    Private Sub mobjMeasureEdgeCmd_OnExecute(ByVal Context As Inventor.NameValueMap) Handles mobjMeasureEdgeCmd.OnExecute

        On Error Resume Next

        Dim objInteraction As New clsInteraction(mobjInventorApp)

        Dim objSelectedEdge As Inventor.Edge
        objSelectedEdge = objInteraction.SelectEntity(Inventor.SelectionFilterEnum.kPartEdgeFilter)

        Dim frmEntityInfo As New frmEntityInformation
        If Not objSelectedEdge Is Nothing Then
            Call frmEntityInfo.DisplayEdgeInformation(objSelectedEdge)
        End If

    End Sub

    Private Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

        'disconnect event sinks
        mobjUserInterfaceEvts = Nothing

        mobjUserInputEvts = Nothing

        mobjApplicationEvts = Nothing

        mobjMeasureSurfaceBodyCmd = Nothing
        mobjMeasureFaceCmd = Nothing
        mobjMeasureEdgeCmd = Nothing

        'release references to objects
        Marshal.ReleaseComObject(mobjInventorApp)
        mobjInventorApp = Nothing

        GC.WaitForPendingFinalizers()
        GC.Collect()

    End Sub

#Region "COM Registration"

    ' Registers this class as an Add-In for Autodesk Inventor.
    ' This function is called when the assembly is registered for COM.
    <System.Runtime.InteropServices.ComRegisterFunction()> _
    Public Shared Sub RegisterFunction(ByVal t As Type)

        'call the method in the AddInRegistration class to register the AddIn
        AddInRegistration.RegisterInventorAddIn(t)

    End Sub

    ' Unregisters this class as an Add-In for Autodesk Inventor.
    ' This function is called when the assembly is unregistered.
    <System.Runtime.InteropServices.ComUnregisterFunction()> _
    Public Shared Sub UnregisterFunction(ByVal t As Type)

        'call the method in the AddInRegistration class to unregister the AddIn
        AddInRegistration.UnregisterInventorAddIn(t)

    End Sub

#End Region

End Class

#Region "ImageToPictureConverter"
Public NotInheritable Class ImageToPictureConverter
    Inherits System.Windows.Forms.AxHost

    Private Sub New()
        MyBase.New(Nothing)
    End Sub

    Public Shared Function Convert(ByVal image As System.Drawing.Image) As stdole.IPictureDisp
        Return CType(System.Windows.Forms.AxHost.GetIPictureDispFromPicture(image), stdole.IPictureDisp)
    End Function

End Class
#End Region