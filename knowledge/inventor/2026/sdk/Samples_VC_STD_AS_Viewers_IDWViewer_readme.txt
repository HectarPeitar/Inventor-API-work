IDWViewer sample
================

DESCRIPTION

This is a simple viewer application that demonstrates how a client may view an Autodesk(R) 
Inventor(R) Drawing document (IDW file).  It uses the Autodesk Inventor API to access the DWF(TM) 
snapshot of the drawing sheets in a drawing file.

IDWViewer uses the DWF Viewer ActiveX control to display the DWF snapshot of a drawing 
sheet.  This control has to be installed in order to use this sample.
DWF Viewer is the easiest way for people to view AutoCAD files in DWF format.

NOTE: The sample creates a DWF file for each sheet in the drawing that is viewed. The location for
these DWF files is the temporary folder which is determined by the TMP environment variable.
(e.g. "C:\Documents and Settings\username\Local Settings\Temp").

Language/Compiler: Visual C++
Server: Apprentice Server

How to create this sample?
Build IDWViewer Project

Exectuable: IDWViewer.exe

How to run this sample?
Run IDWViewer.exe.  The sample viewer has a minimal user interface.  Use the Open command on the 
File menu to select the drawing file (IDW) you want to view.  You can select the drawing sheet from 
the drop-down list box.

Specifically, using the layers menu item, you can selectively turn on and off the drawing views, 
borders, hatching, etc.
