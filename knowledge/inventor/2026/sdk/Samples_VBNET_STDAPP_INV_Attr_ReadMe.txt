  Attributes Sample
  =================

  DESCRIPTION

  Show creation and query of attributes in Autodesk Inventor.

  This is a sample that demonstrates the ability to create, query, save and delete attribute information in Autodesk Inventor. 
  This sample creates a part file (Attributes Sample.ipt) with rectangular block. The UI has 7 buttons which performs the following functions:
  
  	Set Attribute :- Attaches an attribute to a selected entity( face, edge or vertex).
   
  	Get Attributes :- Queries the attribute(if any) of the selected entity. 
  
  	Delete Attribute :- Deletes the attribute (if any) on the selected entity.

  	Save :- Saves the Attribute Sample.ipt document closes it and then opens it immediately.

  	Query Entities :- Search mechanism that highlights the faces that match the specified attribute value.
	
  	Clear :- Clear the highlights.

  	Close :- Ends the application.
  
  After the sample part file is created the user has to select an entity (face, edge or vertex) in the Part document. 
  After selecting an entity, enter the attributes information in the enter attributes text box and click set attribute button.
  On selecting the same entity again and clicking on the get attribute button, the entities attribute information
  gets displayed. If an entity does not have any attributes the get attribute command and the delete attribute command
  would pop up a message box saying this entity has no attributes set. Hence these two commands would work only 
  for those selected entities which have attribute information stored in them. To save the attribute information 
  on to the disk, click on the save button. Save closes the document and then immediately opens it. This way the user
  can query attributes across sessions, by selecting an entity and then clicking on the get attribute command.
  To modify the attribute value of an entity, the user would have select the entity, enter the new information,
  in the attributes text box and click set attribute button. This would modify the attribute information, which can be verified 
  by clicking on get attribute for the same entity. There is also a provision to query for those entities which have a certain 
  specified attribute. Enter the search string in the query text box and click on the query entities button. 
  This would the highlight those faces whose attribute value matches the search string. Click clear button will clear the 
  highlight.

  Language/Compiler: VB.Net.
  Server: Inventor Server.

  How to create this sample: Build Attributes Sample Project.

  Executable: Attributes.exe

  How to run this sample: Start Inventor. Then run Attributes.exe. A part document with a rectangular block would pop up. Select any entities and add attribute information.
  



