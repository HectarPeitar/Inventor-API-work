  EventAddIn Sample
  =======================
  
  DESCRIPTION
  DESCRIPTION:

This sample demonstrates how to use Selection and Interaction Events to write a
command.  The sample has two commands:  Sketch Pattern command and Replicate Workplane command. 
These commands will be displayed in the Add-Ins->General panel.

Sketch Pattern command demonstrates how to use OnPreSelect event to modify the selection
set. This command selects all lines attached to the user selected sketch line and create a pattern from the selected items.  

Replicate Workplane command allows the user to select a workplane, and specify 
count and offset. It then replicates the selected workplane.


  How to run this sample:
 
  1) Copy Autodesk.SimpleAddIn.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\SimpleAddIn.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, the AddIn should be loaded, and on ribbon UI if you open a part document and activate a sketch and you can see "SketchPattern" and "ReplicateWorkplane" commands on the "General" panel on "Add-Ins" tab.
  

  Language/Compiler: C++
  Server: Inventor.

 