  AutoBolt Placement Sample
  =========================

  This sample program illustrates several capabilities of the Inventor API
  including traversing the assembly, accessing and querying the model B-Rep,
  document handling, modifying parameters, dynamic attributes, and assembly 
  occurrence placement.

  The sample is a standalone executable that runs externally to Inventor,
  but requires Inventor because it connects to and drives it.  To run the
  sample you should have any assembly open that contains at least one part with at
  least one hole in it.  The file "Base.ipt" (in the SDK\Data_Files folder)
  can also be used to test the program.

  While the assembly is open run the AutoBolts.exe from an Explorer window.
  The program will connect to Inventor and extract the assembly tree from
  the active document and display it in a dialog.  In the dialog, select the
  part you want to insert the bolts for and click the "Place Bolts" button.

  The program then examines the geometry of the selected component and finds
  anywhere where there's a cylindrical face going perpendicular to a planar
  face (essentially all holes).  When it finds this it also records the size
  of the cylinder.  In the next step it checks the library directory to see
  if a bolt of the correct size already exists.  If it doesn't, it opens
  the seed bolt and modifies the parameter "Diameter" and updates the part
  to create a bolt of the correct size.  Once a correct bolt exists, it
  places it into the assembly.

  The DefineEdge program that's also contained within the same directory was
  used to attach an attribute to an edge in the bolt.  The circular edge
  between the shaft and head of bolt in BoltSeed.ipt has an attribute
  associated with it so this edge can be found when each occurrence is
  placed into the assembly.  Using this edge and an edge that was obtained
  from the part an Insert constraint is created between the bolt and the
  part.  This program is used just in setting up the bolt to be used.  Since
  the attribute has already been placed on the edge in the bolt file, this
  program isn't needed to run the sample, but is delivered so you can see
  how the attribute was attached and as a simple sample for dynamic attributes.
  
  Language/Compiler: VC#.NET.
  Server: Inventor

  How to Create This Sample: Make AutoBolts.exe.

  Executable: AutoBolts.exe.

  How to Run this sample: Start Autodesk Inventor and open an assembly document
  or place the supplied base.ipt file in the assembly.


