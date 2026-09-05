Public Class AddInRegistration

    '*************************************************************************************************************
    'Information used for registration:
    '
    '   1) From AssemblyInfo.vb:
    '           AssemblyTitle       - The display name for the AddIn
    '           AssemblyDescription - The description for the AddIn
    '
    '   2) Fields listed below (Public Const data members)
    '       The un-commented fields will be added to the registry as part of the settings for the AddIn.
    '       The field names (e.g. LoadOnStartUp) will be used for the registry entry's name.
    '       The field values will be the registry entry's value.
    '       The fields that are not to be added to the registry should be commented.
    '
    '       Rules:
    '           Each field must be public and constant or it will be ignored.
    '           Valid types are int, bool, string any other type will be converted to a string using ToString();
    '*************************************************************************************************************

    Public Const LoadOnStartUp As Boolean = True
    Public Const Type As Inventor.ApplicationAddInTypeEnum = Inventor.ApplicationAddInTypeEnum.kStandardApplicationAddIn
    Public Const Version As Integer = 0
    Public Const SupportedSoftwareVersionGreaterThan As String = "14.."
    'Public Const SupportedSoftwareVersionLessThan As String = ""
    'Public Const SupportedSoftwareVersionEqualTo As String = ""
    'Public Const SupportedSoftwareVersionNotEqualTo As String = ""
    'Public Const Hidden As Boolean = False
    'Public Const UserUnloadable As Boolean = True

#Region "AddInRegistration functions (this section need not be edited)"

    '***************************************************************************
    ' The following functions should not be modified.
    ' They are used for registering your add-in for use with Autodesk Inventor.
    '****************************************************************************

    Public Shared Sub RegisterInventorAddIn(ByVal t As Type)

        Dim clsid As Microsoft.Win32.RegistryKey = Nothing
        Dim subKey As Microsoft.Win32.RegistryKey = Nothing

        Try
            'get the RegInfo helper structure (defined below)
            Dim ri As RegInfo = New RegInfo(t)

            'create the subkey corresponding to the Addin's CLSID
            clsid = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("Software\Classes\CLSID\" + ri.AddInGuid)

            'set the DisplayName of the AddIn to the AssemblyTitle attribute
            clsid.SetValue(Nothing, ri.DisplayName)

            'create the subkey corresponding to the "Implemented Categories"
            'this subkey is what determines that this is an Inventor AddIn
            subKey = clsid.CreateSubKey("Implemented Categories\{39AD2B5C-7A29-11D6-8E0A-0010B541CAA8}")
            subKey.Close()

            'create the subkey corresponding to the "Settings"
            subKey = clsid.CreateSubKey("Settings")

            'get the fields of this class, the fields contain the Addin Settings
            Dim fields() As System.Reflection.FieldInfo = GetType(AddInRegistration).GetFields

            'add all the fields under the "Settings" subkey
            Dim field As System.Reflection.FieldInfo
            For Each field In fields
                If field.IsLiteral Then
                    Dim val As Object = field.GetValue(Nothing)
                    If TypeOf val Is Boolean Then ' Boolean will be converted to a string containing 1 or 0
                        subKey.SetValue(field.Name, IIf(CBool(val), "1", "0"))
                    ElseIf TypeOf val Is Integer Then ' Integer should stay as Integer and will be added to registry as DWORD
                        subKey.SetValue(field.Name, val)
                    ElseIf TypeOf val Is Inventor.ApplicationAddInTypeEnum Then ' Convert to a valid string
                        subKey.SetValue(field.Name, val.ToString().Substring(1).Replace("ApplicationAddIn", ""))
                    ElseIf Not val Is Nothing Then ' As long as val isn't empty,
                        If val.ToString() <> String.Empty Then ' any other type (String or other) will be 
                            subKey.SetValue(field.Name, val.ToString()) ' converted to String.
                        End If
                    End If
                End If
            Next
            subKey.Close()

            'create the subkey corresponding to the "Description"
            subKey = clsid.CreateSubKey("Description")

            'set the DisplayName of the AddIn to the AssemblyDescription attribute
            subKey.SetValue(Nothing, ri.Description)

        Catch

        Finally

            If Not subKey Is Nothing Then subKey.Close()
            If Not clsid Is Nothing Then clsid.Close()

        End Try

    End Sub

    Public Shared Sub UnregisterInventorAddIn(ByVal t As Type)

        Dim clsid As Microsoft.Win32.RegistryKey = Nothing

        Try

            'get the RegInfo helper structure (defined below)
            Dim ri As RegInfo = New RegInfo(t)

            'get the subkey corresponding to the Addin's CLSID
            clsid = Microsoft.Win32.Registry.CurrentUser.OpenSubKey("Software\Classes\CLSID\" + ri.AddInGuid, True)

            If clsid Is Nothing Then
                Exit Sub
            End If

            'delete the subkey corresponding to the "Implemented Categories"
            Try
                clsid.DeleteSubKeyTree("Implemented Categories\{39AD2B5C-7A29-11D6-8E0A-0010B541CAA8}")
            Catch ex As ArgumentException
            End Try

            'delete the subkey corresponding to the "Settings"
            Try
                clsid.DeleteSubKeyTree("Settings")
            Catch ex As ArgumentException
            End Try

            'delete the subkey corresponding to the "Description"
            Try
                clsid.DeleteSubKeyTree("Description")
            Catch ex As ArgumentException
            End Try

        Catch

        Finally

            If Not clsid Is Nothing Then clsid.Close()

        End Try

    End Sub

#Region "Registration helper"
    Private NotInheritable Class RegInfo
        Public ReadOnly AddInGuid As String
        Public ReadOnly DisplayName As String
        Public ReadOnly Description As String

        Public Sub New(ByVal t As Type)
            'get the Guid associated with the class
            AddInGuid = t.GUID.ToString("B")

            'get the assembly attributes
            Dim atts() As Object = t.Assembly.GetCustomAttributes(False)

            'find the Title and Description if they exist
            'these attributes are specified in the AssemblyInfo.cs file.
            DisplayName = String.Empty
            Description = String.Empty
            Dim att As Object
            For Each att In atts
                If TypeOf att Is System.Reflection.AssemblyTitleAttribute Then
                    Dim title As System.Reflection.AssemblyTitleAttribute = att
                    DisplayName = title.Title
                ElseIf TypeOf att Is System.Reflection.AssemblyDescriptionAttribute Then
                    Dim desc As System.Reflection.AssemblyDescriptionAttribute = att
                    Description = desc.Description
                End If
            Next
        End Sub
    End Class
#End Region

#End Region

End Class
