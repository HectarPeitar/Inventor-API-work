Imports Inventor
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

Namespace FeatureStatistics
    <ProgIdAttribute("FeatureStatistics.StandardAddInServer"), _
    GuidAttribute("59a37f44-fccf-4769-9f87-ff14583fc492")> _
    Public Class StandardAddInServer
        Implements Inventor.ApplicationAddInServer

        ' Inventor application object.
        Public Shared m_inventorApplication As Inventor.Application
        Private WithEvents oButtonDefFeatureStatistics As Inventor.ButtonDefinition
        Private WithEvents oUserInterfaceEvents As Inventor.UserInterfaceEvents
#Region "ApplicationAddInServer Members"

        Public Sub Activate(ByVal addInSiteObject As Inventor.ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

            ' This method is called by Inventor when it loads the AddIn.
            ' The AddInSiteObject provides access to the Inventor Application object.
            ' The FirstTime flag indicates if the AddIn is loaded for the first time.

            ' Initialize AddIn members.
            m_inventorApplication = addInSiteObject.Application
            blnAddInLoadedFirstTime = firstTime

            Dim oUIMgr As Inventor.UserInterfaceManager
            oUIMgr = m_inventorApplication.UserInterfaceManager
            oUserInterfaceEvents = oUIMgr.UserInterfaceEvents

            Dim oCmdMgr As Inventor.CommandManager
            oCmdMgr = m_inventorApplication.CommandManager




            oButtonDefFeatureStatistics = oCmdMgr.ControlDefinitions.AddButtonDefinition("Feature Statistics", "AppFeatureStatisticsWrapperCmd", Inventor.CommandTypesEnum.kQueryOnlyCmdType)
            oButtonDefFeatureStatistics.Enabled = True

            Dim oCmdCategory As Inventor.CommandCategory
            oCmdCategory = oCmdMgr.CommandCategories.Add("Feature Statistics", "AppFeatureStatisticsWrapperCmd")
            Call oCmdCategory.Add(oButtonDefFeatureStatistics)

            Dim oCmdBar As Inventor.CommandBar
            If firstTime Then
                Call DeleteCmdBar("AppFeatureStatisticsToolbarName")

                On Error Resume Next
                Err.Clear()

                oCmdBar = oUIMgr.CommandBars.Item("AppFeatureStatisticsToolbarName")

                If Not oCmdBar Is Nothing Then
                    Dim oControl As CommandControl
                    For Each oControl In oCmdBar.Controls
                        oControl.Delete()
                    Next


                Else
                    oCmdBar = oUIMgr.CommandBars.Add("FeatureStatistics", "AppFeatureStatisticsToolbarName")



                End If


                Call oCmdBar.Controls.AddButton(oButtonDefFeatureStatistics)
                oCmdBar.Visible = True
            End If

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
        Private Sub ApplicationAddInServer_Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

            'the deactivate method is called by Inventor when the addin is unloaded
            'the addin will be unloaded either manually by the user or
            'when the Inventor session is terminated

            'release references to objects
            lUserWkFeaturesNum = 0
            lUserWkFeaturesTypes = 0
            lSksNum = 0
            lUnSuppressedFeatureTypes = 0
            lUnSuppressedFeaturesNum = 0

            Erase dRebuildTime
            Erase sFeatureName
            Erase lUnSuppressedFeatureCount
            Erase lSuppressedFeatureCount

            oCompDef = Nothing
            oPartDoc = Nothing
            m_inventorApplication = Nothing

            oButtonDefFeatureStatistics.Delete()
            oButtonDefFeatureStatistics = Nothing
            oUserInterfaceEvents = Nothing
        End Sub

        Private Sub oButtonDefFeatureStatistics_OnExecute(ByVal Context As Inventor.NameValueMap) Handles oButtonDefFeatureStatistics.OnExecute
            ListFeatureNameNumInfo()
        End Sub

        Private Sub oUserInterfaceEvents_OnResetCommandBars(ByVal CommandBars As Inventor.ObjectsEnumerator, ByVal Context As Inventor.NameValueMap) Handles oUserInterfaceEvents.OnResetCommandBars
            Dim oCommandBar As Inventor.CommandBar
            For Each oCommandBar In CommandBars
                If oCommandBar.InternalName = "AppFeatureStatisticsToolbarIntName" Then
                    Call oCommandBar.Controls.AddButton(oButtonDefFeatureStatistics)
                    Exit For
                End If
            Next oCommandBar
        End Sub
#End Region

    End Class

End Namespace

