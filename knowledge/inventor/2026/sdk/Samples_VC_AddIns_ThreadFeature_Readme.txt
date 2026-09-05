  ThreadFeature Sample
  =======================
  
 This sample demonstrates the creation and edit of thread features.

Creation:  The sample creates a cylinder in a new part document and creates a thread feature on the cylinder. A ThreadInfo object is newed up by defining all the thread information. This ThreadInfo object is then used as input for creating the thread feature.
Edit: Modification of values on the ThreadFeature object and on the ThreadInfo object obtained from the thread feature are demonstrated. Two ways of modifying information in the ThreadInfo object are shown. In the first case, which requires changes to several values on the ThreadInfo object, the entire ThreadInfo object on the ThreadFeature is replaced. In the second case that requires very few changes to the ThreadInfo object,  the "live tear-off" method is demonstrated.


  
  How to run this sample:
 
  1) Copy Autodesk.ThreadFeature.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\ThreadFeature.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, the commands ('CreateThreadFeature' and 'EditThreadFeature' will be displayed on the Add-Ins->General panel).
  
  The file types supported by the translator will now
  be displayed by Inventor in the Open and Save Copy As dialogs.

  If the user selects the file type supported by the Add-In from the
  Open dialog, Inventor notifies the Add-In and supplies the filename
  of the selected file.  The Add-In can then open the file, perform
  whatever's needed to produce a SAT file and then use the Inventor
  API to create a new document and read in the SAT file.

  If the user selects the file type from the Save Copy As dialog, Inventor
  notifies the Add-In and supplies the name of the file to save to.
  The Add-In can then use the Inventor API to query the model and then
  write the model in the new format to the specified file.
 
  This sample demonstrates this concept by supporting a simple
  translator that translates spheres in Part documents.
  

  Language/Compiler: C++
  Executable /DLL : Translator.dll
  Server: Inventor.

 