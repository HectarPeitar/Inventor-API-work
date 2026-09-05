Option Strict Off
Option Explicit On
Friend Class ScanViewsForm
    Inherits System.Windows.Forms.Form

#Region "GetForm"
    Private Shared m_frmScanViews As ScanViewsForm

    Public Shared Property frmScanViewsInstance() As ScanViewsForm
        Get
            If m_frmScanViews Is Nothing OrElse m_frmScanViews.IsDisposed Then
                m_frmScanViews = New ScanViewsForm
            End If

            frmScanViewsInstance = m_frmScanViews
        End Get
        Set(ByVal value As ScanViewsForm)
            m_frmScanViews = value

        End Set
    End Property


#End Region

    Private Sub ExitBut_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ExitBut.Click
        Me.Close()
    End Sub
End Class