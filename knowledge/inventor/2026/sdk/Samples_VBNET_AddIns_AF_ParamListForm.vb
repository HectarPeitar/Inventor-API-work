Option Strict Off
Option Explicit On
Friend Class ParamListForm
    Inherits System.Windows.Forms.Form

    Public Sub Initialize(ByRef ParamCollection As Inventor.Parameters)
        Dim oParam As Inventor.Parameter
        For Each oParam In ParamCollection
            lstParams.Items.Add(oParam.Name & ", (" & oParam.Expression & ")")
        Next oParam
    End Sub

    Private Sub cmdOK_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdOK.Click
        Me.Visible = False
    End Sub
End Class