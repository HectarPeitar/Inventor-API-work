Imports System.Runtime.InteropServices
Imports Inventor

Friend MustInherit Class Command

    'Inventor application object
    Protected m_application As Application

    'Button definition object 
    Protected m_buttonDefinition As ButtonDefinition

    'Interaction object
    Protected m_interaction As CustomCommand.Interaction

    'InteractionEvents object
    Protected m_interactionEvents As InteractionEvents

    'SelectEvents object
    Protected m_selectEvents As SelectEvents

    'MouseEvents object
    Protected m_mouseEvents As MouseEvents

    'TriadEvents object
    Protected m_triadEvents As TriadEvents

    'Command status
    Protected m_commandIsRunning As Boolean


    Public ReadOnly Property ButtonDefinition() As Inventor.ButtonDefinition
        Get
            ButtonDefinition = m_buttonDefinition
        End Get
    End Property


    Public Sub New()
        m_application = Nothing
        m_buttonDefinition = Nothing
        m_interaction = Nothing
        m_interactionEvents = Nothing
        m_mouseEvents = Nothing
        m_selectEvents = Nothing
        m_triadEvents = Nothing

        m_commandIsRunning = False

    End Sub

    Public Sub CreateButton(ByVal application As Application, _
                            ByVal autoAddToGUI As Boolean, _
                            ByVal displayName As String, _
                            ByVal internalName As String, _
                            ByVal commandType As CommandTypesEnum, _
                            Optional ByVal clientId As Object = Nothing, _
                            Optional ByVal description As String = "", _
                            Optional ByVal toolTip As String = "", _
                            Optional ByVal standardIcon As Object = Nothing, _
                            Optional ByVal largeIcon As Object = Nothing, _
                            Optional ByVal buttonDisplayType As ButtonDisplayEnum = ButtonDisplayEnum.kDisplayTextInLearningMode)

        'Store the Inventor application object
        m_application = application

        'Create the button definition
        m_buttonDefinition = m_application.CommandManager.ControlDefinitions.AddButtonDefinition(displayName, internalName, commandType, clientId, description, toolTip, standardIcon, largeIcon, buttonDisplayType)

        'Connect the button event sink
        AddHandler m_buttonDefinition.OnExecute, AddressOf Me.ButtonDefinition_OnExecute

        ' Disable the button, it will be enabled when the part environment is activated
        m_buttonDefinition.Enabled = False

        'Display button by default if specified
        If (autoAddToGUI) Then
            m_buttonDefinition.AutoAddToGUI()
        End If
    End Sub

    Protected Overridable Sub ButtonDefinition_OnExecute(ByVal context As NameValueMap)
        'If command was already started,stop it first
        If (m_commandIsRunning) Then
            StopCommand()
        End If

        'Start new command
        StartCommand()
    End Sub

    Public Sub RemoveButton()
        'Disconnect button events sink
        If Not (m_buttonDefinition Is Nothing) Then
            RemoveHandler m_buttonDefinition.OnExecute, AddressOf Me.ButtonDefinition_OnExecute
            m_buttonDefinition = Nothing
        End If
    End Sub

    Public Overridable Sub StartCommand()
        'Start interaction events
        StartInteraction()

        'Press the button
        m_buttonDefinition.Pressed = True

        'Set the command status to running
        m_commandIsRunning = True
    End Sub


    'Must be implemented by the derived classes
    Public MustOverride Sub ExecuteCommand()


    Public Sub StartInteraction()
        Try
            'Create instance of the Interaction class
            m_interaction = New CustomCommand.Interaction

            'Set the parent to get the call back when event is terminated,or interaction is completed
            m_interaction.SetParentCmd(Me)

            'Set the interaction events name to the button's internal name
            Dim buttonDefObjInternalName As String
            buttonDefObjInternalName = m_buttonDefinition.InternalName

            'Start interaction events
            m_interaction.StartInteraction(m_application, buttonDefObjInternalName, m_interactionEvents)

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.ToString())
        End Try
    End Sub

    Public Sub StopInteraction()
        'Terminate interaction events
        m_interaction.StopInteraction()
        m_interaction = Nothing

        m_interactionEvents = Nothing

    End Sub

    Public Overridable Sub StopCommand()
        Try
            'Unsubscribe from the events
            UnsubscribeFromEvents()

            'Stop interaction events
            StopInteraction()

            'Un-press the button
            m_buttonDefinition.Pressed = False

            'Set the command status to not-running
            m_commandIsRunning = False

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.ToString())
        End Try
    End Sub

    Public Sub SubscribeToEvent(ByVal interactionType As Interaction.InteractionTypeEnum)
        'Subscribe to the specified event type (selection,mouse etc.)
        Dim eventType As Object
        eventType = Nothing

        m_interaction.SubscribeToEvent(interactionType, eventType)

        If Not (eventType Is Nothing) Then
            If TypeOf eventType Is SelectEvents Then
                m_selectEvents = eventType
            End If

            If TypeOf eventType Is MouseEvents Then
                m_mouseEvents = eventType
            End If

            If TypeOf eventType Is TriadEvents Then
                m_triadEvents = eventType
            End If
        End If
    End Sub

    Public Sub UnsubscribeFromEvents()
        'Unsubscribe from all event objects (selection,mouse etc)
        m_interaction.UnsubscribeFromEvents()

        m_selectEvents = Nothing
        m_mouseEvents = Nothing
        m_triadEvents = Nothing
    End Sub

    Public Overridable Sub EnableInteraction()
        'Enable interaction events
        m_interaction.EnableInteraction()
    End Sub

    Public Overridable Sub DisableInteraction()
        'Disable interaction events
        m_interaction.DisableInteraction()
    End Sub

    Public Sub ExecuteChangeRequest(ByVal changeRequest As CustomCommand.ChangeRequest, ByVal changeDefinition As Object, ByVal document As Inventor._Document)
        changeRequest.Execute(m_application, changeDefinition, document)
    End Sub

    Public Overridable Sub OnHelp(ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    '----------------------------------------------------------
    '-------implementation of Select Events sink methods
    '----------------------------------------------------------
    Public Overridable Sub OnPreSelect(ByVal preSelectEntity As Object, ByRef doHighlight As Boolean, ByVal morePreSelectEntities As ObjectCollection, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        doHighlight = False
    End Sub

    Public Overridable Sub OnPreSelectMouseMove(ByVal preSelectEntity As Object, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnStopPreSelect(ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnSelect(ByVal justSelectedEntities As ObjectsEnumerator, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnUnSelect(ByVal unSelectedEntities As ObjectsEnumerator, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    '----------------------------------------------------
    '-------Implementation of Mouse Events sink methods
    '----------------------------------------------------
    Public Overridable Sub OnMouseUp(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnMouseDown(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnMouseClick(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'not implemented
    End Sub

    Public Overridable Sub OnMouseDoubleClick(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnMouseMove(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    Public Overridable Sub OnMouseLeave(ByVal buttonType As MouseButtonEnum, ByVal shiftKeys As ShiftStateEnum, ByVal view As Inventor.View)
        'Not implemented
    End Sub

    '-------------------------------------------------------
    '--------Implementation of Triad Events sink methods
    '-------------------------------------------------------
    Public Overridable Sub OnActivate(ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnEndMove(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal shiftKeys As ShiftStateEnum, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnMove(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal shiftKeys As ShiftStateEnum, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnEndSequence(ByVal cancelled As Boolean, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnStartSequence(ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnMoveTriadOnlyToggle(ByVal moveTriadOnly As Boolean, ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnStartMove(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal shiftKeys As ShiftStateEnum, ByVal coordinateSystem As Matrix, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnTerminate(ByVal cancelled As Boolean, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub

    Public Overridable Sub OnSegmentSelectionChange(ByVal selectedTriadSegment As TriadSegmentEnum, ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Not implemented
        handlingCode = HandlingCodeEnum.kEventNotHandled
    End Sub
End Class
