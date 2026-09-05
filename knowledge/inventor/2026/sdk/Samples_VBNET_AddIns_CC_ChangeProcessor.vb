Imports Inventor

Friend Class ChangeProcessor

    Private m_changeProcessor As Inventor.ChangeProcessor

    'Parent ChangeRequest object
    Private m_parentRequest As CustomCommand.ChangeRequest

    Public Sub New()
        m_changeProcessor = Nothing
        m_parentRequest = Nothing
    End Sub

    Public Sub Connect(ByVal application As Application, ByVal changeDefinition As Object, ByVal document As Inventor._Document)
        'Get the change manager object
        Dim changeManager As ChangeManager
        changeManager = application.ChangeManager

        'Get the change definition collection for this AddIn
        Dim changeDefinitions As ChangeDefinitions
        changeDefinitions = changeManager("{D7D54695-7FBE-4968-A0DD-B86FA4D59AE5}")

        'Create the change processor associated with the change definition
        m_changeProcessor = changeDefinitions(changeDefinition).CreateChangeProcessor()

        'Connect event handler in order to receive change processor events
        AddHandler m_changeProcessor.OnExecute, AddressOf Me.ChangeProcessorEvents_OnExecute
        AddHandler m_changeProcessor.OnTerminate, AddressOf Me.ChangeProcessorEvents_OnTerminate

        'Execute the change processor
        m_changeProcessor.Execute(document)

    End Sub

    Public Sub Disconnect()
        'Disconnect change processor events sink
        If Not (m_changeProcessor Is Nothing) Then
            RemoveHandler m_changeProcessor.OnExecute, AddressOf Me.ChangeProcessorEvents_OnExecute
            RemoveHandler m_changeProcessor.OnTerminate, AddressOf Me.ChangeProcessorEvents_OnTerminate

            m_changeProcessor = Nothing
        End If
    End Sub

    Public Sub SetParentRequest(ByVal parentRequest As CustomCommand.ChangeRequest)
        'Store the parent request object
        m_parentRequest = parentRequest
    End Sub

    '-------------------------------------------------------------
    '-------Implementation of ChangeProcessor Events sink methods
    '-------------------------------------------------------------

    Public Sub ChangeProcessorEvents_OnExecute(ByVal document As Inventor._Document, ByVal context As NameValueMap, ByRef succeeded As Boolean)
        m_parentRequest.OnExecute(document, context, succeeded)
    End Sub

    Public Sub ChangeProcessorEvents_OnTerminate()
        m_parentRequest.Terminate()
    End Sub
End Class
