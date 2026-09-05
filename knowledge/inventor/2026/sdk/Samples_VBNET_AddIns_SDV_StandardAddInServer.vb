Imports Inventor
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

Namespace ScanDrawingViews
    <ProgIdAttribute("ScanDrawingViews.StandardAddInServer"), _
    GuidAttribute("b11d00bf-8671-474e-b698-03e5478c8a1e")> _
    Public Class StandardAddInServer
        Implements Inventor.ApplicationAddInServer

        ' Inventor application object.
        Private m_inventorApplication As Inventor.Application
        Private WithEvents oButtonDefScanDrawingViews As Inventor.ButtonDefinition
        Private WithEvents oUserInterfaceEvents As Inventor.UserInterfaceEvents

#Region "ApplicationAddInServer Members"

        Public Sub Activate(ByVal addInSiteObject As Inventor.ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

            ' This method is called by Inventor when it loads the AddIn.
            ' The AddInSiteObject provides access to the Inventor Application object.
            ' The FirstTime flag indicates if the AddIn is loaded for the first time.

            ' Initialize AddIn members.
            m_inventorApplication = addInSiteObject.Application

            ' Set a reference to the user interface events.
            oUserInterfaceEvents = m_inventorApplication.UserInterfaceManager.UserInterfaceEvents

            'create the button to create the text graphics
            oButtonDefScanDrawingViews = m_inventorApplication.CommandManager.ControlDefinitions.AddButtonDefinition("Scan Drawing Views", "ScanDrawingViewsCmdIntName", Inventor.CommandTypesEnum.kQueryOnlyCmdType, "{0E2365C9-C7A2-4304-9B1C-29285781218A}", "Scan Drawing Views", "Scan Drawing Views")

            'enable the button
            oButtonDefScanDrawingViews.Enabled = True

            'create the command category
            Dim oCommandCategory As Inventor.CommandCategory
            oCommandCategory = m_inventorApplication.CommandManager.CommandCategories.Add("Scan Drawing Views", "ScanDrawingViewsCmdCatIntName", "{0E2365C9-C7A2-4304-9B1C-29285781218A}")

            oCommandCategory.Add(oButtonDefScanDrawingViews)

            'if AddIn is called first time, create toolbar and add button to toolbar
            Dim oCommandBar As Inventor.CommandBar
            If firstTime = True Then

                'create a new toolbar
                oCommandBar = m_inventorApplication.UserInterfaceManager.CommandBars.Add("Scan Drawing Views", "ScanDrawingViewsToolbarIntName", , "{0E2365C9-C7A2-4304-9B1C-29285781218A}")

                'add the button to the toolbar
                oCommandBar.Controls.AddButton(oButtonDefScanDrawingViews)

                'make the toolbar visible
                oCommandBar.Visible = True

            End If


        End Sub

        Public Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

            ' This method is called by Inventor when the AddIn is unloaded.
            ' The AddIn will be unloaded either manually by the user or
            ' when the Inventor session is terminated.

            'delete the button definition
            oButtonDefScanDrawingViews.Delete()

            'release the references
            'UPGRADE_NOTE: Object oButtonDefScanDrawingViews may not be destroyed until it is garbage collected. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="6E35BFF6-CD74-4B09-9689-3E1A43DF8969"'
            oButtonDefScanDrawingViews = Nothing
            'UPGRADE_NOTE: Object m_inventorApplication may not be destroyed until it is garbage collected. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="6E35BFF6-CD74-4B09-9689-3E1A43DF8969"'
            m_inventorApplication = Nothing


            ' Release objects.
            Marshal.ReleaseComObject(m_inventorApplication)
            m_inventorApplication = Nothing

            System.GC.WaitForPendingFinalizers()
            System.GC.Collect()

        End Sub

        Public ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation

            ' This property is provided to allow the AddIn to expose an API 
            ' of its own to other programs. Typically, this  would be done by
            ' implementing the AddIn's API interface in a class and returning 
            ' that class object through this property.

            Get
                Return Nothing
            End Get

        End Property

        Public Sub ExecuteCommand(ByVal commandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand

            ' Note:this method is now obsolete, you should use the 
            ' ControlDefinition functionality for implementing commands.

        End Sub
        Private Sub oButtonDefScanDrawingViews_OnExecute(ByVal Context As Inventor.NameValueMap) Handles oButtonDefScanDrawingViews.OnExecute

            'Obtain current document
            Dim oDocument As Inventor.Document
            oDocument = m_inventorApplication.ActiveDocument

            If oDocument Is Nothing Then
                MsgBox("DrawingViews: Please open a drawing document.")
                Exit Sub
            End If

            'Ensure document is a drawing
            If oDocument.DocumentType <> Inventor.DocumentTypeEnum.kDrawingDocumentObject Then
                MsgBox("DrawingViews: Please open a drawing document.")
                Exit Sub
            End If

            Dim oDrawingDocument As Inventor.DrawingDocument
            oDrawingDocument = oDocument

            Dim oSheets As Inventor.Sheets
            oSheets = oDrawingDocument.Sheets
            ScanViewsForm.frmScanViewsInstance.Show()
            ScanViewsForm.frmScanViewsInstance.ListBox1.Items.Clear()

            Dim oSheet As Inventor.Sheet
            Dim oDrawViews As Inventor.DrawingViews
            Dim oDrawView As Inventor.DrawingView
            For Each oSheet In oSheets
                ScanViewsForm.frmScanViewsInstance.ListBox1.Items.Add(("Sheet Name: " & oSheet.Name))

                oDrawViews = oSheet.DrawingViews
                If (oDrawViews.Count) = 0 Then
                    ScanViewsForm.frmScanViewsInstance.ListBox1.Items.Add((Space(8) & "No drawing views defined in this sheet. "))
                End If

                For Each oDrawView In oDrawViews
                    With ScanViewsForm.frmScanViewsInstance.ListBox1
                        .Items.Add((Space(8) & "Drawing View Name: " & oDrawView.Name))
                        .Items.Add((Space(16) & "Center Point: " & oDrawView.Center.X & ", " & oDrawView.Center.Y))
                        .Items.Add((Space(16) & "Left edge: " & oDrawView.Left))
                        .Items.Add((Space(16) & "Top edge: " & oDrawView.Top))
                        .Items.Add((Space(16) & "Height: " & oDrawView.Height))
                        .Items.Add((Space(16) & "Width: " & oDrawView.Width))
                        .Items.Add((Space(16) & "Scale: " & oDrawView.Scale))
                        Select Case (oDrawView.ViewStyle)
                            Case Inventor.DrawingViewStyleEnum.kFromBaseDrawingViewStyle
                                .Items.Add((Space(16) & "Drawing View Style: From Base Drawing View"))
                            Case Inventor.DrawingViewStyleEnum.kHiddenLineDrawingViewStyle
                                .Items.Add((Space(16) & "Drawing View Style: Hidden Line"))
                            Case Inventor.DrawingViewStyleEnum.kHiddenLineRemovedDrawingViewStyle
                                .Items.Add((Space(16) & "Drawing View Style: Hidden Line Removed"))
                            Case Inventor.DrawingViewStyleEnum.kShadedDrawingViewStyle
                                .Items.Add((Space(16) & "Drawing View Style: Shaded"))
                        End Select
                        Select Case (oDrawView.ViewType)
                            Case Inventor.DrawingViewTypeEnum.kAuxiliaryDrawingViewType
                                .Items.Add((Space(16) & "View type: Auxiliary"))
                            Case Inventor.DrawingViewTypeEnum.kCustomDrawingViewType
                                .Items.Add((Space(16) & "View type: Custom"))
                            Case Inventor.DrawingViewTypeEnum.kDefaultDrawingViewType
                                .Items.Add((Space(16) & "View type: Default"))
                            Case Inventor.DrawingViewTypeEnum.kDetailDrawingViewType
                                .Items.Add((Space(16) & "View type: Detail"))
                            Case Inventor.DrawingViewTypeEnum.kOLEAttachmentDrawingViewType
                                .Items.Add((Space(16) & "View type: OLE attachment"))
                            Case Inventor.DrawingViewTypeEnum.kSectionDrawingViewType
                                .Items.Add((Space(16) & "View type: section"))
                            Case Inventor.DrawingViewTypeEnum.kStandardDrawingViewType
                                .Items.Add((Space(16) & "View type: Standard"))
                        End Select
                    End With
                Next oDrawView

            Next oSheet

        End Sub

        Private Sub oUserInterfaceEvents_OnResetCommandBars(ByVal CommandBars As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles oUserInterfaceEvents.OnResetCommandBars

            Dim oCommandBar As Inventor.CommandBar
            For Each oCommandBar In CommandBars
                If oCommandBar.InternalName = "ScanDrawingViewsToolbarIntName" Then

                    'add buttons to scan drawing views toolbar
                    oCommandBar.Controls.AddButton(oButtonDefScanDrawingViews)

                    Exit Sub
                End If
            Next oCommandBar
        End Sub
#End Region

    End Class

End Namespace

