
  DataIOExe sample
  ================
  
	DESCRIPTION
  The sample demonstrates the use of the DataIO object obtainable from either the Apprentice
  Server or Inventor. It further demonstrates how associativity can be maintained even via
  a data transfer.

  This project links with Spatial Technology's ACIS libraries. 
  You would need to redefine the 'C++/PreProcessor' and 'Linker/Input' settings
  to point them correctly to the directories where ACIS is installed on your machine.

  Also, the target EXE being built should be placed into a directory from which when
  invoked, will be able to pick up the correct set of ACIS Dlls. This project targets
  the EXE into the same directory in which the ACIS libraries exist. This way, no system
  path need to be changed; Windows loads in DLLs from the EXE's directory first.

  Language/Compiler: Visual C++ 
  Server: Inventor Server or Apprentice.

  How to create this sample: Build DataIOExe
  Executable : DataIOExe.exe
  
  How to run this sample: Run DataIOExe and pass in a partfile name as an argument. 
