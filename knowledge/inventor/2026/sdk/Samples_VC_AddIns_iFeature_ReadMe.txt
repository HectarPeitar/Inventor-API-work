  iFeature Sample
  =======================
  
  DESCRIPTION
  This sample demonstrates a minimal implementation of an Add-In.  
  
  This sample corresponds to the Add-In section of the Developer's Guide found in the programming 
  online help.  See that section for details about how Add-Ins work and how to create an Add-In.

  How to run this sample:
 
  1) Copy Autodesk.SimpleAddIn.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\SimpleAddIn.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, the AddIn should be loaded, and on ribbon UI if you open a part document and activate a sketch and you can see PlaceiFeature and PlaceTableDrivenFeature commands on the "General" panel on "Add-Ins" tab.
  
  Following is the sequence of operations of iFeature placement in the sample:
1)  Create a new part document
2)  Create an extrusion for a rectangular profile
3)  Extract the definition of the iFeature (ArrowX.ide)
4)  Set the skech plane to one of the faces of the extrusion feature
5)  Set the position for placement of the iFeature to one of the vertices of the face
6)  Set the direction for the iFeature axis
7)  Place the iFeature by adding the completed iFeatureDefinition to the iFeatureComponents collection

Following is the sequence of operations of Table Driven iFeature placement in the sample:
1)  Create a new part document
2)  Create an extrusion for a rectangular profile, and choose one of its planar faces
4)  Extract the definition of iFeature(Block.ide)
5)  Set the input to the planar face
6)  Access the existing table driven iFeature, look through the table to find the column with the name "Distance" and the row with the value "1 in"
7)  Set the found row as active row
8)  Create the iFeature and add it to the PartFeatures.


REQUIREMENTS:

This sample requires the following: 
ArrowX.ide file provided in the Samples/Data_Files/  folder
Block.ide file provided in the Samples/Data_Files/  folder

  Language/Compiler: C++
  Server: Inventor.

 