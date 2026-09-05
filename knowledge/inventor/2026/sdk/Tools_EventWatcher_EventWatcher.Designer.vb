<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmEventWatcher
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmEventWatcher))
        Me.lblDocName = New System.Windows.Forms.Label()
        Me.lblArgument3 = New System.Windows.Forms.Label()
        Me.lblArgument2 = New System.Windows.Forms.Label()
        Me.lblArgument4 = New System.Windows.Forms.Label()
        Me.btnClearAll = New System.Windows.Forms.Button()
        Me.lblArgument1 = New System.Windows.Forms.Label()
        Me.btnAddMarker = New System.Windows.Forms.Button()
        Me.txtEventResults = New System.Windows.Forms.TextBox()
        Me.cboHandlingCode = New System.Windows.Forms.ComboBox()
        Me.btnClearList = New System.Windows.Forms.Button()
        Me.boxArgumentList = New System.Windows.Forms.GroupBox()
        Me.tblOptions = New System.Windows.Forms.TableLayoutPanel()
        Me.lblArgument6 = New System.Windows.Forms.Label()
        Me.txtFilename1 = New System.Windows.Forms.TextBox()
        Me.txtFilename2 = New System.Windows.Forms.TextBox()
        Me.txtFilename3 = New System.Windows.Forms.TextBox()
        Me.lblNotSupported = New System.Windows.Forms.Label()
        Me.txtFilename4 = New System.Windows.Forms.TextBox()
        Me.lblArgument5 = New System.Windows.Forms.Label()
        Me.txtFilename5 = New System.Windows.Forms.TextBox()
        Me.chkEventList = New System.Windows.Forms.CheckedListBox()
        Me.OpenFileDialog = New System.Windows.Forms.OpenFileDialog()
        Me.btnCancel = New System.Windows.Forms.Button()
        Me.boxArgumentList.SuspendLayout()
        Me.tblOptions.SuspendLayout()
        Me.SuspendLayout()
        '
        'lblDocName
        '
        Me.lblDocName.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.lblDocName.AutoSize = True
        Me.lblDocName.Location = New System.Drawing.Point(107, 544)
        Me.lblDocName.Name = "lblDocName"
        Me.lblDocName.Size = New System.Drawing.Size(10, 13)
        Me.lblDocName.TabIndex = 14
        Me.lblDocName.Text = " "
        '
        'lblArgument3
        '
        Me.lblArgument3.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblArgument3.Location = New System.Drawing.Point(4, 55)
        Me.lblArgument3.Name = "lblArgument3"
        Me.lblArgument3.Size = New System.Drawing.Size(128, 26)
        Me.lblArgument3.TabIndex = 5
        Me.lblArgument3.Text = "Argument 3:"
        Me.lblArgument3.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblArgument3.Visible = False
        '
        'lblArgument2
        '
        Me.lblArgument2.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblArgument2.Location = New System.Drawing.Point(4, 28)
        Me.lblArgument2.Name = "lblArgument2"
        Me.lblArgument2.Size = New System.Drawing.Size(128, 26)
        Me.lblArgument2.TabIndex = 6
        Me.lblArgument2.Text = "Argument 2:"
        Me.lblArgument2.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblArgument2.Visible = False
        '
        'lblArgument4
        '
        Me.lblArgument4.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblArgument4.Location = New System.Drawing.Point(4, 82)
        Me.lblArgument4.Name = "lblArgument4"
        Me.lblArgument4.Size = New System.Drawing.Size(128, 26)
        Me.lblArgument4.TabIndex = 7
        Me.lblArgument4.Text = "Argument 4:"
        Me.lblArgument4.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblArgument4.Visible = False
        '
        'btnClearAll
        '
        Me.btnClearAll.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.btnClearAll.Location = New System.Drawing.Point(12, 532)
        Me.btnClearAll.Name = "btnClearAll"
        Me.btnClearAll.Size = New System.Drawing.Size(80, 25)
        Me.btnClearAll.TabIndex = 13
        Me.btnClearAll.Text = "Clear All"
        Me.btnClearAll.UseVisualStyleBackColor = True
        '
        'lblArgument1
        '
        Me.lblArgument1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblArgument1.Location = New System.Drawing.Point(4, 1)
        Me.lblArgument1.Name = "lblArgument1"
        Me.lblArgument1.Size = New System.Drawing.Size(128, 26)
        Me.lblArgument1.TabIndex = 4
        Me.lblArgument1.Text = "Argument 1:"
        Me.lblArgument1.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblArgument1.Visible = False
        '
        'btnAddMarker
        '
        Me.btnAddMarker.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnAddMarker.Location = New System.Drawing.Point(811, 151)
        Me.btnAddMarker.Name = "btnAddMarker"
        Me.btnAddMarker.Size = New System.Drawing.Size(75, 23)
        Me.btnAddMarker.TabIndex = 11
        Me.btnAddMarker.Text = "Add Marker"
        Me.btnAddMarker.UseVisualStyleBackColor = True
        '
        'txtEventResults
        '
        Me.txtEventResults.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtEventResults.Location = New System.Drawing.Point(365, 209)
        Me.txtEventResults.Multiline = True
        Me.txtEventResults.Name = "txtEventResults"
        Me.txtEventResults.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtEventResults.Size = New System.Drawing.Size(521, 317)
        Me.txtEventResults.TabIndex = 10
        '
        'cboHandlingCode
        '
        Me.cboHandlingCode.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cboHandlingCode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboHandlingCode.Items.AddRange(New Object() {"Not Handled", "Cancel", "Handled"})
        Me.cboHandlingCode.Location = New System.Drawing.Point(139, 4)
        Me.cboHandlingCode.MaxDropDownItems = 3
        Me.cboHandlingCode.Name = "cboHandlingCode"
        Me.cboHandlingCode.Size = New System.Drawing.Size(285, 21)
        Me.cboHandlingCode.TabIndex = 10
        Me.cboHandlingCode.Visible = False
        '
        'btnClearList
        '
        Me.btnClearList.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnClearList.Location = New System.Drawing.Point(811, 180)
        Me.btnClearList.Name = "btnClearList"
        Me.btnClearList.Size = New System.Drawing.Size(75, 23)
        Me.btnClearList.TabIndex = 12
        Me.btnClearList.Text = "Clear List"
        Me.btnClearList.UseVisualStyleBackColor = True
        '
        'boxArgumentList
        '
        Me.boxArgumentList.Controls.Add(Me.tblOptions)
        Me.boxArgumentList.Location = New System.Drawing.Point(365, 12)
        Me.boxArgumentList.Name = "boxArgumentList"
        Me.boxArgumentList.Size = New System.Drawing.Size(440, 191)
        Me.boxArgumentList.TabIndex = 9
        Me.boxArgumentList.TabStop = False
        Me.boxArgumentList.Text = "Input Arguments"
        '
        'tblOptions
        '
        Me.tblOptions.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.[Single]
        Me.tblOptions.ColumnCount = 2
        Me.tblOptions.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 31.57895!))
        Me.tblOptions.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 68.42105!))
        Me.tblOptions.Controls.Add(Me.lblArgument6, 0, 5)
        Me.tblOptions.Controls.Add(Me.cboHandlingCode, 1, 0)
        Me.tblOptions.Controls.Add(Me.lblArgument1, 0, 0)
        Me.tblOptions.Controls.Add(Me.lblArgument3, 0, 2)
        Me.tblOptions.Controls.Add(Me.lblArgument2, 0, 1)
        Me.tblOptions.Controls.Add(Me.lblArgument4, 0, 3)
        Me.tblOptions.Controls.Add(Me.txtFilename1, 1, 1)
        Me.tblOptions.Controls.Add(Me.txtFilename2, 1, 2)
        Me.tblOptions.Controls.Add(Me.txtFilename3, 1, 3)
        Me.tblOptions.Controls.Add(Me.lblNotSupported, 1, 4)
        Me.tblOptions.Controls.Add(Me.txtFilename4, 1, 5)
        Me.tblOptions.Controls.Add(Me.lblArgument5, 0, 4)
        Me.tblOptions.Controls.Add(Me.txtFilename5, 1, 6)
        Me.tblOptions.Location = New System.Drawing.Point(6, 19)
        Me.tblOptions.Name = "tblOptions"
        Me.tblOptions.RowCount = 7
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26.0!))
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26.0!))
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26.0!))
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26.0!))
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26.0!))
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26.0!))
        Me.tblOptions.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20.0!))
        Me.tblOptions.Size = New System.Drawing.Size(428, 165)
        Me.tblOptions.TabIndex = 5
        '
        'lblArgument6
        '
        Me.lblArgument6.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblArgument6.Location = New System.Drawing.Point(4, 136)
        Me.lblArgument6.Name = "lblArgument6"
        Me.lblArgument6.Size = New System.Drawing.Size(128, 26)
        Me.lblArgument6.TabIndex = 14
        Me.lblArgument6.Text = "Argument 6:"
        Me.lblArgument6.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblArgument6.Visible = False
        '
        'txtFilename1
        '
        Me.txtFilename1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtFilename1.Location = New System.Drawing.Point(139, 31)
        Me.txtFilename1.Name = "txtFilename1"
        Me.txtFilename1.Size = New System.Drawing.Size(285, 20)
        Me.txtFilename1.TabIndex = 12
        Me.txtFilename1.Visible = False
        '
        'txtFilename2
        '
        Me.txtFilename2.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtFilename2.Location = New System.Drawing.Point(139, 58)
        Me.txtFilename2.Name = "txtFilename2"
        Me.txtFilename2.Size = New System.Drawing.Size(285, 20)
        Me.txtFilename2.TabIndex = 12
        Me.txtFilename2.Visible = False
        '
        'txtFilename3
        '
        Me.txtFilename3.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtFilename3.Location = New System.Drawing.Point(139, 85)
        Me.txtFilename3.Name = "txtFilename3"
        Me.txtFilename3.Size = New System.Drawing.Size(285, 20)
        Me.txtFilename3.TabIndex = 12
        Me.txtFilename3.Visible = False
        '
        'lblNotSupported
        '
        Me.lblNotSupported.Anchor = System.Windows.Forms.AnchorStyles.Left
        Me.lblNotSupported.AutoSize = True
        Me.lblNotSupported.Location = New System.Drawing.Point(139, 115)
        Me.lblNotSupported.Name = "lblNotSupported"
        Me.lblNotSupported.Size = New System.Drawing.Size(239, 13)
        Me.lblNotSupported.TabIndex = 11
        Me.lblNotSupported.Text = "Providing input for this argument is not supported."
        Me.lblNotSupported.Visible = False
        '
        'txtFilename4
        '
        Me.txtFilename4.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtFilename4.Location = New System.Drawing.Point(139, 139)
        Me.txtFilename4.Name = "txtFilename4"
        Me.txtFilename4.Size = New System.Drawing.Size(285, 20)
        Me.txtFilename4.TabIndex = 13
        Me.txtFilename4.Visible = False
        '
        'lblArgument5
        '
        Me.lblArgument5.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblArgument5.Location = New System.Drawing.Point(4, 109)
        Me.lblArgument5.Name = "lblArgument5"
        Me.lblArgument5.Size = New System.Drawing.Size(128, 26)
        Me.lblArgument5.TabIndex = 8
        Me.lblArgument5.Text = "Argument 5:"
        Me.lblArgument5.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.lblArgument5.Visible = False
        '
        'txtFilename5
        '
        Me.txtFilename5.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtFilename5.Location = New System.Drawing.Point(139, 166)
        Me.txtFilename5.Name = "txtFilename5"
        Me.txtFilename5.Size = New System.Drawing.Size(285, 20)
        Me.txtFilename5.TabIndex = 15
        Me.txtFilename5.Visible = False
        '
        'chkEventList
        '
        Me.chkEventList.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.chkEventList.FormattingEnabled = True
        Me.chkEventList.Location = New System.Drawing.Point(12, 12)
        Me.chkEventList.Name = "chkEventList"
        Me.chkEventList.Size = New System.Drawing.Size(347, 499)
        Me.chkEventList.TabIndex = 8
        '
        'OpenFileDialog
        '
        Me.OpenFileDialog.FileName = "OpenFileDialog1"
        '
        'btnCancel
        '
        Me.btnCancel.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnCancel.Location = New System.Drawing.Point(806, 532)
        Me.btnCancel.Name = "btnCancel"
        Me.btnCancel.Size = New System.Drawing.Size(80, 25)
        Me.btnCancel.TabIndex = 15
        Me.btnCancel.Text = "Cancel"
        Me.btnCancel.UseVisualStyleBackColor = True
        '
        'frmEventWatcher
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(898, 569)
        Me.Controls.Add(Me.btnCancel)
        Me.Controls.Add(Me.lblDocName)
        Me.Controls.Add(Me.btnClearAll)
        Me.Controls.Add(Me.btnAddMarker)
        Me.Controls.Add(Me.txtEventResults)
        Me.Controls.Add(Me.btnClearList)
        Me.Controls.Add(Me.boxArgumentList)
        Me.Controls.Add(Me.chkEventList)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MinimumSize = New System.Drawing.Size(906, 595)
        Me.Name = "frmEventWatcher"
        Me.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show
        Me.Text = "Event Watcher"
        Me.boxArgumentList.ResumeLayout(False)
        Me.tblOptions.ResumeLayout(False)
        Me.tblOptions.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents lblDocName As System.Windows.Forms.Label
    Friend WithEvents lblArgument3 As System.Windows.Forms.Label
    Friend WithEvents lblArgument2 As System.Windows.Forms.Label
    Friend WithEvents lblArgument4 As System.Windows.Forms.Label
    Friend WithEvents btnClearAll As System.Windows.Forms.Button
    Friend WithEvents lblArgument1 As System.Windows.Forms.Label
    Friend WithEvents btnAddMarker As System.Windows.Forms.Button
    Friend WithEvents txtEventResults As System.Windows.Forms.TextBox
    Friend WithEvents cboHandlingCode As System.Windows.Forms.ComboBox
    Friend WithEvents btnClearList As System.Windows.Forms.Button
    Friend WithEvents boxArgumentList As System.Windows.Forms.GroupBox
    Friend WithEvents tblOptions As System.Windows.Forms.TableLayoutPanel
    Friend WithEvents txtFilename1 As System.Windows.Forms.TextBox
    Friend WithEvents txtFilename2 As System.Windows.Forms.TextBox
    Friend WithEvents txtFilename3 As System.Windows.Forms.TextBox
    Friend WithEvents lblArgument5 As System.Windows.Forms.Label
    Friend WithEvents lblNotSupported As System.Windows.Forms.Label
    Friend WithEvents txtFilename4 As System.Windows.Forms.TextBox
    Friend WithEvents chkEventList As System.Windows.Forms.CheckedListBox
    Friend WithEvents OpenFileDialog As System.Windows.Forms.OpenFileDialog
    Friend WithEvents btnCancel As System.Windows.Forms.Button
    Friend WithEvents lblArgument6 As System.Windows.Forms.Label
    Friend WithEvents txtFilename5 As System.Windows.Forms.TextBox

End Class
