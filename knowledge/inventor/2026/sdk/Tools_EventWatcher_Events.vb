Public Class InventorEvents
    Inherits CollectionBase

    Public Sub New()
        ' Add the supported events to the event list.
        Me.Add("ApplicationEvents", "OnActivateDocument", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnActivateView", "(In)ViewObject As View,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnActiveProjectChanged", "(In)ProjectObject As DesignProject,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnApplicationOptionChange", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnCloseDocument", "(In)DocumentObject As Document,(In)FullDocumentName As String,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnCloseView", "(In)ViewObject As View,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnDeactivateDocument", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnDeactivateView", "(In)ViewObject As View,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnDisplayModeChange", "(In)ViewObject As View,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnDocumentChange", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)ReasonsForChange As CommandTypesEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnInitializeDocument", "(In)DocumentObject As Document,(In)FullDocumentName As String,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnMigrateDocument", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnMoveApplicationWindow", "(In)ApplicationObject As Application,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnMoveView", "(In)ViewObject  As Application,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnNewDocument", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnNewEditObject", "(In)EditObject As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnNewView", "(In)ViewObject As View,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnOpenDocument", "(In)DocumentObject As Document,(In)FullDocumentName As String,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnQuit", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnReady", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnResizeApplicationWindow", "(In)ApplicationObject As Application,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnResizeView", "(In)ViewObject  As Application,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnRestart32BitHost", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnSaveDocument", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnTerminateDocument", "(In)DocumentObject As Document,(In)FullDocumentName As String,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnTranslateDocument", "(In)TranslatingIn As Boolean,(In)DocumentObject As Document,(In)FullFileName As String,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ApplicationEvents", "OnUndoOpenDocument", "(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("AssemblyEvents", "OnAssemblyChange", "(In)DocumentObject As AssemblyDocument,(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("AssemblyEvents", "OnDelete", "(In)DocumentObject As Document,(In)Entity As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("AssemblyEvents", "OnNewOccurrence", "(In)DocumentObject As AssemblyDocument,(In)Occurrence As ComponentOccurrence,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("AssemblyEvents", "OnNewRelationship", "(In)DocumentObject As AssemblyDocument,(In)Relationship As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("AssemblyEvents", "OnOccurrenceChange", "(In)DocumentObject As AssemblyDocument,(In)Occurrence As ComponentOccurrence,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("AssemblyEvents", "OnLoadStateChange", "(In)DocumentObject As AssemblyDocument,(In)NewLoadState As DocumentLoadStateEnum,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("BrowserPane", "OnActivate", "")
        Me.Add("BrowserPane", "OnDeactivate", "")
        Me.Add("BrowserPane", "OnHelp", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("BrowserPanesEvents", "OnBrowserNodeActivate", "(In)BrowserNodeDefinition As Object,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("BrowserPanesEvents", "OnBrowserNodeDeleteEntry", "(In)BrowserNodeDefinition As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("BrowserPanesEvents", "OnBrowserNodeGetDisplayObjects", "(In)BrowserNodeDefinition As Object,(Out)Objects As ObjectCollection,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("BrowserPanesEvents", "OnBrowserNodeLabelEdit", "(In)BrowserNodeDefinition As Object,(In)NewLabel As String,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("BrowserPanesEvents", "OnBrowserNodesReorder", "(In)BrowserPane As BrowserPane, (In)DragNodes As BrowserNodesEnumerator, (In)TargetNode As BrowserNode, (In)eInsertionLoactionType As InsertionLocationTypeEnum,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("CameraEvents", "OnCameraChange", "(In)View As View, (In)BeforeOrAfter As EventTimingEnum, (In)Context As Inventor.NameValueMap")
        Me.Add("DockableWindowsEvents", "OnHelp", "(In)DockableWindow As DockableWindow,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DockableWindowsEvents", "OnHide", "(In)DockableWindow As DockableWindow,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DockableWindowsEvents", "OnShow", "(In)DockableWindow As DockableWindow,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnActivate", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnChange", "(In)ReasonsForChange As CommandTypesEnum,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnChangeSelectSet", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnClose", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnDeactivate", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnDelete", "(In)Entity As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DocumentEvents", "OnSave", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DrawingEvents", "OnRetrieveDimensions", "(In)SketchDimensions As ObjectsEnumerator,(In)DrawingDimensions As GeneralDimensionsEnumerator,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("DrawingViewEvents", "OnViewUpdate", "(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(In)ReasonsForChange As CommandTypesEnum,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileAccessEvents", "OnFileDirty", "(In)RelativeFileName As String,(In)LibraryName As String,(In/Out)CustomLogicalName() As Byte,(In)FullFileName As String,(In)DocumentObject As Document,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileAccessEvents", "OnFileResolution", "(In)RelativeFileName As String,(In)LibraryName As String,(In/Out)CustomLogicalName() As Byte,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)FullFileName As String,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileDialogEvents", "OnOptions", "(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileManagerEvents", "OnFileDelete", "(In)FullFileName As String,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileManagerEvents", "OnFileCopy", "(In)SourceFullFileName As String,(In)DestinationFullFileName As String, (In)Copy As Boolean, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileInsertDialog", "(In)FileTypes() As String,(In)DocumentObject As Document,(In)ParentHWND As Long,(Out)FileName As String,(Out)RelativeFileName As String,(Out)LibraryName As String,(In/Out)CustomLogicalName() As Byte,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileInsertNewDialog", "(In)TemplateDir As String,(In)FileTypes() As String,(In)DocumentObject As Document,(In)ParentHWND As Long,(Out)TemplateFileName As String,(Out)FileName As String,(Out)RelativeFileName As String,(Out)LibraryName As String,(In/Out)CustomLogicalName() As Byte,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileNew", "(In)DocumentType As DocumentTypeEnum,(Out)TemplateFileName As String,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileNewDialog", "(In)TemplateDir As String,(In)ParentHWND As Long,(Out)TemplateFileName As String,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileOpenDialog", "(In)FileTypes() As String,(In)ParentHWND As Long,(Out)FileName As String,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileOpenFromMRU", "(Out)FullFileName As String,(In)Context As NameValueMap(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnFileSaveAsDialog", "(In)FileTypes() As String,(In)SaveCopyAs As Boolean,(In)ParentHWND As Long,(Out)FileName As String,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("FileUIEvents", "OnPopulateFileMetadata", "(In)FileMetadataObjects As ObjectsEnumerator,(In)Formulae As String,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("HelpEvents", "OnApplicationHelp", "(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        'Me.Add("ModelingEvents", "OnModelAnnotationsSolve", "(In)DocumentObject As Document, (In)Annotations As ModelAnnotations, (In)BeforeOrAfter As EventTimingEnum, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnClientFeatureDoubleClick", "(In)DocumentObject As Document, (In)Feature As ClientFeature, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnDelete", "(In)DocumentObject As Document,(In)Entity As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnFeatureChange", "(In)DocumentObject As Document,(In)Feature As PartFeature,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnGenerateMember", "(In)FactoryDocumentObject As Document, (In)MemberName As String, (In)BeforeOrAfter As EventTimingEnum, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnNewFeature", "(In)DocumentObject As Document,(In)Feature As PartFeature,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnNewParameter", "(In)DocumentObject As Document,(In)Parameter As Parameter,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnParameterChange", "(In)DocumentObject As Document,(In)Parameter As Parameter,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelingEvents", "OnGenerateModelStateMember", "(In)FactoryDocumentObject As Document, (In)MemberName As String, (In)BeforeOrAfter As EventTimingEnum, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelStateEvents", "OnActivateModelState", "(In)DocumentObject As Document, (In)ModelState As ModelState, (In)BeforeOrAfter As EventTimingEnum, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelStateEvents", "OnDeleteModelState", "(In)DocumentObject As Document, (In)ModelState As ModelState, (In)BeforeOrAfter As EventTimingEnum, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("ModelStateEvents", "OnNewModelState", "(In)DocumentObject As Document, (In)ModelState As ModelState, (In)BeforeOrAfter As EventTimingEnum, (In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        'Me.Add("PanelBar", "OnCommandBarSelection", "(In)CommandBarObject As CommandBar,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("PartEvents", "OnSurfaceBodyChanged", "(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum,(Out)pHandlingCode As HandlingCodeEnum")
        Me.Add("RepresentationEvents", "OnActivateDesignViewRepresentation", "(In)DocumentObject As AssemblyDocument,(In)Representation As DesignViewRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        ' Me.Add("RepresentationEvents", "OnActivateLevelOfDetailRepresentation", "(In)DocumentObject As Document,(In)Representation As LevelOfDetailRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("RepresentationEvents", "OnActivatePositionalRepresentation", "(In)DocumentObject As AssemblyDocument,(In)Representation As PositionalRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("RepresentationEvents", "OnDelete", "(In)DocumentObject As Document,(In)Entity As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("RepresentationEvents", "OnNewDesignViewRepresentation", "(In)DocumentObject As AssemblyDocument,(In)Representation As DesignViewRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        ' Me.Add("RepresentationEvents", "OnNewLevelOfDetailRepresentation", "(In)DocumentObject As Document,(In)Representation As LevelOfDetailRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("RepresentationEvents", "OnNewPositionalRepresentation", "(In)DocumentObject As AssemblyDocument,(In)Representation As PositionalRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("RepresentationEvents", "OnNewSectionView", "(In)DocumentObject As Document,(In)Representation As DesignViewRepresentation,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SearchBoxEvents", "OnClearSearch", "(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SearchBoxEvents", "OnEndSearch", "(In)SearchResult As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SearchBoxEvents", "OnStartSearch", "(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SearchBoxEvents", "OnStopSearch", "(In)SearchResult As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SketchEvents", "OnDelete", "(In)DocumentObject As Document,(In)Entity As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SketchEvents", "OnNewSketch", "(In)DocumentObject As Document,(In)Sketch As Sketch,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SketchEvents", "OnNewSketch3D", "(In)DocumentObject As Document,(In)Sketch3D As Sketch3D,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SketchEvents", "OnSketch3DChange", "(In)DocumentObject As Document,(In)Sketch3D As Sketch3D,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("SketchEvents", "OnSketchChange", "(In)DocumentObject As Document,(In)Sketch As Sketch,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("StyleEvents", "OnActivateStyle", "(In)DocumentObject As Document,(In)Style As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("StyleEvents", "OnDelete", "(In)DocumentObject As Document,(In)Style As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("StyleEvents", "OnNewStyle", "(In)DocumentObject As Document,(In)Style As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("StyleEvents", "OnStyleChange", "(In)DocumentObject As Document,(In)Style As Object,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("TransactionEvents", "OnAbort", "(In)TransactionObject As Transaction,(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum")
        Me.Add("TransactionEvents", "OnCommit", "(In)TransactionObject As Transaction,(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("TransactionEvents", "OnDelete", "(In)TransactionObject As Transaction,(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum")
        Me.Add("TransactionEvents", "OnRedo", "(In)TransactionObject As Transaction,(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("TransactionEvents", "OnUndo", "(In)TransactionObject As Transaction,(In)Context As NameValueMap,(In)BeforeOrAfter As EventTimingEnum,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("UserInputEvents", "OnActivateCommand", "(In)CommandName As String,(In)Context As NameValueMap")
        'Me.Add("UserInputEvents", "OnContextMenu", "(In)SelectionDevice As SelectionDeviceEnum,(In)AdditionalInfo As NameValueMap,(In)CommandBar As CommandBar")
        Me.Add("UserInputEvents", "OnContextualMiniToolbar", "(In)SelectedEntities As ObjectsEnumerator,(In)DisplayedCommands  As NameValueMap,(In)AdditionalInfo As NameValueMap")
        Me.Add("UserInputEvents", "OnDeleteKeyUp", "(In)SelectedEntities As ObjectsEnumerator,(In)SelectionDevice As SelectionDeviceEnum,(In)View As View, (In)AdditionalInfo As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("UserInputEvents", "OnDoubleClick", "(In)SelectedEntities As ObjectsEnumerator,(In)SelectionDevice As SelectionDeviceEnum,(In)Button As MouseButtonEnum,(In)ShiftKeys As ShiftStateEnum, (In)ModelPosition As Point, (In)ViewPosition As Point2d, (In)View As View, (In)AdditionalInfo As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("UserInputEvents", "OnDrag", "(In)DragState As DragStateEnum,(In)ShiftKeys As ShiftStateEnum,(In)ModelPosition As Point,(In)ViewPosition As Point2d,(In)View As View,(In)AdditionalInfo As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        Me.Add("UserInputEvents", "OnLinearMarkingMenu", "(In)SelectedEntities As ObjectsEnumerator,(In)SelectionDevice As SelectionDeviceEnum,(In)LinearMenu As CommandControls,(In)AdditionalInfo As NameValueMap")
        Me.Add("UserInputEvents", "OnPreSelect", "(In)PreSelectEntity As Object, (In)DoHighlight As Boolean, (In)MorePreSelectEntities As ObjectCollection, (In)SelectionDevice As SelectionDeviceEnum, (In)ModelPosition As Point,(In)ViewPosition As Point2d,(In)View As View")
        Me.Add("UserInputEvents", "OnRadialMarkingMenu", "(In)SelectedEntities As ObjectsEnumerator,(In)SelectionDevice As SelectionDeviceEnum,(In)RadialMenu  As RadialMarkingMenu,(In)AdditionalInfo As NameValueMap")
        Me.Add("UserInputEvents", "OnSelect", "(In)JustSelectedEntities  As ObjectsEnumerator, (In)MoreSelectedEntities As ObjectCollection, (In)SelectionDevice As SelectionDeviceEnum, (In)ModelPosition As Point,(In)ViewPosition As Point2d,(In)View As View")
        Me.Add("UserInputEvents", "OnStopPreSelect", "(In)ModelPosition As Point,(In)ViewPosition As Point2d,(In)View As View")
        Me.Add("UserInputEvents", "OnTerminateCommand", "(In)CommandName As String,(In)Context As NameValueMap")
        Me.Add("UserInputEvents", "OnUnSelect", "(In)UnSelectedEntities As ObjectsEnumerator, (In)SelectionDevice As SelectionDeviceEnum, (In)ModelPosition As Point,(In)ViewPosition As Point2d,(In)View As View")
        Me.Add("UserInterfaceEvents", "OnEnvironmentChange", "(In)Environment As Environment,(In)EnvironmentState As EnvironmentStateEnum,(In)BeforeOrAfter As EventTimingEnum,(In)Context As NameValueMap,(Out)HandlingCode As HandlingCodeEnum")
        'Me.Add("UserInterfaceEvents", "OnResetCommandBars", "(In)CommandBars As ObjectsEnumerator,(In)Context As NameValueMap")
        Me.Add("UserInterfaceEvents", "OnResetEnvironments", "(In)Environments As ObjectsEnumerator,(In)Context As NameValueMap")
        Me.Add("UserInterfaceEvents", "OnResetInventorLayout", "(In)Context As NameValueMap")
        Me.Add("UserInterfaceEvents", "OnResetMarkingMenu", "(In)MarkingMenuInternalName As String,(In)Context As NameValueMap")
        Me.Add("UserInterfaceEvents", "OnResetRibbonInterface", "(In)Context As NameValueMap")
        Me.Add("UserInterfaceEvents", "OnResetShortcuts", "(In)Context As NameValueMap")
    End Sub


    ' Adds a new event to the Events collection.    '
    ' ObjectName - Input string that contains the name of the object the event is a member of.
    ' EventName - Input string that is the name of the event.
    Public Function Add(ByVal ObjectName As String, ByVal EventName As String, ByVal Arguments As String) As InventorEvent
        Try
            ' Create a new object
            Dim newMember As New InventorEvent

            ' Set the properties passed into the method
            newMember.ObjectName = ObjectName
            newMember.EventName = EventName
            newMember.Arguments = Arguments

            ' Initialize the other values.
            newMember.ArgumentValues = ""

            ' Add the object to the collection.
            MyBase.List.Add(newMember)

            ' Return the object created
            Add = newMember
            newMember = Nothing
        Catch ex As Exception
            ' Failure.
            Return Nothing
        End Try
    End Function


    ' Returns the specified item of the collection.
    '
    ' indexKey - Index of the station to return.  The first item in the collection has an index of 1.
    Public ReadOnly Property Item(ByVal indexKey As Integer) As InventorEvent
        Get
            Return CType(MyBase.List.Item(indexKey - 1), InventorEvent)
        End Get
    End Property

    Public ReadOnly Property Item(ByVal ObjectName As String, ByVal EventName As String) As InventorEvent
        Get
            Dim currentEvent As InventorEvent
            For Each currentEvent In Me
                If currentEvent.ObjectName = ObjectName And currentEvent.EventName = EventName Then
                    Return currentEvent
                End If
            Next

            Return Nothing
        End Get
    End Property

    Public ReadOnly Property item(ByVal FullName As String) As InventorEvent
        Get
            Dim objectName As String = FullName.Substring(0, FullName.IndexOf("."))
            Dim eventName As String = FullName.Substring(FullName.IndexOf(".") + 1)

            Return Me.Item(objectName, eventName)
        End Get
    End Property

    Public ReadOnly Property IsEnabled(ByVal ListBox As CheckedListBox, ByVal ObjectName As String, ByVal EventName As String) As Boolean
        Get
            Dim i As Integer
            For i = 0 To ListBox.Items.Count - 1
                If ListBox.Items.Item(i).ToString = ObjectName & "." & EventName Then
                    If ListBox.GetItemCheckState(i) = CheckState.Checked Then
                        Return True
                    Else
                        Return False
                    End If
                End If
            Next

            Return False
        End Get
    End Property

    Public ReadOnly Property EventSetEnabled(ByVal ListBox As CheckedListBox, ByVal ObjectName As String) As Boolean
        Get
            Dim i As Integer
            For i = 0 To ListBox.Items.Count - 1
                Dim currentObject As String
                currentObject = ListBox.Items.Item(i).ToString
                currentObject = currentObject.Substring(0, currentObject.IndexOf("."))
                If currentObject = ObjectName And ListBox.GetItemCheckState(i) = CheckState.Checked Then
                    Return True
                End If
            Next

            Return False
        End Get
    End Property
End Class

Public Class InventorEvent
    Public ObjectName As String
    Public EventName As String
    Public Arguments As String
    Public ArgumentValues As String

    Public Sub GetArgumentInfo(ByVal ArgumentName As String, ByRef ArgumentValue As String, ByRef ArgumentExists As Boolean)
        ArgumentExists = False

        ' Break up the arguments.
        Dim arguments() As String = ArgumentValues.Split("~"c)
        Dim argument As String
        For Each argument In arguments
            ' Get the information for this argument.
            Dim argumentInfo() As String = argument.Split("|"c)
            If argumentInfo(0) = ArgumentName Then
                ArgumentValue = argumentInfo(1)
                ArgumentExists = True
                Return
            End If
        Next
    End Sub
End Class