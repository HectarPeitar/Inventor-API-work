LICENSE AGREEMENT

THESE TERMS AND CONDITIONS AMEND THE END USER LICENSE AGREEMENT INCLUDED WITH THE AUTODESK?INVENTOR?SOFTWARE (THE SOFTWARE? FOR WHICH THIS SOFTWARE DEVELOPERMENT KIT (SDK) IS INTENDED).

BY INSTALLING THIS SDK THE USER ACCEPTS AND AGREES TO THE FOLLOWING:
WHILE AUTODESK, INC. HAS MADE REASONABLE EFFORTS TO VERIFY AND TEST THE SAMPLE FILES (SAMPLE FILES? AND TOOLS, INCLUDING WIZARDS, (COLLECTIVELY TOOLS? PROVIDED IN THIS SDK, THE SDK IS PROVIDED SOLELY ON AN "AS IS" BASIS, "WITH ALL FAULTS." THE SDK, THE SAMPLE FILES AND THE TOOLS CONTAINED ARE EMPLOYED AT THE SOLE RISK OF THE USER. AUTODESK DISCLAIMS ALL EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS, AND WARRANTIES OF ANY KIND, INCLUDING ANY IMPLIED WARRANTY OR CONDITION OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT. THE USER IS FREE TO MODIFY OR CUSTOMIZE THE SAMPLE FILES PROVIDED, HOWEVER AUTODESK MAKES NO REPRESENTATIONS, WARRANTIES, CONDITIONS, OR GUARANTIES AS TO THE QUALITY, SUITABILITY FOR A PARTICULAR PURPOSE, OR SAFETY OF USER¡¯S OTHER APPLICATIONS OR DATA WHEN USED WITH THE SAMPLE FILES OR THE TOOLS.
USER AGREES THAT AUTODESK IS NOT LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, CONSEQUENTIAL, PUNITIVE, OR EXEMPLARY DAMAGES, INCLUDING BUT NOT LIMITED TO, DAMAGES FOR LOSS OF PROFITS, REVENUE, GOODWILL, USE, DATA, ELECTRONICALLY TRANSMITTED ORDERS, OR OTHER ECONOMIC ADVANTAGE (EVEN IF AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES), HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER IN CONTRACT (INCLUDING FUNDAMENTAL BREACH), TORT (INCLUDING NEGLIGENCE) OR OTHERWISE, ARISING OUT OF OR RELATED TO: (i) THE USE OF OR THE INABILITY TO USE THE SAMPLE FILES AND TOOLS; (ii) THE COST OF PROCUREMENT OF SUBSTITUTE GOODS AND SERVICES RESULTING FROM THE USE OR INABILITY TO USE THE SAMPLE FILES AND THE TOOLS; OR (iii) ANY OTHER MATTER RELATING TO THE SAMPLE FILES AND THE TOOLS. USER HAS SOLE RESPONSIBILITY FOR ADEQUATE PROTECTION AND BACKUP OF DATA AND/OR EQUIPMENT USED IN CONNECTION WITH THE SAMPLE FILES AND THE TOOLS CONTAINED IN THE SDK AND WILL NOT MAKE A CLAIM AGAINST AUTODESK FOR LOST DATA, RE-RUN TIME, INACCURATE OUTPUT, WORK DELAYS, OR LOST PROFITS RESULTING FROM THE USE OF SAME. USER AGREES TO HOLD AUTODESK HARMLESS FROM, AND USER COVENANTS NOT TO SUE OR OTHERWISE SEEK LIABILITY FROM AUTODESK FOR, ANY CLAIMS BASED ON USING THE SDK OR THE SAMPLE FILES AND THE TOOLS CONTAINED, WHETHER IN CONTRACT (INCLUDING FUNDAMENTAL BREACH), TORT (INCLUDING NEGLIGENCE) OR OTHERWISE. 
EXCEPT AS PROVIDED HEREIN, ALL OTHER TERMS AND CONDITIONS OF THE END USER LICENSE AGREEMENT ACCOMPANYING THIS SOFTWARE APPLY TO THE SDK.

-------------------------

  
CustomGraphics Sample
=====================

DESCRIPTION:

This sample makes use of the custom graphics objects to simulate a laser drilling operation.
The laser drilling operation involves two major steps: 
1)Laser cutting:
This step involves cutting a circular hole in the part with a laser tool. The laser tool, laser path, sparks and laser trace are all drawn using custom graphics. The laser tool is a blue colored cylindrical tool and its default starting position is at a particular height (one of the laser tool parameters) from the origin of the part, which coincides, with the origin of the sketch of the cylindrical extrusion. Therefore, the very first step is to first draw the custom graphics corresponding to the laser tool at the desired position. In the next step the tool is moved along a circular path whose radius is the radius of the hole to be drilled. When, the laser tool graphics is being moved along the circular path, the graphics for the laser path (laser beam), the sparks and the laser trace (trace left by laser beam on the part) are drawn and also moved to match the new position of the laser tool.
The graphics objects are also associated with Matrix objects that define their position in the document's coordinate system in which they are placed. It is possible to create new Matrix and Vector objects using the TransientGeometry object to create or modify the position of the graphics. So, it is possible to modify the translation and rotation of the matrix associated with the graphics to move the graphics and it is this method that is employed to simulate the movement of the tool and the other related graphics. After the tool has completed the circular path, the movement of the laser tool is stopped and the laser beam, laser path, sparks graphics are made invisible.
2)Removal of cut portion
This step involves removal of the cut portion by pushing it out with the laser tool (the cut portion is shown by the green colored block and the laser tool is the same tool we used to cut the hole). This step first involves the creation of the cut portion graphics, which is cylindrical in shape just like the laser tool. So, the method of generating this graphics is similar to that of the tool except that its position, diameter and thickness are different. In order to create a hole that corresponds to the cut portion, a HoleFeature object whose center is at the origin and radius is equal to the radius of the drilled hole is created. 
The last step involves translating the laser tool graphics along a linear path towards the cut portion, and when the laser tool reaches the cut portion, translating both the laser tool and the cut portion until the cut portion is out of the extruded hole. 




SERVER: Inventor


LANGUAGE/COMPILER: VB.Net


INSTRUCTIONS:

To run this sample, ...
The executable for this sample is called CustomGraphics.exe. 
When you run this executable, a user form is displayed with three buttons:"Draw Tool", "Move Tool" and "Remove Cut Section" with only the "Draw Tool" button being active. When this is depressed, the cylindrical laser tool is created, the "Move Tool" button also becomes active and depressing this simulates the laser cutting operation. After completion of the cutting operation, the "Remove Cut Section" button becomes active and when this is pressed, the laser tool moves to remove the cut portion.





---------------------
For more information on Autodesk Inventor API, visit www.autodesk.com/developinventor
