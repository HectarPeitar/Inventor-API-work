iMateSampleAddin Sample
=======================

DESCRIPTION:

This sample demonstrates  the use of the iMates Api. 
There are three different scenarios in which imates can be used to create assembly constaints.
a) PlaceUsing iMates: This command creates a new assembly document and places a nut and a bolt , 
with the use imate option turned on. This means that when the second occurence is placed in the assembly an 
assembly constraint would be created between the already existing occurrence and this new occurrence, 
provided both the imate definitions are of the same type.

b) Add constraints using imates : This command creates a new assembly document and places a nut and a bolt.
It then queries each occurrence for imate defintions and then creates constraints between the imatedefinitions 
( in this case imatedefinitionproxy) of each occurrence. In this case both the nut and the bolt have an 
insert imate definition and hence this command creates a insert constraint between them. 
You can look in the browser to verify that an insert constraint has been created.

c) Create constraint using imates and entity. This command creates a constraint between occurrences using an 
imatedefinition on one occurrence and an entity ( like a face, edge etc) on the other. This command creates a new 
assembly document and places a nut and a bolt. It then queries the bolt for an circular edges and then creates a 
constraint ( which in this case is an insert constraint) between the insert imate definition on the nut and the 
circular edge on the bolt. You can look in the browser to verify that an insert constraint has been created.



SERVER: Inventor


LANGUAGE/COMPILER: VC++


REQUIREMENTS:

This sample requires the following:
a) Nut.ipt 
b) Bolt.ipt 
in the data_files folder


INSTRUCTIONS:

To build this sample, build iMateSampleAddin.dll

To run this sample, run inventor.exe and go to Add-Ins->General panel and choose any of the following three commands
a) PlaceUsingiMates
b)AddConstraintsFromiMates
c)CreateConstraintFromiMateAndEntity

Register the following files using regsvr32.exe: iMateSampleAddin.dll


---------------------
For more information on Autodesk Inventor API, visit www.autodesk.com/developinventor
