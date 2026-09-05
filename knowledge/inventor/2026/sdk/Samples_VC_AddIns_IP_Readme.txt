  InsertCatalogPart Sample
  ========================
  
  DESCRIPTION
  
  This sample demonstrates using functionality in the Inventor API to create an
  application for standard parts.  In this sample the standard parts data is
  stored as SAT data.  There are two directories that need to be created before
  running the sample.

  C:\Temp\StandardParts\ 
  This directory contains the SAT files that will be used.  You can copy
  the five SAT files delivered with this sample to the directory.

  C:\Temp\CatalogPartsCache\
  This directory will contain the Inventor Part version of the SAT file
  once it has been converted.

  The basic methodology of the approach is that a catalog of standard parts exists
  in some form.  In this case, they exist as SAT files.  They could also exist just as
  descriptions of the parts or as Inventor parts and sets of parameters that can be
  used to create specific parts.

  When a user selects a part for placement the program first determines if the
  selected part has already been created by checking to see if it exists in the
  cache directory.  If it already exists it places it into the assembly.  If the
  part doesn't exist then it creates it on the fly using whatever input data is
  required.  For this sample it creates a new part document, invisibly, and loads
  the SAT file into it.  It then saves the part document using a unique name into
  the cache directory.  Any naming system can be used as long as it guarantees
  uniqueness among all of the possible parts.  Once the part file is created it
  is placed into the assembly. 

  Note: This sample edits the Samples.ipj project file to add an entry to point to 
  the CatalogPartsCache directory. Please make a copy of this project file and remove
  the read-only attribute from this file (if it exists) before running the sample. 
  
  Language\Compiler: VC++
  Server: Inventor.

  How to create this Sample : Build InsertCatalogPart project.
  Executable /DLL: InsertCatalogPart.dll.

  How to run this sample: The sample runs as an Add-In so that it can create commands to interact 
  with the  user.  To enable the sample run Register.bat.  Now you can run Inventor and the 
  commands will be displayed in the Add-Ins->General panel.  The first command "Define Cache Library",
  adds C:\Temp\CatalogPartsCache as a library to the current project.  The second command
  "Insert SAT Part"will allow you to select a part to place and will place it.