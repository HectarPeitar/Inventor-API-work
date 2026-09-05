Simple BRep Sample
==================
	
DESCRIPTION
This sample traverses the BRep and prints out the BRep information during traversal.
	

This is a VC++ console application that demonstrates accessing the B-Rep and geometry of an
Inventor Part using Apprentice Server.  This application traverses the entire B-Rep and 
prints out information during the traversal.  As it traverses, it looks for cylindrical
faces and then uses the geometry query functionality of the API to obtain the radius of 
the cylinder using two different techniques.

Language/Compiler: VC++
Server: Apprentice Server.

How to Create This Sample: Build BRep Traversal Project.

Executable: BRep Traversal.exe

How to Run this sample?
Run the BRepTraversal.exe and choose a part file whose brep needs to be traversed.

Then you will see the list of all the topological entities and their count.