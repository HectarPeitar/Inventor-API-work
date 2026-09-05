  
CustomCommand Sample
=================

DESCRIPTION:

How to run this sample:
  1) Creat CustomCommand.addin file copy the following section into it.

     <?xml version="1.0" encoding="utf-8"?>
     <!-- Type attribute is same as Type registry key (Standard, Translator, Plugin (Server only) -->
     <Addin Type="Standard">

     <ClassId>{D7D54695-7FBE-4968-A0DD-B86FA4D59AE5}</ClassId>
     <ClientId>{D7D54695-7FBE-4968-A0DD-B86FA4D59AE5}</ClientId>

     <!-- Both of the following fields should be translated. NO OTHER FIELDS SHOULD BE TRANSLATED! -->
     <DisplayName>CustomCommand</DisplayName>
     <Description>CustomCommand</Description>

     <!-- Assumes that CustomCommand.dll is underneath Inventor\bin -->
     <Assembly>CustomCommand.dll</Assembly>

     <SupportedSoftwareVersionGreaterThan>17..</SupportedSoftwareVersionGreaterThan>

     <LoadOnStartUp>1</LoadOnStartUp>
     <Hidden>0</Hidden>
     </Addin>

  2) Copy CustomCommand.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  3) Copy bin\CustomCommand.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  4) Startup Inventor, the AddIn should be loaded

This sample demonstrates the recommended procedure for implementing a custom command in an Addin. The intent of
this sample is also to make it possible to extend the sample to implement additional commands. Hence, the use of
base classes for the command and its supporting classes. The base classes implement the general functionality that
is required by all commands, therefore, any command would only have to derive from the base classes and implement
only the command specific funtionality as demonstrated in the "Rack Face" command that this sample implements.

The sample demonstrates command creation, interaction events (selection), interaction graphics and the change 
processor mechanism.

If Inventor is running in Classic UI mode, then the command ("Rack Face") is displayed on the "Part Features" toolbar (which is the default toolbar of the panel bar in the part environment).
If Inventor is running in Ribbon UI mode, then the command ("Rack Face") would be in Modify panel on Model tab in Part document environment.

The command displays a dialog to accept input for creating a rack feature on a selected planar face with at least one
linear edge (e.g. rectangular face). When the dialog is displayed, the user is prompted to select a face on which the 
rack feature will be placed, the cursor is changed to a "+" sign to prompt for face selection. After selecting a planar 
face, the command automatically prompts for selection of the direction for the rack feature. The cursor changes to "+ ->" 
during direction selection. The direction is specified by selecting a linear edge on the selected face. The dimensions 
of the rack feature can be controlled by adjusting the number of teeth, tooth height, tooth width and rack extents. 
The command also displays the preview graphics for the rack feature, adjusting any of the rack input parameters will 
also update the preview graphics. If all the parameters are valid, the "Ok" button is enabled to create the feature.
  
 

REQUIREMENTS:
The command button is displayed only when a part document is open. The rack feature can only be placed on a planar
face corresponding to the rack face, the direction for the rack feature has to be a linear edge on the rack face.

LANGUAGE/COMPILER: VB.net
SERVER: Inventor

