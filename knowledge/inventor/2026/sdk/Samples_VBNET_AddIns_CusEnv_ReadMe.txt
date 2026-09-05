  CustomEnvironment Sample
  ========================
  
  DESCRIPTION
  This sample demonstrates the steps to implement a custom parallel environment in Inventor using 
  the Inventor API. 

  The sample is an Inventor AddIn which creates a new environment called "Analyze Body" which is 
  parallel to the Inventor part environment (i.e. when you launch Inventor with classic UI and if you have the default part environment in Inventor,
  the custom environment can be activated using the "Applications -> Analyze Body" button from the 
  menu bar, while you launch Inventor in ribbon UI, and if you have the default part environment in Inventor then you can activate the custom environment using "Environments -> Begin -> Analyze Body"). In classic UI the environment includes a custom command bar which will be displayed as the default panel
  bar when the environment is activated while in ribbon the environment includes a custom panel "Analyze Body" as default panel. The default panel in turn has three commands:
  
  "Analyze Surface Body": This command displays geometric information about the active part model, e.g.
   volume, extents etc.

  "Analyze Face": This command requests the user to select a face from the part model after which it
   displays geometric information about the face, e.g. area, surface type etc.

  "Analyze Edge": This command displays geometric information about the selected edge in the model.

  This sample also shows how to implement a custom browser pane with custom browser nodes. In this case,
  a tree heirarchy representing the BRep (Boundary representation) geometry is displayed (i.e. SurfaceBody
  -> Faces -> EdgeLoops -> Edges). The custom browser pane will be activated upon switching to the custom
  environment and hovering over the nodes will highlight the corresponding entities in the model (for those
  entities which have a direct equivalent graphical representation, e.g. faces, edges but, not for edge
  loops). The geometric information about the entities can also be displayed by activating (double-clicking)
  the browser node items.

  The sample also demonstrates, user interaction events (selection), context menu, application events and
  browser events.
  
  How to run this sample:
  1) Creat CustomEnvironment.addin file copy the following section into it.

     <?xml version="1.0" encoding="utf-8"?>
     <!-- Type attribute is same as Type registry key (Standard, Translator, Plugin (Server only) -->
     <Addin Type="Standard">
     <ClassId>{a0cc5d86-d345-461f-9e9d-35c5f699d2cb}</ClassId>
     <ClientId>{a0cc5d86-d345-461f-9e9d-35c5f699d2cb}</ClientId>
     
     <!-- Both of the following fields should be translated. NO OTHER FIELDS SHOULD BE TRANSLATED! -->
     <DisplayName>Custom Environment</DisplayName>
     <Description>Custom Environment</Description>

     <!-- Assumes that CustomEnvironment.dll is underneath Inventor\bin -->
     <Assembly>CustomEnvironment.dll</Assembly>

     <SupportedSoftwareVersionGreaterThan>16..</SupportedSoftwareVersionGreaterThan>
     <LoadOnStartUp>1</LoadOnStartUp>
     <Hidden>0</Hidden>
     </Addin>

  2) Copy CustomEnvironment.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  3) Copy bin\CustomEnvironment.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  4) Startup Inventor, the AddIn should be loaded

  After performing these steps, start Inventor and open a part document. 
  The custom environment can then be activated using the "Applications -> Analyze Body" menu pull-down button in classic UI or through "Environments -> Analyze Body" in ribbon UI.

  Language/Compiler: VB.NET.
  Server: Inventor.
  
 