Imports Inventor

Friend Class ChangeRequest

    Private m_changeProcessor As CustomCommand.ChangeProcessor

    Public Sub New()
        m_changeProcessor = Nothing
    End Sub

    Public Overridable Sub OnExecute(ByVal document As Document, ByVal context As NameValueMap, ByVal succeeded As Boolean)
        '
    End Sub

    Public Sub Execute(ByVal application As Application, ByVal changeDefinition As Object, ByVal document As Inventor._Document)
        'Create instance of ChangeProcessor class
        m_changeProcessor = New CustomCommand.ChangeProcessor

        'Set the parent to get the call back when change processor terminates
        m_changeProcessor.SetParentRequest(Me)

        'Connect change processor
        m_changeProcessor.Connect(application, changeDefinition, document)

    End Sub

    Public Sub Terminate()
        'Disconnect change processor
        If Not (m_changeProcessor Is Nothing) Then
            m_changeProcessor.Disconnect()
            m_changeProcessor = Nothing
        End If
    End Sub

End Class
