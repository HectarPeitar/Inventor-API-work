Option Strict Off
Option Explicit On
Imports VB = Microsoft.VisualBasic
<System.Runtime.InteropServices.ProgId("clsCFSolveEvent_NET.clsCFSolveEvent")> Public Class clsCFSolveEvent
	' This class module monitors OnClientFeatureSolve event
	' PartDocument.Rebuild will fire the event when document contains Custom Solved ClientFeature(s)
	Private WithEvents oModelingEvents As Inventor.ModelingEvents
	Private lCounter As Integer
	Private beforeTimer, afterTimer As Single

    Private m_inventorApplication As Inventor.Application

    Public Property InventorApplication() As Inventor.Application
        Get
            InventorApplication = m_inventorApplication
        End Get

        Set(ByVal Value As Inventor.Application)
            m_inventorApplication = Value
        End Set
    End Property
    Public Sub Init()
        m_inventorApplication = FeatureStatistics.StandardAddInServer.m_inventorApplication
        oModelingEvents = m_inventorApplication.ModelingEvents
        lCounter = 0 : beforeTimer = 0 : afterTimer = 0
    End Sub
	
	Public Sub Terminate()
        oModelingEvents = Nothing
		lCounter = 0 : beforeTimer = 0 : afterTimer = 0
	End Sub
	
	Private Sub oModelingEvents_OnClientFeatureSolve(ByVal DocumentObject As Inventor.Document, ByVal Feature As Inventor.ClientFeature, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum)
		
		If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
			beforeTimer = VB.Timer() ' Record the time at the point of starting solve one CF
			HandlingCode = Inventor.HandlingCodeEnum.kEventHandled
		ElseIf BeforeOrAfter = Inventor.EventTimingEnum.kAfter Then 
			afterTimer = VB.Timer() ' Record the time at the point of finishing solve one CF
			lCounter = lCounter + 1
			dRebuildTime(lCounter) = afterTimer - beforeTimer ' The rebuild time for this CF = Finish Time - Start Time
		ElseIf BeforeOrAfter = Inventor.EventTimingEnum.kAbort Then 
			MsgBox("Error: OnClientFeatureSolve fire kAbort")
		End If
	End Sub
End Class