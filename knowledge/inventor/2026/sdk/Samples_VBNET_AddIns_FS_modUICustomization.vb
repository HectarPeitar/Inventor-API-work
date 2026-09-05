Option Strict Off
Option Explicit On

Imports FeatureStatistics
Module modUICustomization

	Public Function CreateButton(ByRef strBtnDisplayName As String, ByRef strBtnInternalName As String, ByRef eBtnType As Inventor.CommandTypesEnum, ByRef blnAutoAddToGUI As Boolean, Optional ByRef strBtnClientId As String = "", Optional ByRef strBtnDescription As String = "", Optional ByRef strBtnToolTipText As String = "", Optional ByRef strBtnStdIcon As String = "", Optional ByRef strBtnLrgIcon As String = "", Optional ByRef eBtnDisplayEnum As Inventor.ButtonDisplayEnum = Inventor.ButtonDisplayEnum.kDisplayTextInLearningMode) As Inventor.ButtonDefinition
		On Error Resume Next
		
		Dim objBtnStdIcon As Object
		If strBtnStdIcon <> "" Then
			objBtnStdIcon = System.Drawing.Image.FromFile(strBtnStdIcon)
		End If
		
		Dim objBtnLrgIcon As Object
		If strBtnLrgIcon <> "" Then
			objBtnLrgIcon = System.Drawing.Image.FromFile(strBtnLrgIcon)
		End If
		
        CreateButton = FeatureStatistics.StandardAddInServer.m_inventorApplication.CommandManager.ControlDefinitions.AddButtonDefinition(strBtnDisplayName, strBtnInternalName, eBtnType, strBtnClientId, strBtnDescription, strBtnToolTipText, objBtnStdIcon, objBtnLrgIcon, eBtnDisplayEnum)

        If blnAutoAddToGUI Then
            CreateButton.AutoAddToGUI()
        End If

        If Err.Number Or CreateButton Is Nothing Then
            MsgBox("Failed to create Button:" & strBtnDisplayName)
        End If

    End Function

    Public Function CreateComboBox(ByRef strCboDisplayName As String, ByRef strCboInternalName As String, ByRef eCboType As Inventor.CommandTypesEnum, ByRef lngCboDropDownWidth As Integer, ByRef blnAutoAddToGUI As Boolean, Optional ByRef strCboClientId As String = "", Optional ByRef strCboDescription As String = "", Optional ByRef strCboToolTipText As String = "", Optional ByRef strCboStdIcon As String = "", Optional ByRef strCboLrgIcon As String = "", Optional ByRef eCboDisplayEnum As Inventor.ButtonDisplayEnum = Inventor.ButtonDisplayEnum.kDisplayTextInLearningMode) As Inventor.ComboBoxDefinition
        On Error Resume Next

        Dim objCboStdIcon As Object
        If strCboStdIcon <> "" Then
            objCboStdIcon = System.Drawing.Image.FromFile(strCboStdIcon)
        End If

        Dim objCboLrgIcon As Object
        If strCboLrgIcon <> "" Then
            objCboLrgIcon = System.Drawing.Image.FromFile(strCboLrgIcon)
        End If

        CreateComboBox = FeatureStatistics.StandardAddInServer.m_inventorApplication.CommandManager.ControlDefinitions.AddComboBoxDefinition(strCboDisplayName, strCboInternalName, eCboType, lngCboDropDownWidth, strCboClientId, strCboDescription, strCboToolTipText, objCboStdIcon, objCboLrgIcon, eCboDisplayEnum)

        If blnAutoAddToGUI Then
            CreateComboBox.AutoAddToGUI()
        End If

        If Err.Number Or CreateComboBox Is Nothing Then
            MsgBox("Failed to create ComboBox:" & strCboDisplayName)
        End If
    End Function

    Public Function CreateMacro(ByRef strMacroName As String, ByRef blnAutoAddToGUI As Boolean) As Inventor.MacroControlDefinition
        On Error Resume Next

        CreateMacro = FeatureStatistics.StandardAddInServer.m_inventorApplication.CommandManager.ControlDefinitions.AddMacroControlDefinition(strMacroName)

        If blnAutoAddToGUI Then
            CreateMacro.AutoAddToGUI()
        End If

        If Err.Number Or CreateMacro Is Nothing Then
            MsgBox("Failed to create Macro:" & strMacroName)
        End If
    End Function

    Public Function CreateAddInCmdBar(ByRef strCmdBarDisplayName As String, ByRef strCmdBarInternalName As String, Optional ByRef eCmdBarType As Inventor.CommandBarTypeEnum = Inventor.CommandBarTypeEnum.kRegularCommandBar, Optional ByRef strCmdBarClientId As String = "") As Inventor.CommandBar
        On Error Resume Next

        If blnAddInLoadedFirstTime Then
            CreateAddInCmdBar = FeatureStatistics.StandardAddInServer.m_inventorApplication.UserInterfaceManager.CommandBars.Add(strCmdBarDisplayName, strCmdBarInternalName, eCmdBarType, strCmdBarClientId)

            If Err.Number Or CreateAddInCmdBar Is Nothing Then
                MsgBox("Failed to create AddIn Command bar")
            End If
        End If

    End Function

    Public Function AddCmdButtonToAddInCmdBar_UsingObjects(ByRef objBtnDef As Inventor.ButtonDefinition, ByRef objCmdBar As Inventor.CommandBar) As Object
        On Error Resume Next

        If blnAddInLoadedFirstTime Then
            Call objCmdBar.Controls.AddButton(objBtnDef)
        End If
    End Function

    Public Function AddCmdComboBoxToAddInCmdBar_UsingObjects(ByRef objCboDef As Inventor.ComboBoxDefinition, ByRef objCmdBar As Inventor.CommandBar) As Object
        On Error Resume Next

        If blnAddInLoadedFirstTime Then
            Call objCmdBar.Controls.AddComboBox(objCboDef)
        End If
    End Function

    Public Function AddCmdMacroToAddInCmdBar_UsingObjects(ByRef objMacroDef As Inventor.MacroControlDefinition, ByRef objCmdBar As Inventor.CommandBar) As Object
        On Error Resume Next

        If blnAddInLoadedFirstTime Then
            Call objCmdBar.Controls.AddMacro(objMacroDef)
        End If
    End Function

    Public Function AddCmdButtonToAddInCmdBar_UsingNames(ByRef strBtnIntName As String, ByRef strCmdBarInternalName As String) As Object
        On Error Resume Next

        Dim objBtnDef As Inventor.ButtonDefinition
        Dim objCmdBar As Inventor.CommandBar
        If blnAddInLoadedFirstTime Then
            objBtnDef = FeatureStatistics.StandardAddInServer.m_inventorApplication.CommandManager.ControlDefinitions(strBtnIntName)

            objCmdBar = FeatureStatistics.StandardAddInServer.m_inventorApplication.UserInterfaceManager.CommandBars(strCmdBarInternalName)

            Call objCmdBar.Controls.AddButton(objBtnDef)
        End If

    End Function

    Public Function AddCmdComboBoxToAddInCmdBar_UsingNames(ByRef strCboIntName As String, ByRef strCmdBarInternalName As String) As Object
        On Error Resume Next

        Dim objCboDef As Inventor.ComboBoxDefinition
        Dim objCmdBar As Inventor.CommandBar
        If blnAddInLoadedFirstTime Then
            objCboDef = FeatureStatistics.StandardAddInServer.m_inventorApplication.CommandManager.ControlDefinitions(strCboIntName)

            objCmdBar = FeatureStatistics.StandardAddInServer.m_inventorApplication.UserInterfaceManager.CommandBars(strCmdBarInternalName)

            Call objCmdBar.Controls.AddComboBox(objCboDef)
        End If
    End Function

    Public Function AddCmdMacroToAddInCmdBar_UsingNames(ByRef strMacroIntName As String, ByRef strCmdBarInternalName As String) As Object
        On Error Resume Next

        Dim objMacroDef As Inventor.MacroControlDefinition
        Dim objCmdBar As Inventor.CommandBar
        If blnAddInLoadedFirstTime Then
            objMacroDef = FeatureStatistics.StandardAddInServer.m_inventorApplication.CommandManager.ControlDefinitions(strMacroIntName)

            objCmdBar = FeatureStatistics.StandardAddInServer.m_inventorApplication.UserInterfaceManager.CommandBars(strCmdBarInternalName)

            Call objCmdBar.Controls.AddMacro(objMacroDef)
        End If
    End Function

    Public Function DeleteButton(ByRef objBtnDef As Inventor.ButtonDefinition) As Object
        On Error Resume Next

        Call objBtnDef.Delete()
        objBtnDef = Nothing

    End Function

    Public Function DeleteComboBox(ByRef objCboDef As Inventor.ComboBoxDefinition) As Object
        On Error Resume Next

        Call objCboDef.Delete()
        objCboDef = Nothing

    End Function

    Public Function DeleteMacro(ByRef objMacroDef As Inventor.MacroControlDefinition) As Object
        On Error Resume Next

        Call objMacroDef.Delete()
        objMacroDef = Nothing

    End Function

    Public Function DeleteCmdBar(ByRef strAddInCmdBarInternalName As String) As Object
        On Error Resume Next

        Call FeatureStatistics.StandardAddInServer.m_inventorApplication.UserInterfaceManager.CommandBars(strAddInCmdBarInternalName).Delete()

    End Function
End Module