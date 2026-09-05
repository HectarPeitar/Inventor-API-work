MFCBrowserPanes
==============

DESCRIPTION

This sample shows inserting of an ActiveX control in Browser Control Bar in Inventor using MFC. This is identical to
the VBBrowserPanes sample that is located in Sample\Visual Basic directory. It shows how to trap events using MFC.


Following are the steps needed to run this sample:
'
' 1. This sample uses an ActiveX control shipped with the SDK. It needs to be registered before the
'    Sample can be run. Register the control by typing the following in a Console window:
'                cd Samples\VC++.NET\Standalone Applications\Inventor\BrowserPane\SimleMFCControl\Optimize
'                Regsvr32 SimpleMFCControl.ocx
'                (While in x64 machine you need to register the SimpleMFControl.ocx using the VS Command Prompt window)
'		
' 2. Start Inventor, and create a document.
' 3. Start this executable(MFCBrowserPanes.exe)
' 4. In the dialog, click on Connect to connect to an existing session of Inventor.
'    Note that Inventor must be running with a document open in order to run this sample.
' 5. Once sample is connected to Inventor, button "Add Browser Panes" is enabled. Click on it to add
'    a browser pane to Inventor browser. This adds a browser pane which contains an ActiveX control(registered in step 1)
' 6. List box in this sample's dialog shows different events fired by ActiveX control and Browserpane object.
' 7. Once BrowserPane is added to Inventor, you can send text to it using AddText button. You can clear
'    it using Clear Text button.
'