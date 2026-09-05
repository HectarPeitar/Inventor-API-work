  
CustomCommand Sample
=================

DESCRIPTION:

How to run this sample:
  1) Copy Autodesk.CustomCommand.Inventor.addin into ...\Autodesk\Inventor 20XX\Bin\Addins folder.

  2) Copy bin\Release\CustomCommand.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, the AddIn should be loaded

This sample demonstrates the recommended procedure for implementing a custom command in an Addin. The intent of
this sample is also to make it possible to extend the sample to implement additional commands. Hence, the use of
base classes for the command and its supporting classes. The base classes implement the general functionality that
is required by all commands, therefore, any command would only have to derive from the base classes and implement
only the command specific funtionality as demonstrated in the "Rack Face" command that this sample implements.

The sample demonstrates command creation, interaction events (selection), interaction graphics and the change 
processor mechanism.

If Inventor is running in Ribbon UI mode, then the command ("Rack Face") would be in Modify panel on Model tab in Part document environment

The command displays a dialog to accept input for creating a rack feature on a selected planar face with at least one
linear edge (e.g. rectangular face). When the dialog is displayed, the user is prompted to select a face on which the 
rack feature will be placed, the cursor is changed to a "+" sign to prompt for face selection. After selecting a planar 
face, the command automatically prompts for selection of the direction for the rack feature. The cursor changes to "+ ->" 
during direction selection. The direction is specified by selecting a linear edge on the selected face. The dimensions 
of the rack feature can be controlled by adjusting the number of teeth, tooth height, tooth width and rack extents. 
The command also displays the preview graphics for the rack feature, adjusting any of the rack input parameters will 
also update the preview graphics. If all the parameters are valid, the "Ok" button is enabled to create the feature.
  

REQUIREMENTS:
The command button is only displayed only when a part document is open. The rack feature can only be placed on a planar
face corresponding to the rack face, the direction for the rack feature has to be a linear edge on the rack face.

LANGUAGE/COMPILER: VC# (.Net)
SERVER: Inventor

