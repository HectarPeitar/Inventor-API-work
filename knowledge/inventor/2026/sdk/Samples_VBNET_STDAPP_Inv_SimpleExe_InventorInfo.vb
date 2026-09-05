Imports Inventor
Imports System.Runtime.InteropServices
Imports System.Windows.Forms

Public Class InventorInfo

    Private Sub InventorInfo_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        Dim m_inventorApp As Inventor.Application = Nothing
        Dim m_quitInventor As Boolean = False

        Try
            ' Try to get an active instance of Inventor
            Try
                m_inventorApp = Win32.GetActiveObject("Inventor.Application")
            Catch ex As Exception
            End Try

            ' If not active, create a new Inventor session
            If m_inventorApp Is Nothing Then

                Dim inventorAppType As Type = System.Type.GetTypeFromProgID("Inventor.Application")
                m_inventorApp = System.Activator.CreateInstance(inventorAppType)

                m_quitInventor = True

            End If

            ' Get some basic property information
            Dim lstViewItem As ListViewItem
            lstViewItem = lstViewInvInfo.Items.Add("Caption")
            lstViewItem.SubItems.Add(m_inventorApp.Caption)

            lstViewItem = lstViewInvInfo.Items.Add("Sofware Version")
            lstViewItem.SubItems.Add(m_inventorApp.SoftwareVersion.DisplayName)

            lstViewItem = lstViewInvInfo.Items.Add("Install Path")
            lstViewItem.SubItems.Add(m_inventorApp.InstallPath)

            lstViewItem = lstViewInvInfo.Items.Add("Language")
            lstViewItem.SubItems.Add(m_inventorApp.LanguageName)

            lstViewItem = lstViewInvInfo.Items.Add("User Name")
            lstViewItem.SubItems.Add(m_inventorApp.UserName)

            lstViewItem = lstViewInvInfo.Items.Add("Active Color Scheme")
            lstViewItem.SubItems.Add(m_inventorApp.ActiveColorScheme.Name)

            lstViewItem = lstViewInvInfo.Items.Add("Active Project File")
            lstViewItem.SubItems.Add(m_inventorApp.FileLocations.FileLocationsFile)

            ' Get the general options
            lstViewItem = lstViewInvInfo.Items.Add("Startup Project File")
            lstViewItem.SubItems.Add(m_inventorApp.GeneralOptions.StartupProjectFileName)

            lstViewItem = lstViewInvInfo.Items.Add("Startup Action")
            Dim startupAction As String = ""
            Select Case m_inventorApp.GeneralOptions.StartupActionType
                Case StartupActionTypeEnum.kFileNewDialogStartupAction
                    startupAction = "File New Dialog"
                Case StartupActionTypeEnum.kFileOpenDialogStartupAction
                    startupAction = "File Open Dialog"
                Case StartupActionTypeEnum.kNewFileFromTemplateStartupAction
                    startupAction = "New File From Template"
                Case StartupActionTypeEnum.kNoStartupAction
                    startupAction = "Nothing"
            End Select
            lstViewItem.SubItems.Add(startupAction)

            ' Get the general preferences
            Dim preferences As ObjectsEnumeratorByVariant
            preferences = m_inventorApp.Preferences

            Dim userPrefObj As Object
            For Each userPrefObj In preferences

                If TypeOf userPrefObj Is GeneralPreferences Then
                    Dim generalPreferences As GeneralPreferences
                    generalPreferences = userPrefObj

                    lstViewItem = lstViewInvInfo.Items.Add("User Mode")
                    Dim multiUserMode As String = ""
                    Select Case generalPreferences.MultiUserMode
                        Case MultiUserModeEnum.kSemiIsolatedMode
                            multiUserMode = "Semi Isolated"
                        Case MultiUserModeEnum.kSemiIsolatedNoCheckoutMode
                            multiUserMode = "Semi Isolated NoCheckout"
                        Case MultiUserModeEnum.kSharedMode
                            multiUserMode = "Shared"
                        Case MultiUserModeEnum.kSingleUserMode
                            multiUserMode = "Single User"
                        Case MultiUserModeEnum.kVaultMode
                            multiUserMode = "Vault"
                    End Select

                    lstViewItem.SubItems.Add(multiUserMode)

                    lstViewItem = lstViewInvInfo.Items.Add("Templates Directory")
                    lstViewItem.SubItems.Add(generalPreferences.TemplateDir)
                End If
            Next

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show("There was a problem getting some Inventor information", "Error", MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error)
        Finally
            If Not m_inventorApp Is Nothing AndAlso m_quitInventor = True Then
                m_inventorApp.Quit()
            End If

            m_inventorApp = Nothing
        End Try

    End Sub

    Private Sub btnClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClose.Click
        Me.Close()
    End Sub

End Class

Public Class Win32
	<DllImport("ole32")>
	Private Shared Function CLSIDFromProgIDEx(
		<MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
	End Function
	<DllImport("ole32")>
	Private Shared Function CLSIDFromProgID(
		<MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
	End Function
	<DllImport("oleaut32")>
	Private Shared Function GetActiveObject(
		<MarshalAs(UnmanagedType.LPStruct)> ByVal rclsid As Guid, ByVal pvReserved As IntPtr, <Out>
		<MarshalAs(UnmanagedType.IUnknown)> ByRef ppunk As Object) As Integer
	End Function

	Public Shared Function GetActiveObject(ByVal progID As String) As Object
		Dim obj As Object = Nothing
		Dim clsid As Guid

		' Call CLSIDFromProgIDEx first then fall back on CLSIDFromProgID if
		' CLSIDFromProgIDEx doesn't exist.
		Try
			CLSIDFromProgIDEx(progID, clsid)
		Catch ex As Exception
			CLSIDFromProgID(progID, clsid)
		End Try

		Dim hr = GetActiveObject(clsid, IntPtr.Zero, obj)
		If hr < 0 Then
			Err.Raise(0)
		End If
		Return obj
	End Function
End Class
