/*
  Copyright(C)1998 by Autodesk, Inc.


  DESCRIPTION

  This file contains the definitions of DispIds of the various methods of the various eventsets
    supported by Inventor and its related products. Third Party programmers may require the knowledge
    of these DispIds while programming a C++ client application to receive these events. This is
    specially true when the Third Party is writing the 'sink' interfaces using ATL wizard to help
    generate the 'sink' interface code.


  HISTORY

  SS  :  06/15/01  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_EVENTSDISPIDS_
#define _AUTODESK_INVENTOR_EVENTSDISPIDS_

#define ApplicationEventsSink_OnNewDocument             0x03000610
#define ApplicationEventsSink_OnNewDocumentS            "Fires just before and soon after initialization of a new Document, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnOpenDocument            0x03000611
#define ApplicationEventsSink_OnOpenDocumentS           "Fires just before and soon after initialization of an opened Document, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnSaveDocument            0x03000612
#define ApplicationEventsSink_OnSaveDocumentS           "Fires just before and soon after save of a Document, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnCloseDocument           0x03000613
#define ApplicationEventsSink_OnCloseDocumentS          "Fires just before and soon after close of a Document, supplying the context in which this action is being taken. When fired after close, the Document passed in can only be used for IUnknown comparisons"
#define ApplicationEventsSink_OnActivateDocument        0x03000614
#define ApplicationEventsSink_OnActivateDocumentS       "Fires just before and soon after activation of a Document, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnDeactivateDocument      0x03000615
#define ApplicationEventsSink_OnDeactivateDocumentS     "Fires just before and soon after deactivation of a Document, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnQuit                    0x0300061a
#define ApplicationEventsSink_OnQuitS                   "Fires just before the shut-down operation is about to begin, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnNewEditObject           0x0300061b
#define ApplicationEventsSink_OnNewEditObjectS          "Fires just before and soon after the current edit object changes, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnTranslateDocument       0x0300061c
#define ApplicationEventsSink_OnTranslateDocumentS      "Fires just before and soon after a Document is translated in or out, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnActiveProjectChanged    0x0300061d
#define ApplicationEventsSink_OnActiveProjectChangedS   "Fires just before and soon after the active project is changed, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnDocumentChange          0x0300061e
#define ApplicationEventsSink_OnDocumentChangeS         "Fires just before the document is changed, supplying the reasons for change and the context in which this action is being taken"
#define ApplicationEventsSink_OnNewView                 0x0300061f
#define ApplicationEventsSink_OnNewViewS                "Fires just before and soon after a view is created"
#define ApplicationEventsSink_OnDisplayModeChange       0x03000620
#define ApplicationEventsSink_OnDisplayModeChangeS      "Fires just before and soon after the display mode changes"
#define ApplicationEventsSink_OnReady                   0x03000621
#define ApplicationEventsSink_OnReadyS                  "Fires only once soon after Inventor has completed its initialization. This includes initialization of all the Add-ins that are loaded at startup."
#define ApplicationEventsSink_OnCloseView               0x03000622
#define ApplicationEventsSink_OnCloseViewS              "Fires just before a view is closed"
#define ApplicationEventsSink_OnActivateView            0x03000623
#define ApplicationEventsSink_OnActivateViewS           "Fires just after a view is activated"
#define ApplicationEventsSink_OnDeactivateView          0x03000624
#define ApplicationEventsSink_OnDeactivateViewS         "Fires just after a view is deactivated"
// #define ApplicationEventsSink_OnNewStyle                0x03000625
// #define ApplicationEventsSink_OnNewStyleS                "Fires whenever a new style is created in a document"
// #define ApplicationEventsSink_OnStyleChange             0x03000626
// #define ApplicationEventsSink_OnStyleChangeS         "Fires whenever a style changes for a document"
#define ApplicationEventsSink_OnPrint                   0x03000627
#define ApplicationEventsSink_OnPrintS                  "Fires whenever a document is printed"
#define ApplicationEventsSink_OnInitializeDocument      0x03000629
#define ApplicationEventsSink_OnInitializeDocumentS     "Fires just before and soon after initialization of a Document, which is not yet open, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnTerminateDocument       0x0300062A
#define ApplicationEventsSink_OnTerminateDocumentS     "Fires just before and soon after termination of a Document, or its full closure, supplying the context in which this action is being taken. When fired after close, the Document passed in can only be used for IUnknown comparisons"
#define ApplicationEventsSink_OnMigrateDocument         0x0300062b
#define ApplicationEventsSink_OnMigrateDocumentS        "Fires just before and soon after a Document is explicitly migrated, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnRestart32BitHost          0x0300062c
#define ApplicationEventsSink_OnRestart32BitHostS         "Applies to 64-bit Inventor only. Fires after the Inventor 32-bit host process has been restarted"
#define ApplicationEventsSink_OnApplicationOptionChange   0x0300062d
#define ApplicationEventsSink_OnApplicationOptionChangeS  "Fires just before and soon after application options are modified"
#define ApplicationEventsSink_OnActivateWebView           0x0300062e
#define ApplicationEventsSink_OnActivateWebViewS          "Event that fires just after a web view is activated."
#define ApplicationEventsSink_OnDeactivateWebView         0x0300062f
#define ApplicationEventsSink_OnDeactivateWebViewS        "Event that fires just before a web view is deactivated."
#define ApplicationEventsSink_OnCloseWebView              0x03000630
#define ApplicationEventsSink_OnCloseWebViewS             "Event that fires just before a web view is closed."
#define ApplicationEventsSink_OnNewWebView                0x03000631
#define ApplicationEventsSink_OnNewWebViewS               "Fires just after a web view is created"
#define ApplicationEventsSink_OnWebViewAct                0x03000632
#define ApplicationEventsSink_OnWebViewActS               "Event that fires just after a web view action occurs"
#define ApplicationEventsSink_OnMoveApplicationWindow     0x03000633
#define ApplicationEventsSink_OnMoveApplicationWindowS    "Fires after application main window is moved"
#define ApplicationEventsSink_OnResizeApplicationWindow   0x03000634
#define ApplicationEventsSink_OnResizeApplicationWindowS  "Fires after application main window is resized, or layout is recalculated"
#define ApplicationEventsSink_OnMoveView                  0x03000635
#define ApplicationEventsSink_OnMoveViewS                 "Fires after view window is moved"
#define ApplicationEventsSink_OnResizeView                0x03000636
#define ApplicationEventsSink_OnResizeViewS               "Fires after view window is resized, or window state is changed"
#define ApplicationEventsSink_OnUndoOpenDocument          0x03000637
#define ApplicationEventsSink_OnUndoOpenDocumentS         "Fires when an open document transaction is undone"
#define ApplicationEventsSink_OnProjectDeleted            0x03000638
#define ApplicationEventsSink_OnProjectDeletedS           "Fires just before and soon after a project is deleted, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnProjectRenamed            0x03000639
#define ApplicationEventsSink_OnProjectRenamedS           "Fires just before and soon after a project is renamed, supplying the context in which this action is being taken"
#define ApplicationEventsSink_OnProjectAdded              0x03000640
#define ApplicationEventsSink_OnProjectAddedS             "Fires just soon after a project is added, supplying the context in which this action is being taken"


#define FileAccessEventsSink_OnFileResolution           0x03000fb1
#define FileAccessEventsSink_OnFileResolutionS          "Fires before the native file resolution algorithm kicks in, supplying the context in which this action is being taken. It is also fired if the file resolution mechanism fails."
#define FileAccessEventsSink_OnFileDirty                0x03000fb2
#define FileAccessEventsSink_OnFileDirtyS               "Fires before the file is 'dirtied' for the first time, supplying the context in which this action is being taken"

#define FileUIEventsSink_OnFileNewDialog                0x0300b802
#define FileUIEventsSink_OnFileNewDialogS               "Fires before a native File New dialog is displayed"
#define FileUIEventsSink_OnFileOpenDialog               0x0300b803
#define FileUIEventsSink_OnFileOpenDialogS              "Fires before a native File Open dialog is displayed"
#define FileUIEventsSink_OnFileSaveAsDialog             0x0300b804
#define FileUIEventsSink_OnFileSaveAsDialogS            "Fires before a native File Save As dialog is displayed"
#define FileUIEventsSink_OnFileInsertNewDialog          0x0300b805
#define FileUIEventsSink_OnFileInsertNewDialogS         "Fires before a native File Insert New dialog is displayed"
#define FileUIEventsSink_OnFileInsertDialog             0x0300b806
#define FileUIEventsSink_OnFileInsertDialogS            "Fires before a native File Insert dialog is displayed"
#define FileUIEventsSink_OnFileOpenFromMRU              0x0300b807
#define FileUIEventsSink_OnFileOpenFromMRUS             "Fires when a file is selected from the MRU list to open"
#define FileUIEventsSink_OnFileNew                      0x0300b808
#define FileUIEventsSink_OnFileNewS                     "Fires before a File New from standard template is executed"
#define FileUIEventsSink_OnPopulateFileMetadata         0x0300b809
#define FileUIEventsSink_OnPopulateFileMetadataS        "Fires when file names and properties are being generated by a command. By responding to this event, clients can override the file names and properties of Inventor files being generated by the command."


#define FileManagerEventsSink_OnFileDelete              0x0300b801
#define FileManagerEventsSink_OnFileDeleteS             "Fires after FileManager deletes a file"
#define FileManagerEventsSink_OnFileCopy                0x0300b802
#define FileManagerEventsSink_OnFileCopyS               "Fires before a file is moved or copied using the MoveFile or CopyFile methods of the FileManager"

#define DocumentEventsSink_OnSave                       0x0300070c
#define DocumentEventsSink_OnSaveS                      "Fires before/after saving of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnClose                      0x0300070d
#define DocumentEventsSink_OnCloseS                     "Fires before/after closing of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnActivate                   0x0300070e
#define DocumentEventsSink_OnActivateS                  "Fires after activation of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnDeactivate                 0x0300070f
#define DocumentEventsSink_OnDeactivateS                "Fires after deactivation of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnNewView                    0x03000710
#define DocumentEventsSink_OnNewViewS                   "Fires after opening of a new View of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnCloseView                  0x03000711
#define DocumentEventsSink_OnCloseViewS                 "Fires before closing of a View of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnActivateView               0x03000712
#define DocumentEventsSink_OnActivateViewS              "Fires after activation of a View of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnDeactivateView             0x03000713
#define DocumentEventsSink_OnDeactivateViewS            "Fires after deactivation of a View of this Document, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnChangeSelectSet            0x03000714
#define DocumentEventsSink_OnChangeSelectSetS           "Fires when the current selection set changes, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnDelete                     0x03000715
#define DocumentEventsSink_OnDeleteS                    "Fires when an object owned by this document is deleted, supplying the context in which this action is being taken"
#define DocumentEventsSink_OnChange                     0x03000716
#define DocumentEventsSink_OnChangeS                    "Fires when this document changes, supplying the reasons for change and the context in which this action is being taken"

#define TransactionEventsSink_OnCommitMeth              0x03002981
#define TransactionEventsSink_OnCommitMethS             "Fires before/after a transaction is committed. Successful commit adds to the collection of 'Committed Transactions' held by the manager"
#define TransactionEventsSink_OnUndoMeth                0x03002982
#define TransactionEventsSink_OnUndoMethS               "Fires before/after a transaction is undone. Successful undo adds to the collection of 'Undone Transactions' held by the manager"
#define TransactionEventsSink_OnRedoMeth                0x03002983
#define TransactionEventsSink_OnRedoMethS               "Fires before/after a transaction is redone"
#define TransactionEventsSink_OnAbortMeth               0x03002984
#define TransactionEventsSink_OnAbortMethS              "Fires before/after an ongoing transaction is aborted due to an error condition"
#define TransactionEventsSink_OnDeleteMeth              0x03002985
#define TransactionEventsSink_OnDeleteMethS             "Fires before/after a transaction is deleted"


#define InteractionEventsSink_OnActivateMeth            0x03005481
#define InteractionEventsSink_OnActivateMethS           "Fires signaling the client to begin the associated activity"
#define InteractionEventsSink_OnTerminateMeth           0x03005482
#define InteractionEventsSink_OnTerminateMethS          "Fires signaling the client to halt the associated activity"
#define InteractionEventsSink_OnSuspendMeth             0x03005483
#define InteractionEventsSink_OnSuspendMethS            "Fires signaling the client to temporarily suspend its associated activities"
#define InteractionEventsSink_OnResumeMeth              0x03005484
#define InteractionEventsSink_OnResumeMethS             "Fires signaling the client to resume its associated activities"
#define InteractionEventsSink_OnHelpMeth                0x03005485
#define InteractionEventsSink_OnHelpMethS               "Fires signaling the client to present help for the associated activity"


#define SelectEventsSink_OnPreSelectMeth                0x03005581
#define SelectEventsSink_OnPreSelectMethS               "Fires signaling that a particular object has been indicated as a potential candidate for selection"
#define SelectEventsSink_OnPreSelectMouseMoveMeth       0x03005582
#define SelectEventsSink_OnPreSelectMouseMoveMethS      "Fires on a mouse move while a given object has been indicated as a potential candidate for selection"
#define SelectEventsSink_OnStopPreSelectMeth            0x03005583
#define SelectEventsSink_OnStopPreSelectMethS           "Fires signaling that a particular object has just been gestured out of being a potential candidate for selection"
#define SelectEventsSink_OnSelectMeth                   0x03005584
#define SelectEventsSink_OnSelectMethS                  "Fires signaling that a particular object has just been selected by the end-user"
#define SelectEventsSink_OnUnSelectMeth                 0x03005585
#define SelectEventsSink_OnUnSelectMethS                "Fires signaling that a particular object has just been un-selected by the end-user"

#define MouseEventsSink_OnMouseUpMeth                   0x03005681
#define MouseEventsSink_OnMouseUpMethS                  "Fires when a mouse button trasnsitions to 'up'"
#define MouseEventsSink_OnMouseDownMeth                 0x03005682
#define MouseEventsSink_OnMouseDownMethS                "Fires when a mouse button trasnsitions to 'down'"
#define MouseEventsSink_OnMouseClickMeth                0x03005683
#define MouseEventsSink_OnMouseClickMethS               "Fires when a mouse button has experienced a down followed by an up within the same window"
#define MouseEventsSink_OnMouseDoubleClickMeth          0x03005684
#define MouseEventsSink_OnMouseDoubleClickMethS         "Fires when a mouse button has experienced a double-click"
#define MouseEventsSink_OnMouseMoveMeth                 0x03005685
#define MouseEventsSink_OnMouseMoveMethS                "Fires when the mouse has been moved to a new position"
#define MouseEventsSink_OnMouseLeaveMeth                0x03005686
#define MouseEventsSink_OnMouseLeaveMethS               "Fires when the mouse leaves a view"

#define KeyboardEventsSink_OnKeyDownMeth                0x03005881
#define KeyboardEventsSink_OnKeyDownMethS               "Fires when a key is pressed down. The precise hardware key pressed is returned"
#define KeyboardEventsSink_OnKeyUpMeth                  0x03005882
#define KeyboardEventsSink_OnKeyUpMethS                 "Fires when a key transitions to the up position. The precise hardware key released is returned"
#define KeyboardEventsSink_OnKeyPressMeth               0x03005883
#define KeyboardEventsSink_OnKeyPressMethS              "Fires when a key is clicked. The ASCII value of the key is returned"

#define TriadEventsSink_OnActivateMeth                  0x0300ec81
#define TriadEventsSink_OnActivateMethS                 "Fires when the triad is activated"
#define TriadEventsSink_OnMoveMeth                      0x0300ec82
#define TriadEventsSink_OnMoveMethS                     "Fires when the triad moves as a result of a drag, reposition or user entering values for translation and rotation"
#define TriadEventsSink_OnMoveTriadOnlyToggleMeth       0x0300ec83
#define TriadEventsSink_OnMoveTriadOnlyToggleMethS      "Superseded; use OnMoveTriadOnlyToggle2"
#define TriadEventsSink_OnStartMoveMeth                 0x0300ec84
#define TriadEventsSink_OnStartMoveMethS                "Fires when the triad begins to move as a result of a drag, reposition or user entering values for translation and rotation"
#define TriadEventsSink_OnTerminateMeth                 0x0300ec85
#define TriadEventsSink_OnTerminateMethS                "Superseded; use OnTerminate2"
#define TriadEventsSink_OnSegmentSelectionChangeMeth    0x0300ec86
#define TriadEventsSink_OnSegmentSelectionChangeMethS   "Fires every time a segment of a triad is selected"
#define TriadEventsSink_OnEndMoveMeth                   0x0300ec87
#define TriadEventsSink_OnEndMoveMethS                  "Fires when the user ends an intermediate move of the triad"
#define TriadEventsSink_OnStartSequenceMeth             0x0300ec88
#define TriadEventsSink_OnStartSequenceMethS            "Superseded; use OnStartSequence2"
#define TriadEventsSink_OnEndSequenceMeth               0x0300ec89
#define TriadEventsSink_OnEndSequenceMethS              "Superseded; use OnEndSequence2"
#define TriadEventsSink_OnMoveTriadOnlyToggle2Meth      0x0300ec8a
#define TriadEventsSink_OnMoveTriadOnlyToggle2MethS     "Fires when the 'Move Triad Only' option is toggled"
#define TriadEventsSink_OnTerminate2Meth                0x0300ec8b
#define TriadEventsSink_OnTerminate2MethS               "Fires when the triad is terminated"
#define TriadEventsSink_OnEndSequence2Meth              0x0300ec8c
#define TriadEventsSink_OnEndSequence2MethS             "Fires when the user ends a move sequence of the triad"

#define ManipulatorEventsSink_OnManipulatorElementSelectionChangeMeth   0x0301e181
#define ManipulatorEventsSink_OnManipulatorElementSelectionChangeMethS  "Fires when a manipulator element is selected"
#define ManipulatorEventsSink_OnStartDragMeth                           0x0301e182
#define ManipulatorEventsSink_OnStartDragMethS                          "Fires when a manipulator element is selected"
#define ManipulatorEventsSink_OnEndDragMeth                             0x0301e183
#define ManipulatorEventsSink_OnEndDragMethS                            "Fires when the user ends an intermediate drag of the manipulator"
#define ManipulatorEventsSink_OnDragMeth                                0x0301e184
#define ManipulatorEventsSink_OnDragMethS                               "Fires fires when the manipulator moves as a result of a drag, reposition or user entering values for translation, rotation and scaling"

#define MeasureEventsSink_OnSelectParameterMeth         0x03014b81
#define MeasureEventsSink_OnSelectParameterMethS        "Fires when the user selects a dimension or parameter."
#define MeasureEventsSink_OnMeasureMeth                 0x03014b82
#define MeasureEventsSink_OnMeasureMethS                "Fires when the user selects entities for measure. Measured value is returned in centimeters for kDistanceMeasure and in radians for kAngleMeasure."

#define BrowserPaneSink_OnActivateMeth                  0x03007901
#define BrowserPaneSink_OnActivateMethS                 "Fires when a Browser Pane is activated"
#define BrowserPaneSink_OnDeactivateMeth                0x03007902
#define BrowserPaneSink_OnDeactivateMethS               "Fires when a Browser Pane is deactivated"
#define BrowserPaneSink_OnHelpMeth                      0x03007903
#define BrowserPaneSink_OnHelpMethS                     "Fires when a Browser Pane is active and the user presses its help button. Handle this event to provide browser pane specific help."

#define BrowserPanesSink_OnBrowserNodeActivateMeth           0x0300db01
#define BrowserPanesSink_OnBrowserNodeActivateMethS          "Event that is fired whenever a node is activated by the user"
#define BrowserPanesSink_OnBrowserNodeGetDisplayObjectsMeth  0x0300db02
#define BrowserPanesSink_OnBrowserNodeGetDisplayObjectsMethS "Event that is fired when a user requests that the objects represented by a browser node be highlighted"
#define BrowserPanesSink_OnBrowserNodeLabelEditMeth          0x0300db03
#define BrowserPanesSink_OnBrowserNodeLabelEditMethS         "Event that is fired whenever a node is renamed by the user"
#define BrowserPanesSink_OnBrowserNodeDeleteEntryMeth        0x0300db04
#define BrowserPanesSink_OnBrowserNodeDeleteEntryMethS       "Event that is fired whenever the user requests that a node be deleted"
#define BrowserPanesSink_OnBrowserNodesReorderMeth           0x0300db05
#define BrowserPanesSink_OnBrowserNodesReorderMethS          "Event that fires just before and after browser nodes are reordered."

#define PartEventsSink_OnSurfaceBodyChangedMeth         0x05002501
#define PartEventsSink_OnSurfaceBodyChangedMethS        "Fires after any change occurs that impacts the Surface Body(ies)"

#define AssemblyEventsSink_OnAssemblyChangedMeth            0x06001001
#define AssemblyEventsSink_OnAssemblyChangedMethS           "Fires after any change occurs that impacts the Assembly Structure"
#define AssemblyEventsSink_OnAssemblyChangeMeth             0x06001003
#define AssemblyEventsSink_OnAssemblyChangeMethS            "Fires when any change occurs that impacts the Assembly Structure"

#define AssemblyEventsSink_OnNewOccurrenceMeth              0x06001004
#define AssemblyEventsSink_OnNewOccurrenceMethS             "Fires whenever an occurrence is created"
#define AssemblyEventsSink_OnOccurrenceChangeMeth           0x06001005
#define AssemblyEventsSink_OnOccurrenceChangeMethS          "Fires whenever an occurrence changes"
#define AssemblyEventsSink_OnNewConstraintMeth               0x06001006
#define AssemblyEventsSink_OnNewConstraintMethS              "Fires whenever an assembly constraint or iMateResult is created"
//#define AssemblyEventsSink_OnConstraintChangeMeth            0x06001007
//#define AssemblyEventsSink_OnConstraintChangeMethS           "Fires whenever an assembly constraint or iMateResult changes"
#define AssemblyEventsSink_OnDeleteMeth                     0x06001008
#define AssemblyEventsSink_OnDeleteMethS                    "Fires when an Assembly related object is deleted, supplying the context in which this action is being taken"
#define AssemblyEventsSink_OnLoadStateChangeMeth            0x06001009
#define AssemblyEventsSink_OnLoadStateChangeMethS           "Fires when an assembly document goes from lite to full or full to lite loading"
#define AssemblyEventsSink_OnNewRelationshipMeth            0x06001010
#define AssemblyEventsSink_OnNewRelationshipMethS           "Fires whenever an assembly relationship or iMateResult is created"


#define ButtonDefinitionHandlerEventsSink_OnClickMeth       0x0300a680
#define ButtonDefinitionHandlerEventsSink_OnClickMethS      "Fires when ButtonDefinitionHandlerObject is clicked"

#define EnvironmentBaseHandlerEventsSink_OnActivateMeth     0x0300a980
#define EnvironmentBaseHandlerEventsSink_OnActivateMethS    "Fires when Environment is activated"
#define EnvironmentBaseHandlerEventsSink_OnDeactivateMeth   0x0300a981
#define EnvironmentBaseHandlerEventsSink_OnDeactivateMethS  "Fires when Environment is deactivated"

#define DocumentSubTypeHandlerEventsSink_OnChangeTypeMeth   0x0300af80
#define DocumentSubTypeHandlerEventsSink_OnChangeTypeMethS  "Fires when DocumentSubType is changed"

#define UserInputEventsSink_OnStartCommand                  0x03002202
#define UserInputEventsSink_OnStartCommandS                 "Fires before starting up a command"
#define UserInputEventsSink_OnStopCommand                   0x03002203
#define UserInputEventsSink_OnStopCommandS                  "Fires after a command terminates"
#define UserInputEventsSink_OnContextMenuOld                0x03002204
#define UserInputEventsSink_OnContextMenuOldS               "Fires just before context menu is about to be displayed"
#define UserInputEventsSink_OnDrag                          0x03002205
#define UserInputEventsSink_OnDragS                         "Fires when the user performs a drag operation when no command is active"
#define UserInputEventsSink_OnContextMenu                   0x03002206
#define UserInputEventsSink_OnContextMenuS                  "Fires just before context menu is about to be displayed"
#define UserInputEventsSink_OnActivateCommand               0x03002207
#define UserInputEventsSink_OnActivateCommandS              "Fires just before a command starts"
#define UserInputEventsSink_OnTerminateCommand              0x03002208
#define UserInputEventsSink_OnTerminateCommandS             "Fires just before a command terminates"
#define UserInputEventsSink_OnDoubleClick                   0x03002209
#define UserInputEventsSink_OnDoubleClickS                  "Fires when the user performs a double click operation when no command is active"
#define UserInputEventsSink_OnPreSelect                     0x0300220a
#define UserInputEventsSink_OnPreSelectS                    "Fires when the user hovers over an Inventor object, and it is a potential candidate for selection"
#define UserInputEventsSink_OnStopPreSelect                 0x0300220b
#define UserInputEventsSink_OnStopPreSelectS                "Fires when the user hovers away from an Inventor object and it is no longer highlighted"
#define UserInputEventsSink_OnSelect                        0x0300220c
#define UserInputEventsSink_OnSelectS                       "Fires when the user selects an object by clicking"
#define UserInputEventsSink_OnUnSelect                      0x0300220d
#define UserInputEventsSink_OnUnSelectS                     "Fires when an object is un-selected in any way (by selecting some other object. clicking in space, etc.)"
#define UserInputEventsSink_OnRadialMarkingMenu             0x0300220e
#define UserInputEventsSink_OnRadialMarkingMenuS            "Fires before the marking menu is displayed to the user or before the user gestures using the right mouse button"
#define UserInputEventsSink_OnLinearMarkingMenu             0x0300220f
#define UserInputEventsSink_OnLinearMarkingMenuS            "Fires before the overflow context menu is displayed to the user"
#define UserInputEventsSink_OnContextualMiniToolbar         0x03002210
#define UserInputEventsSink_OnContextualMiniToolbarS        "Fires before contextual commands are displayed to the user in the graphics window when the user selects an object"
#define UserInputEventsSink_OnDeleteKeyUp                   0x03002211
#define UserInputEventsSink_OnDeleteKeyUpS                  "Fires when the user performs a delete key click when no command is active"
#define UserInputEventsSink_OnMarkTutorialCommand			0x03002212
#define UserInputEventsSink_OnMarkTutorialCommandS			"Fires when click a command on ribbon during the tutorial record process"

#define ClientBrowserNodeDefinitionSink_OnActivateMeth            0x0300d201
#define ClientBrowserNodeDefinitionSink_OnActivateMethS           "Event that is fired whenever this node is activated by the user"
#define ClientBrowserNodeDefinitionSink_OnGetDisplayObjectsMeth   0x0300d202
#define ClientBrowserNodeDefinitionSink_OnGetDisplayObjectsMethS  "Event that is fired when a user requests that the objects represented by this browser node be highlighted"
#define ClientBrowserNodeDefinitionSink_OnLabelEditMeth           0x0300d203
#define ClientBrowserNodeDefinitionSink_OnLabelEditMethS          "Event that is fired whenever this node is renamed by the user"

#define BrowserNodeDefinitionSink_OnLabelEditMeth           0x0300d801
#define BrowserNodeDefinitionSink_OnLabelEditMethS          "Event that is fired whenever this node is renamed by the user"

#define ModelingEventsSink_OnDeleteMeth                 0x03012d11
#define ModelingEventsSink_OnDeleteMethS                "Fires when an object is deleted, supplying the context in which this action is being taken"
#define ModelingEventsSink_OnNewFeatureMeth             0x03012d12
#define ModelingEventsSink_OnNewFeatureMethS            "Event that is fired whenever a feature is created."
#define ModelingEventsSink_OnFeatureChangeMeth          0x03012d13
#define ModelingEventsSink_OnFeatureChangeMethS         "Event that is fired whenever a feature changes."
#define ModelingEventsSink_OnNewParameterMeth           0x03012d14
#define ModelingEventsSink_OnNewParameterMethS          "Event that is fired whenever a parameter is created."
#define ModelingEventsSink_OnParameterChangeMeth        0x03012d15
#define ModelingEventsSink_OnParameterChangeMethS       "Event that is fired whenever a parameter changes."
#define ModelingEventsSink_OnClientFeatureDoubleClickMeth  0x03012d1c
#define ModelingEventsSink_OnClientFeatureDoubleClickMethS "Event that fires when the user double-click a client feature."
#define ModelingEventsSink_OnClientFeatureSolveMeth        0x03012d1d
#define ModelingEventsSink_OnClientFeatureSolveMethS       "Event that fires before and after the client feature is solved"
#define ModelingEventsSink_OnGenerateMemberMeth        0x03012d1e
#define ModelingEventsSink_OnGenerateMemberMethS       "Event that fires before and after an iPart or an iAssembly member is being generated or regenerated"
#define ModelingEventsSink_OnModelAnnotationsSolveMeth  0x03012d1f
#define ModelingEventsSink_OnModelAnnotationsSolveMethS "Event that fires before and after ModelAnnotations are solved."
#define ModelingEventsSink_OnGeneralSurfaceProfileGDTSolveMeth    0x03012d20
#define ModelingEventsSink_OnGeneralSurfaceProfileGDTSolveMethS   "Event that fires after General Surface Profile tolerance GDT is solved."
#define ModelingEventsSink_OnModelAnnotationsScaleChangeMeth  0x03012d21
#define ModelingEventsSink_OnModelAnnotationsScaleChangeMethS "Event that fires before and after scale of model annotations is changed."
#define ModelingEventsSink_OnPreGenerateMemberMeth      0x03012d22
#define ModelingEventsSink_OnPreGenerateMemberMethS     "Event that fires before OnGenerateMember"
#define ModelingEventsSink_OnGenerateModelStateMemberMeth   0x03012d23
#define ModelingEventsSink_OnGenerateModelStateMemberMethS  "Event that fires before and after an model state member document is being generated or regenerated."

#define SketchEventsSink_OnNewSketchMeth                0x03012d16
#define SketchEventsSink_OnNewSketchMethS               "Event that is fired whenever a sketch is created."
#define SketchEventsSink_OnSketchChangeMeth             0x03012d17
#define SketchEventsSink_OnSketchChangeMethS            "Event that is fired whenever a sketch changes."
#define SketchEventsSink_OnNewSketch3DMeth              0x03012d18
#define SketchEventsSink_OnNewSketch3DMethS             "Event that is fired whenever a sketch 3D is created."
#define SketchEventsSink_OnSketch3DChangeMeth           0x03012d19
#define SketchEventsSink_OnSketch3DChangeMethS          "Event that is fired whenever a sketch 3D changes."
#define SketchEventsSink_OnSketch3DSolveMeth            0x03012d1A
#define SketchEventsSink_OnSketch3DSolveMethS           "Event that is fired whenever a sketch or sketch 3D containing client controlled geometry needs to be updated."
#define SketchEventsSink_OnDeleteMeth                   0x03012d1B
#define SketchEventsSink_OnDeleteMethS                  "Fires when a Sketch object is deleted, supplying the context in which this action is being taken"

#define StyleEventsSink_OnNewStyleMeth                  0x03014311
#define StyleEventsSink_OnNewStyleMethS                 "Event that is fired whenever a Style is created in a document."
#define StyleEventsSink_OnActivateStyleMeth             0x03014312
#define StyleEventsSink_OnActivateStyleMethS            "Event that is fired whenever the current style for a document changes."
#define StyleEventsSink_OnDeleteMeth                    0x03014313
#define StyleEventsSink_OnDeleteMethS                   "Fires when a style object is deleted from a document, supplying the context in which this action is being taken"
#define StyleEventsSink_OnStyleChangeMeth               0x03014314
#define StyleEventsSink_OnStyleChangeMethS              "Fires whenever a style object of a document changes, supplying the context in which this action is being taken"
#define StyleEventsSink_OnMigrateStyleLibraryMeth       0x03014315
#define StyleEventsSink_OnMigrateStyleLibraryMethS      "Fires whenever a style library migrates, supplying the context in which this action is being taken"


#define RepresentationEventsSink_OnNewDesignViewRepresentationMeth  0x03013711
#define RepresentationEventsSink_OnNewDesignViewRepresentationMethS  "Event that is fired whenever a DesignViewRepresentation is created."
#define RepresentationEventsSink_OnActivateDesignViewRepresentationMeth  0x03013712
#define RepresentationEventsSink_OnActivateDesignViewRepresentationMethS  "Event that is fired whenever a DesignViewRepresentation changes."
#define RepresentationEventsSink_OnNewPositionalRepresentationMeth  0x03013713
#define RepresentationEventsSink_OnNewPositionalRepresentationMethS  "Event that is fired whenever a PositionalRepresentation is created."
#define RepresentationEventsSink_OnActivatePositionalRepresentationMeth  0x03013714
#define RepresentationEventsSink_OnActivatePositionalRepresentationMethS  "Event that is fired whenever a PositionalRepresentation changes."
#define RepresentationEventsSink_OnNewLevelOfDetailRepresentationMeth  0x03013715
#define RepresentationEventsSink_OnNewLevelOfDetailRepresentationMethS  "Event that is fired whenever a LevelOfDetailRepresentation is created"
#define RepresentationEventsSink_OnActivateLevelOfDetailRepresentationMeth  0x03013716
#define RepresentationEventsSink_OnActivateLevelOfDetailRepresentationMethS  "Event that is fired whenever a LevelOfDetailRepresentation changes"
#define RepresentationEventsSink_OnDeleteMeth           0x03013717
#define RepresentationEventsSink_OnDeleteMethS          "Fires when a Representation object is deleted, supplying the context in which this action is being taken"
#define RepresentationEventsSink_OnNewDesignViewMeth        0x03013718
#define RepresentationEventsSink_OnNewDesignViewMethS       "Event that is fired whenever a DesignViewRepresentation is created."
#define RepresentationEventsSink_OnActivateDesignViewMeth   0x03013719
#define RepresentationEventsSink_OnActivateDesignViewMethS  "Event that is fired whenever a DesignViewRepresentation changes."
#define RepresentationEventsSink_OnNewSectionViewMeth       0x0301371A
#define RepresentationEventsSink_OnNewSectionViewMethS      "Event that is fired whenever an section view is created in part or assembly."

#define DrawingViewEventsSink_OnViewUpdateMeth          0x07002601
#define DrawingViewEventsSink_OnViewUpdateMethS         "Event that is fired whenever the view updates due to change in the model. This event is also fired for 'Associative Draft Views' due to changes to the attributes of referenced documents."

#define ControlDefinitionEventsSink_OnCommandInputsMeth            0x0300e501
#define ControlDefinitionEventsSink_OnCommandInputsMethS           "Event that is fired whenever the command requests an input from the user"

#define ChangeDefinitionSink_OnReplayMeth                0x0300e1b1
#define ChangeDefinitionSink_OnReplayMethS               "Fired by Inventor in a script replay scenario. At this point, the client who created this ChangeDefinition is expected to create a new ChangeProcessor using the CreateChangeProcessor method and advise onto it’s events."

#define ChangeProcessorSink_OnExecuteMeth                0x0300e2b1
#define ChangeProcessorSink_OnExecuteMethS               "Fired when Inventor is in a state to accept changes to data.  This is the event where the client application executes its logic on the specified document."
#define ChangeProcessorSink_OnReadFromScriptMeth         0x0300e2b2
#define ChangeProcessorSink_OnReadFromScriptMethS        "Fired in a replay scenario supplying the cached Inputs string.  The client application interprets the inputs and converts them into meaningful data for use in the execution of logic in the OnExecute event.  This event is always followed by the OnExecute event."
#define ChangeProcessorSink_OnWriteToScriptMeth          0x0300e2b3
#define ChangeProcessorSink_OnWriteToScriptMethS         "Fired before execution of the change when scripting is enabled.  The Inputs argument should be set with a formatted string of the arguments.  The Inputs string may be persisted for eventual replay, such as a transcript replay."
#define ChangeProcessorSink_OnTerminateMeth              0x0300e2b4
#define ChangeProcessorSink_OnTerminateMethS             "Fired when this ChangeProcessor is done being used for the current execution"

#define ComboBoxDefinitionSink_OnSelectMeth              0x03009e81
#define ComboBoxDefinitionSink_OnSelectMethS             "Fires when ComboBox is selected"
#define ComboBoxDefinitionSink_OnHelpMeth                0x03009e82
#define ComboBoxDefinitionSink_OnHelpMethS               "Fires signaling the client to present help for the associated command"

#define ButtonDefinitionSink_OnExecuteMeth               0x03009c81
#define ButtonDefinitionSink_OnExecuteMethS              "Fires when ButtonDefinition is Executed"
#define ButtonDefinitionSink_OnHelpMeth                  0x03009c82
#define ButtonDefinitionSink_OnHelpMethS                 "Fires signaling the client to present help for the associated command"

#define ContentQuerySink_OnCancelMeth                    0x0300f101
#define ContentQuerySink_OnCancelMethS                   "Fires when a Content Active Query is canceled"
#define ContentQuerySink_OnDoneMeth                      0x0300f102
#define ContentQuerySink_OnDoneMethS                     "Fires when a Content Active Query is done"

#define PanelBarEventsSink_OnCommandBarSelectMeth       0x0300a05
#define PanelBarEventsSink_OnCommandBarSelectMethS      "Fires when current selection of PanelBar is changed"

#define DrawingEventsSink_OnRetrieveDimensionsMeth       0x07006101
#define DrawingEventsSink_OnRetrieveDimensionsMethS      "Event that is fired whenever dimensions are retrieved for a drawing sketch"
#define DrawingEventsSink_OnDeleteMeth                   0x07006102
#define DrawingEventsSink_OnDeleteMethS                  "Fires when an object is deleted, supplying the context in which this action is being taken"
//#define DrawingEventsSink_OnNewDrawingViewMeth         0x07006103
//#define DrawingEventsSink_OnNewDrawingViewMethS        "Event that is fired whenever a new drawing view is created"
//#define DrawingEventsSink_OnDrawingViewChangeMeth      0x07006104
//#define DrawingEventsSink_OnDrawingViewChangeMethS     "Event that is fired whenever a new drawing view is created"
#define DrawingEventsSink_OnRetrieveDimensionsNewMeth    0x07006105
#define DrawingEventsSink_OnRetrieveDimensionsNewMethS   "Event that is fired whenever dimensions are retrieved for a drawing sketch"


#define UserInterfaceEventsSink_OnResetEnvironmentsMeth     0x03011201
#define UserInterfaceEventsSink_OnResetEnvironmentsMethS    "Event that is fired whenever ResetEnvironments is executed"
#define UserInterfaceEventsSink_OnResetCommandBarsMeth      0x03011202
#define UserInterfaceEventsSink_OnResetCommandBarsMethS     "Event that is fired whenever ResetCommandsBars is executed"
#define UserInterfaceEventsSink_OnEnvironmentChange         0x03011203
#define UserInterfaceEventsSink_OnEnvironmentChangeS        "Fires when the active environment changes"
#define UserInterfaceEventsSink_OnResetShortcutsMeth        0x03011204
#define UserInterfaceEventsSink_OnResetShortcutsMethS       "Event that is fired when command shortcuts/aliases are reset in the Customize dialog"
#define UserInterfaceEventsSink_OnResetRibbonInterfaceMeth  0x03011205
#define UserInterfaceEventsSink_OnResetRibbonInterfaceMethS "Event that is fired when the ribbon user interface is reset"
#define UserInterfaceEventsSink_OnResetMarkingMenuMeth  0x03011206
#define UserInterfaceEventsSink_OnResetMarkingMenuMethS "Event that is fired when the marking menu user interface is reset"
#define UserInterfaceEventsSink_OnResetInventorLayoutMeth  0x03011207
#define UserInterfaceEventsSink_OnResetInventorLayoutMethS "Event that is fired when the Inventor layout is reset"

#define ContentCenterDialogEventsSink_OnSelectMeth              0x03013001
#define ContentCenterDialogEventsSink_OnSelectMethS             "Event that is fired when the user's action provides focus onto a selectable item (Category, Family or Member)"
#define ContentCenterDialogEventsSink_OnSelectionCommitMeth     0x03013002
#define ContentCenterDialogEventsSink_OnSelectionCommitMethS    "Event that is fired when the user has a confirmed selection of a Content Center Item (Category, Family or Member, as appropriate)"
#define ContentCenterDialogEventsSink_OnTerminateMeth           0x03013003
#define ContentCenterDialogEventsSink_OnTerminateMethS          "Event that is fired when the user decides to cancel out of the dialog"

#define FileDialogEventsSink_OnOptions                  0x030144b1
#define FileDialogEventsSink_OnOptionsS                 "Fires when the user clicks the Options button on the file dialog. Clients can use this event to put up their own options dialog."
#define FileDialogEventsSink_OnOptionsReset             0x030144b2
#define FileDialogEventsSink_OnOptionsResetS            "Fires when the action to reset options on the file dialog occurs, e.g. file filter type changes, etc."

#define ContentCenterEventsSink_OnRefreshStandardComponents     0x03015b01
#define ContentCenterEventsSink_OnRefreshStandardComponentsS    "Fires when a standard component is refreshed"

#define ProgressBarSink_OnCancelButtonMeth               0x03015981
#define ProgressBarSink_OnCancelButtonMethS              "Event that fires when the user hits"

#define CameraEventsSink_OnCameraChangeMeth               0x03019581
#define CameraEventsSink_OnCameraChangeMethS              "Event that fires when the camera of a view has been modified but before the view has been updated"

#define DockableWindowsEventsSink_OnHelpMeth          0x0301b051
#define DockableWindowsEventsSink_OnHelpMethS         "Fires whenever the user clicks the help button in a dockable window"

#define DockableWindowsEventsSink_OnHideMeth          0x0301b052
#define DockableWindowsEventsSink_OnHideMethS         "Fires whenever a dockable window is hidden (i.e. closed)"

#define DockableWindowsEventsSink_OnShowMeth          0x0301b053
#define DockableWindowsEventsSink_OnShowMethS         "Fires whenever a dockable window is shown"

#define MiniToolbarSink_OnApplyMeth                    0x0301ac81
#define MiniToolbarSink_OnApplyMethS                   "Event that fires when the ‘Apply’ button is clicked"
#define MiniToolbarSink_OnCancelMeth                   0x0301ac82
#define MiniToolbarSink_OnCancelMethS                  "Event that fires when the ‘Cancel’ button is clicked"
#define MiniToolbarSink_OnOKMeth                       0x0301ac83
#define MiniToolbarSink_OnOKMethS                      "Event that fires when the ‘OK’ button is clicked"
#define MiniToolbarSink_OnStartMoveMeth                0x0301ac84
#define MiniToolbarSink_OnStartMoveMethS               "Event that fires when this MiniToolbar begins to move as a result of a drag or a reposition"
#define MiniToolbarSink_OnMoveMeth                     0x0301ac85
#define MiniToolbarSink_OnMoveMethS                    "Event that fires when this MiniToolbar moves as a result of a drag"
#define MiniToolbarSink_OnEndMoveMeth                  0x0301ac86
#define MiniToolbarSink_OnEndMoveMethS                 "Event that fires when a drag or a reposition of this MiniToolbar ends"
#define MiniToolbarSink_OnHideMeth                     0x0301ac87
#define MiniToolbarSink_OnHideMethS                    "Event that fires when this MiniToolbar is hidden"
#define MiniToolbarSink_OnShowMeth                     0x0301ac88
#define MiniToolbarSink_OnShowMethS                    "Event that fires when this MiniToolbar is shown"

#define BalloonTipSink_OnClickMeth                    0x0301aeb1
#define BalloonTipSink_OnClickMethS                   "Event that fires when the BalloonTip object is clicked"
#define BalloonTipSink_OnDisplayMeth                  0x0301aeb2
#define BalloonTipSink_OnDisplayMethS                 "Event that fires when the BalloonTip object is being displayed"

#define HelpEventsSink_OnApplicationHelpMeth          0x0301b201
#define HelpEventsSink_OnApplicationHelpMethS         "Event that fires before Application Help is displayed"

#define DriveConstraintSettingsSink_OnCollisionMeth   0x06009091
#define DriveConstraintSettingsSink_OnCollisionMethS  "Event that is fired whenever a collision occurs during the animation/play of the constraint"

#define DriveSettingsSink_OnCollisionMeth			  0x06009092
#define DriveSettingsSink_OnCollisionMethS			  "Event that is fired whenever a collision occurs during the animation/play"

#define ReferenceKeyEventsSink_OnBindKeyToObjectMeth  0x0301b381
#define ReferenceKeyEventsSink_OnBindKeyToObjectMethS "Event that fires when either the BindKeyToObject or CanBindKeyToObject method of the ReferenceKeyManager object is called with a custom reference key"
#define MiniToolbarButtonSink_OnClickMeth             0x0301b581
#define MiniToolbarButtonSink_OnClickMethS            "Event that is fired when the button is clicked by the user"
#define MiniToolbarCheckBoxSink_OnClickMeth           0x0301b681
#define MiniToolbarCheckBoxSink_OnClickMethS          "Event that is fired when the check box is toggled by the user"
#define MiniToolbarComboBoxSink_OnPreMenuDisplayMeth  0x0301b781
#define MiniToolbarComboBoxSink_OnPreMenuDisplayMethS "Event that is fired when the user clicks the combobox"
#define MiniToolbarComboBoxSink_OnItemHoverEndMeth    0x0301b782
#define MiniToolbarComboBoxSink_OnItemHoverEndMethS   "Event that is fired when the user stops hovering over an item in the combobox in the expanded state"
#define MiniToolbarComboBoxSink_OnItemHoverStartMeth  0x0301b783
#define MiniToolbarComboBoxSink_OnItemHoverStartMethS "Event that is fired when the user starts to hover over an item in the combobox in the expanded state"
#define MiniToolbarComboBoxSink_OnItemRemoveMeth      0x0301b784
#define MiniToolbarComboBoxSink_OnItemRemoveMethS     "Event that is fired when the user removes an item from the combobox"
#define MiniToolbarComboBoxSink_OnSelectMeth          0x0301b785
#define MiniToolbarComboBoxSink_OnSelectMethS         "Event that is fired soon after the user changes the currently selected item using the drop down"
#define MiniToolbarDropdownSink_OnPreMenuDisplayMeth  0x0301b881
#define MiniToolbarDropdownSink_OnPreMenuDisplayMethS "Event that is fired when the user clicks the currently selected item"
#define MiniToolbarDropdownSink_OnSelectMeth          0x0301b882
#define MiniToolbarDropdownSink_OnSelectMethS         "Event that is fired soon after the user changes the currently selected item using the drop down"
#define MiniToolbarDropdownSink_OnItemRemoveMeth      0x0301b883
#define MiniToolbarDropdownSink_OnItemRemoveMethS     "Event that is fired when the user removes an item from the dropdown"
#define MiniToolbarDropdownSink_OnItemHoverEndMeth    0x0301b884
#define MiniToolbarDropdownSink_OnItemHoverEndMethS   "Event that is fired when the user stops hovering over an item in the drop down in the expanded state"
#define MiniToolbarDropdownSink_OnItemHoverStartMeth  0x0301b885
#define MiniToolbarDropdownSink_OnItemHoverStartMethS "Event that is fired when the user starts to hover over an item in the drop down in the expanded state"
#define MiniToolbarValueEditorSink_OnChangeMeth       0x0301b981
#define MiniToolbarValueEditorSink_OnChangeMethS      "Event that is fired when the content of the value editor is changed by the user"
#define MiniToolbarValueEditorSink_OnEnterMeth        0x0301b982
#define MiniToolbarValueEditorSink_OnEnterMethS       "Event that is fired just before the control gets focus"
#define MiniToolbarValueEditorSink_OnExitMeth         0x0301b983
#define MiniToolbarValueEditorSink_OnExitMethS        "Event that is fired just before the control loses focus"
#define MiniToolbarTextBoxSink_OnChangeMeth           0x0301fc81
#define MiniToolbarTextBoxSink_OnChangeMethS          "Event that is fired when the content of the value editor is changed by the user"
#define MiniToolbarTextBoxSink_OnEnterMeth            0x0301fc82
#define MiniToolbarTextBoxSink_OnEnterMethS           "Event that is fired just before the control gets focus"
#define MiniToolbarTextBoxSink_OnExitMeth             0x0301fc83
#define MiniToolbarTextBoxSink_OnExitMethS            "Event that is fired just before the control loses focus"
#define MiniToolbarTextBoxSink_OnItemHoverEndMeth     0x0301fc84
#define MiniToolbarTextBoxSink_OnItemHoverEndMethS    "Event that is fired when the user stops hovering over an item in the drop down in the expanded state"
#define MiniToolbarTextBoxSink_OnItemHoverStartMeth   0x0301fc85
#define MiniToolbarTextBoxSink_OnItemHoverStartMethS  "Event that is fired when the user starts to hover over an item in the drop down in the expanded state"
#define MiniToolbarTextBoxSink_OnItemRemoveMeth       0x0301fc86
#define MiniToolbarTextBoxSink_OnItemRemoveMethS      "Event that is fired when the user removes an item from the drop down"
#define MiniToolbarTextBoxSink_OnSelectMeth           0x0301fc87
#define MiniToolbarTextBoxSink_OnSelectMethS          "Event that is fired soon after the user changes the currently selected item using the drop down"
#define MiniToolbarTextEditorSink_OnChangeMeth        0x0301dc41
#define MiniToolbarTextEditorSink_OnChangeMethS       "Event that is fired when the content of the text editor is changed by the user"
#define MiniToolbarTextEditorSink_OnEnterMeth         0x0301dc42
#define MiniToolbarTextEditorSink_OnEnterMethS        "Event that is fired just before the control gets focus"
#define MiniToolbarTextEditorSink_OnExitMeth          0x0301dc43
#define MiniToolbarTextEditorSink_OnExitMethS         "Event that is fired just before the control loses focus"

#define ProjectOptionsButtonSink_OnClickMeth          0x0301bb81
#define ProjectOptionsButtonSink_OnClickMethS         "Event that is fired whenever click the button"

#define MiniToolbarSliderSink_OnValueChangeMeth       0x0301c281
#define MiniToolbarSliderSink_OnValueChangeMethS      "Event that is fired when the value of the slider has changed.  This event is fired after the user has finished any scrolling and released the left mouse button.  Use the Value property to get the current value of the slider."

#define WebBrowserDialogEventsSink_OnClose            0x0301e501
#define WebBrowserDialogEventsSink_OnCloseS           "Fires when the user clicks the close button on the Web Browser Dialog. Clients can use this event to handle the close dialog event."

#define WebBrowserDialogEventsSink_OnHelp             0x0301e502
#define WebBrowserDialogEventsSink_OnHelpS            "Event that fires when F1 is pressed when the Web Browser Dialog is active."

#define PresentationEventsSink_OnNewPublicationMarkedViewMeth             0x08002311
#define PresentationEventsSink_OnNewPublicationMarkedViewMethS            "Event that fires just before and after a publication marked view is added."
#define PresentationEventsSink_OnDeleteMeth								  0x08002312
#define PresentationEventsSink_OnDeleteMethS                              "Event that fires just before and after an entity is deleted."
#define PresentationEventsSink_OnStoryboardChangeMeth                     0x08002314
#define PresentationEventsSink_OnStoryboardChangeMethS                    "Event that fires just before and after a publication is updated because of modeling data changes."
#define PresentationEventsSink_OnPublicationDesignViewChangeMeth          0x08002315
#define PresentationEventsSink_OnPublicationDesignViewChangeMethS         "Event that fires just before and after a publication design view is changed."
#define PresentationEventsSink_OnPublicationComponentChangeMeth           0x08002316
#define PresentationEventsSink_OnPublicationComponentChangeMethS          "Event that fires just before and after a publication component is changed."
#define PresentationEventsSink_OnNewPublicationMeth                       0x08002317
#define PresentationEventsSink_OnNewPublicationMethS                      "Event that fires just before and after a publication is created."
#define PresentationEventsSink_OnPublicationModelingDataUpdateMeth        0x08002318
#define PresentationEventsSink_OnPublicationModelingDataUpdateMethS       "Event that fires just before and after a publication component is changed."
#define PresentationEventsSink_OnPublicationNameChangeMeth                0x08002319
#define PresentationEventsSink_OnPublicationNameChangeMethS               "Event that fires just before and after a publication component’s name is changed."

#define SearchBoxEventsSink_OnStartSearch                  0x0301fe81
#define SearchBoxEventsSink_OnStartSearchS                 "Event that fires just after the search is started."
#define SearchBoxEventsSink_OnEndSearch                    0x0301fe82
#define SearchBoxEventsSink_OnEndSearchS                   "Event that fires just after the search is ended."
#define SearchBoxEventsSink_OnStopSearch                   0x0301fe83
#define SearchBoxEventsSink_OnStopSearchS                  "Event that fires just after the search is stopped."
#define SearchBoxEventsSink_OnClearSearch                  0x0301fe84
#define SearchBoxEventsSink_OnClearSearchS                 "Event that fires just after the search is cleared."

#define PublicationEventsSink_OnModelingDataUpdateMeth                    0x0301ff81
#define PublicationEventsSink_OnModelingDataUpdateMethS                   "Event that fires just before and after a publication component is changed."

#define CustomDataEventsSink_OnRequestCustomDataMeth                      0x03020081
#define CustomDataEventsSink_OnRequestCustomDataMethS                     "Event just fires when the custom data is requested."
#define CustomDataEventsSink_OnExecuteCustomActionMeth                    0x03020082
#define CustomDataEventsSink_OnExecuteCustomActionMethS                   "Event just fires when a custom action is executed."

#define PluginLicenseManagerEventsSink_OnLoseLicense			0x03020611
#define PluginLicenseManagerEventsSink_OnLoseLicenseS			"Event that fires when the plugin license is lost"
#define PluginLicenseManagerEventsSink_OnChangeLicense			0x03020612
#define PluginLicenseManagerEventsSink_OnChangeLicenseS			"Event that fires when the plugin license changes"

#define ModelStateEventsSink_OnDeleteModelStateMeth       0x03021101
#define ModelStateEventsSink_OnDeleteModelStateMethS      "Event that fires when a model state is deleted."
#define ModelStateEventsSink_OnNewModelStateMeth          0x03021102
#define ModelStateEventsSink_OnNewModelStateMethS         "Event that fires when a model state is created."
#define ModelStateEventsSink_OnActivateModelStateMeth     0x03021103
#define ModelStateEventsSink_OnActivateModelStateMethS    "Event that fires when a model state is activated."

#define ClientOperationEvents_OnClientOperationMeth  0x03022002
#define ClientOperationEvents_OnClientOperationMethS "Event that is fired when FireOnClientOperation method is called."

#endif
