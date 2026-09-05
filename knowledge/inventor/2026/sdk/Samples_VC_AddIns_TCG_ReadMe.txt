  TextClientGraph Sample
  =======================
  
 This sample program illustrates simple usage of the client text capability introduced in Inventor 6.  
It will place a sample string into an assembly, anchored at 0,0,0. This string can be formatted using the properties 
of the TextGraphics object.In common with other client graphics, the resultant text is 'tied' to the model space.

  
  How to run this sample:
 
  1) Copy Autodesk.TextClientGraph.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\TextClientGraph.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, You will notice a new command TextClientGraphics->TextClientGraphics in Add-Ins->General panel. 
Start the command with the TextClientGraphics menu item. When run, you will notice some sample text added to the view of 
the assembly. You may rotate, zoom etc. the assembly as normal, but the text will remain anchored and oriented correctly. 
Attributes such as font, content, font size, color and position can all be modified in the code sample. 
To remove the sample client graphics text from the assembly, just run the  command once more - it acts as a toggle.
  
  Language/Compiler: C++
  Executable /DLL : Translator.dll
  Server: Inventor.

 