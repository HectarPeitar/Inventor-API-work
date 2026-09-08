Deutscher Stahlbau-Verband




        STANDARD DESCRIPTION FOR
        STEEL STRUCTURE PIECES
        FOR THE NUMERICAL CONTROLS


        Recommendations of the
        DSTV Commissions

        Juli 1998
        (7. St Edition)
        This Version delete and replace all the previous ones


        Edited by:
        Jan- Peter Gutsch
        Ulrich Kammertöns
        Jürgen Keil
        Dieter Knierim
        Dr. Heinz-Günter Liekweg
        Ulrich Pfingst
        Frank Streit
        Jan Verlies
        Bernhard Wiefel
        Jochen Zühlke

        Englisch translation done by BSI S.A. B4560 Ocquier
        Tel 00 32 86 349 191 – Version 980511
        In case of Problems, only the german version is valid
                                                                     2/2



Table of contents:
 News of the 7th Corrected Edition ............................................................................................. 3
 Foreword .................................................................................................................................... 4
 Recommendation for futur users of the DSTV......................................................................... 4
 Generalities ................................................................................................................................ 4
 Interface File............................................................................................................................... 5
 Units............................................................................................................................................ 6
 Used Profils ................................................................................................................................ 6
 The Coordinates System of the Piece ...................................................................................... 7
 System of Coordinates of the Standard Views ........................................................................ 8
 Compensation of the Tolerances of Rolling............................................................................. 8
 Header Data................................................................................................................................ 9
    Saw Length.......................................................................................................................................... 9
    Skew Cuts............................................................................................................................................ 9
 Bloc List of Holes..................................................................................................................... 10
    Complete Holes, Non Complete Holes & Countersink Holes ......................................................................11
 Bloc Marks by Powder or by Punch ....................................................................................... 12
 Bloc Numeration ...................................................................................................................... 12
 Bloc External & Internal Contour............................................................................................ 13
    Welding Preparation (Forming of the edges) .................................................................................. 14
    Notches.............................................................................................................................................. 14
 Bloc Cut (Saw, Cutting) ........................................................................................................... 15
 Bloc Tolerance ......................................................................................................................... 15
 Bloc Camber ( Preform ).......................................................................................................... 15
 Bloc Plane Definition ............................................................................................................... 16
 Bloc Bended Parts ................................................................................................................... 18
 Bloc Profile (Own User Profile Sections)................................................................................ 19
 Bloc Informations..................................................................................................................... 20
 Example:................................................................................................................................... 21
                                               3/3

                                News of the 7th Corrected Edition

• This page, gives the list of the news of the 7th Edition

• The table of contents (Page 1) and a new structure by theme

• Annulment of the limitation of 8 Characters for the filenames (Page 4)

    Because the used Operating Systems allows to use longer filenames , the old limitation
    has no reason to stay.

• Handling of Comments (Page 5, Table of the Blocs Codes)

    The Comments must be taken in account by the programs for in case where, the
    Interface is exported again. They must be placed in the same place with the same form
    in the new interface, they cannot be lost. Some new Comments can be introduced.

• Code for left threaded (Page 10)

    The List of Codes for Complete Holes, Threaded, Marking as. Punch or Countersink has
    been elongated with the Code l for the left threaded.

• Adjustment for External and Internal Contours (Page 13)

    All Contours must be closed, it means that the coordinates X and Y of the first and the
    last points of the Contour must be the same. All other Points of the Contour must be
    present only once.

• Bloc Plane Definition (Page 16 ff.)

    In the Bloc Profil the user can define its own Profile Sections, but without the possibility
    to describe the Geometries as Holes, Internal Contours or Marking of number in all the
    faces of these profiles. This Problem also appears for the Standard Profile type as
    Round and Rounded Tube (pipes).

    The Bloc Plane Definition brings now the solution.

General Comments

Handling for alternative Descriptions possibilities of Geometries

When for one Geometrie more than one Interpretation of the Interface exists, It MUST be
taken into account the Interpretation with the lower priority, it means for example that:

−   one Hole, which can be described by the Bloc BO , can only be described by this Bloc.
    The use of the Bloc IK (Internal Contour) is in this case totally forbidden.

−   The use of the Bloc AK has higher priority that the Bloc SC.

About Theme Skew Cuts and Bloc External Contour

Contrarily to the previous version the Interface asks that the Skew Cuts must be described
in the header data, also when the modifications of the External Contours needs other types
of the Bloc AK. Other Contour Elements have the value 0.0 at this place in the header data.
                                              4/4


Foreword

It is a standard interface for the geometrical description of the steel structure pieces for the
post-processors with numerical control:

    Saw
    Drill
    Flame Cutting
    Puncher
    …

The essential aim of this interface is to be neutral, it means that with only one standard
description we can manage several different NC machines.

The interface standardizes the link between a CAD-program or a graphical system, via a
CAM-file for the NC machines.

The geometry of the piece is introduced completely neutraly and after knowing the
parameters of the NC machine the post-processor can translate this neutral language to the
NC machine language.

The external contour of a beam can be given either by the Code bloc SC (cut) or by the
Code bloc AK (external contours of the flanges and the web) but to eliminate any
contradictions we recommand to use only one of these two blocs.

At the beginning of this interface, we start with the tradionnal way which describes the
external contours.
The Bloc SC was created for the description of special 3D cuts which cannot be described
by the description of external contours because for example several and different welding
preparation can be located on one edge of the piece.

Recommendation for futur users of the DSTV

The factories which are buying a new NC machine should attach this DSTV description to
their order form and so protect themself from any surprises.

Generalities

This interface describes the link between the CAD and graphical system to the NC machine
of the workshop. It contains only the data of the pieces independently of the NC machine.
The datas of the parts are divided in :

-   Header Data
-   Description of the holes
-   Description of internal and external contours with welding preparation
-   Description of numerotation
-   Description of the marks by powder or by punch
-   Description of special cuts
-   Description of bended parts



It is the distributor of the machine who must guaranty that its Postprocessor can transform
the piece‘s data from this interface to a correct and collisions free machine program. The
advantage of this interface is that the data introduced before the fabrication will not be
affected if the workshop needs to use another machine. These changes in the workshop
can be done without any changes in the piece data.
                                               5/5

Interface file

The interface file is an editable text-file (ASCII-File). This file is created in the CAD computer
and sorted by order, it can be transfered by any transfer procedure (KERMIT, DPCI, EMT
for example) to the computer of the NC machine or directly in this one.

Each part has its own file. The name of the file is componed by the Name followed by an
extension. For the extension, of maximum 3 characters, we recommend NC.The Name
must be meaningful and contains the number of the Drawing and the Piece. So for
example the file Z23P15.NC contains the data of the Piece 15 of the Drawing 23. Of
course, you must control that the length of the Name is compatible with the Operating
System used.

The syntax depends on the different possible descriptions which are described hereafter.
The first two columns have a special meaning. They contain a Code Bloc giving the
beginning of a part, the opening of a bloc or a comment line. The line with the Code Bloc
is empty from the third column, the data lines start with two space. From the third column
the format is free. The separator of the data is the space.
For compatibility reasons, the passage of a numerical value to a letter or vice-versa is also
interpreted as a separator. (This is the reason why the numerical value must be separated
either by at least one space, or by a letter which must be interpreted.)

Code bloc                                        Signification
  ST                                             STart = beginning of piece description
  EN                                             ENde = end of piece description
  BO                                             Opening bloc hole
  SI                                             Opening bloc numbering
  AK                                             Opening bloc external contour
  IK                                             Opening bloc internal contour
  PU                                             Opening bloc powder
  KO                                             Opening bloc mark
  SC                                             Opening bloc cut (Saw, Cutting)
  TO                                             Opening bloc Tolerance
  UE                                             Opening bloc Camber
  PR                                             Opening bloc Profile description
  KA                                             Opening bloc Bending
  En (0 >= n <= 9)                               Opening bloc definition Plan n
  Bn (0 >= n <= 9)                               Opening bloc BO of Plan n
  Sn (0 >= n <= 9)                               Opening bloc SI of Plan n
  An (0 >= n <= 9)                               Opening bloc AK of Plan n
  In (0 >= n <= 9)                               Opening bloc IK of Plan n
  Pn (0 >= n <= 9)                               Opening bloc PU of Plan n
  Kn (0 >= n <= 9)                               Opening bloc KO of Plan n
  **                                             Comment Line
                                                 Can be in any place of the interface
                                                 These informations are also saved: it means
                                                 that they cannot be lost with further uses.
                                              6/6

Units

The interface contains free text, integer numbers (without unity), lengths, angles, weight
and painting surfaces by meter.

Value                           Unity                  Format
Free Text                          -                   $ a (cadré à gauche, max. 80 Caract.)
Integer number                     -                      i
Length                             [mm]                   f (decimal number)
Angle                              degree                 f
Weight by meter                    [kg/m]                 f
Painting surface by meter          [m²/m]                 f
Empty column                       -                      x

The angles are positive in the mathematical orientation (anti-clock-wise).

Used Profils

The interface is previewed for the current steel structure profiles. Considering the quantity
of the different designations for different profiles, we will use a Code Profile to recognize
them more easily.
The names and designations of the profiles are taken in the standard of DSTV called :
„Einheitliche Bezeichnungen für den Datenaustausch im Stahlbau“.

Code Profile                                    Type of Profile
   I                                            Profile I
   L                                            Profile L
   U                                            Profile U
   B                                            Sheets, Plate, teared sheets, etc.
   RU                                           Round
   RO                                           Rounded Tube
   M                                            Rectangular Tube
   C                                            Profile C
   T                                            Profile T
   SO                                           Special Profile

The Code profile identifies the type of the profile.
                                               7/7

The coordinates system of the piece



The different faces of a piece depend of the positions of the piece in the machine and are
positionned in the coordinates system of these reference planes of the machine. The name
of these reference planes and the position of the coordinates sytem by type of profile are
represented in the scheme below.




Prof-type                                                                V
                            V    Z                                              Z

            O                              U     RO O                                      U

  I         Y
                  T       H           Np
                                           X     RU Y            T       H           Np
                                                                                          X

                          V      Z                                       V      Z

            O                              U               O                               U

  U         Y
                  T       H           Np
                                           X         B     Y
                                                                 T       H           Np
                                                                                          X

                          V      Z                                       V      Z

            O                              U               O                               U

  L         Y
                  T       H           Np
                                           X         C     Y
                                                                 T       H           Np
                                                                                          X

                          V      Z                                       V      Z

            O                              U               O                               U

  M         Y
                  T       H           Np
                                           X         T     Y
                                                                 T        H          Np
                                                                                          X


V = Web=front face U = Bottom O = Top H = Behind
Np = Zero Point    T = Displacement Direction

All the coordinates are referenced to this coordinates system with theorical dimensions of
perfect profiles perfectly lamined. The smallest X-coordinate of a piece is 0.0, the plates are
described by the smallest rectangle in which they can be inserted.
                                            8/8

System of Coordinates of the Standard Views

                                                          x




                                             Front




                              q                                  q

                 Top                                                     Bottom
x                                                                                              x
                              q




                                           Behind




Compensation of the tolerances of rolling                 x
The reference of the dimension (for example „upper edge“) indicates from which edge of
the piece the dimensions are taken. That means that the eventual tolerances of rolling will
be placed on the opposite. If we give no reference for the dimension, the previous value
stays valid. The reference of the dimension does not modify the value of a coordinate, it is
the post-processor which must uses it to balance the tolerance of rolling.
                                                       9/9
Header data

The header data follow immediately the Code Bloc ST for the beginning of the description
of the piece. They contain the most important data of the piece and the geometrical
dimensions which are necessary for the NC.
Format         Signification                                 For the sheets
2x, a          Order identification
2x, a          Drawing identification
2x, a          Phase identification
2x, a          Piece identification
2x, a          Steel quality
2x, i          Quantity of pieces
2x, a          Profile
2x, a          Code Profile
2x, f [, f ]   Length , Saw Length      < mm >
2x, f          Profile height           < mm >               Width
2x, f          Flange width             < mm >               0.0
2x, f          Flange thickness         < mm >               0.0
2x, f          Web thickness            < mm >               Sheet thickness
2x, f          Radius                   < mm >
2x, f          Weight by meter          < kg/m >             kg/m²
2x, f          Painting surface by meter    < m²/m >         m²/m²
2x, f          Web Start Cut           < degree >                                  The skew cuts angles
2x, f          Web End Cut             < degree >                                  must be given in any case
2x, f          Flange Start Cut        < degree >
2x, f          Flange End Cut          < degree >
2x,a           Text info on piece
2x,a           Text info on piece
2x,a           Text info on piece
2x,a           Text info on piece

After this bloc containing the header data, follow, in any order, the blocs giving the form.
We recognize them with the Code in the columns 1 and 2.
If the program cannot reads a bloc, it must skip to the line where it can found a readable
bloc.

Saw length
If an Rough length is necessary for the workshop, this one is introduced behind the normal
length as Saw length. The saw length is the length between the teorical points. We will
always take the shortest one.
Length data in the Bloc ST : Length , Saw Length.
                                  Saw length

                                     Length




Skew Cuts
The skew cuts of the web are represented in the view of the front face, the ones of the
flange in the bottom face.


                                                                               Bottom
                       Front




        +15 Degree             -15                              +15 Degree          -15
                                               10/10

Bloc List of Holes

The Bloc List of holes starts by BO in column 1 and 2.

The data relative to a hole are composed by the reference plane of the piece in which the
hole has to be done, the absolute coordinates in X and Y, the diameter, one Code for the
fabrication and if necessary the data for slotted or rectangular holes.

For the countersink or threaded holes some more data are necessary. It is the post-
processor which is doing the repartition for the steps for the pre-drilling and the thread. To
describe the slotted or rectangular holes we add the value ttt.tt the letter "l" the width,
height and the angle.

Format:
2xa1f          a1f          a1 f        1x f    a1 f     1x f    1x f

  o          o         g             l
..v xxxxxx.xx qqqqqq.qq ddd.dd ttt.tt bbbb.bb hhhh.hh ww.ww
  u          s         m
  h          u         s             l => slotted hole, rectangul. hole
                                     Values : Width, Height, Angle

                              => Complete hole. d= diameter, t= 0.0
                            g => Thread. d= diameter, t= 0.0
                            l => Left threaded, d= diameter, t= 0.0
                            m => Mark, Trace. d= 0.0, t= 0.0
                            s => Counter. d= Diameter, t=depth. countersink
                 o => Dimensions reference top edge
                   => Previous Dimensions reference
                 s => Dimensions reference axis
                 u => Dimensions reference bottom edge

    o => top flange
    v => front web
    u => bottom flange
    h => behind web




                                    b




                                                                          h




                                                                          +w




                                d
                                          11/11

Complete holes, Not complete holes and Countersink holes

The dimensions, etc. for the countersink bolts follow the DIN 74 Part 1 and Part 2, the
complete holes the DIN ISO 273 and the diameter for the pre-drilling for the threaded holes
the DIN 336. The different forms of holes are represented in the four examples here after:


               D 18



                                        BO
                                          v100.00u100.00 18.0 0.0
                                        EN




               D 18



                                           12

                                       BO
                                         v100.00u100.00 18.0 12.0
                                       EN




               D 18
               D 12

                                           12

                                       BO
                                         v 100.00u100.00s18.0 12.0
                                         v 100.00u100.00 12.0 0.0
                                       EN


              90Deg.

               D 18
               D 12
                                           8

                                       BO
                                         v 100.00u100.00s18.0       8.0 0.0 0.0 90.0
                                         v 100.00u100.00 12.0       0.0
                                       EN
                                             12/12



Bloc Marks by Powder or by Punch

The Bloc Marks by Powder or by Punch for the flame cutting begin by the Code Bloc PU for
the powder and KO for the punch in column 1 or 2.

The description is identical to the internal contour one.

Format:
2xa1 f             a1 f          1x f

  o           o
..v xxxxxx.xx   qqqqqq.qq rrr.rr
  u           s
  h           u              Radius
                     o => Dimensions reference top edge
                       => Previous Dimensions reference
                     s => Dimensions reference axis
                     u => Dimensions

    o => top flange
    v => front web
    u => bottom flange
    h => behind web


From the second point of a same contour, it is no more necessary to indicate to which face
the contour belongs.

Bloc Numeration

The Bloc Numeration starts by the Code SI in column 1 and 2.

The data for a numbering are composed by the reference plane of the piece in which the
numbering will be done, the absolute coordinates in X and Y, an angle, the text height and
the text to write itself.

Format:
2xa1f       a1 f          1x f   1x i a1 40a1

  o        o                 r
..v xxxx.xx qqqq.qq ww.ww hhh a.....a
  u        s                 z
  h        u

                                            r => The Text follow the piece if turned
                                            empty => Text at the same position
                                            z => Force all parameters
                                                 If one or more parameters are not done
                                                 The numeration is not done.

                                         Text Height (mm)
                                 Angle
                      o => Dimensions reference top edge
                        => Previous Dimensions reference
                      s => Dimensions reference axis
                      u => Dimensions

        o => top flange
        v => front web
        u => bottom flange
                                                13/13




Bloc external & internal Contour

The Bloc Contour starts by AK or IK in the column 1 and2.

The Bloc External Contour must not be introduced, if the piece is completely described by
its length, its dimensions and its skewed cuts in the header data or if the Bloc Cut has been
completely and correctly described.

The description of the contour is based on the introduction of Points and parallely
introduction of radius. The sign + in front of the Radius gives the orientation of this one: the
sign + is the mathematical orientation. The maximal angle is +/- 180°. We must divide an
angle of 220° in 2 angles : 180° and 40°

All contours have to be closed, it means that the coordinates X and Y of the first and the
last point of the contour are identical. All others points of the contour cannot be described
two times. The external contours are described in the mathematic orientation and the
internal contours clockwise.

For the profiles, the description of the contour is done by a transformation of the profile in
plates. The dimensions of the plates is the total height of the profile, for example the web of
a beam HEB has a height equal to the width of the web plus the thickness of the two
flanges.

A „Plate“ defined like this is easily identified by the letters "o, u, v, h" each letter gives the
right reference plane of the beam. Each "Plate" is one face of the beam, it is in real
dimensions, and no other material can be in interference with it. You can use all the faces
but it is better to use first the faces "o et v". If for a profile, by following the rules here-
before, we have several outside contours(in the same view), they will be merged in a unique
one. Thus a Rectangular Tube(M) and a C Profile(C) will only have a “PLATE” to describe
their web contour.

Format:
2xa1f            a1 f           a1 f      1x f          1x f   1x f   1x f

  o           o           t
..v xxxxxx.xx   qqqqqq.qq   rrr.rr www.ww yyy.yy www.ww yyy.yy
  u           s           w
  h           u
                                     Value for the welding preparation

                                       Radius
                                   t or w : Tool for the notche
                    o => Dimensions reference top edge
                      => Previous Dimensions reference
                    s => Dimensions reference axis
                    u => Dimensions

    o => top flange
    v => front web
    u => bottom flange
    h => behind web


From the second point of a same contour, it is no more necessary to indicate to which face
the contour belongs.
                                                   14/14

For the round tubes and the solid rounds, the „Plate“will be the development of the external
cylindric surface of the profile. The width of the “plate” will be the external perimeter of the
profile, it is described in „V“.



All the contours describe the external edge of the material. If we have also welding
preparation they are oriented to the external edge of the contour described in the direction
of the material. For the Profiles „divided“ in „Plates“ the special cuts in direction of the
material can be specified by the welding preparation.

Welding preparation (Forming of the edges)

For all the "Plates" described by contour we can give the forming of the edges of the
thickness of the plates by introducing the welding preparation.
Two values can be introduced after the radius of a point of the contour, they give for this
point the angle of flamecutting (Phi) to the verticale and the distance Y see sketches.

We will use two couples of values if we need a welding preparation on both sides. Phi can
be positive or negative see sketches.

                    +Phi

                                                                                           - Phi




                                          Y
                                                                                             Y

Notches

When notches are needed, the Bloc AK contains an information line which is not a part of
the contour description.
This line contains the coordinates of the corner as well as the type of radius to notch this
corner. We write "t" if we want a tangential notch or a "w" if we want a hole like hereafter.

                                                   R 20
        80     D 40                           80                            80

200




             100                                   100                               100


      AK                                AK                             AK
        v 100.00u    200.00      0.00     v 100.00u   200.00    0.00     v 100.00u   200.00        0.00
          100.00     140.00    -20.00       100.00    140.00 -20.00        100.00    120.00        0.00
          100.00     120.00w   -20.00       100.00    120.00t -20.00       100.00    120.00w       0.00
      →   100.00     100.00    -20.00   →    80.00    120.00    0.00   →     0.00    120.00        0.00
           80.00     120.00      0.00         0.00    120.00    0.00         0.00    0.00          0.00
            0.00     120.00      0.00         0.00      0.00    0.00
            0.00       0.00      0.00
                                             15/15

Bloc Cut (Saw, Cutting)

The Bloc Cut is opened by the Code Bloc SC in column 1 and 2. The cuts are always given
by a normal vector to the initial or final section of the profile coming out from the material to
outside. This normal vector starts from a specific point of the section.

Format:
2x 1x f         1x f        1x f         1x f         1x f         1x f

 .. xxxxxx.xx yyyyyy.yy zzzzzz.zz xxxxxx.xx yyyyyy.yy zzzzzz.zz

        Specif. Pt. Of the section            Data of the normal vector
                                              (from the section to outside)


Bloc Tolerance

The Bloc Tolerance starts with the Code Bloc TO in column 1 and 2 and must be distribute
proportionnaly on the length of the piece.

The Tolerance values for one length of beam are given by a minimum and a maximum
value.

Format:
2x f    1x f

..xxxx.xx yyy.yy


                 Maximum Value

    Minimum Value




Bloc Camber ( Preform )

The Bloc Camber starts by the Code UE in the column 1 and 2.

All the coordinates of the interface are given for the beam WITHOUT camber.

Format:
2xa1f        1x f

  o
..v xxxx.xx uuuu.uu
  u
  h

                     Dim. in Y of the Camber


       Dim. in X of the Camber

   o => top flange
   v => front web
   u => bottom flange
   h => behinf web
                                             16/16

Bloc Plane Definition

We can use more Planes only for the Geometries, for which the reference Plane cannot be
described by the standard faces of the pieces, given by the letters:

• v for Front,
• o for Top,
• u for Bottom and
• h for Behind

The Definition starts with the Code Bloc E in Column 1 and a Number between 0 and 9 in
Column 2, which is the number of the Plane.

After we have 3 lines,
• the first contain the coordinates X-, Y- and Z- of the Original Point of the Plane,
• the second contain the coordinates of a point of the X- axis situated at 100mm from the
    Origin
• the third contain the coordinates of a point of the Y- axis situated at 100mm from the
    Origin.

As Origin of the Plane we take one of the 2 intersection Points of the Plane with the Y- Axis
and the Z- Axis of the system of coordinates of the piece, the right point is the point which
has the smaller distance with the zero-point of the piece.

After the definition of the Plane are written the affiliated geometries, in that the opening
Code Bloc of the Bloc contains in column 2 the number of the Plane to which it is reported.
The letter at the start of the lines of coordinates giving the face of the piece (for example. v
for Front) is not existing if these lines are reported to a Plane.

To not reach the limit of 10 definitions of Plane, we can call several times the same number.
Before the new call of a number of Plane the description of geometries which are reported
to the old Plane must be finished.

The use of the Blocs BO, IK used for standard pieces, can also be done after the definition
of additional Plane.
                                                  17/17
Example of file with a call to an additional Plane E1:


ST
**NC-DSTV-Schnittstelle, Stand Juli 1998
  1
  1
  14
  14
  RST37-2
  2
  ZS175*1.5
 SO
    1133.00
     175.00
      81.00
       1.50
       1.50
       4.00
     4.416
     0.753
     0.000
     0.000
     0.000
     0.000
  Pfette



PR
  +   0.000           79.500       0.00
  + 48.000            79.500       0.00
  + 311.000          165.000       0.00
  + 347.000          165.000       0.00
  + 347.000           23.415       0.00
  + 310.400            2.259       0.00
  + 311.910            0.000       0.00
  + 350.000           21.650       0.00
  + 350.000          168.000       0.00
  + 310.510          168.000       0.00
  + 47.540            82.500       0.00
  +   3.000           82.500       0.00
  +   3.000          239.820       0.00
  + 39.620           260.950       0.00
  + 38.120           263.550       0.00
  +   0.000          241.550       0.00
  +   0.000           79.500       0.00
E1
      0.00           0.00       90.00
    100.00           0.00       90.00
      0.00         151.00       41.00
B1
    1100.00u        53.00       18.00
    1100.00u       131.00       18.00
S1
     100.00u         50.00 0000.00            5 1/1/14
EN

Comment:
For the description of Special Profiles the Section of the profile is defined by the
Bloc Profile. With the introduction of the interfaces of the Steel Structure Products
and the Standardization of the Material description, the preparation of a List of
Special Profiles is discussed. This List will clarify the names of Profiles, their Section
and their Position refered to the Coordinates System of the Piece. As soon as the
used Profile will be in the List, we can forget to use the Bloc Profile.
                                                18/18

Bloc Bended Parts

The Bloc of the bended parts begins by KA in the columns 1 and 2.

After we have for every axis of bending a line with the coordinates of the two points giving
the axis of bending, which is in the plane of the material, then the angle and the radius of
bending. The coordinates of the bending are given like all other elements compared to the
the piece not bended. The sign in front of the angles gives the direction of these angles. A
positive angle describes a bending in the plane XY in Z positive direction.

Format:
2x f                1x f           1x f        1x f


..xxxxxx.xx            yyyyyy.yy     www.ww         rrr.rr

                                                         Bending rad
                                          Bending Ang
                           Y Value Y of bending axis
      X Value of bending axis




             R 15                                                                        80

                                   R 15




             25                               120                      30




                                                                                         100
                  K1               K2                          K3             K4




        25                 8                    120                    8         30

KA
      25.0 0.0 25.0 100.0 -90.0 15.0
     105.0 0.0 105.0 100.0 90.0 15.0
     225.0 0.0 225.0 100.0 90.0
     305.0 0.0 305.0 100.0 -90.0
                                                19/19


Bloc Profile (Own user profile sections)

The Bloc Profile begins by PR in the column 1 and 2.

The section of the profile can be described by the Code Bloc PR .

The description is done by the contour description. In place of the letters giving the face of
the piece we give a sign ‘+’for the external contours, and a sign ‘-’for the internal contours
of the sections. The description of the contour must follow a normal rotation without
crossing. The description is possible only in one of the four faces.
The Code Profile must be SO.

Format:
2xa1f               1x f       1x f

  +
..- yyyyyyy.yy         zzzzzz.zz   rrr.rr

                               Radius
      + => Code for external Contour
      - => Code for internal Contour


                                            V                     Z



                                                                              U
                O
                                                                                    X
      100




     Y
                                                        50   20
                                         H
                                       200

PR
     +   0.0     0.0   0.0
     +   0.0   100.0   0.0
     + 20.0    100.0   0.0
     + 20.0     20.0   0.0
     + 70.0     20.0   0.0
     + 70.0    100.0   0.0
     + 200.0   100.0   0.0
     + 200.0     0.0   0.0
     +   0.0     0.0   0.0
     - 90.0     20.0   0.0
     - 180.0    20.0   0.0
     - 180.0    80.0   0.0
     - 90.0     80.0   0.0
     - 90.0     20.0   0.0
                                           20/20



Bloc Informations

The Bloc Informations begins by IN in the columns 1 and 2.

The data for an information is composed by the description of the area, the separator
column (:) and the contents of the area.


Format:
2xa     a1     a                                                                        .


..a...a :  a.....a
  |     |  |
  |     |  Contents
  |     |
  | Separator
  |
  Description in german


IN
     BESTELLER                 : Customer
     OBJEKT                    : Object
     PROJEKTLEITER             : Project manager
     STARTTERMIN               : Start date
     ENDTERMIN                 : End date
     GRUNDANSTRICH             : First painting
     DECKANSTRICH              : Final painting
     ENTZUNDERUNG              : Blasting
     VERZINKUNG                : Galvanized
     GEZEICHNET VON            : Drawned by
     GEZEICHNET AM             : Drawned on the
     GERÜFT VON                : Controled by
     GEPRÜFT AM                : Controled on the
                                       21/21
ST
**NC-DSTV-Schnittstelle
   DSTV
  1
  3
  3
  RST37-2
  1
  HEB400
  I
     2000.00
      400.00
      300.00
       24.00
       13.50
       27.00
    155.000
      1.930
      0.000
      0.000
      0.000
      0.000
  TRAEGER



BO
  v 1512.00o    144.00 24.00 0.00l   100.00       60.00   10.00
   v 450.00o    280.00   24.00
  v 900.00o     300.00   29.00
AK
  v 200.00o       0.00      0.00
   v 1952.00o     0.00      0.00 -18.430       13.50
  v 1952.00o    350.00      0.00
  v 1750.00o    350.00      0.00
  v 1750.00o    400.00      0.00
  v 163.50o     400.00      0.00
  v 150.00o     325.00      0.00
  v     0.00o   325.00      0.00
  v     0.00o   100.00      0.00
  v 190.00o     100.00    -10.00
  v 200.00o     100.00w   -10.00
  v 200.00o     110.00    -10.00
  v 200.00o      90.00      0.00
   v 200.00o      0.00      0.00
BO
  u 1415.00s    251.50 24.00 0.00l    70.00        0.00   0.00
  u 350.00s      98.00   18.00
  u 650.00s     229.00   20.00
  u 1150.00s    240.50   22.00
AK
  u 200.00s       0.00     0.00
  u 1900.00s      0.00     0.00
  u 2000.00s    300.00     0.00
  u 200.00s     300.00     0.00
  u 200.00s       0.00     0.00
BO
  o 1415.00s    251.50 24.00 0.00l    70.00        0.00    0.00
  o 350.00s      98.00   18.00
  o 650.00s     229.00   20.00
  o 1150.00s    240.50   22.00
AK
  o 159.50s       0.00     0.00   10.000       0.00
  o 159.50s     300.00     0.00
  o 1750.00s    300.00     0.00
  o 1750.00s      0.00     0.00
  o 159.50s       0.00     0.00
SI
  u 200.00u     225.00 0000.00       5 1/1/1
22/22
23/23
