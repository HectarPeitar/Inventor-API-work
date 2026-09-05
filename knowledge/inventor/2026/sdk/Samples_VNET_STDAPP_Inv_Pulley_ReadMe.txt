  Pulley Sample
  =============
  
  DESCRIPTION
  This sample demonstrates modifying parameters in a Part document,
  updating the part, and fitting the modified graphics within the
  window.

  The sample part is a simple pulley taken from a drive
  products catalog.  It's a standard Inventor part where care has
  been taken to build it so it can be modified correctly by modifying
  parameters.  This was done by correctly naming parameters so specific
  parameters can be easily identified.  Relationships between parameters
  were also created where needed.

  Also part of this sample is an Excel spreadsheet.  This spreadsheet
  contains the table information defining the various members of 
  the pulley family.  Within this spreadsheet is also a VBA program
  that will take the selected member data from Excel and modify the
  parameter values within the Inventor part.
 
  Language/Compiler: VBA.
  Server: Inventor Server.
  
  How to create this sample: The sample is a VBA macro. Refer pulley.xls
  
  How to run this sample: To use the sample open both the part file with 
  Inventor and the spreadsheet within Excel.  Select the desired pulley 
  size by clicking in any of the cells within the desired row and then 
  clicking the "Update Part" button.  The Inventor part should update
  to the specified size.  Clicking the "Update Part" button causes the VBA function to run.