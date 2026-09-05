With Inventor 2013 the Inventor Wizards are no longer provided as a seperate installer but are installed as part of the DeveloperTools installation.  After installing DeveloperTools the wizards are available in Visual Studio.  After installing DeveloperTools, you *must* quit all Visual Studio instances before proceeding.


Autodesk Inventor Wizards for Microsoft Visual Studio
-----------------------------------------------------------------------

**********************************************************************************************************
Visual C++:
**********************************************************************************************************

1- Introduction
---------------

This wizard implements the templates for VC++ that help in generating Inventor AddIn 
applications. The wizard is integrated into Microsoft Visual Studio (15.0, 16.0 and 17.0). In order to 
use the wizard, you would need to have one of these versions of Microsoft Visual Studio installed. 

2- Using the Wizard
-------------------

After DeveloperTools is installed, you will be able to use the wizards from a Visual Studio session,
select the "New Projects" menu, among the templates that are displayed, there should be a 
"Autodesk Inventor AddIn" template. Selecting this template to create a project will add all the 
necessary files containing the source code to create an Inventor AddIn.

The *AddInServer.cpp/h files contain the class that implements the ApplicationAddInServer 
interface, which is required by all Inventor AddIns. This class also implements a rgs
file to add and remove the Inventor required registry settings (the communication between 
the AddIn and Inventor is via COM. Inventor recognizes an AddIn based on these registry 
settings, hence, these settings are required).

Note: If you encounter a dialog saying:"Platform 'x64' was not found" when you create a Visual C++ project with this Inventor Addin wizard, that indicates you need to update the Visual Studio to support x64 compilers and tools. Solution is in Add or Remove Programs panel, click Change/Remove button for the Visual Studio, and on the Visual Studio Maintenance Mode panel choose to Add or Remove Features, and for Language Tools of Visual C++ check the optional button of 'X64 Compilers and Tools' and update this feature.

3- The Visual C++ AddIn
-----------------------

The Visual C++ AddIn is accessible through a toolbar only, which should appear automatically 
when you first run Visual C++ after having installed the Wizards. If not, go to the 
Visual C++ 'AddIn Manager' dialog, and load the Inventor Visual C++ AddIn.

4- The ATL wizards
------------------

The Inventor Event Wizard is responsible for creating new Event Sink ATL Class. The Inventor Event 
Sink ATL Class wizard will create event sink classes for you so you can sink Inventor events easily.
Note that this wizard does create new classes for sinking events but does not create code to actually 
sink events. This means you will still be responsible for creating instances of those classes and 
attach/detach them to the event manager objects of Inventor. Examples are provided in comments for 
each event sink classes created. To access the Inventor Event Wizard right click project, choose 'Add->New Item...' command and in the Add New Item dialog under the Visual C++ category you can find Inventor 20xx sub-category, and choose one proper version if you have multiple options, and select 'Autodesk Inventor Events Object' item to add.


**********************************************************************************************************
Visual Basic.NET, Visual C#.NET:
**********************************************************************************************************

1- Introduction
---------------

This wizard implements the templates for VC#.NET and VB.NET that help in generating Inventor AddIn 
applications. The wizard is integrated into Microsoft Visual Studio .NET (15.0, 16.0 and 17.0). In order to 
use the wizard, you would need to have one of these versions of Microsoft Visual Studio installed. 

Note: Since Inventor 2025 the .Net 8 is introduced to replace .Net Framework, the Visual Studio 17.8.3 version or higher version is required to make use of the updated Inventor Addin Wizards for VS 2022.

2- Using the Wizard
-------------------

After DeveloperTools is installed, you will be able to use it from a Visual Studio .NET session,
select the "New Projects" menu, among the templates that are displayed, there should be a 
"Autodesk Inventor AddIn" template for both VC#.NET and VB.NET projects. Selecting this template to create a
project will add all the necessary files containing the source code to create an Inventor AddIn.

The StandardAddInServer.cs (for VC#.NET) and StandardAddInServer.vb (for VB.NET) files contain the 
class that implements the ApplicationAddInServer interface, which is required by all Inventor 
AddIns. This class also implements the static methods to add and remove the Inventor required
registry settings (the communication between the AddIn and Inventor is via COM Interop and 
Inventor recognizes an AddIn based on these registry settings, hence, these settings are 
required).


**********************************************************************************************************
Visual Studio Express(VB/VC# .Net)
**********************************************************************************************************

If you just use Visual Studio Express(VB/VC# .Net) version to create Inventor addin with this wizard, please make sure that you have the Windows SDK installed, eitherwise you may receive an alert when you compile the addin project.
