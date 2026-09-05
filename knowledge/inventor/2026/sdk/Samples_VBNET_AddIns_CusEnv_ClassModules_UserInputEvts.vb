Option Strict Off
Option Explicit On
<System.Runtime.InteropServices.ProgId("CustomEnv.UserInputEvts")> Public Class clsUserInputEvts

    Private mobjInventorApp As Inventor.Application

    Private WithEvents mobjUserInputEvents As Inventor.UserInputEvents

    Private Structure udtEnvCommand
        Dim EnvInternalName As String
        Dim CmdInternalNames() As String
    End Structure

    Private mudtEnvCommands() As udtEnvCommand

    Private Sub Class_Init()

       
    End Sub
    Public Sub New(ByVal objInventorApp As Inventor.Application)
        MyBase.New()

        mobjInventorApp = objInventorApp

        'get the command manager
        Dim objCommandMgr As Inventor.CommandManager
        objCommandMgr = mobjInventorApp.CommandManager

        'initialize user interface events
        mobjUserInputEvents = objCommandMgr.UserInputEvents

    End Sub

    Public Sub AddCmdToEnvContextMenu(ByRef objControlDefinition As Inventor.ControlDefinition, ByRef strEnvInternalName As String)

        On Error Resume Next

        Dim lngmudtEnvCommandSize As Integer
        lngmudtEnvCommandSize = UBound(mudtEnvCommands)

        Dim lngEnvCt As Integer
        Dim blnCommandExists As Boolean
        Dim lngCommandCt As Integer
        If Err.Number Or lngmudtEnvCommandSize = 0 Then

            ReDim mudtEnvCommands(1)
            mudtEnvCommands(1).EnvInternalName = strEnvInternalName

            ReDim mudtEnvCommands(1).CmdInternalNames(1)
            mudtEnvCommands(1).CmdInternalNames(1) = objControlDefinition.InternalName

        Else

            For lngEnvCt = LBound(mudtEnvCommands) To UBound(mudtEnvCommands)
                If mudtEnvCommands(lngEnvCt).EnvInternalName = strEnvInternalName Then

                    For lngCommandCt = LBound(mudtEnvCommands(lngEnvCt).CmdInternalNames) To UBound(mudtEnvCommands(lngEnvCt).CmdInternalNames)
                        If mudtEnvCommands(lngEnvCt).CmdInternalNames(lngCommandCt) = objControlDefinition.InternalName Then
                            blnCommandExists = True
                            Exit For
                        End If
                    Next

                    If blnCommandExists = False Then
                        ReDim Preserve mudtEnvCommands(lngEnvCt).CmdInternalNames(UBound(mudtEnvCommands(lngEnvCt).CmdInternalNames) + 1)
                        mudtEnvCommands(lngEnvCt).CmdInternalNames(UBound(mudtEnvCommands(lngEnvCt).CmdInternalNames)) = objControlDefinition.InternalName
                    End If

                End If
            Next
        End If

    End Sub

    Private Sub mobjUserInputEvents_OnContextMenu(ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal AdditionalInfo As Inventor.NameValueMap, ByVal CommandBar As Inventor.CommandBar) Handles mobjUserInputEvents.OnContextMenu

        Dim objActiveEnv As Inventor.Environment
        Dim lngEnvCt As Integer
        Dim lngCommandCt As Integer
        Dim objControlDefinition As Inventor.ControlDefinition
        If SelectionDevice = Inventor.SelectionDeviceEnum.kGraphicsWindowSelection Then

            'get the active environment
            objActiveEnv = mobjInventorApp.ActiveEnvironment

            'go through the list of environments to check if the active environment,
            'is there in it
            For lngEnvCt = LBound(mudtEnvCommands) To UBound(mudtEnvCommands)
                If mudtEnvCommands(lngEnvCt).EnvInternalName = objActiveEnv.InternalName Then

                    'get all the commands for the active environment and,
                    'add them to the context menu list
                    For lngCommandCt = LBound(mudtEnvCommands(lngEnvCt).CmdInternalNames) To UBound(mudtEnvCommands(lngEnvCt).CmdInternalNames)

                        objControlDefinition = mobjInventorApp.CommandManager.ControlDefinitions(mudtEnvCommands(lngEnvCt).CmdInternalNames(lngCommandCt))

                        Call CommandBar.Controls.AddButton(objControlDefinition)
                    Next

                End If
            Next

        End If

    End Sub

    Protected Overrides Sub Finalize()

        'set the user input events to Nothing
        mobjUserInputEvents = Nothing

        MyBase.Finalize()
    End Sub
End Class