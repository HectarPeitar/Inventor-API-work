Option Strict Off
Option Explicit On


Imports FeatureStatistics

Module GetFeaturesInfo


    ' This sample uses Inventor to get a part document's model information:
    ' solid bodies, work surfaces, custom features and rebuild times.
	
    ' Declarations of the global variables

    Public blnAddInLoadedFirstTime As Boolean

    Public oPartDoc As Inventor.PartDocument
    Public oCompDef As Inventor.PartComponentDefinition
    Public Const sWkFeaturesName As String = "Work Geometries"
    Public Const sSksName As String = "2D & 3D Sketches"
    Private FrmFeatureStatistics As FrmFeatureStatistics
    ' "lUserWkFeaturesNum" records the count of user-defined works features (plane, axis and point)
    ' "lUserWkFeaturesTypes" records the types count of user-defined works features
    ' "lSksNum records" the count of 2s&3d sketches
    ' "lUnSuppressedFeatureTypes" records the types count of unsuppressed part features
    ' "lUnSuppressedFeaturesNum" records the count of unsuppressed part features
    Public lUnSuppressedFeatureTypes, lUserWkFeaturesTypes, lUserWkFeaturesNum, lSksNum, lUnSuppressedFeaturesNum As Integer

    ' "sFeatureName()" indicates the list of types name of part features
    ' "lUnSuppressedFeatureCount()" indicates the list of the unsuppressed feature(s) count(can be zero) of each type part feature
    ' "lSuppressedFeatureCount()" indicates the list of the suppressed feature(s) count of each type part feature
    ' "dRebuildTime()" indicates the list of rebuild time of each feature: part feature, user-defined work feature, 2d & 3d sketch, with creation order
    Public sFeatureName() As String
    Public lUnSuppressedFeatureCount() As Integer
    Public lSuppressedFeatureCount() As Integer
    Public dRebuildTime() As Double

    ' Get numbers for each feature types and list them alphabetically
    Public Sub ListFeatureNameNumInfo()
        Err.Clear()
        On Error Resume Next

        oPartDoc = FeatureStatistics.StandardAddInServer.m_inventorApplication.ActiveDocument

        If Err.Number <> 0 Or oPartDoc Is Nothing Then
            MsgBox("Please open a part document")
            Err.Clear() : Exit Sub
        End If

        oCompDef = oPartDoc.ComponentDefinition

        FrmFeatureStatistics = New FrmFeatureStatistics

        FrmFeatureStatistics.Show()

        ' Assign values for labels to show DisplayName, solids count and work surfaces count
        With FrmFeatureStatistics
            .lblFileNameText.Text = oPartDoc.DisplayName
            .lblRebuildTime.Visible = True
            .lblTime.Visible = True
            .lblSolidsNumCount.Text = CStr(oCompDef.SurfaceBodies.Count)
            .lblSurfNumsCount.Text = CStr(oCompDef.WorkSurfaces.Count)
        End With

        ' Get features' counts and types info for part model
        GetMultiFeaturesInfo()
        SetCurrentFeaturesCountTypesInfo()

        ' List features' counts and types info at ListView window
        Dim lstItem As System.Windows.Forms.ListViewItem
        Dim l As Integer
        With FrmFeatureStatistics.ListViewInfo
            .Columns.Clear()
            .Items.Clear()

            .Columns.Add("Feature Name", 200)
            .Columns.Add("Num", 80)
            '.Columns.Add(Insert(1, "", "Feature Name", 20)) ' CInt(Microsoft.VisualBasic.Compatibility.VB6.TwipsToPixelsX(2000)))

            '.Columns.Insert(2, "", "Num", 8) 'CInt(Microsoft.VisualBasic.Compatibility.VB6.TwipsToPixelsX(800)))

            ' List user-defined work features info if not ignore work feature
            If FrmFeatureStatistics.checkIgnWkFeatures.CheckState = 0 Then

                lstItem = Nothing
                lstItem = .Items.Add("")
                lstItem.Text = sWkFeaturesName

                If lstItem.SubItems.Count > 1 Then
                    lstItem.SubItems(1).Text = CStr(lUserWkFeaturesNum)
                Else
                    lstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUserWkFeaturesNum)))
                End If
            End If

            ' List 2d&3d sketchs info if not ignore sketch
            If FrmFeatureStatistics.checkIgnSks.CheckState = 0 Then

                lstItem = Nothing
                lstItem = .Items.Add("")
                lstItem.Text = sSksName
                If lstItem.SubItems.Count > 1 Then
                    lstItem.SubItems(1).Text = CStr(lSksNum)
                Else
                    lstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lSksNum)))
                End If
            End If

            For l = 0 To UBound(sFeatureName)
                ' List certain part feature info according to checkIgnSuppressFeatures setting
                If FrmFeatureStatistics.checkIgnSuppressFeatures.CheckState = 0 Then
                    lstItem = Nothing
                    lstItem = .Items.Add("")
                    lstItem.Text = sFeatureName(l)
                    If lstItem.SubItems.Count > 1 Then
                        lstItem.SubItems(1).Text = CStr(lUnSuppressedFeatureCount(l) + lSuppressedFeatureCount(l))
                    Else
                        lstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUnSuppressedFeatureCount(l) + lSuppressedFeatureCount(l))))
                    End If
                ElseIf FrmFeatureStatistics.checkIgnSuppressFeatures.CheckState = 1 Then
                    If lUnSuppressedFeatureCount(l) > 0 Then
                        lstItem = Nothing
                        lstItem = .Items.Add("")
                        lstItem.Text = sFeatureName(l)
                        If lstItem.SubItems.Count > 1 Then
                            lstItem.SubItems(1).Text = CStr(lUnSuppressedFeatureCount(l))
                        Else
                            lstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUnSuppressedFeatureCount(l))))
                        End If
                    End If
                End If
            Next
        End With

    End Sub

    ' Get rebuild time info for each feature: part feature, user-defined work feature, 2d & 3d sketch and list them in their creation order
    Public Sub ListFeatureOrderRebuilTimeInfo()
        'Dim FrmFeatureStatistics As FrmFeatureStatistics
        FrmFeatureStatistics.Visible = False

        Dim oTxnMgr As Inventor.TransactionManager
        oTxnMgr = FeatureStatistics.StandardAddInServer.m_inventorApplication.TransactionManager

        ' Share all consumed but unshared 2d&3d sketches within one transaction named "Share 2d & 3d Sketches"
        Dim oShareSkTxn As Inventor.Transaction
        oShareSkTxn = oTxnMgr.StartTransaction(oPartDoc, "Share 2d & 3d Sketches")
        Dim oSk As Inventor.PlanarSketch
        Dim oSk3d As Inventor.Sketch3D
        For Each oSk In oCompDef.Sketches
            If oSk.Consumed And Not oSk.Shared Then oSk.Shared = True
        Next oSk

        For Each oSk3d In oCompDef.Sketches3D
            If oSk3d.Consumed And Not oSk3d.Shared Then oSk3d.Shared = True
        Next oSk3d
        oShareSkTxn.End()

        Dim oModelPane As Inventor.BrowserPane
        oModelPane = oPartDoc.BrowserPanes("Model")

        Dim oTopNode As Inventor.BrowserNode
        oTopNode = oModelPane.TopNode

        Dim oBrowerNodes As Inventor.BrowserNodesEnumerator
        oBrowerNodes = oTopNode.BrowserNodes

        ' Find the start and end nodes' position
        Dim oNode As Inventor.BrowserNode
        Dim lStartNodeOrder As Integer : lStartNodeOrder = 1
        Dim lEndNodeOrder As Integer : lEndNodeOrder = 0

        For Each oNode In oBrowerNodes
            lStartNodeOrder = lStartNodeOrder + 1
            If StrComp(oNode.FullPath, oTopNode.FullPath & ":Origin", CompareMethod.Text) = 0 Then Exit For
        Next oNode

        For Each oNode In oBrowerNodes
            lEndNodeOrder = lEndNodeOrder + 1
            If StrComp(oNode.FullPath, oTopNode.FullPath & ":End of Part", CompareMethod.Text) = 0 Then Exit For
        Next oNode

        Dim oCF() As Inventor.ClientFeature
        Dim l As Integer : l = 1
        ReDim dRebuildTime(lEndNodeOrder - lStartNodeOrder)
        ReDim oCF(lEndNodeOrder - lStartNodeOrder)

        ' Create ClientFeatures to contain part feature, user-defined work feature, 2d sketch or 3d sketch one by one
        ' according to their creation order, which within another new transaction named "Create Multiple CF"
        Dim oCreateCFTxn As Inventor.Transaction
        oCreateCFTxn = oTxnMgr.StartTransaction(oPartDoc, "Create Multiple CF")
        Dim oTmpCFDef As Inventor.ClientFeatureDefinition
        For l = lStartNodeOrder To lEndNodeOrder - 1
            oTmpCFDef = oCompDef.Features.ClientFeatures.CreateDefinition
            Call oTmpCFDef.ClientFeatureElements.Add(oBrowerNodes(l).NativeObject, True)
            oTmpCFDef.IsCustomSolved = True
            oCF(l - lStartNodeOrder + 1) = oCompDef.Features.ClientFeatures.Add(oTmpCFDef, "CFID" & l)
        Next
        oCreateCFTxn.End()

        Dim clsCFSolve As New clsCFSolveEvent
        clsCFSolve.Init() ' Start monitor ModelingEvents.OnClientFeatureSolve event
        oPartDoc.Rebuild() ' Rebuild part model
        clsCFSolve.Terminate() ' Terminate ModelingEvents

        Dim dSumRebuildTime As Double ' Get total rebuild time
        For l = 1 To lEndNodeOrder - lStartNodeOrder : dSumRebuildTime = dSumRebuildTime + dRebuildTime(l) : Next

        ' Write the rebuild time info for each feature into list view
        Dim lstItem As System.Windows.Forms.ListViewItem
        Dim lTmpIndex As Integer
        With FrmFeatureStatistics.ListViewInfo
            .Columns.Clear()
            .Items.Clear()

            .Columns.Add("", "Feature Order", 200)
            .Columns.Add("", "Time(s)", 80)
            .Columns.Add("", "Time %", 80)

            FrmFeatureStatistics.lblRebuildTime.Visible = True
            FrmFeatureStatistics.lblTime.Visible = True
            FrmFeatureStatistics.lblTime.Text = CStr(System.Math.Round(dSumRebuildTime, 2))

            For l = lStartNodeOrder To lEndNodeOrder - 1
                lTmpIndex = l - lStartNodeOrder + 1

                lstItem = Nothing
                lstItem = .Items.Add("")

                lstItem.Text = oBrowerNodes(l).NativeObject.Name
                If lstItem.SubItems.Count > 1 Then
                    lstItem.SubItems(1).Text = CStr(System.Math.Round(dRebuildTime(lTmpIndex), 4))
                Else
                    lstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(System.Math.Round(dRebuildTime(lTmpIndex), 2))))
                End If
                If lstItem.SubItems.Count > 2 Then
                    lstItem.SubItems(2).Text = CStr(System.Math.Round(dRebuildTime(lTmpIndex) / dSumRebuildTime * 100, 2))
                Else
                    lstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(System.Math.Round(dRebuildTime(lTmpIndex) / dSumRebuildTime * 100, 2))))
                End If
            Next
        End With
        FrmFeatureStatistics.Visible = True

        ' Recover the part model
        oTxnMgr.UndoTransaction() ' undo rebuild
        oTxnMgr.UndoTransaction() ' undo create multiple client features
        oTxnMgr.UndoTransaction() ' undo share 2d & 3d sketches

    End Sub

    ' Get features' counts and types info
    Public Sub GetMultiFeaturesInfo()

        ' Initilize to clear
        lUserWkFeaturesNum = 0
        lUserWkFeaturesTypes = 0
        lSksNum = 0
        lUnSuppressedFeatureTypes = 0
        lUnSuppressedFeaturesNum = 0

        Erase sFeatureName
        Erase lUnSuppressedFeatureCount
        Erase lSuppressedFeatureCount

        ' Get user-defined work features' count and types
        lUserWkFeaturesNum = oCompDef.WorkAxes.Count + oCompDef.WorkPlanes.Count + oCompDef.WorkPoints.Count - 7
        If oCompDef.WorkAxes.Count > 3 Then lUserWkFeaturesTypes = lUserWkFeaturesTypes + 1
        If oCompDef.WorkPlanes.Count > 3 Then lUserWkFeaturesTypes = lUserWkFeaturesTypes + 1
        If oCompDef.WorkPoints.Count > 1 Then lUserWkFeaturesTypes = lUserWkFeaturesTypes + 1

        ' Get 2d&3d sketches' count
        lSksNum = oCompDef.Sketches.Count + oCompDef.Sketches3D.Count

        ' Get part feature types name list
        sFeatureName = Split(GetFeaturesList, ";")

        ' Resize two dynamic arrys according to part feature types' count
        ReDim lUnSuppressedFeatureCount(UBound(sFeatureName))
        ReDim lSuppressedFeatureCount(UBound(sFeatureName))

        ' Get the counts of unsuppressed and suppressed part feature respectively
        ' e.g lSuppressedFeatureCount(N) indicates the count of suppressed ExtrudeFeature(s) while
        ' lUnSuppressedFeatureCount(N) indicates the count of unsuppressed ExtrudeFeature(s)
        Dim oFeature As Inventor.PartFeature
        Dim l As Integer
        For Each oFeature In oCompDef.Features
            If Not oFeature.Suppressed Then lUnSuppressedFeaturesNum = lUnSuppressedFeaturesNum + 1
        Next oFeature

        For l = 0 To UBound(sFeatureName)
            For Each oFeature In oCompDef.Features
                If StrComp(sFeatureName(l), GetNameOfFeature(oFeature), CompareMethod.Text) = 0 Then
                    If oFeature.Suppressed Then
                        lSuppressedFeatureCount(l) = lSuppressedFeatureCount(l) + 1
                    Else : lUnSuppressedFeatureCount(l) = lUnSuppressedFeatureCount(l) + 1
                    End If
                End If
            Next oFeature
        Next

        lUnSuppressedFeatureTypes = UBound(sFeatureName) + 1
        For l = 0 To UBound(sFeatureName)
            If lUnSuppressedFeatureCount(l) = 0 Then lUnSuppressedFeatureTypes = lUnSuppressedFeatureTypes - 1
        Next

    End Sub

    ' Assign values to lblFeatureNumsCount and lblFeatureTypesCount according to current checkIgnSuppressFeatures and checkIgnWkFeatures settings
    ' lblFeatureNumsCount = PartFeatures' Count + User-defined WorkFeatures' Count(if not Ignore WorkFeatures) - Suppressed PartFeatures' Count(if not Ignore Suppressed Features)
    ' lblFeatureTypesCount = PartFeatures' Type + User-defined WorkFeatures' Type(if not Ignore WorkFeatures) - Suppressed PartFeatures' Type(if not Ignore Suppressed Features)
    Public Sub SetCurrentFeaturesCountTypesInfo()
        'Dim FrmFeatureStatistics As FrmFeatureStatistics
        With FrmFeatureStatistics
            If .checkIgnSuppressFeatures.CheckState = 0 Then
                .lblFeatureNumsCount.Text = CStr(oCompDef.Features.Count)
                .lblFeatureTypesCount.Text = CStr(UBound(sFeatureName) + 1)
            ElseIf .checkIgnSuppressFeatures.CheckState = 1 Then
                .lblFeatureNumsCount.Text = CStr(lUnSuppressedFeaturesNum)
                .lblFeatureTypesCount.Text = CStr(lUnSuppressedFeatureTypes)
            End If

            If .checkIgnWkFeatures.CheckState = 0 Then
                .lblFeatureNumsCount.Text = CStr(CDbl(.lblFeatureNumsCount.Text) + lUserWkFeaturesNum)
                .lblFeatureTypesCount.Text = CStr(CDbl(.lblFeatureTypesCount.Text) + lUserWkFeaturesTypes)
            End If
        End With
    End Sub

    ' Retuns the name list contains all part feature types in the model
    Private Function GetFeaturesList() As String
        GetFeaturesList = ""
        Dim oFeature As Inventor.PartFeature
        Dim sName As String

        For Each oFeature In oCompDef.Features
            sName = GetNameOfFeature(oFeature)
            If InStr(1, GetFeaturesList, sName, CompareMethod.Text) = 0 Then
                If GetFeaturesList = "" Then
                    GetFeaturesList = sName
                Else : GetFeaturesList = GetFeaturesList & ";" & sName
                End If
            End If
        Next oFeature
    End Function

    ' Returns the name of the part feature type
    Private Function GetNameOfFeature(ByRef oFeature As Object) As String
        Dim sName As String
        sName = TypeName(oFeature)

        If Left(sName, 3) = "IRx" Then sName = Mid(sName, 4)
        GetNameOfFeature = sName
    End Function
End Module