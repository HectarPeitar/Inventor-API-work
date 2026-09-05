'Inventor SDK Sample
'Purpose: Illustrate how to build sketches, sketch entities, constrains, features and custom graphics in part environment via Inventor API
'Language & Platform: Microsoft Visual Studio .Net 2005 (Visual Basic)
'Copyright Autodesk

'import libraries
Imports Inventor
Imports System.Runtime.InteropServices

<ProgId("PartFeaturesAddin.BoltMaker"), _
GuidAttribute("7B0327D5-9D20-46A2-8181-393F0AF09919")> _
Public Class BoltMaker
    Implements Inventor.ApplicationAddInServer

#Region "Data Members"
    Private Declare Function SetParent Lib "user32" Alias "SetParent" (ByVal hWndChild As Int32, ByVal hWndNewParent As Int32) As Int32

    'constant definition
    Public Const TRANSACTION_NAME As String = "Create Bolt"
    Public Const PROPERTY_SET_NAME As String = "Bolt Property Set"
    Public Const PROPERTY_SET_INTERNALNAME As String = "{E76809C5-35C0-4005-9E48-A61C0CD5CE83}"
    Public Const PROPERTY_LAST_BOLT_ID As String = "LastBoltID"
    Public Const BOLT_ID_BASE As String = "Bolt"

    'class variable definitions
    Private InventorApplication As Inventor.Application
    Private oTG As TransientGeometry = Nothing
    Private obuttonCtl As CommandBarControl = Nothing
    Private opreviewDoc As PartDocument = Nothing       'to record user-specified document
    Private opreviewLocation As Point = Nothing     'to record user-specified location
    Private otransaction As Transaction = Nothing
    Private icurrentBoltID As Integer = 0

    Private WithEvents oparaDlg As BoltParas = Nothing
    Private WithEvents ointeraction As InteractionEvents = Nothing
    Private WithEvents obuttonDef As ButtonDefinition = Nothing
    Private WithEvents omouseEvent As MouseEvents = Nothing
#End Region

#Region "ApplicationAddInServer Members"

    Public Sub Activate(ByVal addInSiteObject As Inventor.ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

        'the Activate method is called by Inventor when it loads the addin
        'the AddInSiteObject provides access to the Inventor Application object
        'the FirstTime flag indicates if the addin is loaded for the first time

        Try
            'initialize AddIn members
            InventorApplication = addInSiteObject.Application

            'get transient geometry object
            oTG = InventorApplication.TransientGeometry

            'create button in part environment
            AddCreateBoltButton(FirstTime)
        Catch ex As Exception
            MsgBox(ex.Message, MsgBoxStyle.OkOnly + MsgBoxStyle.Exclamation)
        End Try
    End Sub

    Public Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

        'the Deactivate method is called by Inventor when the AddIn is unloaded
        'the AddIn will be unloaded either manually by the user or
        'when the Inventor session is terminated

        Try
            'release objects
            otransaction = Nothing
            oTG = Nothing
            opreviewLocation = Nothing
            opreviewDoc = Nothing
            oButtonCtl = Nothing
            ointeraction = Nothing
            oparaDlg = Nothing
            obuttonDef = Nothing
            omouseEvent = Nothing
            If Not InventorApplication Is Nothing Then
                Runtime.InteropServices.Marshal.ReleaseComObject(InventorApplication)
                InventorApplication = Nothing
            End If
        Catch
        Finally
            System.GC.WaitForPendingFinalizers()
            System.GC.Collect()
        End Try
    End Sub

    Public ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation

        'if you want to return an interface to another client of this addin,
        'implement that interface in a class and return that class object 
        'through this property

        Get
            Return Nothing
        End Get

    End Property

    Public Sub ExecuteCommand(ByVal commandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand

        'this method was used to notify when an AddIn command was executed
        'the CommandID parameter identifies the command that was executed

        'Note:this method is now obsolete, you should use the new
        'ControlDefinition objects to implement commands, they have
        'their own event sinks to notify when the command is executed

    End Sub

#End Region

#Region "COM Registration"

    ' Registers this class as an Add-In for Autodesk Inventor.
    ' This function is called when the assembly is registered for COM.
    <System.Runtime.InteropServices.ComRegisterFunction()> _
    Public Shared Sub RegisterFunction(ByVal t As Type)

        'call the method in the AddInRegistration class to register the AddIn
        AddInRegistration.RegisterInventorAddIn(t)

    End Sub

    ' Unregisters this class as an Add-In for Autodesk Inventor.
    ' This function is called when the assembly is unregistered.
    <System.Runtime.InteropServices.ComUnregisterFunction()> _
    Public Shared Sub UnregisterFunction(ByVal t As Type)

        'call the method in the AddInRegistration class to unregister the AddIn
        AddInRegistration.UnregisterInventorAddIn(t)

    End Sub

#End Region

#Region "Event Handlers"

    Private Sub oButton_OnExecute(ByVal context As Inventor.NameValueMap) Handles obuttonDef.OnExecute
        Dim ocmdMgr As CommandManager

        Try
            If Not InventorApplication.ActiveView Is Nothing Then
                'create a dialog to let user input parameters
                oparaDlg = New BoltParas(InventorApplication.ActiveDocument.UnitsOfMeasure)
                SetParent(oparaDlg.Handle.ToInt32(), InventorApplication.MainFrameHWND)
                icurrentBoltID = GetLastBoltID(InventorApplication.ActiveView.Document) + 1
                oparaDlg.txtBoltName.Text = BOLT_ID_BASE & iCurrentBoltID.ToString()
                oparaDlg.Show()

                'get command manager object
                ocmdMgr = InventorApplication.CommandManager

                'create an interacting command
                ointeraction = ocmdMgr.CreateInteractionEvents()

                'attach handler to mouse event
                omouseEvent = ointeraction.MouseEvents

                'start interacting
                ointeraction.Start()

                'create transaction
                otransaction = InventorApplication.TransactionManager.StartTransaction(InventorApplication.ActiveView.Document, TRANSACTION_NAME)
            End If
        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.Message, "PartFeaturesAddin", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation)
        End Try
    End Sub

    Private Sub oMouseEvent_OnMouseClick(ByVal button As Inventor.MouseButtonEnum, ByVal shiftKeys As Inventor.ShiftStateEnum, ByVal modelPosition As Inventor.Point, ByVal viewPosition As Inventor.Point2d, ByVal view As Inventor.View) Handles oMouseEvent.OnMouseClick
        Dim odoc As Document

        Try
            'check the view parameter
            If Not view Is Nothing Then
                'create bolt
                odoc = view.Document
                If Not oDoc Is Nothing Then
                    If oDoc.DocumentType = DocumentTypeEnum.kPartDocumentObject And Not oparaDlg Is Nothing Then
                        'draw preview
                        UpdatePreview(modelPosition)

                        'show position coordinates
                        If Not oparaDlg Is Nothing Then oparaDlg.SetPosition(modelPosition)

                        'allow user to create bolt if there is no parameter errors
                        If oparaDlg.iParameterErrors = 0 Then
                            oparaDlg.btCreate.Enabled = True
                        End If

                        'allow user to modify position
                        oparaDlg.txtX.Enabled = True
                        oparaDlg.txtY.Enabled = True
                        oparaDlg.txtZ.Enabled = True
                    End If
                End If
            End If
        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.Message, "PartFeaturesAddin", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation)
        End Try
    End Sub

    Private Sub oParaDlg_CreateBoltEvent(ByVal sender As Object, ByVal okFlag As Boolean, ByVal odefinition As clsBolt.BoltParameter) Handles oparaDlg.CreateBoltEvent
        Dim obolt As clsBolt
        Try
            If okFlag Then
                'create instance of bolt object
                obolt = New clsBolt(odefinition)

                'create a bolt
                obolt.Create(InventorApplication, opreviewDoc, opreviewLocation)

                'set Bolt ID
                SetLastBoltID(opreviewDoc, icurrentBoltID)

                'transaction finished
                If Not otransaction Is Nothing Then
                    otransaction.End()
                    otransaction = Nothing
                End If
            End If
        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.Source & ex.Message, "PartFeaturesAddin", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation)
        Finally
            'stop interacting
            ointeraction.Stop()
        End Try
    End Sub

    Private Sub oParaDlg_PositionChangedEvent(ByVal sender As Object, ByVal x As Double, ByVal y As Double, ByVal z As Double) Handles oParaDlg.PositionChangedEvent
        Try
            If Not opreviewDoc Is Nothing Then
                UpdatePreview(oTG.CreatePoint(x, y, z))
            End If
        Catch : End Try
    End Sub

    Private Sub oInteraction_OnActivate() Handles ointeraction.OnActivate
        'keep panel button in pressed status
        If Not obuttonDef Is Nothing Then obuttonDef.Pressed = True
    End Sub

    Private Sub oInteraction_OnTerminate() Handles ointeraction.OnTerminate
        Try
            'close dialog
            If Not oparaDlg Is Nothing Then oparaDlg.Close()

            'transaction aborted
            If Not otransaction Is Nothing Then
                otransaction.Abort()
                otransaction = Nothing
            End If

            'release panel button
            If Not obuttonDef Is Nothing Then obuttonDef.Pressed = False
        Catch : End Try
    End Sub

#End Region

#Region "Utility Methods"

    'add button to the toolbar
    Private Sub AddCreateBoltButton(ByVal bfirstTime As Boolean)
        Dim ocmdMgr As CommandManager
        Dim ouiMgr As UserInterfaceManager

        Try
            ocmdMgr = InventorApplication.CommandManager
            ouiMgr = InventorApplication.UserInterfaceManager

            'create button's definition here
            obuttonDef = ocmdMgr.ControlDefinitions.AddButtonDefinition("Create Bolt", "CreateBoltIntCmd",
                                   CommandTypesEnum.kShapeEditCmdType, Me.GetType().GUID.ToString("B"), "Create a User-Defined Bolt", "Create a User-Defined Bolt",
                                      ConvertImage.ImageToIPicture(New Drawing.Bitmap(Me.GetType(), "bolt.ico")))

            'add this button into part environment panel only if the addin is loaded for the first time
            If bfirstTime Then
                obuttonCtl = ouiMgr.Environments("PMxPartEnvironment").PanelBar.DefaultCommandBar.Controls.AddButton(obuttonDef)
            End If
        Catch
            Throw
        End Try
    End Sub

    'update preview of bolt
    Private Sub UpdatePreview(ByVal olocation As Point)
        Dim opreviewGraphics As ClientGraphics
        Dim opreviewDataSets As GraphicsDataSets
        Dim ocustomCoordinateSet As GraphicsCoordinateSet
        Dim ocustomColorSet As GraphicsColorSet
        Dim ocustomGNode, ogNode As GraphicsNode
        Dim ogSet As GraphicsDataSet
        Dim ocustomLines As LineGraphics
        Dim oview As View

        Try
            If Not ointeraction Is Nothing Then
                'get custom graphics object for preview
                opreviewGraphics = ointeraction.InteractionGraphics.PreviewClientGraphics
                opreviewDataSets = oInteraction.InteractionGraphics.GraphicsDataSets

                'clear previous preview
                For Each ogNode In opreviewGraphics
                    ogNode.Delete()
                Next
                For Each ogSet In opreviewDataSets
                    ogSet.Delete()
                Next

                If Not olocation Is Nothing Then
                    'record current preview parameter
                    opreviewDoc = ointeraction.TargetDocument
                    opreviewLocation = olocation

                    'draw preview by custom graphics
                    ocustomCoordinateSet = oPreviewDataSets.CreateCoordinateSet(1)
                    ocustomColorSet = oPreviewDataSets.CreateColorSet(1)

                    'set coordinates to draw an arrow
                    ocustomCoordinateSet.Add(1, oTG.CreatePoint(olocation.X - 0.5, olocation.Y, olocation.Z))
                    ocustomCoordinateSet.Add(2, oTG.CreatePoint(olocation.X + 0.5, olocation.Y, olocation.Z))
                    ocustomCoordinateSet.Add(3, oTG.CreatePoint(olocation.X, olocation.Y - 0.5, olocation.Z))
                    ocustomCoordinateSet.Add(4, oTG.CreatePoint(olocation.X, olocation.Y + 0.5, olocation.Z))
                    ocustomCoordinateSet.Add(5, oTG.CreatePoint(olocation.X, olocation.Y, olocation.Z + 0.5))
                    ocustomCoordinateSet.Add(6, oTG.CreatePoint(olocation.X, olocation.Y, olocation.Z - 1.5))
                    ocustomCoordinateSet.Add(7, oTG.CreatePoint(olocation.X, olocation.Y, olocation.Z - 1.5))
                    ocustomCoordinateSet.Add(8, oTG.CreatePoint(olocation.X - 0.05, olocation.Y, olocation.Z - 1.4))
                    ocustomCoordinateSet.Add(9, oTG.CreatePoint(olocation.X, olocation.Y, olocation.Z - 1.5))
                    ocustomCoordinateSet.Add(10, oTG.CreatePoint(olocation.X, olocation.Y - 0.05, olocation.Z - 1.4))
                    ocustomCoordinateSet.Add(11, oTG.CreatePoint(olocation.X, olocation.Y, olocation.Z - 1.5))
                    ocustomCoordinateSet.Add(12, oTG.CreatePoint(olocation.X + 0.05, olocation.Y, olocation.Z - 1.4))
                    ocustomCoordinateSet.Add(13, oTG.CreatePoint(olocation.X, olocation.Y, olocation.Z - 1.5))
                    ocustomCoordinateSet.Add(14, oTG.CreatePoint(olocation.X, olocation.Y + 0.05, olocation.Z - 1.4))

                    'set colors 
                    oCustomColorSet.Add(1, 255, 0, 0)

                    'create graphics node
                    ocustomGNode = opreviewGraphics.AddNode(1)
                    ocustomLines = oCustomGNode.AddLineGraphics()
                    ocustomLines.CoordinateSet = ocustomCoordinateSet
                    ocustomLines.ColorSet = ocustomColorSet
                    ocustomLines.ColorBinding = ColorBindingEnum.kOverallColor
                End If

                'update every relevant view
                For Each oview In opreviewDoc.Views
                    oview.Update()
                Next
            End If
        Catch
            Throw
        End Try
    End Sub

    'get the max id of created bolts
    Private Function GetLastBoltID(ByVal opartDoc As PartDocument) As Integer
        Dim opropertySet As PropertySet

        Try
            opropertySet = opartDoc.PropertySets(PROPERTY_SET_INTERNALNAME)
            Return opropertySet.Item(PROPERTY_LAST_BOLT_ID).Value
        Catch
            Return 0
        End Try
    End Function

    'record the max id of created bolts into document properties
    Private Sub SetLastBoltID(ByVal opartDoc As PartDocument, ByVal ilastID As Integer)
        Dim opropertySet As PropertySet = Nothing
        Dim oprop As Inventor.Property = Nothing

        Try
            opropertySet = opartDoc.PropertySets(PROPERTY_SET_INTERNALNAME)
        Catch
            opropertySet = opartDoc.PropertySets.Add(PROPERTY_SET_INTERNALNAME)
        End Try
        Try
            oprop = opropertySet.Item(PROPERTY_LAST_BOLT_ID)
            oprop.Value = ilastID
        Catch
            oprop = opropertySet.Add(ilastID, PROPERTY_LAST_BOLT_ID)
        End Try
    End Sub

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
