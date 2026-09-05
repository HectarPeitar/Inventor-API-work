Imports Inventor
Imports System.Drawing
Imports System.Windows.Forms

Friend MustInherit Class Button

#Region "Data Members"

    Private Shared m_inventorApplication As Inventor.Application

    Private m_buttonDefinition As ButtonDefinition

#End Region

#Region "Properties"

    Public Shared Property InventorApplication() As Inventor.Application
        Get
            InventorApplication = m_inventorApplication
        End Get

        Set(ByVal Value As Inventor.Application)
            m_inventorApplication = Value
        End Set
    End Property

    Public ReadOnly Property ButtonDefinition() As Inventor.ButtonDefinition
        Get
            ButtonDefinition = m_buttonDefinition
        End Get
    End Property

#End Region

#Region "Methods"

    Public Sub New(ByVal displayName As String,
                    ByVal internalName As String,
                    ByVal commandType As CommandTypesEnum,
                    ByVal clientId As String,
                    Optional ByVal description As String = "",
                    Optional ByVal tooltip As String = "",
                    Optional ByVal standardIcon As Icon = Nothing,
                    Optional ByVal largeIcon As Icon = Nothing,
                    Optional ByVal buttonDisplayType As ButtonDisplayEnum = ButtonDisplayEnum.kDisplayTextInLearningMode)

        Try
            'get IPictureDisp for icons
            Dim stdIconIPictureDisp As Object = System.Type.Missing
            Dim largeIconIPictureDisp As Object = System.Type.Missing

            If Not standardIcon Is Nothing Then
                stdIconIPictureDisp = ConvertImage.ImageToIPicture(standardIcon.ToBitmap())
                'stdIconIPictureDisp = Microsoft.VisualBasic.Compatibility.VB6.Support.IconToIPicture(standardIcon)
            End If

            If Not largeIcon Is Nothing Then
                largeIconIPictureDisp = ConvertImage.ImageToIPicture(largeIcon.ToBitmap())
                'largeIconIPictureDisp = Microsoft.VisualBasic.Compatibility.VB6.Support.IconToIPicture(largeIcon)
            End If

            'create button definition
            m_buttonDefinition = m_inventorApplication.CommandManager.ControlDefinitions.AddButtonDefinition(displayName, internalName, commandType, clientId, description, tooltip, stdIconIPictureDisp, largeIconIPictureDisp, buttonDisplayType)

            'enable the button
            m_buttonDefinition.Enabled = True

            'connect the button event sink
            AddHandler m_buttonDefinition.OnExecute, AddressOf Me.ButtonDefinition_OnExecute

        Catch ex As Exception
            MessageBox.Show(ex.ToString)
        End Try

    End Sub

    Protected MustOverride Sub ButtonDefinition_OnExecute(ByVal context As NameValueMap)

#End Region

End Class

Public Class ConvertImage
    Inherits System.Windows.Forms.AxHost

    Public Sub New()
        MyBase.New("59EE46BA-677D-4d20-BF10-8D8067CB8B33")
    End Sub

    'Public Shared Function ImageToIPicture(ByVal Image As System.Drawing.Image) As stdole.IPictureDisp
    '    Dim iPic As stdole.IPictureDisp
    '    Try
    '        Dim obj As Object = GetIPictureFromPicture(Image)
    '        iPic = CType(obj, stdole.IPictureDisp)
    '    Catch e As Exception
    '        Return Nothing
    '    End Try
    '    Return iPic
    'End Function

    Public Shared Function ImageToIPicture(ByVal Image As System.Drawing.Image) As stdole.IPictureDisp
        Dim iPic As stdole.IPictureDisp
        Try
            Dim obj As Object = GetIPictureFromPicture(Image)
            iPic = CType(obj, stdole.IPictureDisp)
        Catch e As Exception
            Return Nothing
        End Try
        Return iPic
    End Function

End Class
