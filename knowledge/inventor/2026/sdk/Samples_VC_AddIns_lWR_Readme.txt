  LoftFeature Sample
  =======================
  
DESCRIPTION:

This sample demonstrates creation of loft feature which makes use of railing. 
This sample has one command.

Following is the sequence of operations in the sample:

1)  Create a part document.
2)  Create two ellipses of same size in XY sketch planes.
3)  Create small ellipse in YZ plane.
4)  Create two small ellipses in XY plane inside existing ellipses.
5)  Create Workplane parallel to XZ.
6)  Get workpoint between above two ellipses and Workplane (parallel to XZ).
7)  Create WorkAxis between workpoints obtained in step 6.
8)  Create Workplane at an angle of -30 deg to existing workplane created in step 5.
9)  Create 2 SketchLines and SketchArc(Fillet) on above workplane using workpoints created.
    in step 6 and also by creating additional 2d point (200,-150) in center top.
10) Get intersection workpoint between workplane created in step 3 and sketchArc.
11) Create the sketch plane on workplane parallel to YZ.
12) Transform the workpoint obtained in step 10 to sketch space.
13) Create a SketchCircle so that it passes through workpoint obtained in step 10.
14) Create simple loft between ellipses created in step 2 and 3.
15) Create loft between ellipses (step 5) and sketchCircle using rail collection(step 9).

  
  How to run this sample:
 
  1) Copy Autodesk.LoftFeature.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\LoftFeature.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor and run the Add-Ins->General->Loft With Railings->Loft command on the ribbon.
  
  Language/Compiler: C++
  Executable /DLL : LoftFeature.dll
  Server: Inventor.

 