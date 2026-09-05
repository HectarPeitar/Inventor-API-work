Option Strict Off
Option Explicit On
Friend Class Analyses
    Implements System.Collections.IEnumerable

    Private m_InventorApp As Inventor.Application

    'local variable to hold collection
    Private m_Col As Collection
    Private m_ActiveCase As Analysis

    Public Function Add(ByVal InDocument As Inventor.AssemblyDocument) As Analysis

        'create a new object
        Dim NewMember As Analysis
        NewMember = New Analysis

        NewMember.Initialize(m_InventorApp, InDocument, Me)
        m_Col.Add(NewMember, InDocument.FullFileName)

        'return the object created
        Add = NewMember
        NewMember = Nothing

    End Function


    Public Function SetActiveCase(ByRef m_Doc As Inventor.AssemblyDocument) As Analysis
        ' Check to see if an analysis case already exists for this document.
        m_ActiveCase = Me.Item((m_Doc.FullFileName))

        ' If no case exists then create a new one.
        If m_ActiveCase Is Nothing Then
            m_ActiveCase = Me.Add(m_Doc)
        End If

        SetActiveCase = m_ActiveCase
    End Function


    Public Property ActiveCase() As Analysis
        Get
            ActiveCase = m_ActiveCase
        End Get
        Set(ByVal value As Analysis)
            m_ActiveCase = value
        End Set
    End Property


    Default Public ReadOnly Property Item(ByVal vntIndex As Object) As Analysis
        Get
            'used when referencing an element in the collection
            'vntIndexKey contains either the Index or Key to the collection,
            'this is why it is declared as a Variant
            'Syntax: Set foo = x.Item(xyz) or Set foo = x.Item(5)
            On Error Resume Next
            Item = m_Col.Item(vntIndex)
            If Err.Number Then
                Item = Nothing
            End If
        End Get
    End Property


    Public ReadOnly Property Count() As Integer
        Get
            'used when retrieving the number of elements in the
            'collection. Syntax: Debug.Print x.Count
            Count = m_Col.Count()
        End Get
    End Property

    Public Function GetEnumerator() As System.Collections.IEnumerator Implements System.Collections.IEnumerable.GetEnumerator
        GetEnumerator = m_Col.GetEnumerator
    End Function


    Public Sub Remove(ByRef vntIndexKey As Object)
        'used when removing an element from the collection
        'vntIndexKey contains either the Index or Key, which is why
        'it is declared as a Variant
        'Syntax: x.Remove(xyz)

        If Me.Item(vntIndexKey) Is m_ActiveCase Then
            m_ActiveCase = Nothing
        End If

        m_Col.Remove(vntIndexKey)
    End Sub

    Private Sub Class_Init(ByVal InventorApp As Inventor.Application)

        m_InventorApp = InventorApp

        'creates the collection when this class is created
        m_Col = New Collection

        m_ActiveCase = Nothing
    End Sub

    Public Sub New(ByVal InventorApp As Inventor.Application)
        MyBase.New()
        Class_Init(InventorApp)
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