Option Strict Off
Option Explicit On
<System.Runtime.InteropServices.ProgId("CustomEnv.ApplicationEvts")> Public Class clsApplicationEvts

    Private mobjInventorApp As Inventor.Application

    Private WithEvents mobjApplicationEvents As Inventor.ApplicationEvents
    Private mobjCustomBrowserPane As clsCustomBrowserPane

    Public Sub New(ByVal objInventorApp As Inventor.Application, ByVal strClientID As String)

        MyBase.New()

        On Error Resume Next

        mobjInventorApp = objInventorApp

        'initialize application events
        mobjApplicationEvents = mobjInventorApp.ApplicationEvents

        'initialize custom browser pane
        mobjCustomBrowserPane = New clsCustomBrowserPane(objInventorApp, strClientID)

    End Sub

    Protected Overrides Sub Finalize()

        'set the application events to Nothing
        mobjApplicationEvents = Nothing

        'set the custom browser pane to Nothing
        mobjCustomBrowserPane = Nothing

        MyBase.Finalize()
    End Sub

    Private Sub mobjApplicationEvents_OnActivateDocument(ByVal DocumentObject As Inventor.Document, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum)

        If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
            If DocumentObject.DocumentType = Inventor.DocumentTypeEnum.kPartDocumentObject Then
                Call mobjCustomBrowserPane.CreateBrepTree(DocumentObject)
            End If
        End If

    End Sub
End Class