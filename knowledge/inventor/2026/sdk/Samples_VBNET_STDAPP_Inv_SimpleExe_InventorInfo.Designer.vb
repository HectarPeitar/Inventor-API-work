<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class InventorInfo
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing AndAlso components IsNot Nothing Then
            components.Dispose()
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim ListViewItem1 As System.Windows.Forms.ListViewItem = New System.Windows.Forms.ListViewItem(New String() {"", ""}, -1)
        Me.btnClose = New System.Windows.Forms.Button
        Me.lstViewInvInfo = New System.Windows.Forms.ListView
        Me.PropertyColumnHeader = New System.Windows.Forms.ColumnHeader
        Me.ValueColumnHeader = New System.Windows.Forms.ColumnHeader
        Me.SuspendLayout()
        '
        'btnClose
        '
        Me.btnClose.Location = New System.Drawing.Point(363, 333)
        Me.btnClose.Name = "btnClose"
        Me.btnClose.Size = New System.Drawing.Size(99, 54)
        Me.btnClose.TabIndex = 0
        Me.btnClose.Text = "Close"
        Me.btnClose.UseVisualStyleBackColor = True
        '
        'lstViewInvInfo
        '
        Me.lstViewInvInfo.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.PropertyColumnHeader, Me.ValueColumnHeader})
        Me.lstViewInvInfo.Items.AddRange(New System.Windows.Forms.ListViewItem() {ListViewItem1})
        Me.lstViewInvInfo.Location = New System.Drawing.Point(29, 29)
        Me.lstViewInvInfo.MultiSelect = False
        Me.lstViewInvInfo.Name = "lstViewInvInfo"
        Me.lstViewInvInfo.Size = New System.Drawing.Size(433, 283)
        Me.lstViewInvInfo.TabIndex = 2
        Me.lstViewInvInfo.UseCompatibleStateImageBehavior = False
        Me.lstViewInvInfo.View = System.Windows.Forms.View.Details
        '
        'PropertyColumnHeader
        '
        Me.PropertyColumnHeader.Text = "Property"
        Me.PropertyColumnHeader.Width = 110
        '
        'ValueColumnHeader
        '
        Me.ValueColumnHeader.Text = "Value"
        Me.ValueColumnHeader.Width = 319
        '
        'InventorInfo
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(507, 399)
        Me.Controls.Add(Me.lstViewInvInfo)
        Me.Controls.Add(Me.btnClose)
        Me.Name = "InventorInfo"
        Me.Text = "Inventor Information"
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents btnClose As System.Windows.Forms.Button
    Friend WithEvents lstViewInvInfo As System.Windows.Forms.ListView
    Friend WithEvents PropertyColumnHeader As System.Windows.Forms.ColumnHeader
    Friend WithEvents ValueColumnHeader As System.Windows.Forms.ColumnHeader

End Class
