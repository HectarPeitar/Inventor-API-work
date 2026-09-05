
ApprenticeViewerMDI Sample
==============================

DESCRIPTION:

This sample demonstrates the file display API features in a stand alone MFC EXE application. It allows you to display multiple part, assembly and drawing files each in its own window and allows manipulation to the views of the file being displayed outside of Inventor. The feature is part of the Inventor Apprentice server. C++ is the language used to program the stand alone application.

The file display feature is using the CView derived class CApprenticeViewerMDIView as a place holder where the file is going to displayed. ApprenticeServerDocument object is used to open a ipt/iam/idw file. The CApprenticeViewerMDIView's handle is added to the ClientViews and returns an InventorApprentice.ClientView object. With access to the InventorApprentice.Camera object, the desired view orientation type is set. Finally, InventorApprentice.ClientView.Update is called and the file image is displayed just as it is displayed in Inventor.

There are some mouse events, OnLButtonDown, OnMButtonDown, OnMouseWheel and OnMouseMove, need to be handled so the file view can be manipulated. 

Obviously, there are a lot of the MFC code that is only relevant to the MDI application specifics. They don't apply to the file display feature but necessary in setting up the MDI framework.

Note that for assembly files, occurrence specific visibility and color are not supported when displaying an assembly file that has these settings.

SERVER: Apprentice

LANGUAGE/COMPILER: VC++


REQUIREMENTS:

This sample requires the following: 

1. Inventor Apprentice Server
2. To be able to compile the application, Microsoft Visual C++ has to be installed


INSTRUCTIONS:

To compile this sample, open the ApprenticeViewerMDI.vcproj file and build the project.

To run this sample, copy the ApprenticeViewerMDI.exe to Inventor Bin folder and execute it, then open IPT, IAM or IDW files.


