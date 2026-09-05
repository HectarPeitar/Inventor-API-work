Imports Inventor
Imports System.Runtime.InteropServices
Imports Microsoft.Win32
<ProgId("Analyze.StandardAddInServer"), _
GuidAttribute("AFEBDB0D-C529-4f55-94E7-E7B87807F5A4")> _
Public Class StandardAddInServer
    Implements Inventor.ApplicationAddInServer

#Region "Data Members"

    Private m_InventorApp As Inventor.Application

    Private m_Analyses As Analyses

    Private WithEvents m_ParamsButtonDef As Inventor.ButtonDefinition
    Private WithEvents m_RunAnalysisButtonDef As Inventor.ButtonDefinition

    Private WithEvents m_UserInterfaceEvents As Inventor.UserInterfaceEvents

    Private m_ParamForm As ParametersForm
#End Region

#Region "ApplicationAddInServer Members"

    Private Sub Activate(ByVal AddInSiteObject As Inventor.ApplicationAddInSite, ByVal FirstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

        ' Set a reference to the Inventor Application object.
        m_InventorApp = AddInSiteObject.Application

        ' Set a reference to the Analyses object.
        m_Analyses = New Analyses(m_InventorApp)

        ' Set a reference to the user interface events.
        m_UserInterfaceEvents = m_InventorApp.UserInterfaceManager.UserInterfaceEvents

        Dim ThisGuidString As String = ""
        Try
            'retrieve the GUID for this class
            Dim ThisGuid As GuidAttribute
            ThisGuid = CType(System.Attribute.GetCustomAttribute(GetType(StandardAddInServer), GetType(GuidAttribute)), GuidAttribute)
            ThisGuidString = "{" & ThisGuid.Value & "}"
        Catch
        End Try

        Dim AnalysisIconIPictureDisp As Object = System.Type.Missing
        Dim ParamsIconPictureDisp As Object = System.Type.Missing

        Try
            Dim AnalysisIconStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("Analyze.Params.BMP")
            Dim AnalysisIconImage As System.Drawing.Image = New System.Drawing.Bitmap(AnalysisIconStream)

            AnalysisIconIPictureDisp = ImageToPictureConverter.Convert(AnalysisIconImage)
        Catch ex As Exception
        End Try

        Try
            Dim ParamsIconStream As System.IO.Stream = Me.GetType().Assembly.GetManifestResourceStream("Analyze.Analysis.BMP")
            Dim ParamsIconImage As System.Drawing.Image = New System.Drawing.Bitmap(ParamsIconStream)

            ParamsIconPictureDisp = ImageToPictureConverter.Convert(ParamsIconImage)
        Catch ex As Exception
        End Try

        'create the button to define analysis parameters
        m_ParamsButtonDef = m_InventorApp.CommandManager.ControlDefinitions.AddButtonDefinition("Define Analysis Parameters", "DefineParamsCmdIntName", Inventor.CommandTypesEnum.kNonShapeEditCmdType, ThisGuidString, "Define Analysis Parameters", "Define Analysis Parameters", ParamsIconPictureDisp, ParamsIconPictureDisp)

        'create the button to run analysis
        m_RunAnalysisButtonDef = m_InventorApp.CommandManager.ControlDefinitions.AddButtonDefinition("Run Analysis", "RunAnalysisCmdIntName", Inventor.CommandTypesEnum.kShapeEditCmdType, ThisGuidString, "Run Analysis", "Run Analysis", AnalysisIconIPictureDisp, AnalysisIconIPictureDisp)

        'enable the buttons
        m_ParamsButtonDef.Enabled = True
        m_RunAnalysisButtonDef.Enabled = True

        'create the command category
        Dim CommandCategory As Inventor.CommandCategory
        CommandCategory = m_InventorApp.CommandManager.CommandCategories.Add("Analyze Mechanism", "AnalyzeMechanismCmdCatIntName", "{5F0B44BA-6655-49E6-8B9E-F1E67535B730}")

        CommandCategory.Add(m_ParamsButtonDef)
        CommandCategory.Add(m_RunAnalysisButtonDef)

        'if AddIn is called first time, toolbar and add button to toolbar
        Dim CommandBar As Inventor.CommandBar
        Dim AssemEnv As Inventor.Environment
        If FirstTime = True Then

            'create a new toolbar
            CommandBar = m_InventorApp.UserInterfaceManager.CommandBars.Add("Analyze Mechanism", "AnalyzeMechanismToolbarIntName", , "{5F0B44BA-6655-49E6-8B9E-F1E67535B730}")

            'add the buttons to the toolbar
            CommandBar.Controls.AddButton(m_ParamsButtonDef)
            CommandBar.Controls.AddButton(m_RunAnalysisButtonDef)

            'add the toolbar to the panel bar for the assembly environment
            AssemEnv = m_InventorApp.UserInterfaceManager.Environments.Item("AMxAssemblyEnvironment")
            Call AssemEnv.PanelBar.CommandBarList.Add(CommandBar)

        End If

    End Sub

    Private ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation
        Get
            Return Nothing
        End Get
    End Property

    Private Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

        ' Release all references.
        If Not m_Analyses.ActiveCase Is Nothing Then
            m_Analyses.ActiveCase = Nothing
        End If

        m_Analyses = Nothing

        'delete the button definitions
        m_ParamsButtonDef.Delete()
        m_RunAnalysisButtonDef.Delete()

        m_ParamsButtonDef = Nothing
        m_RunAnalysisButtonDef = Nothing

        m_ParamForm.Close()

        Marshal.ReleaseComObject(m_InventorApp)
        m_InventorApp = Nothing

        GC.WaitForPendingFinalizers()
        GC.Collect()

    End Sub

    Private Sub ExecuteCommand(ByVal CommandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand
        ' not used
    End Sub
#End Region

    Private Sub ParamsButtonDef_OnExecute(ByVal Context As Inventor.NameValueMap) Handles m_ParamsButtonDef.OnExecute

        'get the active document
        Dim m_Doc As Inventor.Document
        m_Doc = m_InventorApp.ActiveDocument

        If m_Doc Is Nothing Then
            MsgBox("Please open an assembly document first")
            Exit Sub
        End If

        'set the active case for the current document
        Dim ActiveCase As Analysis
        ActiveCase = m_Analyses.SetActiveCase(m_Doc)

        'display the parameters dialog
        m_ParamForm = New ParametersForm(m_InventorApp, m_Analyses)
        m_ParamForm.ShowDialog()

        'check to see if analysis can be enabled
        If ActiveCase.IsAnalysisReady Then
            ActiveCase.IsAnalysisEnabled = True
        Else
            ActiveCase.IsAnalysisEnabled = False
        End If

    End Sub

    Private Sub RunAnalysisButtonDef_OnExecute(ByVal Context As Inventor.NameValueMap) Handles m_RunAnalysisButtonDef.OnExecute

        'get the active document
        Dim m_Doc As Inventor.Document
        m_Doc = m_InventorApp.ActiveDocument

        If m_Doc Is Nothing Then
            MsgBox("Please open an assembly document first")
            Exit Sub
        End If

        Call m_Analyses.SetActiveCase(m_Doc)

        'make sure the correct browser pane is displayed
        m_Analyses.ActiveCase.ShowBrowser()

    End Sub

    Private Sub UserInterfaceEvents_OnResetCommandBars(ByVal CommandBars As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetCommandBars

        Dim CommandBar As Inventor.CommandBar
        For Each CommandBar In CommandBars
            If CommandBar.InternalName = "AnalyzeMechanismToolbarIntName" Then

                'add buttons to analyze mechanism toolbar
                CommandBar.Controls.AddButton(m_ParamsButtonDef)
                CommandBar.Controls.AddButton(m_RunAnalysisButtonDef)

                Exit Sub
            End If
        Next CommandBar

    End Sub

    Private Sub UserInterfaceEvents_OnResetEnvironments(ByVal Environments As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetEnvironments

        'make the analyze mechanism command bar accessible in the panel menu for the assembly
        Dim CommandBar As Inventor.CommandBar
        Dim Environment As Inventor.Environment
        For Each CommandBar In m_InventorApp.UserInterfaceManager.CommandBars

            'get the analyze mechanism command bar
            If CommandBar.InternalName = "AnalyzeMechanismToolbarIntName" Then

                For Each Environment In Environments
                    'get the assembly environment
                    If Environment.InternalName = "AMxAssemblyEnvironment" Then

                        'make the command bar accessible in the panel menu for the assembly environment
                        Environment.PanelBar.CommandBarList.Add(CommandBar)

                        Exit Sub
                    End If
                Next Environment
            End If
        Next CommandBar

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