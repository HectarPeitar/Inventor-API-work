Option Strict Off
Option Explicit On
<System.Runtime.InteropServices.ProgId("CustomEnv.Interaction")> Public Class clsInteraction

    Private mobjInventorApp As Inventor.Application

    'declare the event objects
    Private WithEvents mobjInteractionEvents As Inventor.InteractionEvents
    Private WithEvents mobjSelectEvents As Inventor.SelectEvents

    'declare a flag that is used to determine when selection stops
    Private mblnStillSelecting As Boolean

    Public Sub New(ByVal objInventorApp As Inventor.Application)

        MyBase.New()

        mobjInventorApp = objInventorApp

        On Error Resume Next

        'initialize the interaction events object
        mobjInteractionEvents = mobjInventorApp.CommandManager.CreateInteractionEvents

        'set a reference to the select events
        mobjSelectEvents = mobjInteractionEvents.SelectEvents

    End Sub

    Public Function SelectEntity(ByRef filter_Renamed As Inventor.SelectionFilterEnum) As Object

        On Error Resume Next

        SelectEntity = Nothing

        Dim objSelectedEntities As Inventor.ObjectsEnumerator
        If Not mobjInteractionEvents Is Nothing And Not mobjSelectEvents Is Nothing Then

            'initialize the flag to specify selection is still active
            mblnStillSelecting = True

            'define that we want select events
            mobjInteractionEvents.SelectionActive = True

            'set the filter using the value passed in
            mobjSelectEvents.AddSelectionFilter(filter_Renamed)

            'disable receiving mouse move during selection
            mobjSelectEvents.MouseMoveEnabled = False

            'start the InteractionEvents object
            mobjInteractionEvents.Start()

            'loop until a selection is made
            Do While mblnStillSelecting
                System.Windows.Forms.Application.DoEvents()
            Loop

            'get the selected item.  If more than one thing was selected,
            ' just get the first item and ignore the rest
            objSelectedEntities = mobjSelectEvents.SelectedEntities
            If objSelectedEntities.Count > 0 Then
                SelectEntity = objSelectedEntities.Item(1)
            Else
                SelectEntity = Nothing
            End If

            'stop the InteractionEvents object
            mobjInteractionEvents.Stop()

        End If

    End Function

    Private Sub mobjInteractionEvents_OnTerminate() Handles mobjInteractionEvents.OnTerminate

        'set the flag to indicate selection is done
        mblnStillSelecting = False

    End Sub

    Private Sub mobjSelectEvents_OnSelect(ByVal JustSelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles mobjSelectEvents.OnSelect

        'set the flag to indicate selection is done
        mblnStillSelecting = False

    End Sub

    Protected Overrides Sub Finalize()

        'set the select events to Nothing
        mobjSelectEvents = Nothing

        'set the interaction events to Nothing
        mobjInteractionEvents = Nothing

        MyBase.Finalize()
    End Sub
End Class