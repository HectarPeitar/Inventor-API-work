Option Strict Off
Option Explicit On
Friend Class ParamSettings
    Implements System.Collections.IEnumerable

    'local variable to hold collection
    Private m_Col As Collection

    Public Function Add(ByRef Parameter As Inventor.Parameter, ByRef StartValue As String, ByRef EndValue As String) As ParamSetting
        'create a new object
        Dim objNewMember As ParamSetting
        objNewMember = New ParamSetting

        'set the properties passed into the method
        objNewMember.Parameter = Parameter
        objNewMember.StartValue = StartValue
        objNewMember.EndValue = EndValue

        m_Col.Add(objNewMember, Parameter.Name)

        'return the object created
        Add = objNewMember
        objNewMember = Nothing
    End Function

    Default Public ReadOnly Property Item(ByVal Index As Object) As ParamSetting
        Get
            Item = m_Col.Item(Index)
        End Get
    End Property

    Public ReadOnly Property Count() As Integer
        Get
            Count = m_Col.Count()
        End Get
    End Property

    Public Function GetEnumerator() As System.Collections.IEnumerator Implements System.Collections.IEnumerable.GetEnumerator
        GetEnumerator = m_Col.GetEnumerator
    End Function

    Public Sub Remove(ByRef vntIndexKey As Object)
        m_Col.Remove(vntIndexKey)
    End Sub

    Private Sub Class_Init()
        'creates the collection when this class is created
        m_Col = New Collection
    End Sub
    Public Sub New()
        MyBase.New()
        Class_Init()
    End Sub

    Private Sub Class_Terminated()
        'destroys collection when this class is terminated
        m_Col = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Class_Terminated()
        MyBase.Finalize()
    End Sub
End Class