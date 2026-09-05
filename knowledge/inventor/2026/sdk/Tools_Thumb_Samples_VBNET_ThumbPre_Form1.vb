Imports System.IO
Imports InventorThumbnailViewLib

Public Class Form1
    Inherits System.Windows.Forms.Form

    Friend WithEvents OFD As System.Windows.Forms.OpenFileDialog
    Private pThumbnailProvider As InventorThumbnailViewLib.ThumbnailProvider
    Private CurrentFileName As String

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox
        Me.Button1 = New System.Windows.Forms.Button
        Me.Button2 = New System.Windows.Forms.Button
        Me.Label1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.TextBox1 = New System.Windows.Forms.TextBox
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'PictureBox1
        '
        Me.PictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.PictureBox1.Location = New System.Drawing.Point(88, 56)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(180, 180)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 0
        Me.PictureBox1.TabStop = False
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(288, 16)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(64, 24)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "&Browse..."
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(160, 248)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(56, 24)
        Me.Button2.TabIndex = 2
        Me.Button2.Text = "&Done"
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(120, 136)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(104, 16)
        Me.Label1.TabIndex = 3
        Me.Label1.Text = "View thumbnail"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(8, 16)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(72, 16)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Source File:"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(72, 16)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(208, 20)
        Me.TextBox1.TabIndex = 5
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(360, 286)
        Me.Controls.Add(Me.TextBox1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.PictureBox1)
        Me.Name = "Form1"
        Me.Text = "View Thumbnail"
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

#End Region

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        On Error Resume Next

        'define thumbnail viewer
        pThumbnailProvider = New InventorThumbnailViewLib.ThumbnailProvider

        If pThumbnailProvider Is Nothing Then
            MsgBox("Could not obtain thumbnail provider. Please make sure the InventorThumbnailView dll has been registered", vbOKOnly + vbExclamation)
            Me.Close()
            End
        End If

        On Error GoTo 0
    End Sub

    Private Sub ShowThumbnail()
        Me.OFD = New System.Windows.Forms.OpenFileDialog
        'open file dialog file filter settings 
        OFD.Filter = "Inventor Files (*.iam; *.idw; *.ide; *.ipt; *.ipn)|*.iam;*.idw;*.ide;*.ipt;*.ipn|Assembly Fiels (*.iam)|*.iam|Drawing Files (*.idw)|*.idw|iFeature Files (*.ide)|*.ide|Part Files (*.ipt)|*.ipt|Presentation Files (*.ipn)|*.ipn|All Files (*.*)|*.*"
        'showing file open dialog box
        OFD.ShowDialog()

        'Thumbnailing image and loading into picturebox 
        CurrentFileName = OFD.FileName
        If File.Exists(CurrentFileName) Then

            'get thumbnail from viewer
            Dim ppPicture As stdole.IPictureDisp = pThumbnailProvider.GetThumbnail(CurrentFileName)

            'if get thumbnail succeeded
            If Not ppPicture Is Nothing Then
                'set image to picture box
                PictureBox1.Image = Microsoft.VisualBasic.Compatibility.VB6.IPictureDispToImage(ppPicture)

                'set text in textbox
                TextBox1.Text = CurrentFileName

                'set text visible to false
                Label1.Visible = False
            End If
        End If

    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        'goto view thumbnail function
        ShowThumbnail()
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        'close me
        Me.Close()
    End Sub

    Private Sub TextBox1_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles TextBox1.KeyPress
        If e.KeyChar = Chr(Keys.Enter) Then
            e.Handled = False
            CurrentFileName = sender.Text
            ShowThumbnail()
        End If
    End Sub

    Private Sub TextBox1_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles TextBox1.LostFocus
        If sender.Text <> CurrentFileName Then
            CurrentFileName = sender.Text
            ShowThumbnail()
        End If
    End Sub
End Class
