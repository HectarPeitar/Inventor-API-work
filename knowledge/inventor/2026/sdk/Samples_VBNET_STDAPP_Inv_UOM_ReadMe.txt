  Units of Measure Sample
  =======================
  
  DESCRIPTION
  This sample demonstrates the Units of Measure portion of the Inventor
  API.  
  
  The Units of Measure allows an application to get and display unit
  information to the user in the same way Inventor does.  For example, if
  a user measures the length of an edge, the resulting display of the 
  length is controlled by the settings the user has defined using the "Units"
  tab of the "Document Settings" command.  Using this tab, the user specifies
  which units they want to use for length, angle, time, and mass units.  They
  can also specify the precision to display in.  In this example, if the length
  units are set to inch and the precision is "0.123" the result of a one inch
  edge will be "1.000 in".  Using the Units of Measure functionality of the API 
  you can display unit values in the same way.

  When a user specifies unit information to Inventor, Inventor is very flexible
  about the values entered.  For example, if they've specified inch as the
  length unit and enter "3" in a dialog asking for a length unit, this is
  interpreted as 3 inches.  They could also enter "3 cm" to specify the specific
  unit and override whatever the default unit it.  It also supports equations
  and using parameters.  The following is a valid input, assuming the parameter
  d0 exists: "(3 cm + d0) / 2".

  Internally Inventor uses consistent units regardless of the units the user
  has specified for the document.  Lengths within Autodesk Inventor are always in cm,
  angles are always in radians, mass is always in kilograms, and time is always
  in seconds.  When working with any other function in Inventor you can assume
  the values are in these units.  It's only when interacting with the user
  that you need to be able to get and display information using the units as
  specified by the user.  This sample demonstrates taking a string from the
  user and converting it into the internal unit type.  It also illustrates
  taking a value in internal units and creating the appropriate string to display
  to the user.

  The bottom portion of the form allows you to change the current settings for
  the various units.  This is equivalent to the functionality on the "Units" tab
  of the "Document Settings" command in Inventor. 

  The last section shows how to convert units between any two compatible units.

  Language/Compiler: VB.Net
  Server: Inventor Server.
  
  How to create this sample: Make Uom.exe
  Executable : uom.exe
  
  How to run this sample: To run the sample, have Inventor running with a document open.  It will use
  the unit settings of the active document.
