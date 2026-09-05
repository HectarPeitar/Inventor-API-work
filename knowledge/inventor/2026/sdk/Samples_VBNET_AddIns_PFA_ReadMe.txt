  PartFeaturesAddin Sample
  =======================
  
  DESCRIPTION
  This sample demonstrates the functionality to create part features in an Inventor Add-In.  
  
  How to run this sample:
  1) Copy Autodesk.PartFeaturesAddin.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\PartFeaturesAddin.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, the AddIn should be loaded
  
  How to use BoltMaker to create bolts:
  
  1. Open a part document, and you may find the "Create Bolt" button on PartFeaturesAddin.BoltMaker Panel in Add-Ins tab.
  2. Click the "Create Bolt" button, and a dialog shows to let you input parameters of your 
     bolt.
  3. Move mouse to the location where you want to place your bolt, click the left button, 
     and an arrow will appear to show the position of your bolt to be created.
  4. Click another location or modify coordinates on the parameter dialog to change the 
     position of your bolt.
  5. Click OK to actually create the bolt.
  

  Language/Compiler: VB (.NET)
  Server: Inventor.

 