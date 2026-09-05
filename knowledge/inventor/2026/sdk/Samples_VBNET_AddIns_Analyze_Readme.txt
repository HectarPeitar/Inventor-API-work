  Analyze Sample
  ==============

  DESCRIPTION
  This sample demonstrates much of the functionality with Autodesk Inventor 
  that enables integrated "in the window" applications.  Some of this 
  functionality is user interface customization including creating a toolbar 
  and making it available within the panel menu for a specific environment, 
  browser customization, user selection, attributes, and client graphics.

  Language/Compiler: Visual Basic.NET
  Server: Inventor

  Sample Setup:
  This sample consists of two projects, one defines a control that is used 
  within the Inventor browser.  The other project is the main program and is
  an Add-In.  The following steps can be followed to enable the sample.

  1. Creat Analyze.addin file copy the following section into it.

     <?xml version="1.0" encoding="utf-8"?>
     <!-- Type attribute is same as Type registry key (Standard, Translator, Plugin (Server only) -->
     <Addin Type="Standard">
     <ClassId>{AFEBDB0D-C529-4f55-94E7-E7B87807F5A4}</ClassId>
     <ClientId>{AFEBDB0D-C529-4f55-94E7-E7B87807F5A4}</ClientId>
     
     <!-- Both of the following fields should be translated. NO OTHER FIELDS SHOULD BE TRANSLATED! -->
     <DisplayName>Analyze path sample</DisplayName>
     <Description>Analyze path sample</Description>

     <!-- Assumes that Analyze.dll is underneath Inventor\bin -->
     <Assembly>Analyze.dll</Assembly>

     <SupportedSoftwareVersionGreaterThan>17..</SupportedSoftwareVersionGreaterThan>
     <LoadOnStartUp>1</LoadOnStartUp>
     <Hidden>0</Hidden>
      </Addin>

  2. Copy Analyze.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  3. Copy bin\Analyze.dll,AnalyzeControl.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  4. Start Inventor and open an assembly document, you can find the "Analyze path sample" panel on the Add-Ins tab.


  Running the Sample:
  The sample can be used with any assembly, but one is delivered with the
  sample so you can see how it works.  Here are some steps you can use
  with the delivered sample.

  1. Open the 4Bar.iam assembly in the Assembly directory.
  2. Note the "Analyze path sample" contains "Define Analysis Parameters" and "Run Analysis" commands.
  3. Run the "Define Analysis Parameters" command.
  4. Holding the control key, select the parameters Swivel and Crank and click OK.
  5. Select Crank in the parameter list and set the end value to 360.
  6. Select Swivel in the parameter list and set the end value to 720.
  7. Click OK to dismiss the Properties dialog.
  8. Run the "Run Analysis" command from the Analyze menu.
  9. Click the "Click to add point" in the browser.
  10. Select the circular end of Swivel.ipt facing you.
  11. Select one of the visible vertices on the Link.ipt part that is near where Swivel.ipt connects to it.  
      (You can select any point on the assembly.)
  12. Press Esc to end selection.
  13. Click the "Run Analysis" button to drive the assembly and see the paths.

  You can experiment by going back to the parameters dialog and change the 
  parameter values.  You can also edit Link.ipt and increase the length of 
  the arm and/or it angle.  After making any changes, click the "Run Analysis" 
  button to see the new results.

