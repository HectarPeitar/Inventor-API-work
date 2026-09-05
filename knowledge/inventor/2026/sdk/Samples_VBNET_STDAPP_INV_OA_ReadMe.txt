  Overlay Assembly Sample
  =======================
  
  DESCRIPTION
  This sample creates an 'overlay' assembly by creating occurrences of multiple positional representations of a source assembly. The user has the option of selecting the representations used to build the overlay. The newly created assembly may then be used directly to create an overlay drawing.

Here are the steps followed by the sample:

1. Obtain the file name of a source assembly containing positional representations from the user.
2. Populate a list box with all available positional representations in the source assembly.
   (The user then selects the positional representations to create an overlay assembly of.)
3. Create a new assembly document and create an occurrence of the source assembly for each selected positional representation. The occurrences are created at the origin of the new assembly.
4. Mark all occurrences as 'Grounded'.
5. Mark all occurrences, except the first one selected, as 'Reference'.
6. Mark the new assembly document as 'Excluded from BOM'.


  Language/Compiler: VB.Net.
  Server: Autodesk Inventor Server.
  
  How to create this sample: Make OverlayAssembly.exe
  Executable : OverlayAssembly.exe
  
  How to run this sample: To run the sample, have Inventor running. If the active document is an assembly containing multiple positional representations, it will be automatically picked up by the sample, else you may use the 'Browse...' option to select a file from disk.