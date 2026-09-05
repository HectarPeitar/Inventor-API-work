Imports Inventor

Public Class frmEventWatcher
    Private m_EventList As New InventorEvents

    Private m_App As Inventor.Application = Nothing
    Private m_Document As Inventor.Document = Nothing
    Private m_LoadingForm As Boolean = False

    Private WithEvents m_ApplicationEvents As Inventor.ApplicationEvents = Nothing
    Private WithEvents m_AssemblyEvents As Inventor.AssemblyEvents = Nothing
    Private WithEvents m_BrowserPane As Inventor.BrowserPane = Nothing
    Private WithEvents m_BrowserPanesEvents As Inventor.BrowserPanesEvents = Nothing
    Private WithEvents m_CameraEvents As Inventor.CameraEvents = Nothing
    Private WithEvents m_DockableWindowsEvents As Inventor.DockableWindowsEvents = Nothing
    Private WithEvents m_DocumentEvents As Inventor.DocumentEvents = Nothing
    Private WithEvents m_DrawingEvents As Inventor.DrawingEvents = Nothing
    Private WithEvents m_DrawingViewEvents As Inventor.DrawingViewEvents = Nothing
    Private WithEvents m_FileAccessEvents As Inventor.FileAccessEvents = Nothing
    Private WithEvents m_FileDialogEvents As Inventor.FileDialogEvents = Nothing
    Private WithEvents m_FileManagerEvents As Inventor.FileManagerEvents = Nothing
    Private WithEvents m_FileUIEvents As Inventor.FileUIEvents = Nothing
    Private WithEvents m_HelpEvents As Inventor.HelpEvents = Nothing
    Private WithEvents m_ModelingEvents As Inventor.ModelingEvents = Nothing
    Private WithEvents m_ModelStateEvents As Inventor.ModelStateEvents = Nothing
    'Private WithEvents m_PanelBar As Inventor.PanelBar = Nothing
    Private WithEvents m_PartEvents As Inventor.PartEvents = Nothing
    Private WithEvents m_RepresentationEvents As Inventor.RepresentationEvents = Nothing
    Private WithEvents m_SearchBoxEvents As Inventor.SearchBoxEvents = Nothing
    Private WithEvents m_SketchEvents As Inventor.SketchEvents = Nothing
    Private WithEvents m_StyleEvents As Inventor.StyleEvents = Nothing
    Private WithEvents m_TransactionEvents As Inventor.TransactionEvents = Nothing
    Private WithEvents m_UserInputEvents As Inventor.UserInputEvents = Nothing
    Private WithEvents m_UserInterfaceEvents As Inventor.UserInterfaceEvents = Nothing

    Private m_Labels(5) As Label
    Private m_Filenames(4) As System.Windows.Forms.TextBox

    Private Sub frmEventWatcher_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Try
            m_App = CType(GetObject(, "Inventor.Application"), Inventor.Application)
        Catch ex As Exception
            MsgBox("Inventor must be running.")
            End
        End Try

        Dim currentEvent As InventorEvent
        For Each currentEvent In m_EventList
            Me.chkEventList.Items.Add(currentEvent.ObjectName & "." & currentEvent.EventName, False)
        Next

        m_Labels(0) = lblArgument1
        m_Labels(1) = lblArgument2
        m_Labels(2) = lblArgument3
        m_Labels(3) = lblArgument4
        m_Labels(4) = lblArgument5
        m_Labels(5) = lblArgument6

        m_Filenames(0) = txtFilename1
        m_Filenames(1) = txtFilename2
        m_Filenames(2) = txtFilename3
        m_Filenames(3) = txtFilename4
        m_Filenames(4) = txtFilename5

        m_LoadingForm = True
        cboHandlingCode.SelectedIndex = 0
        m_LoadingForm = False
    End Sub


    Private Sub ConnectEventSets()
        ' Connect each event set, if it's been specified in the dialog.
        If m_EventList.EventSetEnabled(chkEventList, "ApplicationEvents") Then
            If m_ApplicationEvents Is Nothing Then
                m_ApplicationEvents = m_App.ApplicationEvents
            End If
        Else
            If Not m_ApplicationEvents Is Nothing Then
                m_ApplicationEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "AssemblyEvents") Then
            If m_AssemblyEvents Is Nothing Then
                m_AssemblyEvents = CType(m_App.AssemblyEvents, Inventor.AssemblyEvents)
            End If
        Else
            If Not m_AssemblyEvents Is Nothing Then
                m_AssemblyEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "BrowserPane") Then
            If m_BrowserPane Is Nothing Then
                ' connect to the active pane of the active document.
                If Not m_App.ActiveDocument Is Nothing Then
                    m_BrowserPane = m_App.ActiveDocument.BrowserPanes.ActivePane
                Else
                    MsgBox("A document must be active when listening for this event.")
                    Return
                End If
            Else
                m_BrowserPane = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "BrowserPanesEvents") Then
            If m_BrowserPanesEvents Is Nothing Then
                ' connect to the active pane of the active document.
                If Not m_App.ActiveDocument Is Nothing Then
                    m_BrowserPanesEvents = m_App.ActiveDocument.BrowserPanes.BrowserPanesEvents
                Else
                    MsgBox("A document must be active when listening for this event.")
                    Return
                End If
            End If
        Else
            m_BrowserPanesEvents = Nothing
        End If

        If m_EventList.EventSetEnabled(chkEventList, "CameraEvents") Then
            If m_CameraEvents Is Nothing Then
                m_CameraEvents = m_App.CameraEvents
            End If
        Else
            If Not m_CameraEvents Is Nothing Then
                m_CameraEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "DockableWindowsEvents") Then
            If m_DockableWindowsEvents Is Nothing Then
                m_DockableWindowsEvents = m_App.UserInterfaceManager.DockableWindows.Events
            End If
        Else
            If Not m_DockableWindowsEvents Is Nothing Then
                m_DockableWindowsEvents = Nothing
            End If
        End If


        If m_EventList.EventSetEnabled(chkEventList, "DocumentEvents") Then
            If m_DocumentEvents Is Nothing Then
                If m_App.ActiveDocument Is Nothing Then
                    MsgBox("A document must be active in order to listen to document events.")
                    Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
                    lblDocName.Text = ""
                Else
                    m_Document = m_App.ActiveDocument
                    lblDocName.Text = "Document events for: " & m_Document.DisplayName
                    m_DocumentEvents = m_Document.DocumentEvents
                End If
            End If
        Else
            If Not m_DocumentEvents Is Nothing Then
                m_DocumentEvents = Nothing
                m_Document = Nothing
                lblDocName.Text = ""
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "DrawingEvents") Then
            ' Check that a drawing document is active.
            If m_App.ActiveDocument Is Nothing Then
                MsgBox("A drawing document must be active to listen to drawing events.")
                Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
            Else
                If m_App.ActiveDocumentType = Inventor.DocumentTypeEnum.kDrawingDocumentObject Then
                    Dim drawingDoc As Inventor.DrawingDocument = CType(m_App.ActiveDocument, Inventor.DrawingDocument)

                    If m_DrawingEvents Is Nothing Then
                        m_DrawingEvents = drawingDoc.DrawingEvents
                    End If
                Else
                    MsgBox("A drawing document must be active to listen to drawing events.")
                    Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
                End If
            End If
        Else
            If Not m_DrawingEvents Is Nothing Then
                m_DrawingEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "DrawingViewEvents") Then
            ' Check that a drawing document is active.
            If m_App.ActiveDocument Is Nothing Then
                MsgBox("A drawing document with a view on the active sheet must be open to listen to drawing events.")
                Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
            Else
                If m_App.ActiveDocumentType = Inventor.DocumentTypeEnum.kDrawingDocumentObject Then
                    Dim drawingDoc As Inventor.DrawingDocument = CType(m_App.ActiveDocument, Inventor.DrawingDocument)

                    If drawingDoc.ActiveSheet.DrawingViews.Count = 0 Then
                        MsgBox("A drawing document with a view on the active sheet must be open to listen to drawing events.")
                        Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
                        drawingDoc = Nothing
                    Else
                        If m_DrawingViewEvents Is Nothing Then
                            m_DrawingViewEvents = drawingDoc.ActiveSheet.DrawingViews.Item(1).DrawingViewEvents
                            MsgBox("Listening to DrawingViewEvents for drawing view """ & drawingDoc.ActiveSheet.DrawingViews.Item(1).Name & """")
                        End If
                    End If
                Else
                    MsgBox("A drawing document with a view on the active sheet must be open to listen to drawing events.")
                    Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
                End If
            End If
        Else
            If Not m_DrawingViewEvents Is Nothing Then
                m_DrawingViewEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "FileAccessEvents") Then
            If m_FileAccessEvents Is Nothing Then
                m_FileAccessEvents = m_App.FileAccessEvents
            End If
        Else
            If Not m_FileAccessEvents Is Nothing Then
                m_FileAccessEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "FileDialogEvents") Then
            If m_FileDialogEvents Is Nothing Then
                Dim fileDlg As Inventor.FileDialog
                fileDlg = Nothing

                'Only create a dialog for test since the existed dialog can not be got from API 
                m_App.CreateFileDialog(fileDlg)

                ' Here use the Open dialog as example
                m_FileDialogEvents = fileDlg.FileDialogEvents
                fileDlg.OptionsEnabled = True
                fileDlg.ShowOpen()
            End If
        Else
            If Not m_FileDialogEvents Is Nothing Then
                m_FileDialogEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "FileManagerEvents") Then
            If m_FileManagerEvents Is Nothing Then
                m_FileManagerEvents = m_App.FileManager.FileManagerEvents
            End If
        Else
            If Not m_FileManagerEvents Is Nothing Then
                m_FileManagerEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "FileUIEvents") Then
            If m_FileUIEvents Is Nothing Then
                m_FileUIEvents = m_App.FileUIEvents
            End If
        Else
            If Not m_FileUIEvents Is Nothing Then
                m_FileUIEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "HelpEvents") Then
            If m_HelpEvents Is Nothing Then
                m_HelpEvents = m_App.HelpManager.HelpEvents
            End If
        Else
            If Not m_HelpEvents Is Nothing Then
                m_HelpEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "ModelingEvents") Then
            If m_ModelingEvents Is Nothing Then
                m_ModelingEvents = m_App.ModelingEvents
            End If
        Else
            If Not m_ModelingEvents Is Nothing Then
                m_ModelingEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "ModelStateEvents") Then
            If m_ModelStateEvents Is Nothing Then
                m_ModelStateEvents = m_App.ModelStateEvents
            End If
        Else
            If Not m_ModelStateEvents Is Nothing Then
                m_ModelStateEvents = Nothing
            End If
        End If

        'If m_EventList.EventSetEnabled(chkEventList, "PanelBar") Then
        '    If m_PanelBar Is Nothing Then
        '        m_PanelBar = m_App.UserInterfaceManager.ActiveEnvironment.PanelBar
        '    End If
        'Else
        '    If Not m_PanelBar Is Nothing Then
        '        m_PanelBar = Nothing
        '    End If
        'End If

        If m_EventList.EventSetEnabled(chkEventList, "PartEvents") Then
            If m_App.ActiveDocumentType = Inventor.DocumentTypeEnum.kPartDocumentObject Then
                Dim partDoc As Inventor.PartDocument = CType(m_App.ActiveDocument, Inventor.PartDocument)

                If m_PartEvents Is Nothing Then
                    m_PartEvents = partDoc.ComponentDefinition.PartEvents
                End If
            End If
        Else
            If Not m_PartEvents Is Nothing Then
                m_PartEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "RepresentationEvents") Then
            If m_RepresentationEvents Is Nothing Then
                m_RepresentationEvents = m_App.RepresentationEvents
            End If
        Else
            If Not m_RepresentationEvents Is Nothing Then
                m_RepresentationEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "SearchBoxEvents") Then
            ' Check that a  document is active.
            If m_SearchBoxEvents Is Nothing Then
                If m_App.ActiveDocument Is Nothing Then
                    MsgBox("A  document is required to enable the search box events.")
                    Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
                Else
                    Select Case m_App.ActiveDocumentType
                        Case DocumentTypeEnum.kAssemblyDocumentObject
                            m_SearchBoxEvents = m_App.ActiveDocument.BrowserPanes("AmBrowserArrangement").SearchBox.SearchBoxEvents
                        Case DocumentTypeEnum.kPartDocumentObject
                            m_SearchBoxEvents = m_App.ActiveDocument.BrowserPanes("PmDefault").SearchBox.SearchBoxEvents
                        Case DocumentTypeEnum.kDrawingDocumentObject
                            m_SearchBoxEvents = m_App.ActiveDocument.BrowserPanes("DlHierarchy").SearchBox.SearchBoxEvents
                        Case DocumentTypeEnum.kPresentationDocumentObject
                            m_SearchBoxEvents = m_App.ActiveDocument.BrowserPanes("DxHierarchy").SearchBox.SearchBoxEvents
                        Case Else
                            MsgBox("A valid document is required to enable the search box events.")
                            Me.chkEventList.SetItemCheckState(Me.chkEventList.SelectedIndex, CheckState.Unchecked)
                    End Select
                End If
            End If
        Else
            If Not m_SearchBoxEvents Is Nothing Then
                m_SearchBoxEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "SketchEvents") Then
            If m_SketchEvents Is Nothing Then
                m_SketchEvents = m_App.SketchEvents
            End If
        Else
            If Not m_SketchEvents Is Nothing Then
                m_SketchEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "StyleEvents") Then
            If m_StyleEvents Is Nothing Then
                m_StyleEvents = m_App.StyleEvents
            End If
        Else
            If Not m_StyleEvents Is Nothing Then
                m_StyleEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "TransactionEvents") Then
            If m_TransactionEvents Is Nothing Then
                m_TransactionEvents = m_App.TransactionManager.TransactionEvents
            End If
        Else
            If Not m_TransactionEvents Is Nothing Then
                m_TransactionEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "UserInputEvents") Then
            If m_UserInputEvents Is Nothing Then
                m_UserInputEvents = m_App.CommandManager.UserInputEvents
            End If
        Else
            If Not m_UserInputEvents Is Nothing Then
                m_UserInputEvents = Nothing
            End If
        End If

        If m_EventList.EventSetEnabled(chkEventList, "UserInterfaceEvents") Then
            If m_UserInterfaceEvents Is Nothing Then
                m_UserInterfaceEvents = m_App.UserInterfaceManager.UserInterfaceEvents
            End If
        Else
            If Not m_UserInterfaceEvents Is Nothing Then
                m_UserInterfaceEvents = Nothing
            End If
        End If
    End Sub

    Private Sub SetHandlingCode(ByVal FullEventName As String, ByRef HandlingCode As Inventor.HandlingCodeEnum)
        Dim thisEvent As InventorEvent = m_EventList.item(FullEventName)
        Dim handlingCodeValue As String = ""
        Dim argumentExists As Boolean = False
        thisEvent.GetArgumentInfo("HandlingCode", handlingCodeValue, argumentExists)
        If argumentExists Then
            Select Case handlingCodeValue
                Case "Cancel"
                    HandlingCode = Inventor.HandlingCodeEnum.kEventCanceled
                Case "Handled"
                    HandlingCode = Inventor.HandlingCodeEnum.kEventHandled
                Case "Not Handled"
                    HandlingCode = Inventor.HandlingCodeEnum.kEventNotHandled
                Case Else
                    HandlingCode = Inventor.HandlingCodeEnum.kEventNotHandled
            End Select
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnActivateDocument(ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnActivateDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnActivateDocument") Then
            EventReporter("ApplicationEvents.OnActivateDocument", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnActivateDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnActivateView(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnActivateView
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnActivateView") Then
            EventReporter("ApplicationEvents.OnActivateView", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnActivateView", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnActiveProjectChanged(ByVal ProjectObject As Inventor.DesignProject, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnActiveProjectChanged
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnActiveProjectChanged") Then
            EventReporter("ApplicationEvents.OnActiveProjectChanged", "ProjectObject", ProjectObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnActiveProjectChanged", HandlingCode)
            End If

            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & "     * FileLocations.FileLocationsFile: " & m_App.FileLocations.FileLocationsFile
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnApplicationOptionChange(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnApplicationOptionChange
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnApplicationOptionChange") Then
            EventReporter("ApplicationEvents.OnApplicationOptionChange", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnApplicationOptionChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnCloseDocument(ByVal DocumentObject As Inventor._Document, ByVal FullDocumentName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnCloseDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnCloseDocument") Then
            EventReporter("ApplicationEvents.OnCloseDocument", "DocumentObject", DocumentObject, "FullDocumentName", FullDocumentName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnCloseDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnCloseView(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnCloseView
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnCloseView") Then
            EventReporter("ApplicationEvents.OnCloseView", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnCloseView", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnDeactivateDocument(ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnDeactivateDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnDeactivateDocument") Then
            EventReporter("ApplicationEvents.OnDeactivateDocument", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnDeactivateDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnDeactivateView(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnDeactivateView
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnDeactivateView") Then
            EventReporter("ApplicationEvents.OnDeactivateView", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnDeactivateView", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnDisplayModeChange(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnDisplayModeChange
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnDisplayModeChange") Then
            EventReporter("ApplicationEvents.OnDisplayModeChange", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnDisplayModeChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnDocumentChange(ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal ReasonsForChange As Inventor.CommandTypesEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnDocumentChange
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnDocumentChange") Then
            EventReporter("ApplicationEvents.OnDocumentChange", "DocumentObject", DocumentObject, "ReasonsForChange", ReasonsForChange, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnDocumentChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnInitializeDocument(ByVal DocumentObject As Inventor._Document, ByVal FullDocumentName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnInitializeDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnInitializeDocument") Then
            EventReporter("ApplicationEvents.OnInitializeDocument", "DocumentObject", DocumentObject, "FullDocumentName", FullDocumentName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnInitializeDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnMigrateDocument(ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnMigrateDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnMigrateDocument") Then
            EventReporter("ApplicationEvents.OnMigrateDocument", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnMigrateDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnMoveApplicationWindow(ByVal ApplicationObject As Inventor.Application, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnMoveApplicationWindow
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnMoveApplicationWindow") Then
            EventReporter("ApplicationEvents.OnMoveApplicationWindow", "ApplicationObject", ApplicationObject, BeforeOrAfter, Context, HandlingCode)
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnMoveView(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnMoveView
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnMoveView") Then
            EventReporter("ApplicationEvents.OnMoveView", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnMoveView", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnNewDocument(ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnNewDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnNewDocument") Then
            EventReporter("ApplicationEvents.OnNewDocument", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnNewDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnNewEditObject(ByVal EditObject As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnNewEditObject
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnNewEditObject") Then
            EventReporter("ApplicationEvents.OnNewEditObject", "EditObject", EditObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnNewEditObject", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnNewView(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnNewView
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnNewView") Then
            EventReporter("ApplicationEvents.OnNewView", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnNewView", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnOpenDocument(ByVal DocumentObject As Inventor._Document, ByVal FullDocumentName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnOpenDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnOpenDocument") Then
            EventReporter("ApplicationEvents.OnOpenDocument", "DocumentObject", DocumentObject, "FullDocumentName", FullDocumentName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnOpenDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnQuit(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnQuit
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnQuit") Then
            EventReporter("ApplicationEvents.OnQuit", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnQuit", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnReady(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnReady
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnReady") Then
            EventReporter("ApplicationEvents.OnReady", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnReady", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnResizeApplicationWindow(ByVal ApplicationObject As Inventor.Application, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnResizeApplicationWindow
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnResizeApplicationWindow") Then
            EventReporter("ApplicationEvents.OnResizeApplicationWindow", "ApplicationObject", ApplicationObject, BeforeOrAfter, Context, HandlingCode)
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnResizeView(ByVal ViewObject As Inventor.View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnResizeView
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnResizeView") Then
            EventReporter("ApplicationEvents.OnResizeView", "ViewObject", ViewObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnResizeView", HandlingCode)
            End If
        End If
    End Sub
    Private Sub m_ApplicationEvents_OnRestart32BitHost(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnRestart32BitHost
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnRestart32BitHost") Then
            EventReporter("ApplicationEvents.OnRestart32BitHost", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnRestart32BitHost", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnSaveDocument(ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnSaveDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnSaveDocument") Then
            EventReporter("ApplicationEvents.OnSaveDocument", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnSaveDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnTerminateDocument(ByVal DocumentObject As Inventor._Document, ByVal FullDocumentName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnTerminateDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnTerminateDocument") Then
            EventReporter("ApplicationEvents.OnTerminateDocument", "DocumentObject", DocumentObject, "FullDocumentName", FullDocumentName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnTerminateDocument", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ApplicationEvents_OnTranslateDocument(ByVal TranslatingIn As Boolean, ByVal DocumentObject As Inventor._Document, ByVal FullFileName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ApplicationEvents.OnTranslateDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnTranslateDocument") Then
            EventReporter("ApplicationEvents.OnTranslateDocument", "TranslatingIn", TranslatingIn, "DocumentObject", DocumentObject, "FullFileName", FullFileName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnTranslateDocument", HandlingCode)
            End If
        End If
    End Sub
    Private Sub m_ApplicationEvents_OnUndoOpenDocument(DocumentObject As _Document, BeforeOrAfter As EventTimingEnum, Context As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_ApplicationEvents.OnUndoOpenDocument
        If m_EventList.IsEnabled(chkEventList, "ApplicationEvents", "OnUndoOpenDocument") Then
            EventReporter("ApplicationEvents.OnUndoOpenDocument", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ApplicationEvents.OnUndoOpenDocument", HandlingCode)
            End If
        End If
    End Sub
    Private Sub m_AssemblyEvents_OnAssemblyChange(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnAssemblyChange
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnAssemblyChange") Then
            EventReporter("AssemblyEvents.OnAssemblyChange", "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnAssemblyChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnAssemblyChanged(ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnAssemblyChanged
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnAssemblyChanged") Then
            EventReporter("AssemblyEvents.OnAssemblyChanged", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnAssemblyChanged", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnAssemblySolve(ByVal Solver As Inventor._AssemblySolver, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap) Handles m_AssemblyEvents.OnAssemblySolve
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnAssemblySolve") Then
            EventReporter("AssemblyEvents.OnAssemblySolve", "Solver", Solver, BeforeOrAfter, Context, Nothing)
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnDelete(ByVal DocumentObject As Inventor._Document, ByVal Entity As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnDelete") Then
            EventReporter("AssemblyEvents.OnDelete", "DocumentObject", DocumentObject, "Entity", Entity, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnDelete", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnLoadStateChange(DocumentObject As Inventor._AssemblyDocument, NewLoadState As Inventor.DocumentLoadStateEnum, BeforeOrAfter As Inventor.EventTimingEnum, Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnLoadStateChange
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnLoadStateChange") Then
            EventReporter("AssemblyEvents.OnLoadStateChange", "DocumentObject", DocumentObject, "NewLoadState", NewLoadState, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnLoadStateChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnNewOccurrence(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Occurrence As Inventor.ComponentOccurrence, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnNewOccurrence
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnNewOccurrence") Then
            EventReporter("AssemblyEvents.OnNewOccurrence", "DocumentObject", DocumentObject, "Occurrence", Occurrence, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnNewOccurrence", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnNewRelationship(DocumentObject As Inventor._AssemblyDocument, Relationship As Object, BeforeOrAfter As Inventor.EventTimingEnum, Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnNewRelationship
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnNewRelationship") Then
            EventReporter("AssemblyEvents.OnNewRelationship", "DocumentObject", DocumentObject, "Relationship", Relationship, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnNewRelationship", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_AssemblyEvents_OnOccurrenceChange(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Occurrence As Inventor.ComponentOccurrence, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_AssemblyEvents.OnOccurrenceChange
        If m_EventList.IsEnabled(chkEventList, "AssemblyEvents", "OnOccurrenceChange") Then
            EventReporter("AssemblyEvents.OnOccurrenceChange", "DocumentObject", DocumentObject, "Occurrence", Occurrence, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("AssemblyEvents.OnOccurrenceChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_CameraEvents_OnCameraChange(ByVal View As View, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap) Handles m_CameraEvents.OnCameraChange
        If m_EventList.IsEnabled(chkEventList, "CameraEvents", "OnCameraChange") Then
            EventReporter("CameraEvents.OnCameraChange", "View", View, BeforeOrAfter, Context, Nothing)
        End If
    End Sub

    Private Sub m_DockableWindowsEvents_OnHelp(ByVal DockableWindow As DockableWindow, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DockableWindowsEvents.OnHelp
        If m_EventList.IsEnabled(chkEventList, "DockableWindowsEvents", "OnHelp") Then
            EventReporter("DockableWindowsEvents.OnHelp", "DockableWindow", DockableWindow, Nothing, Context, HandlingCode)
        End If
    End Sub

    Private Sub m_DockableWindowsEvents_OnHide(ByVal DockableWindow As DockableWindow, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DockableWindowsEvents.OnHide
        If m_EventList.IsEnabled(chkEventList, "DockableWindowsEvents", "OnHide") Then
            EventReporter("DockableWindowsEvents.OnHide", "DockableWindow", DockableWindow, BeforeOrAfter, Context, HandlingCode)
        End If
    End Sub

    Private Sub m_DockableWindowsEvents_OnShow(ByVal DockableWindow As DockableWindow, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DockableWindowsEvents.OnShow
        If m_EventList.IsEnabled(chkEventList, "DockableWindowsEvents", "OnShow") Then
            EventReporter("DockableWindowsEvents.OnShow", "DockableWindow", DockableWindow, BeforeOrAfter, Context, HandlingCode)
        End If
    End Sub
    Private Sub m_FileAccessEvents_OnFileDirty(ByVal RelativeFileName As String, ByVal LibraryName As String, ByRef CustomLogicalName() As Byte, ByVal FullFileName As String, ByVal DocumentObject As Inventor._Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileAccessEvents.OnFileDirty
        If m_EventList.IsEnabled(chkEventList, "FileAccessEvents", "OnFileDirty") Then
            EventReporter("FileAccessEvents.OnFileDirty", "RelativeFileName", RelativeFileName, "LibraryName", LibraryName, "CustomLogicalName", CustomLogicalName, "FullFileName", FullFileName, "DocumentObject", DocumentObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("FileAccessEvents.OnFileDirty", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_FileAccessEvents_OnFileResolution(ByVal RelativeFileName As String, ByVal LibraryName As String, ByRef CustomLogicalName() As Byte, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef FullFileName As String, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileAccessEvents.OnFileResolution
        If m_EventList.IsEnabled(chkEventList, "FileAccessEvents", "OnFileResolution") Then
            EventReporter("FileAccessEvents.OnFileResolution", "RelativeFileName", RelativeFileName, "LibraryName", LibraryName, "FullFileName", FullFileName, "CustomLogicalName", CustomLogicalName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("FileAccessEvents.OnFileResolution", HandlingCode)

                Dim thisEvent As InventorEvent = m_EventList.item("FileAccessEvents.OnFileResolution")
                Dim fullFilenameArgument As String = ""
                Dim argumentExists As Boolean = False
                thisEvent.GetArgumentInfo("FullFilename", fullFilenameArgument, argumentExists)
                If argumentExists Then
                    FullFileName = fullFilenameArgument
                Else
                    FullFileName = ""
                End If
            End If
        End If
    End Sub

    Private Sub m_FileDialogEvents_OnOptions(ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileDialogEvents.OnOptions
        If m_EventList.IsEnabled(chkEventList, "FileDialogEvents", "OnOptions") Then
            EventReporter("FileDialogEvents.OnOptions", Nothing, Context, HandlingCode)

            SetHandlingCode("FileDialogEvents.OnOptions", HandlingCode)
        End If
    End Sub

    Private Sub m_FileManagerEvents_OnFileDelete(ByVal FullFileName As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileManagerEvents.OnFileDelete
        If m_EventList.IsEnabled(chkEventList, "FileManagerEvents", "OnFileDelete") Then
            EventReporter("FileManagerEvents.OnFileDelete", "FullFileName", FullFileName, Nothing, Context, HandlingCode)

            SetHandlingCode("FileManagerEvents.OnFileDelete", HandlingCode)
        End If
    End Sub

    Private Sub m_FileManagerEvents_OnFileCopy(ByVal SourceFullFileName As String, ByVal DestinationFullFileName As String, ByVal Copy As Boolean, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileManagerEvents.OnFileCopy
        If m_EventList.IsEnabled(chkEventList, "FileManagerEvents", "OnFileCopy") Then
            EventReporter("FileManagerEvents.OnFileCopy", "SourceFullFileName", SourceFullFileName, "DestinationFullFileName", DestinationFullFileName, "Copy", Copy, Nothing, Context, HandlingCode)

            SetHandlingCode("FileManagerEvents.OnFileCopy", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileInsertDialog(ByRef FileTypes() As String, ByVal DocumentObject As Inventor._Document, ByVal ParentHWND As Integer, ByRef FileName As String, ByRef RelativeFileName As String, ByRef LibraryName As String, ByRef CustomLogicalName() As Byte, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileInsertDialog
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileInsertDialog") Then
            EventReporter("FileUIEvents.OnFileInsertDialog", "FileTypes", FileTypes, "DocumentObject", DocumentObject, "ParentHWND", ParentHWND, "FileName", FileName, "RelativeFileName", RelativeFileName, "LibraryName", LibraryName, "CustomLogicalName", CustomLogicalName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileInsertDialog")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("FileName", argumentValue, argumentExists)
            If argumentExists Then
                FileName = argumentValue
            End If

            currentEvent.GetArgumentInfo("RelativeFileName", argumentValue, argumentExists)
            If argumentExists Then
                RelativeFileName = argumentValue
            End If

            currentEvent.GetArgumentInfo("LibraryName", argumentValue, argumentExists)
            If argumentExists Then
                LibraryName = argumentValue
            End If

            currentEvent.GetArgumentInfo("CustomLogicalName", argumentValue, argumentExists)
            If argumentExists Then
                ' Create an array of bytes from the string.
                Dim pieces() As String = argumentValue.Split(","c)
                Dim tempArray(pieces.Length - 1) As Byte

                ' Convert the string into an array of bytes.
                Dim i As Integer
                For i = 0 To pieces.Length - 1
                    tempArray(i) = CType(pieces(i), Byte)
                Next
                CustomLogicalName = tempArray
            End If

            SetHandlingCode("FileUIEvents.OnFileInsertDialog", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileInsertNewDialog(ByVal TemplateDir As String, ByRef FileTypes() As String, ByVal DocumentObject As Inventor._Document, ByVal ParentHWND As Integer, ByRef TemplateFileName As String, ByRef FileName As String, ByRef RelativeFileName As String, ByRef LibraryName As String, ByRef CustomLogicalName() As Byte, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileInsertNewDialog
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileInsertNewDialog") Then
            EventReporter("FileUIEvents.OnFileInsertNewDialog", "TemplateDir", TemplateDir, "FileTypes", FileTypes, "DocumentObject", DocumentObject, "ParentHWND", ParentHWND, "TemplateFileName", TemplateFileName, "FileName", FileName, "RelativeFileName", RelativeFileName, "LibraryName", LibraryName, "CustomLogicalName", CustomLogicalName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileInsertNewDialog")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("TemplateFileName", argumentValue, argumentExists)
            If argumentExists Then
                TemplateFileName = argumentValue
            End If

            currentEvent.GetArgumentInfo("FileName", argumentValue, argumentExists)
            If argumentExists Then
                FileName = argumentValue
            End If

            currentEvent.GetArgumentInfo("RelativeFileName", argumentValue, argumentExists)
            If argumentExists Then
                RelativeFileName = argumentValue
            End If

            currentEvent.GetArgumentInfo("LibraryName", argumentValue, argumentExists)
            If argumentExists Then
                LibraryName = argumentValue
            End If

            currentEvent.GetArgumentInfo("CustomLogicalName", argumentValue, argumentExists)
            If argumentExists Then
                ' Create an array of bytes from the string.
                Dim pieces() As String = argumentValue.Split(","c)
                Dim tempArray(pieces.Length - 1) As Byte

                ' Convert the string into an array of bytes.
                Dim i As Integer
                For i = 0 To pieces.Length - 1
                    tempArray(i) = CType(pieces(i), Byte)
                Next
                CustomLogicalName = tempArray
            End If

            SetHandlingCode("FileUIEvents.OnFileInsertNewDialog", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileNew(ByVal DocumentType As Inventor.DocumentTypeEnum, ByRef TemplateFileName As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileNew
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileNew") Then
            EventReporter("FileUIEvents.OnFileNew", "DocumentType", DocumentType, "TemplateFileName", TemplateFileName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileNew")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("TemplateFileName", argumentValue, argumentExists)
            If argumentExists Then
                TemplateFileName = argumentValue
            End If

            SetHandlingCode("FileUIEvents.OnFileNew", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileNewDialog(ByVal TemplateDir As String, ByVal ParentHWND As Integer, ByRef TemplateFileName As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileNewDialog
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileNewDialog") Then
            EventReporter("FileUIEvents.OnFileNewDialog", "TemplateDir", TemplateDir, "ParentHWND", ParentHWND, "TemplateFileName", TemplateFileName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileNewDialog")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("TemplateFileName", argumentValue, argumentExists)
            If argumentExists Then
                TemplateFileName = argumentValue
            End If

            SetHandlingCode("FileUIEvents.OnFileNewDialog", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileOpenDialog(ByRef FileTypes() As String, ByVal ParentHWND As Integer, ByRef FileName As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileOpenDialog
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileOpenDialog") Then
            EventReporter("FileUIEvents.OnFileOpenDialog", "FileTypes", FileTypes, "ParentHWND", ParentHWND, "FileName", FileName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileOpenDialog")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("FileName", argumentValue, argumentExists)
            If argumentExists Then
                FileName = argumentValue
            End If

            SetHandlingCode("FileUIEvents.OnFileOpenDialog", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileOpenFromMRU(ByRef FullFileName As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileOpenFromMRU
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileOpenFromMRU") Then
            EventReporter("FileUIEvents.OnFileOpenFromMRU", "FullFileName", FullFileName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileOpenFromMRU")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("FullFileName", argumentValue, argumentExists)
            If argumentExists Then
                FullFileName = argumentValue
            End If

            SetHandlingCode("FileUIEvents.OnFileOpenFromMRU", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnFileSaveAsDialog(ByRef FileTypes() As String, ByVal SaveCopyAs As Boolean, ByVal ParentHWND As Integer, ByRef FileName As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnFileSaveAsDialog
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnFileSaveAsDialog") Then
            EventReporter("FileUIEvents.OnFileSaveAsDialog", "FileTypes", FileTypes, "SaveCopyAs", SaveCopyAs, "ParentHWND", ParentHWND, "FileName", FileName, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnFileSaveAsDialog")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("FileName", argumentValue, argumentExists)
            If argumentExists Then
                FileName = argumentValue
            End If

            SetHandlingCode("FileUIEvents.OnFileSaveAsDialog", HandlingCode)
        End If
    End Sub

    Private Sub m_FileUIEvents_OnPopulateFileMetadata(ByVal FileMetadataObjects As Inventor.ObjectsEnumerator, ByVal Formulae As String, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_FileUIEvents.OnPopulateFileMetadata
        If m_EventList.IsEnabled(chkEventList, "FileUIEvents", "OnPopulateFileMetadata") Then
            EventReporter("FileUIEvents.OnPopulateFileMetadata", "FileMetadataObjects", FileMetadataObjects, "Formulae", Formulae, Nothing, Context, HandlingCode)

            Dim currentEvent As InventorEvent = m_EventList.item("FileUIEvents.OnPopulateFileMetadata")

            Dim argumentExists As Boolean
            Dim argumentValue As String = ""
            currentEvent.GetArgumentInfo("FileMetadataObjects", argumentValue, argumentExists)
            If argumentExists Then
                FileMetadataObjects = argumentValue
            End If

            currentEvent.GetArgumentInfo("Formulae", argumentValue, argumentExists)
            If argumentExists Then
                Formulae = argumentValue
            End If
            SetHandlingCode("FileUIEvents.OnPopulateFileMetadata", HandlingCode)
        End If
    End Sub
    Private Sub m_HelpEvents_OnApplicationHelp(Context As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_HelpEvents.OnApplicationHelp
        If m_EventList.IsEnabled(chkEventList, "HelpEvents", "OnApplicationHelp") Then
            EventReporter("HelpEvents.OnApplicationHelp", Nothing, Context, HandlingCode)
            SetHandlingCode("HelpEvents.OnApplicationHelp", HandlingCode)
        End If
    End Sub

    'Private Sub m_ModelingEvents_OnModelAnnotationsSolve(ByVal DocumentObject As Inventor._Document, ByVal Annotations As Inventor.ModelAnnotations, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnModelAnnotationsSolve
    '    If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnModelAnnotationsSolve") Then
    '        EventReporter("ModelingEvents.OnModelAnnotationsSolve", "DocumentObject", DocumentObject, "Annotations", Annotations, BeforeOrAfter, Context, HandlingCode)

    '        If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
    '            SetHandlingCode("ModelingEvents.OnDelete", HandlingCode)
    '        End If
    '    End If
    'End Sub

    Private Sub m_ModelingEvents_OnClientFeatureDoubleClick(ByVal DocumentObject As Inventor._Document, ByVal Feature As Inventor.ClientFeature, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnClientFeatureDoubleClick
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnClientFeatureDoubleClick") Then
            EventReporter("ModelingEvents.OnClientFeatureDoubleClick", "DocumentObject", DocumentObject, "Feature", Feature, Nothing, Context, HandlingCode)
            SetHandlingCode("ModelingEvents.OnClientFeatureDoubleClick", HandlingCode)
        End If
    End Sub

    Private Sub m_ModelingEvents_OnDelete(ByVal DocumentObject As Inventor._Document, ByVal Entity As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnDelete") Then
            EventReporter("ModelingEvents.OnDelete", "DocumentObject", DocumentObject, "Entity", Entity, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnDelete", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelingEvents_OnFeatureChange(ByVal DocumentObject As Inventor._Document, ByVal Feature As Inventor.PartFeature, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnFeatureChange
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnFeatureChange") Then
            EventReporter("ModelingEvents.OnFeatureChange", "DocumentObject", DocumentObject, "Feature", Feature, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnFeatureChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelingEvents_OnGenerateMember(ByVal FactoryDocumentObject As Inventor._Document, ByVal MemberName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnGenerateMember
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnGenerateMember") Then
            EventReporter("ModelingEvents.OnGenerateMember", "FactoryDocumentObject", FactoryDocumentObject, "MemberName", MemberName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnGenerateMember", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelingEvents_OnNewFeature(ByVal DocumentObject As Inventor._Document, ByVal Feature As Inventor.PartFeature, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnNewFeature
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnNewFeature") Then
            EventReporter("ModelingEvents.OnNewFeature", "DocumentObject", DocumentObject, "Feature", Feature, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnNewFeature", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelingEvents_OnNewParameter(ByVal DocumentObject As Inventor._Document, ByVal Parameter As Inventor.Parameter, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnNewParameter
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnNewParameter") Then
            EventReporter("ModelingEvents.OnNewParameter", "DocumentObject", DocumentObject, "Parameter", Parameter, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnNewParameter", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelingEvents_OnParameterChange(ByVal DocumentObject As Inventor._Document, ByVal Parameter As Inventor.Parameter, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnParameterChange
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnParameterChange") Then
            EventReporter("ModelingEvents.OnParameterChange", "DocumentObject", DocumentObject, "Parameter", Parameter, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnParameterChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelingEvents_OnGenerateModelStateMember(ByVal FactoryDocumentObject As Inventor._Document, ByVal MemberName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelingEvents.OnGenerateModelStateMember
        If m_EventList.IsEnabled(chkEventList, "ModelingEvents", "OnGenerateModelStateMember") Then
            EventReporter("ModelingEvents.OnGenerateModelStateMember", "FactoryDocumentObject", FactoryDocumentObject, "MemberName", MemberName, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelingEvents.OnGenerateModelStateMember", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelStateEvents_OnActivateModelState(ByVal DocumentObject As Inventor._Document, ByVal ModelState As Inventor.ModelState, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelStateEvents.OnActivateModelState
        If m_EventList.IsEnabled(chkEventList, "ModelStateEvents", "OnActivateModelState") Then
            EventReporter("ModelStateEvents.OnActivateModelState", "DocumentObject", DocumentObject, "ModelState", ModelState, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelStateEvents.OnActivateModelState", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelStateEvents_OnDeleteModelState(ByVal DocumentObject As Inventor._Document, ByVal ModelState As Inventor.ModelState, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelStateEvents.OnDeleteModelState
        If m_EventList.IsEnabled(chkEventList, "ModelStateEvents", "OnDeleteModelState") Then
            EventReporter("ModelStateEvents.OnDeleteModelState", "DocumentObject", DocumentObject, "ModelState", ModelState, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelStateEvents.OnDeleteModelState", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_ModelStateEvents_OnNewModelState(ByVal DocumentObject As Inventor._Document, ByVal ModelState As Inventor.ModelState, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_ModelStateEvents.OnNewModelState
        If m_EventList.IsEnabled(chkEventList, "ModelStateEvents", "OnNewModelState") Then
            EventReporter("ModelStateEvents.OnNewModelState", "DocumentObject", DocumentObject, "ModelState", ModelState, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("ModelStateEvents.OnNewModelState", HandlingCode)
            End If
        End If
    End Sub
    'Private Sub m_PanelBar_OnCommandBarSelection(ByVal CommandBarObject As Inventor.CommandBar, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_PanelBar.OnCommandBarSelection
    '    If m_EventList.IsEnabled(chkEventList, "PanelBar", "OnCommandBarSelection") Then
    '        EventReporter("PanelBar.OnCommandBarSelection", "CommandBarObject", CommandBarObject, BeforeOrAfter, Context, HandlingCode)

    '        If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
    '            SetHandlingCode("PanelBar.OnCommandBarSelection", HandlingCode)
    '        End If
    '    End If
    'End Sub

    Private Sub m_PartEvents_OnSurfaceBodyChanged(ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByRef pHandlingCode As Inventor.HandlingCodeEnum) Handles m_PartEvents.OnSurfaceBodyChanged
        If m_EventList.IsEnabled(chkEventList, "PartEvents", "OnSurfaceBodyChanged") Then
            EventReporter("PartEvents.OnSurfaceBodyChanged", BeforeOrAfter, Context, pHandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("PartEvents.OnSurfaceBodyChanged", pHandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnActivateDesignViewRepresentation(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Representation As Inventor.DesignViewRepresentation, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnActivateDesignViewRepresentation
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnActivateDesignViewRepresentation") Then
            EventReporter("RepresentationEvents.OnActivateDesignViewRepresentation", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnActivateDesignViewRepresentation", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnActivateLevelOfDetailRepresentation(ByVal DocumentObject As Inventor._Document, ByVal Representation As Inventor.LevelOfDetailRepresentation, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnActivateLevelOfDetailRepresentation
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnActivateLevelOfDetailRepresentation") Then
            EventReporter("RepresentationEvents.OnActivateLevelOfDetailRepresentation", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnActivateLevelOfDetailRepresentation", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnActivatePositionalRepresentation(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Representation As Inventor.PositionalRepresentation, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnActivatePositionalRepresentation
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnActivatePositionalRepresentation") Then
            EventReporter("RepresentationEvents.OnActivatePositionalRepresentation", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnActivatePositionalRepresentation", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnDelete(ByVal DocumentObject As Inventor._Document, ByVal Entity As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnDelete") Then
            EventReporter("RepresentationEvents.OnDelete", "DocumentObject", DocumentObject, "Entity", Entity, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnDelete", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnNewDesignViewRepresentation(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Representation As Inventor.DesignViewRepresentation, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnNewDesignViewRepresentation
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnNewDesignViewRepresentation") Then
            EventReporter("RepresentationEvents.OnNewDesignViewRepresentation", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnNewDesignViewRepresentation", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnNewLevelOfDetailRepresentation(ByVal DocumentObject As Inventor._Document, ByVal Representation As Inventor.LevelOfDetailRepresentation, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnNewLevelOfDetailRepresentation
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnNewLevelOfDetailRepresentation") Then
            EventReporter("RepresentationEvents.OnNewLevelOfDetailRepresentation", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnNewLevelOfDetailRepresentation", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnNewPositionalRepresentation(ByVal DocumentObject As Inventor._AssemblyDocument, ByVal Representation As Inventor.PositionalRepresentation, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_RepresentationEvents.OnNewPositionalRepresentation
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnNewPositionalRepresentation") Then
            EventReporter("RepresentationEvents.OnNewPositionalRepresentation", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("RepresentationEvents.OnNewPositionalRepresentation", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_RepresentationEvents_OnNewSectionView(DocumentObject As _Document, Representation As DesignViewRepresentation, BeforeOrAfter As EventTimingEnum, Context As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_RepresentationEvents.OnNewSectionView
        If m_EventList.IsEnabled(chkEventList, "RepresentationEvents", "OnNewSectionView") Then
            EventReporter("RepresentationEvents.OnNewSectionView", "DocumentObject", DocumentObject, "Representation", Representation, BeforeOrAfter, Context, HandlingCode)
        End If
    End Sub
    Private Sub m_SearchBoxEvents_OnClearSearch(ByRef HandlingCode As HandlingCodeEnum) Handles m_SearchBoxEvents.OnClearSearch
        If m_EventList.IsEnabled(chkEventList, "SearchBoxEvents", "OnClearSearch") Then
            EventReporter("SearchBoxEvents.OnClearSearch", Nothing, Nothing, HandlingCode)
            SetHandlingCode("SearchBoxEvents.OnClearSearch", HandlingCode)
        End If
    End Sub

    Private Sub m_SearchBoxEvents_OnEndSearch(ByVal SearchResult As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_SearchBoxEvents.OnEndSearch
        If m_EventList.IsEnabled(chkEventList, "SearchBoxEvents", "OnEndSearch") Then
            EventReporter("SearchBoxEvents.OnEndSearch", "SearchResult", SearchResult, Nothing, Nothing, HandlingCode)
            SetHandlingCode("SearchBoxEvents.OnEndSearch", HandlingCode)
        End If
    End Sub

    Private Sub m_SearchBoxEvents_OnStartSearch(ByRef HandlingCode As HandlingCodeEnum) Handles m_SearchBoxEvents.OnStartSearch
        If m_EventList.IsEnabled(chkEventList, "SearchBoxEvents", "OnStartSearch") Then
            EventReporter("SearchBoxEvents.OnStartSearch", Nothing, Nothing, HandlingCode)
            SetHandlingCode("SearchBoxEvents.OnStartSearch", HandlingCode)
        End If
    End Sub

    Private Sub m_SearchBoxEvents_OnStopSearch(ByVal SearchResult As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_SearchBoxEvents.OnStopSearch
        If m_EventList.IsEnabled(chkEventList, "SearchBoxEvents", "OnStopSearch") Then
            EventReporter("SearchBoxEvents.OnStopSearch", "SearchResult", SearchResult, Nothing, Nothing, HandlingCode)
            SetHandlingCode("SearchBoxEvents.OnStopSearch", HandlingCode)
        End If
    End Sub
    Private Sub m_SketchEvents_OnDelete(ByVal DocumentObject As Inventor._Document, ByVal Entity As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_SketchEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "SketchEvents", "OnDelete") Then
            EventReporter("SketchEvents.OnDelete", "DocumentObject", DocumentObject, "Entity", Entity, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("SketchEvents.OnDelete", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_SketchEvents_OnNewSketch(ByVal DocumentObject As Inventor._Document, ByVal Sketch As Inventor.Sketch, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_SketchEvents.OnNewSketch
        If m_EventList.IsEnabled(chkEventList, "SketchEvents", "OnNewSketch") Then
            EventReporter("SketchEvents.OnNewSketch", "DocumentObject", DocumentObject, "Sketch", Sketch, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("SketchEvents.OnNewSketch", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_SketchEvents_OnNewSketch3D(ByVal DocumentObject As Inventor._Document, ByVal Sketch3D As Inventor.Sketch3D, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_SketchEvents.OnNewSketch3D
        If m_EventList.IsEnabled(chkEventList, "SketchEvents", "OnNewSketch3D") Then
            EventReporter("SketchEvents.OnNewSketch3D", "DocumentObject", DocumentObject, "Sketch3D", Sketch3D, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("SketchEvents.OnNewSketch3D", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_SketchEvents_OnSketch3DChange(ByVal DocumentObject As Inventor._Document, ByVal Sketch3D As Inventor.Sketch3D, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_SketchEvents.OnSketch3DChange
        If m_EventList.IsEnabled(chkEventList, "SketchEvents", "OnSketch3DChange") Then
            EventReporter("SketchEvents.OnSketch3DChange", "DocumentObject", DocumentObject, "Sketch3D", Sketch3D, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("SketchEvents.OnSketch3DChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_SketchEvents_OnSketch3DSolve(ByVal DocumentObject As Inventor._Document, ByVal Sketch As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_SketchEvents.OnSketch3DSolve
        If m_EventList.IsEnabled(chkEventList, "SketchEvents", "OnSketch3DSolve") Then
            EventReporter("SketchEvents.OnSketch3DSolve", "DocumentObject", DocumentObject, "Sketch", Sketch, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("SketchEvents.OnSketch3DSolve", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_SketchEvents_OnSketchChange(ByVal DocumentObject As Inventor._Document, ByVal Sketch As Inventor.Sketch, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_SketchEvents.OnSketchChange
        If m_EventList.IsEnabled(chkEventList, "SketchEvents", "OnSketchChange") Then
            EventReporter("SketchEvents.OnSketchChange", "DocumentObject", DocumentObject, "Sketch", Sketch, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("SketchEvents.OnSketchChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_StyleEvents_OnActivateStyle(ByVal DocumentObject As Inventor._Document, ByVal Style As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_StyleEvents.OnActivateStyle
        If m_EventList.IsEnabled(chkEventList, "StyleEvents", "OnActivateStyle") Then
            EventReporter("StyleEvents.OnActivateStyle", "DocumentObject", DocumentObject, "Style", Style, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("StyleEvents.OnActivateStyle", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_StyleEvents_OnDelete(ByVal DocumentObject As Inventor._Document, ByVal Style As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_StyleEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "StyleEvents", "OnDelete") Then
            EventReporter("StyleEvents.OnDelete", "DocumentObject", DocumentObject, "Style", Style, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("StyleEvents.OnDelete", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_StyleEvents_OnMigrateStyleLibrary(ByVal LibraryPath As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_StyleEvents.OnMigrateStyleLibrary
        If m_EventList.IsEnabled(chkEventList, "StyleEvents", "OnMigrateStyleLibrary") Then
            EventReporter("StyleEvents.OnMigrateStyleLibrary", "LibraryPath", LibraryPath, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("StyleEvents.OnMigrateStyleLibrary", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_StyleEvents_OnNewStyle(ByVal DocumentObject As Inventor._Document, ByVal Style As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_StyleEvents.OnNewStyle
        If m_EventList.IsEnabled(chkEventList, "StyleEvents", "OnNewStyle") Then
            EventReporter("StyleEvents.OnNewStyle", "DocumentObject", DocumentObject, "Style", Style, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("StyleEvents.OnNewStyle", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_StyleEvents_OnStyleChange(ByVal DocumentObject As Inventor._Document, ByVal Style As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_StyleEvents.OnStyleChange
        If m_EventList.IsEnabled(chkEventList, "StyleEvents", "OnStyleChange") Then
            EventReporter("StyleEvents.OnStyleChange", "DocumentObject", DocumentObject, "Style", Style, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("StyleEvents.OnStyleChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_TransactionEvents_OnAbort(ByVal TransactionObject As Inventor.Transaction, ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum) Handles m_TransactionEvents.OnAbort
        If m_EventList.IsEnabled(chkEventList, "TransactionEvents", "OnAbort") Then
            EventReporter("TransactionEvents.OnAbort", "TransactionObject", TransactionObject, BeforeOrAfter, Context, Nothing)
        End If
    End Sub

    Private Sub m_TransactionEvents_OnCommit(ByVal TransactionObject As Inventor.Transaction, ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_TransactionEvents.OnCommit
        If m_EventList.IsEnabled(chkEventList, "TransactionEvents", "OnCommit") Then
            EventReporter("TransactionEvents.OnCommit", "TransactionObject", TransactionObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("TransactionEvents.OnCommit", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_TransactionEvents_OnDelete(ByVal TransactionObject As Inventor.Transaction, ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum) Handles m_TransactionEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "TransactionEvents", "OnDelete") Then
            EventReporter("TransactionEvents.OnDelete", "TransactionObject", TransactionObject, BeforeOrAfter, Context, Nothing)
        End If
    End Sub

    Private Sub m_TransactionEvents_OnRedo(ByVal TransactionObject As Inventor.Transaction, ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_TransactionEvents.OnRedo
        If m_EventList.IsEnabled(chkEventList, "TransactionEvents", "OnRedo") Then
            EventReporter("TransactionEvents.OnRedo", "TransactionObject", TransactionObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("TransactionEvents.OnRedo", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_TransactionEvents_OnUndo(ByVal TransactionObject As Inventor.Transaction, ByVal Context As Inventor.NameValueMap, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_TransactionEvents.OnUndo
        If m_EventList.IsEnabled(chkEventList, "TransactionEvents", "OnUndo") Then
            EventReporter("TransactionEvents.OnUndo", "TransactionObject", TransactionObject, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("TransactionEvents.OnUndo", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_BrowserPane_OnActivate() Handles m_BrowserPane.OnActivate
        If m_EventList.IsEnabled(chkEventList, "BrowserPane", "OnActivate") Then
            EventReporter("BrowserPane.OnActivate")
        End If
    End Sub

    Private Sub m_BrowserPane_OnDeactivate() Handles m_BrowserPane.OnDeactivate
        If m_EventList.IsEnabled(chkEventList, "BrowserPane", "OnDeactivate") Then
            EventReporter("BrowserPane.OnDeactivate")
        End If
    End Sub

    Private Sub m_BrowserPane_OnHelp(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_BrowserPane.OnHelp
        If m_EventList.IsEnabled(chkEventList, "BrowserPane", "OnHelp") Then
            EventReporter("BrowserPane.OnHelp", BeforeOrAfter, Context, HandlingCode)


            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("BrowserPane.OnHelp", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_BrowserPanesEvents_OnBrowserNodeActivate(ByVal BrowserNodeDefinition As Object, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_BrowserPanesEvents.OnBrowserNodeActivate
        If m_EventList.IsEnabled(chkEventList, "BrowserPanesEvents", "OnBrowserNodeActivate") Then
            EventReporter("BrowserPanesEvents.OnBrowserNodeActivate", "BrowserNodeDefinition", BrowserNodeDefinition, Nothing, Context, HandlingCode)
        End If
    End Sub

    Private Sub m_BrowserPanesEvents_OnBrowserNodeDeleteEntry(ByVal BrowserNodeDefinition As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_BrowserPanesEvents.OnBrowserNodeDeleteEntry
        If m_EventList.IsEnabled(chkEventList, "BrowserPanesEvents", "OnBrowserNodeDeleteEntry") Then
            EventReporter("BrowserPanesEvents.OnBrowserNodeDeleteEntry", "BrowserNodeDefinition", BrowserNodeDefinition, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("BrowserPanesEvents.OnBrowserNodeDeleteEntry", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_BrowserPanesEvents_OnBrowserNodeGetDisplayObjects(ByVal BrowserNodeDefinition As Object, ByRef Objects As Inventor.ObjectCollection, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_BrowserPanesEvents.OnBrowserNodeGetDisplayObjects
        If m_EventList.IsEnabled(chkEventList, "BrowserPanesEvents", "OnBrowserNodeGetDisplayObjects") Then
            EventReporter("BrowserPanesEvents.OnBrowserNodeGetDisplayObjects", "BrowserNodeDefinition", BrowserNodeDefinition, "Objects", Objects, Nothing, Context, HandlingCode)

            SetHandlingCode("BrowserPanesEvents.OnBrowserNodeGetDisplayObjects", HandlingCode)
        End If
    End Sub

    Private Sub m_BrowserPanesEvents_OnBrowserNodeLabelEdit(ByVal BrowserNodeDefinition As Object, ByVal NewLabel As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_BrowserPanesEvents.OnBrowserNodeLabelEdit
        If m_EventList.IsEnabled(chkEventList, "BrowserPanesEvents", "OnBrowserNodeLabelEdit") Then
            EventReporter("BrowserPanesEvents.OnBrowserNodeLabelEdit", "BrowserNodeDefinition", BrowserNodeDefinition, "NewLabel", NewLabel, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("BrowserPanesEvents.OnBrowserNodeLabelEdit", HandlingCode)
            End If
        End If
    End Sub
    Private Sub m_BrowserPanesEvents_OnBrowserNodesReorder(ByVal BrowserPane As BrowserPane, ByVal DragNodes As BrowserNodesEnumerator, ByVal TargetNode As BrowserNode, ByVal eInsertionLoactionType As InsertionLocationTypeEnum, ByVal BeforeOrAfter As EventTimingEnum, ByVal Context As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_BrowserPanesEvents.OnBrowserNodesReorder
        If m_EventList.IsEnabled(chkEventList, "BrowserPanesEvents", "OnBrowserNodesReorder") Then
            EventReporter("BrowserPanesEvents.OnBrowserNodesReorder", "BrowserPane", BrowserPane, "DragNodes", DragNodes, "TargetNode", TargetNode, "eInsertionLoactionType", eInsertionLoactionType, BeforeOrAfter, Context, HandlingCode)

        End If
    End Sub
    Private Sub m_DocumentEvents_OnActivate(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnActivate
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnActivate") Then
            EventReporter("DocumentEvents.OnActivate", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnActivate", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DocumentEvents_OnChange(ByVal ReasonsForChange As Inventor.CommandTypesEnum, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnChange
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnChange") Then
            EventReporter("DocumentEvents.OnChange", "ReasonsForChange", ReasonsForChange, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnChange", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DocumentEvents_OnChangeSelectSet(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnChangeSelectSet
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnChangeSelectSet") Then
            EventReporter("DocumentEvents.OnChangeSelectSet", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnChangeSelectSet", HandlingCode)
            End If

            Dim selectSet As Inventor.SelectSet
            selectSet = m_Document.SelectSet

            Dim reportString As String = ""
            If selectSet.Count = 0 Then
                reportString = "     Select set is empty."
            Else
                reportString = "     Select set contents:"
                Dim i As Integer
                For i = 1 To selectSet.Count
                    reportString = reportString & vbCrLf & "                   " & TypeName(selectSet.Item(i))
                Next
            End If
            WriteString(reportString)
        End If
    End Sub

    Private Sub m_DocumentEvents_OnClose(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnClose
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnClose") Then
            EventReporter("DocumentEvents.OnClose", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnClose", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DocumentEvents_OnDeactivate(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnDeactivate
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnDeactivate") Then
            EventReporter("DocumentEvents.OnDeactivate", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnDeactivate", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DocumentEvents_OnDelete(ByVal Entity As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnDelete
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnDelete") Then
            EventReporter("DocumentEvents.OnDelete", "Entity", Entity, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnDelete", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DocumentEvents_OnSave(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocumentEvents.OnSave
        If m_EventList.IsEnabled(chkEventList, "DocumentEvents", "OnSave") Then
            EventReporter("DocumentEvents.OnSave", BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DocumentEvents.OnSave", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DrawingEvents_OnRetrieveDimensions(ByVal SketchDimensions As Inventor.ObjectsEnumerator, ByVal DrawingDimensions As Inventor.GeneralDimensionsEnumerator, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DrawingEvents.OnRetrieveDimensions
        If m_EventList.IsEnabled(chkEventList, "DrawingEvents", "OnRetrieveDimensions") Then
            EventReporter("DrawingEvents.OnRetrieveDimensions", "SketchDimensions", SketchDimensions, "DrawingDimensions", DrawingDimensions, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DrawingEvents.OnRetrieveDimensions", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_DrawingViewEvents_OnViewUpdate(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal ReasonsForChange As Inventor.CommandTypesEnum, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DrawingViewEvents.OnViewUpdate
        If m_EventList.IsEnabled(chkEventList, "DrawingViewEvents", "OnViewUpdate") Then
            EventReporter("DrawingViewEvents.OnViewUpdate", "ReasonsForChange", ReasonsForChange, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("DrawingViewEvents.OnViewUpdate", HandlingCode)
            End If
        End If
    End Sub

    Private Sub m_UserInputEvents_OnActivateCommand(ByVal CommandName As String, ByVal Context As Inventor.NameValueMap) Handles m_UserInputEvents.OnActivateCommand
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnActivateCommand") Then
            EventReporter("UserInputEvents.OnActivateCommand", "CommandName", CommandName, Nothing, Context, Nothing)
        End If
    End Sub

    'Private Sub m_UserInputEvents_OnContextMenu(ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal AdditionalInfo As Inventor.NameValueMap, ByVal CommandBar As Inventor.CommandBar) Handles m_UserInputEvents.OnContextMenu
    '    If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnContextMenu") Then
    '        EventReporter("UserInputEvents.OnContextMenu", "SelectionDevice", SelectionDevice, "AdditionalInfo", AdditionalInfo, "CommandBar", CommandBar, Nothing, Nothing, Nothing)
    '    End If
    'End Sub

    Private Sub m_UserInputEvents_OnContextualMiniToolbar(ByVal SelectedEntities As Inventor.ObjectsEnumerator, ByVal DisplayedCommands As Inventor.NameValueMap, ByVal AdditionalInfo As Inventor.NameValueMap) Handles m_UserInputEvents.OnContextualMiniToolbar
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnContextualMiniToolbar") Then
            EventReporter("UserInputEvents.OnContextualMiniToolbar", "SelectedEntities", SelectedEntities, Nothing, Nothing, Nothing)
        End If
    End Sub

    'Private Sub m_UserInputEvents_OnContextMenuOld(ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal AdditionalInfo As Inventor.NameValueMap, ByVal CommandBar As Inventor.CommandBar) Handles m_UserInputEvents.OnContextMenuOld
    '    If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnContextMenuOld") Then
    '        EventReporter("UserInputEvents.OnContextMenuOld", "SelectionDevice", SelectionDevice, "AdditionalInfo", AdditionalInfo, "CommandBar", CommandBar, Nothing, Nothing, Nothing)
    '    End If
    'End Sub
    Private Sub m_UserInputEvents_OnDeleteKeyUp(SelectedEntities As ObjectsEnumerator, SelectionDevice As SelectionDeviceEnum, View As View, AdditionalInfo As NameValueMap, ByRef HandlingCode As HandlingCodeEnum) Handles m_UserInputEvents.OnDeleteKeyUp
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnDeleteKeyUp") Then
            EventReporter("UserInputEvents.OnDeleteKeyUp", "SelectedEntities", SelectedEntities, "SelectionDevice", SelectionDevice, "View", View, "AdditionalInfo", AdditionalInfo, Nothing, Nothing, HandlingCode)

            SetHandlingCode("UserInputEvents.OnDeleteKeyUp", HandlingCode)
        End If
    End Sub
    Private Sub m_UserInputEvents_OnDoubleClick(ByVal SelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View, ByVal AdditionalInfo As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_UserInputEvents.OnDoubleClick
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnDoubleClick") Then
            EventReporter("UserInputEvents.OnDoubleClick", "SelectedEntities", SelectedEntities, "SelectionDevice", SelectionDevice, "Button", Button, "ShiftKeys", ShiftKeys, "ModelPosition", ModelPosition, "ViewPosition", ViewPosition, "View", View, "AdditionalInfo", AdditionalInfo, Nothing, Nothing, HandlingCode)

            SetHandlingCode("UserInputEvents.OnDoubleClick", HandlingCode)
        End If
    End Sub

    Private Sub m_UserInputEvents_OnDrag(ByVal DragState As Inventor.DragStateEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View, ByVal AdditionalInfo As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_UserInputEvents.OnDrag
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnDrag") Then
            EventReporter("UserInputEvents.OnDrag", "DragState", DragState, "ShiftKeys", ShiftKeys, "ModelPosition", ModelPosition, "ViewPosition", ViewPosition, "View", View, "AdditionalInfo", AdditionalInfo, Nothing, Nothing, HandlingCode)

            SetHandlingCode("UserInputEvents.OnDrag", HandlingCode)
        End If
    End Sub

    Private Sub m_UserInputEvents_OnLinearMarkingMenu(ByVal SelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal LinearMenu As Inventor.CommandControls, ByVal AdditionalInfo As Inventor.NameValueMap) Handles m_UserInputEvents.OnLinearMarkingMenu
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnLinearMarkingMenu") Then
            EventReporter("UserInputEvents.OnLinearMarkingMenu", "SelectedEntities", SelectedEntities, "LinearMenu", LinearMenu, Nothing, Nothing, Nothing)
        End If
    End Sub

    Private Sub m_UserInputEvents_OnPreSelect(ByRef PreSelectEntity As Object, ByRef DoHighlight As Boolean, ByRef MorePreSelectEntities As ObjectCollection, ByVal SelectionDevice As SelectionDeviceEnum, ByVal ModelPosition As Point, ByVal ViewPosition As Point2d, ByVal View As View) Handles m_UserInputEvents.OnPreSelect
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnPreSelect") Then
            EventReporter("UserInputEvents.OnPreSelect", "PreSelectEntity", PreSelectEntity, "DoHighlight", DoHighlight, Nothing, Nothing, Nothing)
            ' EventReporter("UserInputEvents.OnPreSelect", "PreSelectEntity", PreSelectEntity, "DoHighlight", DoHighlight, Nothing)
        End If
    End Sub

    Private Sub m_UserInputEvents_OnRadialMarkingMenu(ByVal SelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal RadialMenu As Inventor.RadialMarkingMenu, ByVal AdditionalInfo As Inventor.NameValueMap) Handles m_UserInputEvents.OnRadialMarkingMenu
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnRadialMarkingMenu") Then
            EventReporter("UserInputEvents.OnRadialMarkingMenu", "SelectedEntities", SelectedEntities, "RadialMenu", RadialMenu, Nothing, Nothing, Nothing)
        End If
    End Sub
    Private Sub m_UserInputEvents_OnSelect(JustSelectedEntities As ObjectsEnumerator, ByRef MoreSelectedEntities As ObjectCollection, SelectionDevice As SelectionDeviceEnum, ModelPosition As Point, ViewPosition As Point2d, View As View) Handles m_UserInputEvents.OnSelect
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnSelect") Then
            EventReporter("UserInputEvents.OnSelect", "JustSelectedEntities", JustSelectedEntities, "MoreSelectedEntities", MoreSelectedEntities, Nothing, Nothing, Nothing)
        End If
    End Sub

    Private Sub m_UserInputEvents_OnStopPreSelect(ModelPosition As Point, ViewPosition As Point2d, View As View) Handles m_UserInputEvents.OnStopPreSelect
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnStopPreSelect") Then
            EventReporter("UserInputEvents.OnStopPreSelect", "ModelPosition", ModelPosition, "ViewPosition", ViewPosition, Nothing, Nothing, Nothing)
        End If
    End Sub
    Private Sub m_UserInputEvents_OnTerminateCommand(ByVal CommandName As String, ByVal Context As Inventor.NameValueMap) Handles m_UserInputEvents.OnTerminateCommand
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnTerminateCommand") Then
            EventReporter("UserInputEvents.OnTerminateCommand", "CommandName", CommandName, Nothing, Context, Nothing)
        End If
    End Sub
    Private Sub m_UserInputEvents_OnUnSelect(UnSelectedEntities As ObjectsEnumerator, SelectionDevice As SelectionDeviceEnum, ModelPosition As Point, ViewPosition As Point2d, View As View) Handles m_UserInputEvents.OnUnSelect
        If m_EventList.IsEnabled(chkEventList, "UserInputEvents", "OnUnSelect") Then
            EventReporter("UserInputEvents.OnUnSelect", "UnSelectedEntities", UnSelectedEntities, "ModelPosition", ModelPosition, Nothing, Nothing, Nothing)
        End If
    End Sub

    Private Sub m_UserInterfaceEvents_OnEnvironmentChange(ByVal Environment As Inventor.Environment, ByVal EnvironmentState As Inventor.EnvironmentStateEnum, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_UserInterfaceEvents.OnEnvironmentChange
        If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnEnvironmentChange") Then
            EventReporter("UserInterfaceEvents.OnEnvironmentChange", "Environment", Environment, "EnvironmentState", EnvironmentState, BeforeOrAfter, Context, HandlingCode)

            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                SetHandlingCode("UserInterfaceEvents.OnEnvironmentChange", HandlingCode)
            End If
        End If
    End Sub

    'Private Sub m_UserInterfaceEvents_OnResetCommandBars(ByVal CommandBars As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetCommandBars
    '    If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnResetCommandBars") Then
    '        EventReporter("UserInterfaceEvents.OnResetCommandBars", "CommandBars", CommandBars, Nothing, Context, Nothing)
    '    End If
    'End Sub

    Private Sub m_UserInterfaceEvents_OnResetEnvironments(ByVal Environments As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetEnvironments
        If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnResetEnvironments") Then
            EventReporter("UserInterfaceEvents.OnResetEnvironments", "Environments", Environments, Nothing, Context, Nothing)
        End If
    End Sub

    Private Sub m_UserInterfaceEvents_OnResetInventorLayout(ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetInventorLayout
        If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnResetInventorLayout") Then
            EventReporter("UserInterfaceEvents.OnResetInventorLayout", Nothing, Context, Nothing)
        End If
    End Sub

    Private Sub m_UserInterfaceEvents_OnResetMarkingMenu(ByVal MarkingMenuInternalName As String, ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetMarkingMenu
        If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnResetMarkingMenu") Then
            EventReporter("UserInterfaceEvents.OnResetMarkingMenu", "MarkingMenuInternalName", MarkingMenuInternalName, Nothing, Context, Nothing)
        End If
    End Sub

    Private Sub m_UserInterfaceEvents_OnResetRibbonInterface(ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetRibbonInterface
        If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnResetRibbonInterface") Then
            EventReporter("UserInterfaceEvents.OnResetRibbonInterface", Nothing, Context, Nothing)
        End If
    End Sub

    Private Sub m_UserInterfaceEvents_OnResetShortcuts(ByVal Context As Inventor.NameValueMap) Handles m_UserInterfaceEvents.OnResetShortcuts
        If m_EventList.IsEnabled(chkEventList, "UserInterfaceEvents", "OnResetShortcuts") Then
            EventReporter("UserInterfaceEvents.OnResetShortcuts", Nothing, Context, Nothing)
        End If
    End Sub

    Private Sub WriteString(ByVal ReportString As String)
        Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & ReportString

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String)
        Dim reportString As String = ""

        reportString = EventName

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        '        Debug.Print(reportString)
        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)
        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal Argument4Name As String, ByVal Argument4Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)
        reportString = reportString & vbCrLf & "     " & Argument4Name & ": " & ValueOf(Argument4Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal Argument4Name As String, ByVal Argument4Value As Object, ByVal Argument5Name As String, ByVal Argument5Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)
        reportString = reportString & vbCrLf & "     " & Argument4Name & ": " & ValueOf(Argument4Value)
        reportString = reportString & vbCrLf & "     " & Argument5Name & ": " & ValueOf(Argument5Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal Argument4Name As String, ByVal Argument4Value As Object, ByVal Argument5Name As String, ByVal Argument5Value As Object, ByVal Argument6Name As String, ByVal Argument6Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)
        reportString = reportString & vbCrLf & "     " & Argument4Name & ": " & ValueOf(Argument4Value)
        reportString = reportString & vbCrLf & "     " & Argument5Name & ": " & ValueOf(Argument5Value)
        reportString = reportString & vbCrLf & "     " & Argument6Name & ": " & ValueOf(Argument6Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal Argument4Name As String, ByVal Argument4Value As Object, ByVal Argument5Name As String, ByVal Argument5Value As Object, ByVal Argument6Name As String, ByVal Argument6Value As Object, ByVal Argument7Name As String, ByVal Argument7Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)
        reportString = reportString & vbCrLf & "     " & Argument4Name & ": " & ValueOf(Argument4Value)
        reportString = reportString & vbCrLf & "     " & Argument5Name & ": " & ValueOf(Argument5Value)
        reportString = reportString & vbCrLf & "     " & Argument6Name & ": " & ValueOf(Argument6Value)
        reportString = reportString & vbCrLf & "     " & Argument7Name & ": " & ValueOf(Argument7Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub


    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal Argument4Name As String, ByVal Argument4Value As Object, ByVal Argument5Name As String, ByVal Argument5Value As Object, ByVal Argument6Name As String, ByVal Argument6Value As Object, ByVal Argument7Name As String, ByVal Argument7Value As Object, ByVal Argument8Name As String, ByVal Argument8Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)
        reportString = reportString & vbCrLf & "     " & Argument4Name & ": " & ValueOf(Argument4Value)
        reportString = reportString & vbCrLf & "     " & Argument5Name & ": " & ValueOf(Argument5Value)
        reportString = reportString & vbCrLf & "     " & Argument6Name & ": " & ValueOf(Argument6Value)
        reportString = reportString & vbCrLf & "     " & Argument7Name & ": " & ValueOf(Argument7Value)
        reportString = reportString & vbCrLf & "     " & Argument8Name & ": " & ValueOf(Argument8Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub EventReporter(ByVal EventName As String, ByVal Argument1Name As String, ByVal Argument1Value As Object, ByVal Argument2Name As String, ByVal Argument2Value As Object, ByVal Argument3Name As String, ByVal Argument3Value As Object, ByVal Argument4Name As String, ByVal Argument4Value As Object, ByVal Argument5Name As String, ByVal Argument5Value As Object, ByVal Argument6Name As String, ByVal Argument6Value As Object, ByVal Argument7Name As String, ByVal Argument7Value As Object, ByVal Argument8Name As String, ByVal Argument8Value As Object, ByVal Argument9Name As String, ByVal Argument9Value As Object, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum)
        Dim reportString As String = ""

        reportString = EventName
        reportString = reportString & vbCrLf & "     " & Argument1Name & ": " & ValueOf(Argument1Value)
        reportString = reportString & vbCrLf & "     " & Argument2Name & ": " & ValueOf(Argument2Value)
        reportString = reportString & vbCrLf & "     " & Argument3Name & ": " & ValueOf(Argument3Value)
        reportString = reportString & vbCrLf & "     " & Argument4Name & ": " & ValueOf(Argument4Value)
        reportString = reportString & vbCrLf & "     " & Argument5Name & ": " & ValueOf(Argument5Value)
        reportString = reportString & vbCrLf & "     " & Argument6Name & ": " & ValueOf(Argument6Value)
        reportString = reportString & vbCrLf & "     " & Argument7Name & ": " & ValueOf(Argument7Value)
        reportString = reportString & vbCrLf & "     " & Argument8Name & ": " & ValueOf(Argument8Value)
        reportString = reportString & vbCrLf & "     " & Argument9Name & ": " & ValueOf(Argument9Value)

        reportString = reportString & EventInfo(BeforeOrAfter, Context, HandlingCode)

        If Me.txtEventResults.Text = "" Then
            Me.txtEventResults.Text = reportString
        Else
            Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & reportString
        End If

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub


    Private Function EventInfo(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByVal HandlingCode As Inventor.HandlingCodeEnum) As String
        Dim reportString As String = ""

        If Not Context Is Nothing Then
            If Context.Count = 0 Then
                reportString = "     Context: No context information"
            Else
                reportString = "     Context:"
                Dim i As Integer = 0
                For i = 1 To Context.Count
                    Dim contextValue As Object = Context.Item(i)

                    If TypeOf contextValue Is Array Then
                        reportString = reportString & vbCrLf & "          " & Context.Name(i)

                        Dim tempArray As Array
                        tempArray = CType(Context.Item(i), Array)
                        Dim j As Integer = 0
                        For j = 0 To tempArray.Length - 1
                            reportString = reportString & vbCrLf & "               " & ValueOf(tempArray(j))
                        Next
                    Else
                        reportString = reportString & vbCrLf & "          " & Context.Name(i) & " = " & ValueOf(contextValue, Context.Name(i))
                    End If
                Next
            End If
        Else
            reportString = "     Context is Nothing"
        End If

        If BeforeOrAfter <> Nothing Then
            If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
                reportString = reportString & vbCrLf & "     BeforeOrAfter: kBefore"
            ElseIf BeforeOrAfter = Inventor.EventTimingEnum.kAfter Then
                reportString = reportString & vbCrLf & "     BeforeOrAfter: kAfter"
            ElseIf BeforeOrAfter = Inventor.EventTimingEnum.kAbort Then
                reportString = reportString & vbCrLf & "     BeforeOrAfter: kAbort"
            Else
                reportString = reportString & vbCrLf & "     BeforeOrAfter: Uknown type specified."
            End If
        Else
            ' reportString = reportString & vbCrLf & "     BeforeOrAfter is Nothing."
        End If

        If HandlingCode <> Nothing Then
            If HandlingCode = Inventor.HandlingCodeEnum.kEventCanceled Then
                reportString = reportString & vbCrLf & "     HandlingCode: kEventCanceled"
            ElseIf HandlingCode = Inventor.HandlingCodeEnum.kEventHandled Then
                reportString = reportString & vbCrLf & "     HandlingCode: kEventHandled"
            ElseIf HandlingCode = Inventor.HandlingCodeEnum.kEventNotHandled Then
                reportString = reportString & vbCrLf & "     HandlingCode: kEventNotHandled"
            Else
                reportString = reportString & vbCrLf & "     HandlingCode: Uknown type specified."
            End If
        Else
            ' reportString = reportString & vbCrLf & "     HandlingCode is Nothing."
        End If

        ' Add a line feed at the begining of the string.
        If reportString <> "" Then
            reportString = vbCrLf & reportString
        End If

        Return reportString
    End Function

    Private Function ValueOf(ByVal InputValue As Object, Optional ByVal ArgumentName As String = "") As String
        If VarType(InputValue) = VariantType.Object Then
            If TypeOf InputValue Is Inventor.Point Then
                Dim point3d As Inventor.Point = CType(InputValue, Inventor.Point)
                Return TypeName(InputValue) & " = " & point3d.X.ToString("0.000000") & ", " & point3d.Y.ToString("0.000000") & ", " & point3d.Z.ToString("0.000000")
            ElseIf TypeOf InputValue Is Inventor.Point2d Then
                Dim point2d As Inventor.Point2d = CType(InputValue, Inventor.Point2d)
                Return TypeName(InputValue) & " = " & point2d.X.ToString("0.000000") & ", " & point2d.Y.ToString("0.000000")
            End If

            Dim objectName As String = ""
            Try
                objectName = InputValue.name

                ' Special case if parameter to show the value.
                If TypeOf InputValue Is Inventor.Parameter Then
                    Dim parameter As Inventor.Parameter = CType(InputValue, Inventor.Parameter)
                    Return objectName & ", Value = " & parameter.Value & " (" & TypeName(InputValue) & ")"
                Else
                    Return objectName & " (" & TypeName(InputValue) & ")"
                End If
            Catch ex As Exception
                ' Do nothing
            End Try

            Try
                objectName = InputValue.DisplayName
                Return objectName & " (" & TypeName(InputValue) & ")"
            Catch ex As Exception
                ' Do nothing
            End Try

            Try
                objectName = InputValue.InternalName
                Return objectName & " (" & TypeName(InputValue) & ")"
            Catch ex As Exception
                ' Do nothing
            End Try

            Try
                objectName = InputValue.caption
                Return objectName & " (" & TypeName(InputValue) & ")"
            Catch ex As Exception
                ' Do nothing
            End Try

            Try
                objectName = InputValue.Label
                Return objectName & " (" & TypeName(InputValue) & ")"
            Catch ex As Exception
                ' Do nothing
            End Try

            ' Check to see if the object is a collection by seeing if it supports the Count property.
            Try
                Dim returnString As String
                returnString = TypeName(InputValue) & ":"
                Dim i As Integer
                For i = 1 To InputValue.Count
                    returnString = returnString & vbCrLf & "                " & ValueOf(InputValue.item(i))
                Next
                Return returnString
            Catch ex As Exception
                Return TypeName(InputValue)
            End Try
        ElseIf VarType(InputValue) = VariantType.String Then
            Return """" & CType(InputValue, String) & """"
        ElseIf VarType(InputValue) = VariantType.Boolean Then
            If CType(InputValue, Boolean) = True Then
                Return "True"
            Else
                Return "False"
            End If
        ElseIf VarType(InputValue) = VariantType.Date Then
            Return InputValue.ToString
        ElseIf (VarType(InputValue) And VariantType.Array) = VariantType.Array Then
            If (VarType(InputValue) And VariantType.String) = VariantType.String Then
                Dim returnString As String = ""
                Dim stringArray() As String
                stringArray = CType(InputValue, String())
                Dim stringValue As String
                For Each stringValue In stringArray
                    returnString = returnString & vbCrLf & "                    " & stringValue
                Next

                Return returnString
            ElseIf (VarType(InputValue) And VariantType.Byte) = VariantType.Byte Then
                Dim returnString As String = ""
                Dim byteArray() As Byte
                byteArray = CType(InputValue, Byte())

                If byteArray.Length = 0 Then
                    returnString = "No data"
                Else
                    Dim byteValue As String
                    Dim count As Integer = 0
                    For Each byteValue In byteArray
                        If count = 0 Then
                            If returnString = "" Then
                                returnString = byteValue.ToString
                            Else
                                returnString = returnString & "                                         " & byteValue.ToString
                            End If
                        Else
                            returnString = returnString & "," & byteValue.ToString
                        End If
                        count = count + 1
                        If count = 15 Then
                            returnString = returnString & "," & vbCrLf
                            count = 0
                        End If
                    Next
                End If

                Return returnString
            End If
        ElseIf TypeOf InputValue Is Inventor.CommandTypesEnum Or ArgumentName = "ReasonsForChange" Then
            Dim commandType As Inventor.CommandTypesEnum = CType(InputValue, Inventor.CommandTypesEnum)
            Dim commandTypesList As New Collection
            If (commandType And Inventor.CommandTypesEnum.kEditMaskCmdType) = Inventor.CommandTypesEnum.kEditMaskCmdType Then
                commandTypesList.Add("kEditMaskCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kFileOperationsCmdType) = Inventor.CommandTypesEnum.kFileOperationsCmdType Then
                commandTypesList.Add("kFileOperationsCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kFilePropertyEditCmdType) = Inventor.CommandTypesEnum.kFilePropertyEditCmdType Then
                commandTypesList.Add("kFilePropertyEditCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kNonShapeEditCmdType) = Inventor.CommandTypesEnum.kNonShapeEditCmdType Then
                commandTypesList.Add("kNonShapeEditCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kQueryOnlyCmdType) = Inventor.CommandTypesEnum.kQueryOnlyCmdType Then
                commandTypesList.Add("kQueryOnlyCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kReferencesChangeCmdType) = Inventor.CommandTypesEnum.kReferencesChangeCmdType Then
                commandTypesList.Add("kReferencesChangeCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kSchemaChangeCmdType) = Inventor.CommandTypesEnum.kSchemaChangeCmdType Then
                commandTypesList.Add("kSchemaChangeCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kShapeEditCmdType) = Inventor.CommandTypesEnum.kShapeEditCmdType Then
                commandTypesList.Add("kShapeEditCmdType")
            End If

            If (commandType And Inventor.CommandTypesEnum.kUpdateWithReferencesCmdType) = Inventor.CommandTypesEnum.kUpdateWithReferencesCmdType Then
                commandTypesList.Add("kUpdateWithReferencesCmdType")
            End If

            Dim i As Integer
            Dim cmdList As String = ""
            For i = 1 To commandTypesList.Count
                If i = 1 Then
                    cmdList = CType(commandTypesList.Item(i), String)
                Else
                    cmdList = cmdList & ", " & CType(commandTypesList.Item(i), String)
                End If
            Next

            Return cmdList
        ElseIf ArgumentName = "HealthStatusEnum" Then
            Dim healthType As Inventor.HealthStatusEnum = CType(InputValue, Inventor.HealthStatusEnum)
            Select Case healthType
                Case Inventor.HealthStatusEnum.kBeyondStopNodeHealth
                    Return "kBeyondStopNodeHealth"
                Case Inventor.HealthStatusEnum.kCannotComputeHealth
                    Return "kCannotComputeHealth"
                Case Inventor.HealthStatusEnum.kDeletedHealth
                    Return "kDeletedHealth"
                Case Inventor.HealthStatusEnum.kDriverLostHealth
                    Return "kDriverLostHealth"
                Case Inventor.HealthStatusEnum.kInconsistentHealth
                    Return "kInconsistentHealth"
                Case Inventor.HealthStatusEnum.kInErrorHealth
                    Return "kInErrorHealth"
                Case Inventor.HealthStatusEnum.kOutOfDateHealth
                    Return "kOutOfDateHealth"
                Case Inventor.HealthStatusEnum.kRedundantHealth
                    Return "kRedundantHealth"
                Case Inventor.HealthStatusEnum.kSuppressedHealth
                    Return "kSuppressedHealth"
                Case Inventor.HealthStatusEnum.kUnknownHealth
                    Return "kUnknownHealth"
                Case Inventor.HealthStatusEnum.kUpToDateHealth
                    Return "kUpToDateHealth"
            End Select
        ElseIf ArgumentName = "Type" Then
            Dim objectType As Inventor.ObjectTypeEnum = CType(InputValue, Inventor.ObjectTypeEnum)
            Select Case objectType
                Case Inventor.ObjectTypeEnum.kRenderStyleObject
                    Return "kRenderStyleObject"
                Case Inventor.ObjectTypeEnum.kDimensionStyleObject
                    Return "kDimensionStyleObject"
                Case Inventor.ObjectTypeEnum.kTextStyleObject
                    Return "kTextStyleObject"
                Case Inventor.ObjectTypeEnum.kMaterialObject
                    Return "kMaterialObject"
                Case Inventor.ObjectTypeEnum.kDrawingStandardStyleObject
                    Return "kDrawingStandardStyleObject"
                Case Inventor.ObjectTypeEnum.kLightingStyleObject
                    Return "kLightingStyleObject"
                Case Inventor.ObjectTypeEnum.kSheetMetalStyleObject
                    Return "kSheetMetalStyleObject"
                Case Inventor.ObjectTypeEnum.kLayerObject
                    Return "kLayerObject"
                Case Else
                    Return "Unhandled type: " & InputValue.ToString
            End Select
        ElseIf TypeOf InputValue Is Inventor.FileManagementEnum Or ArgumentName = "FileManagementOption" Then
            Dim fileManagementType As Inventor.FileManagementEnum = CType(InputValue, Inventor.FileManagementEnum)
            Dim fileManagementTypesList As New Collection
            If (fileManagementType And Inventor.FileManagementEnum.kCopyFileMask) = Inventor.FileManagementEnum.kCopyFileMask Then
                fileManagementTypesList.Add("kCopyFileMask")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kDeleteFileMask) = Inventor.FileManagementEnum.kDeleteFileMask Then
                fileManagementTypesList.Add("kDeleteFileMask")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kForceFile) = Inventor.FileManagementEnum.kForceFile Then
                fileManagementTypesList.Add("kForceFile")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kMoveFileMask) = Inventor.FileManagementEnum.kMoveFileMask Then
                fileManagementTypesList.Add("kMoveFileMask")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kNoForceFile) = Inventor.FileManagementEnum.kNoForceFile Then
                fileManagementTypesList.Add("kNoForceFile")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kOverwriteExistingFile) = Inventor.FileManagementEnum.kOverwriteExistingFile Then
                fileManagementTypesList.Add("kOverwriteExistingFile")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kOverwriteReadOnlyFile) = Inventor.FileManagementEnum.kOverwriteReadOnlyFile Then
                fileManagementTypesList.Add("kOverwriteReadOnlyFile")
            End If

            If (fileManagementType And Inventor.FileManagementEnum.kOverwriteReservedFile) = Inventor.FileManagementEnum.kOverwriteReservedFile Then
                fileManagementTypesList.Add("kOverwriteReservedFile")
            End If

            Dim i As Integer
            Dim cmdList As String = ""
            For i = 1 To fileManagementTypesList.Count
                If i = 1 Then
                    cmdList = CType(fileManagementTypesList.Item(i), String)
                Else
                    cmdList = cmdList & ", " & CType(fileManagementTypesList.Item(i), String)
                End If
            Next

            Return cmdList
        Else
            Return InputValue.ToString
        End If

        Return ""
    End Function

    Private Sub chkEventList_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkEventList.SelectedIndexChanged
        Dim currentEvent As InventorEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        boxArgumentList.Text = "Input arguments for " & currentEvent.ObjectName & "." & currentEvent.EventName

        ' Reset each of the items.
        Dim i As Integer
        For i = 0 To 5
            m_Labels(i).Visible = False
        Next

        For i = 0 To 4
            m_Filenames(i).Visible = False
            m_Filenames(i).Text = ""
        Next

        cboHandlingCode.Visible = False
        lblNotSupported.Visible = False

        ' Process each of the "out" arguments.
        Dim labelCount As Integer = 0
        Dim filenameCount As Integer = 0
        Dim arguments() As String = currentEvent.Arguments.Split(","c)
        Dim argument As String
        For Each argument In arguments
            If argument.Contains("Out)") Then
                ' Get the argument name.
                Dim argumentName As String
                If argument.Contains("CustomLogicalName") Then
                    argumentName = argument.Substring(8, argument.IndexOf("()") - 8)
                Else
                    argumentName = argument.Substring(5, argument.IndexOf(" As") - 5)
                End If

                m_Labels(labelCount).Text = argumentName & ": "
                m_Labels(labelCount).Visible = True
                If argumentName.ToUpper.Contains("FILENAME") Or argumentName.Contains("LibraryName") Then  'And argumentName <> "RelativeFileName" Then
                    tblOptions.SetRow(m_Filenames(filenameCount), labelCount)
                    m_Filenames(filenameCount).Visible = True

                    ' Check to see if this value has been defined.
                    Dim argumentValue As String = ""
                    Dim argumentExists As Boolean
                    currentEvent.GetArgumentInfo(argumentName, argumentValue, argumentExists)
                    If argumentExists Then
                        m_Filenames(filenameCount).Text = argumentValue
                    End If

                    filenameCount += 1
                ElseIf argumentName.Contains("CustomLogicalName") Then
                    ' Special case for this because it's only for a couple of events
                    ' where setting the logical name if valid.
                    If currentEvent.EventName = "OnFileInsertDialog" Or currentEvent.EventName = "OnFileInsertNewDialog" Or currentEvent.EventName = "OnFileDirty" Or currentEvent.EventName = "OnFileResolution" Then
                        tblOptions.SetRow(m_Filenames(filenameCount), labelCount)
                        m_Filenames(filenameCount).Visible = True

                        ' Check to see if this value has been defined.
                        Dim argumentValue As String = ""
                        Dim argumentExists As Boolean
                        currentEvent.GetArgumentInfo("CustomLogicalName", argumentValue, argumentExists)
                        If argumentExists Then
                            m_Filenames(filenameCount).Text = argumentValue
                        End If

                        filenameCount += 1
                    End If
                ElseIf argumentName.Contains("HandlingCode") Then
                    tblOptions.SetRow(cboHandlingCode, labelCount)

                    ' Check to see if this event has a predefined value for this argument.
                    Dim argumentValue As String = ""
                    Dim argumentExists As Boolean
                    currentEvent.GetArgumentInfo("HandlingCode", argumentValue, argumentExists)
                    If argumentExists Then
                        Select Case argumentValue
                            Case "Not Handled"
                                cboHandlingCode.SelectedIndex = 0
                            Case "Cancel"
                                cboHandlingCode.SelectedIndex = 1
                            Case "Handled"
                                cboHandlingCode.SelectedIndex = 2
                        End Select
                    Else
                        cboHandlingCode.SelectedIndex = 0
                    End If
                    cboHandlingCode.Visible = True
                Else
                    tblOptions.SetRow(lblNotSupported, labelCount)
                    lblNotSupported.Visible = True
                End If

                labelCount += 1
            End If
        Next
    End Sub


    Private Sub chkEventList_SelectedValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkEventList.SelectedValueChanged
        ConnectEventSets()
    End Sub

    Private Sub txtFilename1_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtFilename1.Click
        HandleTextBoxClick(txtFilename1)
    End Sub

    Private Sub txtFilename2_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtFilename2.Click
        HandleTextBoxClick(txtFilename2)
    End Sub

    Private Sub txtFilename3_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtFilename3.Click
        HandleTextBoxClick(txtFilename3)
    End Sub

    Private Sub txtFilename4_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtFilename4.Click
        HandleTextBoxClick(txtFilename4)
    End Sub

    Private Sub txtFilename5_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtFilename5.Click
        HandleTextBoxClick(txtFilename5)
    End Sub


    Private Sub HandleTextBoxClick(ByVal clickedTextBox As System.Windows.Forms.TextBox)
        ' Determine which row in the table this text box is within.
        Dim argumentName As String = m_Labels(tblOptions.GetRow(clickedTextBox)).Text
        argumentName = argumentName.Substring(0, argumentName.Length - 2)

        If argumentName = "CustomLogicalName" Then
            MsgBox("Specify a list of bytes, (values 0-255), using a comma delimited list.  For example:" & vbCr & "45,1,255,0,56,47,2,0,54")
        Else
            With OpenFileDialog
                .Filter = "All Files (*.*)|*.*"
                .FilterIndex = 0
                .Title = "Specify Filename"
                .FileName = ""
                .CheckFileExists = False
                .ShowDialog()
                clickedTextBox.Text = .FileName
            End With
        End If

        ' Set the associated argument.
        Dim currentEvent As InventorEvent
        currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        SetArguments(currentEvent, argumentName, clickedTextBox.Text)
    End Sub


    Private Sub cboHandlingCode_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cboHandlingCode.SelectedIndexChanged
        If Not chkEventList.SelectedItem Is Nothing And Not m_LoadingForm Then
            Dim currentEvent As InventorEvent
            currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

            SetArguments(currentEvent, "HandlingCode", cboHandlingCode.Text)
        End If
    End Sub

    Private Sub txtFilename1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFilename1.TextChanged
        ' Determine which row in the table this text box is within.
        Dim argumentName As String = m_Labels(tblOptions.GetRow(txtFilename1)).Text
        argumentName = argumentName.Substring(0, argumentName.Length - 2)

        ' Set the associated argument.
        Dim currentEvent As InventorEvent
        currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        SetArguments(currentEvent, argumentName, txtFilename1.Text)
    End Sub


    Private Sub txtFilename2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFilename2.TextChanged
        ' Determine which row in the table this text box is within.
        Dim argumentName As String = m_Labels(tblOptions.GetRow(txtFilename2)).Text
        argumentName = argumentName.Substring(0, argumentName.Length - 2)

        ' Set the associated argument.
        Dim currentEvent As InventorEvent
        currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        SetArguments(currentEvent, argumentName, txtFilename2.Text)
    End Sub

    Private Sub txtFilename3_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFilename3.TextChanged
        ' Determine which row in the table this text box is within.
        Dim argumentName As String = m_Labels(tblOptions.GetRow(txtFilename3)).Text
        argumentName = argumentName.Substring(0, argumentName.Length - 2)

        ' Set the associated argument.
        Dim currentEvent As InventorEvent
        currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        SetArguments(currentEvent, argumentName, txtFilename3.Text)
    End Sub

    Private Sub txtFilename4_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFilename4.TextChanged
        ' Determine which row in the table this text box is within.
        Dim argumentName As String = m_Labels(tblOptions.GetRow(txtFilename4)).Text
        argumentName = argumentName.Substring(0, argumentName.Length - 2)

        ' Set the associated argument.
        Dim currentEvent As InventorEvent
        currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        SetArguments(currentEvent, argumentName, txtFilename4.Text)
    End Sub


    Private Sub txtFilename5_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFilename5.TextChanged
        ' Determine which row in the table this text box is within.
        Dim argumentName As String = m_Labels(tblOptions.GetRow(txtFilename5)).Text
        argumentName = argumentName.Substring(0, argumentName.Length - 2)

        ' Set the associated argument.
        Dim currentEvent As InventorEvent
        currentEvent = m_EventList.item(chkEventList.SelectedItem.ToString)

        SetArguments(currentEvent, argumentName, txtFilename5.Text)
    End Sub

    Private Sub SetArguments(ByVal CurrentEvent As InventorEvent, ByVal ArgumentName As String, ByVal ArgumentValue As String)
        ' Construct the string that provides the details for this argument.
        Dim argumentDetails As String
        argumentDetails = ArgumentName & "|" & ArgumentValue.ToString

        ' Get the current argument information for this event.
        Dim ArgumentString As String = CurrentEvent.ArgumentValues

        Dim notFound As Boolean = True
        Dim resultString As String = ""
        If ArgumentString <> "" Then
            ' Split up the argument string into the different arguments.
            Dim arguments() As String = ArgumentString.Split("~"c)

            ' Find this argument in the list.
            Dim argument As String = ""
            For Each argument In arguments
                ' Split each argument up into its pieces (Name, Value).
                Dim argumentValues() As String = argument.Split("|"c)
                If argumentValues(0) = ArgumentName Then
                    notFound = False

                    ' Replace the value of this argument.
                    If resultString = "" Then
                        resultString = argumentDetails
                    Else
                        resultString = resultString & "~" & argumentDetails
                    End If
                Else
                    ' This is a different argument so just add it back onto the list.
                    If resultString = "" Then
                        resultString = argument
                    Else
                        resultString = resultString & "~" & argument
                    End If
                End If
            Next
        End If

        ' This argument isn't in the argument list so add it.
        If notFound Then
            If resultString = "" Then
                resultString = argumentDetails
            Else
                resultString = resultString & "~" & argumentDetails
            End If
        End If

        CurrentEvent.ArgumentValues = resultString
    End Sub

    Private Sub btnClearList_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClearList.Click
        Me.txtEventResults.Text = ""
    End Sub

    Private Sub btnAddMarker_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnAddMarker.Click
        Me.txtEventResults.Text = Me.txtEventResults.Text & vbCrLf & "============================================"

        ' Scroll to the bottom of the text control.
        Me.txtEventResults.SelectionStart = Me.txtEventResults.Text.Length
        Me.txtEventResults.ScrollToCaret()
    End Sub

    Private Sub btnClearAll_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClearAll.Click
        Dim indexChecked As Integer
        For Each indexChecked In Me.chkEventList.CheckedIndices
            Me.chkEventList.SetItemCheckState(indexChecked, CheckState.Unchecked)
        Next
        ConnectEventSets()
    End Sub

    Public Sub New()

        ' This call is required by the Windows Form Designer.
        InitializeComponent()

        ' Add any initialization after the InitializeComponent() call.
        Control.CheckForIllegalCrossThreadCalls = False
    End Sub

    Private Sub btnCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCancel.Click
        End
    End Sub

    Private Sub txtEventResults_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtEventResults.TextChanged

    End Sub


End Class

