  ClientGraphics Sample
  =======================
  
  DESCRIPTION
  This sample demonstrates a minimal implementation of an Add-In.  
  
  This sample corresponds to the Add-In section of the Developer's Guide found in the programming 
  online help.  See that section for details about how Add-Ins work and how to create an Add-In.



  Language/Compiler: C++
  Server: Inventor.

  
How to run this sample:
 
  1) Copy Autodesk.ClientGraphics.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\ClientGraphics.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, the AddIn should be loaded, and on ribbon UI if you open a part or assembly document and you can see the "General" panel on "Add-Ins" tab.
  
  The client graphics commands allow you to create, show, move, hide and clear the custom graphics. Following is the description of each of these commands:


Draw Squares 
	Creates two squares by adding a triangle strip with strip lengths set for
  two triangle strips of four vertices (two triangles) each.  The first triangle
  in each strip takes three vertices and each additional triangle takes an additional
  vertex.  See DrawGraphicsStrips for another example of this.  This example also
  shows how to add data to a GraphicsDataSet one at a time or all at once (in an array).
  The colors are added one at a time while the coordinates are added all at once.


  Draw Von Koch  
  Creates a von Koch snowflake which replaces each line in a set of lines with
  four new lines.  Each time the function is run it retrieves the coordinates for
  the first line strip under a graphics node and uses those coordinates as the
  basis for the next iteration of the snowflake.  Shows line graphics and 
  coordinate retrieval and editing.

	Draw Circle  
  Adds a circle as a line strip and then adds a text label anchored at a corner
  point of the bounding box for the circle and marks some of the vertices 
  with points.  Shows line strip graphics, text graphics, and point graphics.

  Draw Shared Coords 
  Creates a square with a triangle set and a line set that borders the square.
  Both the triangles and lines share the same coordinate set.  Then the entire 
  graphics node is copied with a transform.

  Draw Cylinder 
	Creates a cylinder by adding a triangle strip for the main surface of the
  cylinder and two triange fans to form the end caps of the cylinder.  A
  line strip is also added to hilight one of the edges.  All of these graphics
  primitives share the same coordinate set that is made up of two circular sets of
  points and two center points.  A render style is also created for the cylinder.

  Draw Graphics Strips 
	This example creates a triangle strip and a line strip with essentially the
  same coordinates (offset differently along the Y-axis) but with strip lengths
  applied to the triangle strip which creates two different strips from a single
  TriangleStripGraphics object.

  Clear All 
	Delete all of the graphics nodes for our client.  This permanently deletes
  all of the client graphics that were added to the current document, with the
  exception of an undo by the user which would restore the graphics as they
  were before the ClearAll was done.

	Show Graphics 
	If show is false then all of the graphics nodes added to the current document 
  will be hidden.  If show is true then all graphics nodes added to the current 
  document will be made visible. 


 