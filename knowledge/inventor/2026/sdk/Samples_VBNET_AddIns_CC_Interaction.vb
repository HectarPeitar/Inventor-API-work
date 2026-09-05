Imports Inventor
Imports System.Runtime.InteropServices

Friend Class Interaction

    Public Enum InteractionTypeEnum
        kSelection
        kMouse
        kKeyboard
        kTriad
    End Enum

    'Interaction Types collection
    Private m_interactionTypes As System.Collections.ArrayList

    'InteractionEvents object
    Private m_interactionEvents As InteractionEvents

    'SelectEvents object
    Private m_selectEvents As SelectEvents

    'MouseEvents object
    Private m_mouseEvents As MouseEvents

    'TriadEvents object
    Private m_triadEvents As TriadEvents

    'Parent Command object
    Private m_parentCmd As CustomCommand.Command

    Public Sub New()
        m_interactionTypes = New System.Collections.ArrayList

        m_interactionEvents = Nothing
        m_selectEvents = Nothing
        m_mouseEvents = Nothing
        m_triadEvents = Nothing

        m_parentCmd = Nothing
    End Sub

    Public Sub StartInteraction(ByVal application As Application, ByVal interactionName As String, ByRef interactionEvents As InteractionEvents)
        Try
            'Create the InteractionEvents object
            m_interactionEvents = application.CommandManager.CreateInteractionEvents()

            'Define that we want select events rather than mouse events
            m_interactionEvents.SelectionActive = True

            'Set the name for the interation events
            m_interactionEvents.Name = interactionName

            'Connect the interaction event sink
            ConnectInteractionEventsSink()

            'Set a reference to the select events
            m_selectEvents = m_interactionEvents.SelectEvents

            'Connect the select event sink
            ConnectSelectEventsSink()

            'Set a reference to the mouse events
            m_mouseEvents = m_interactionEvents.MouseEvents

            'Connect the mouse event sink
            ConnectMouseEventsSink()

            'Set a reference to the triad events
            m_triadEvents = m_interactionEvents.TriadEvents

            'Connect the triad event sink
            ConnectTriadEventsSink()

            'Start the InteractionEvents
            m_interactionEvents.Start()

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.ToString())
        Finally
            interactionEvents = m_interactionEvents
        End Try
    End Sub

    Public Sub StopInteraction()
        'Disconnect interaction events sink
        If Not (m_interactionEvents Is Nothing) Then
            DisConnectInteractionEventsSink()

            m_interactionEvents.Stop()
            m_interactionEvents = Nothing
        End If
    End Sub

    Public Sub SubscribeToEvent(ByVal interactionType As InteractionTypeEnum, ByRef eventType As Object)
        'Check if aleady subscribed to
        Dim interactionEvtsCount As Integer
        For interactionEvtsCount = 0 To m_interactionTypes.Count - 1
            If m_interactionTypes(interactionEvtsCount) = interactionType Then
                Exit Sub
            End If
        Next

        'If not already subscribed to then,subscribe
        m_interactionTypes.Add(interactionType)

        Select Case interactionType
            Case InteractionTypeEnum.kSelection
                If m_selectEvents Is Nothing Then
                    ''Set a reference to the select events
                    m_selectEvents = m_interactionEvents.MouseEvents

                    'Connect the select event sink
                    ConnectSelectEventsSink()
                End If

                'Specify bure through
                m_selectEvents.PreSelectBurnThrough = True
                eventType = m_selectEvents

            Case InteractionTypeEnum.kMouse
                If m_mouseEvents Is Nothing Then
                    'Set a reference to the mouse events
                    m_mouseEvents = m_interactionEvents.MouseEvents

                    'Connect the mouse event sink
                    ConnectMouseEventsSink()
                End If
                eventType = m_mouseEvents

            Case InteractionTypeEnum.kTriad
                If m_triadEvents Is Nothing Then
                    'Set a reference to the triad events
                    m_triadEvents = m_interactionEvents.TriadEvents

                    'Connect the triad event sink
                    ConnectTriadEventsSink()
                End If
                eventType = m_triadEvents
        End Select
    End Sub

    Public Sub UnsubscribeFromEvents()
        Dim interactionEvtsCount As Integer
        Dim interactionType As InteractionTypeEnum
        For interactionEvtsCount = 0 To m_interactionTypes.Count - 1
            interactionType = m_interactionTypes(interactionEvtsCount)
            Select Case interactionType
                Case InteractionTypeEnum.kSelection
                    'Disconnect selection events sink
                    If Not (m_selectEvents Is Nothing) Then
                        DisConnectSelectEventsSink()
                        m_selectEvents = Nothing
                    End If

                Case InteractionTypeEnum.kMouse
                    'Disconnect mouse events sink
                    If Not (m_mouseEvents Is Nothing) Then
                        DisConnectMouseEventsSink()
                        m_mouseEvents = Nothing
                    End If

                Case InteractionTypeEnum.kTriad
                    'Disconnect triad events sink
                    If Not (m_triadEvents Is Nothing) Then
                        DisConnectTriadEventsSink()
                        m_triadEvents = Nothing
                    End If
            End Select

        Next
        m_interactionTypes.Clear()
    End Sub

    Public Sub EnableInteraction()
        'Enable events
        Dim interactionEvtsCount As Integer
        Dim interactionType As InteractionTypeEnum
        For interactionEvtsCount = 0 To m_interactionTypes.Count - 1
            interactionType = m_interactionTypes(interactionEvtsCount)

            Select Case interactionType
                Case InteractionTypeEnum.kSelection
                    'Re-subscribe to selection events
                    If m_selectEvents Is Nothing Then
                        'Set a reference to the select events
                        m_selectEvents = m_interactionEvents.SelectEvents

                        'Connect the select event sink
                        ConnectSelectEventsSink()

                        'Specify burn through 
                        m_selectEvents.PreSelectBurnThrough = True
                    End If

                Case InteractionTypeEnum.kMouse
                    'Re-subscribe to mouse events
                    If m_mouseEvents Is Nothing Then
                        'Set a reference to the mouse events
                        m_mouseEvents = m_interactionEvents.MouseEvents

                        'Connect the mouse event sink
                        ConnectMouseEventsSink()
                    End If

                Case InteractionTypeEnum.kTriad
                    'Re-subscribe to triad events
                    If m_triadEvents Is Nothing Then
                        'Set a reference to the triad events
                        m_triadEvents = m_interactionEvents.TriadEvents

                        'Connect the triad event sink
                        ConnectTriadEventsSink()
                    End If
            End Select

        Next
    End Sub

    Public Sub DisableInteraction()
        'Disable subscribed to events
        Dim interactionType As InteractionTypeEnum
        Dim interactionEvtsCount As Integer
        For interactionEvtsCount = 0 To m_interactionTypes.Count - 1
            interactionType = m_interactionTypes(interactionEvtsCount)

            Select Case interactionType
                Case InteractionTypeEnum.kSelection
                    'Un-subscribe and delete selection events
                    If Not (m_selectEvents Is Nothing) Then
                        DisConnectSelectEventsSink()
                        m_selectEvents = Nothing
                    End If

                Case InteractionTypeEnum.kMouse
                    'Un-subscribe and delete mouse events
                    If Not (m_mouseEvents Is Nothing) Then
                        DisConnectMouseEventsSink()
                        m_mouseEvents = Nothing
                    End If

                Case InteractionTypeEnum.kTriad
                    'Un-subscribe and delete triad events
                    If Not (m_triadEvents Is Nothing) Then
                        DisConnectTriadEventsSink()
                        m_triadEvents = Nothing
                    End If
            End Select
        Next
    End Sub

    Private Sub ConnectInteractionEventsSink()
        AddHandler m_interactionEvents.OnTerminate, AddressOf Me.InteractionEvents_OnTerminate
        AddHandler m_interactionEvents.OnHelp, AddressOf Me.InteractionEvents_OnHelp
    End Sub

    Private Sub DisConnectInteractionEventsSink()
        RemoveHandler m_interactionEvents.OnTerminate, AddressOf Me.InteractionEvents_OnTerminate
        RemoveHandler m_interactionEvents.OnHelp, AddressOf Me.InteractionEvents_OnHelp
    End Sub

    Private Sub ConnectMouseEventsSink()
        AddHandler m_mouseEvents.OnMouseUp, AddressOf Me.MouseEvents_OnMouseUp
        AddHandler m_mouseEvents.OnMouseDown, AddressOf Me.MouseEvents_OnMouseDown
        AddHandler m_mouseEvents.OnMouseClick, AddressOf Me.MouseEvents_OnMouseClick
        AddHandler m_mouseEvents.OnMouseDoubleClick, AddressOf Me.MouseEvents_OnMouseDoubleClick
        AddHandler m_mouseEvents.OnMouseMove, AddressOf Me.MouseEvents_OnMouseMove
        AddHandler m_mouseEvents.OnMouseLeave, AddressOf Me.MouseEvents_OnMouseLeave
    End Sub

    Private Sub DisConnectMouseEventsSink()
        RemoveHandler m_mouseEvents.OnMouseUp, AddressOf Me.MouseEvents_OnMouseUp
        RemoveHandler m_mouseEvents.OnMouseDown, AddressOf Me.MouseEvents_OnMouseDown
        RemoveHandler m_mouseEvents.OnMouseClick, AddressOf Me.MouseEvents_OnMouseClick
        RemoveHandler m_mouseEvents.OnMouseDoubleClick, AddressOf Me.MouseEvents_OnMouseDoubleClick
        RemoveHandler m_mouseEvents.OnMouseMove, AddressOf Me.MouseEvents_OnMouseMove
        RemoveHandler m_mouseEvents.OnMouseLeave, AddressOf Me.MouseEvents_OnMouseLeave
    End Sub

    Private Sub ConnectSelectEventsSink()
        AddHandler m_selectEvents.OnPreSelect, AddressOf Me.SelectEvents_OnPreSelect
        AddHandler m_selectEvents.OnPreSelectMouseMove, AddressOf Me.SelectEvents_OnPreSelectMouseMove
        AddHandler m_selectEvents.OnStopPreSelect, AddressOf Me.SelectEvents_OnStopPreSelect
        AddHandler m_selectEvents.OnSelect, AddressOf Me.SelectEvents_OnSelect
        AddHandler m_selectEvents.OnUnSelect, AddressOf Me.SelectEvents_OnUnSelect
    End Sub

    Private Sub DisConnectSelectEventsSink()
        RemoveHandler m_selectEvents.OnPreSelect, AddressOf Me.SelectEvents_OnPreSelect
        RemoveHandler m_selectEvents.OnPreSelectMouseMove, AddressOf Me.SelectEvents_OnPreSelectMouseMove
        RemoveHandler m_selectEvents.OnStopPreSelect, AddressOf Me.SelectEvents_OnStopPreSelect
        RemoveHandler m_selectEvents.OnSelect, AddressOf Me.SelectEvents_OnSelect
        RemoveHandler m_selectEvents.OnUnSelect, AddressOf Me.SelectEvents_OnUnSelect
    End Sub

    Private Sub ConnectTriadEventsSink()
        AddHandler m_triadEvents.OnActivate, AddressOf Me.TriadEvents_OnActivate
        AddHandler m_triadEvents.OnEndMove, AddressOf Me.TriadEvents_OnEndMove
        AddHandler m_triadEvents.OnEndSequence, AddressOf Me.TriadEvents_OnEndSequence
        AddHandler m_triadEvents.OnMove, AddressOf Me.TriadEvents_OnMove
        AddHandler m_triadEvents.OnMoveTriadOnlyToggle, AddressOf Me.TriadEvents_OnMoveTriadOnlyToggle
        AddHandler m_triadEvents.OnSegmentSelectionChange, AddressOf Me.TriadEvents_OnSegmentSelectionChange
        AddHandler m_triadEvents.OnStartMove, AddressOf Me.TriadEvents_OnStartMove
        AddHandler m_triadEvents.OnStartSequence, AddressOf Me.TriadEvents_OnStartSequence
        AddHandler m_triadEvents.OnTerminate, AddressOf Me.TriadEvents_OnTerminate
    End Sub

    Private Sub DisConnectTriadEventsSink()
        RemoveHandler m_triadEvents.OnActivate, AddressOf Me.TriadEvents_OnActivate
        RemoveHandler m_triadEvents.OnEndMove, AddressOf Me.TriadEvents_OnEndMove
        RemoveHandler m_triadEvents.OnEndSequence, AddressOf Me.TriadEvents_OnEndSequence
        RemoveHandler m_triadEvents.OnMove, AddressOf Me.TriadEvents_OnMove
        RemoveHandler m_triadEvents.OnMoveTriadOnlyToggle, AddressOf Me.TriadEvents_OnMoveTriadOnlyToggle
        RemoveHandler m_triadEvents.OnSegmentSelectionChange, AddressOf Me.TriadEvents_OnSegmentSelectionChange
        RemoveHandler m_triadEvents.OnStartMove, AddressOf Me.TriadEvents_OnStartMove
        RemoveHandler m_triadEvents.OnStartSequence, AddressOf Me.TriadEvents_OnStartSequence
        RemoveHandler m_triadEvents.OnTerminate, AddressOf Me.TriadEvents_OnTerminate
    End Sub

    Public Sub SetParentCmd(ByVal parentCmd As CustomCommand.Command)
        'Store a copy of the parent command
        m_parentCmd = parentCmd
    End Sub

    '----------------------------------------------------------
    '--------Implementation of Interaction Events sink methods
    '----------------------------------------------------------

    Public Sub InteractionEvents_OnTerminate()
        'Terminate the command
        m_parentCmd.StopCommand()
    End Sub

    Public Sub InteractionEvents_OnHelp(ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnHelp(beforeOrAfter, context, handlingCode)
    End Sub

    '-----------------------------------------------------------
    '----- Implementation of Select Events sink methods
    '----------------------------------------------------------
    Public Sub SelectEvents_OnPreSelect(ByRef preSelectEntity As Object, ByRef doHighlight As Boolean, ByRef morePreSelectEntities As ObjectCollection, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnPreSelect(preSelectEntity, doHighlight, morePreSelectEntities, selectionDevice, modelPosition, viewPosition, view)
    End Sub

    Public Sub SelectEvents_OnPreSelectMouseMove(ByVal preSelectEntity As Object, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnPreSelectMouseMove(preSelectEntity, modelPosition, viewPosition, view)
    End Sub

    Public Sub SelectEvents_OnStopPreSelect(ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnStopPreSelect(modelPosition, viewPosition, view)
    End Sub

    Public Sub SelectEvents_OnSelect(ByVal justSelectedEntities As ObjectsEnumerator, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnSelect(justSelectedEntities, selectionDevice, modelPosition, viewPosition, view)
    End Sub

    Public Sub SelectEvents_OnUnSelect(ByVal unSelectedEntities As ObjectsEnumerator, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnUnSelect(unSelectedEntities, selectionDevice, modelPosition, viewPosition, view)
    End Sub

    '-------------------------------------------------------------------
    '-----Implementation of Mouse Events sink methods
    '------------------------------------------------------------------

    Public Sub MouseEvents_OnMouseUp(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnMouseUp(buttonType, shiftKeys, modelPosition, viewPosition, view)
    End Sub

    Public Sub MouseEvents_OnMouseDown(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnMouseDown(buttonType, shiftKeys, modelPosition, viewPosition, view)
    End Sub

    Public Sub MouseEvents_OnMouseClick(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnMouseClick(buttonType, shiftKeys, modelPosition, viewPosition, view)
    End Sub

    Public Sub MouseEvents_OnMouseDoubleClick(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnMouseDoubleClick(buttonType, shiftKeys, modelPosition, viewPosition, view)
    End Sub

    Public Sub MouseEvents_OnMouseMove(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        m_parentCmd.OnMouseMove(buttonType, shiftKeys, modelPosition, viewPosition, view)
    End Sub

    Public Sub MouseEvents_OnMouseLeave(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal view As Inventor.View)
        m_parentCmd.OnMouseLeave(buttonType, shiftKeys, view)
    End Sub

    '---------------------------------------------------------------------
    '-----------Implementation of Triad Events sink methods
    '---------------------------------------------------------------------

    Public Sub TriadEvents_OnActivate(ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnActivate(context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnEndMove(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal shiftKeys As ShiftStateEnum, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnEndMove(selectedTriadSegment, shiftKeys, coordinateSystem, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnMove(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal shiftKeys As ShiftStateEnum, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnMove(selectedTriadSegment, shiftKeys, coordinateSystem, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnEndSequence(ByVal cancelled As Boolean, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnEndSequence(cancelled, coordinateSystem, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnStartSequence(ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnStartSequence(coordinateSystem, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnMoveTriadOnlyToggle(ByVal moveTriadOnly As Boolean, ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnMoveTriadOnlyToggle(moveTriadOnly, beforeOrAfter, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnStartMove(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal shiftKeys As ShiftStateEnum, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnStartMove(selectedTriadSegment, shiftKeys, coordinateSystem, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnTerminate(ByVal cancelled As Boolean, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnTerminate(cancelled, context, handlingCode)
    End Sub

    Public Sub TriadEvents_OnSegmentSelectionChange(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        m_parentCmd.OnSegmentSelectionChange(selectedTriadSegment, beforeOrAfter, context, handlingCode)
    End Sub
End Class
