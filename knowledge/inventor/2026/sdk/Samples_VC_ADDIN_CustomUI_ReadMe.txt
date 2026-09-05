
  CustomUI sample
  ==================
  DESCRIPTION
  This builds an AddIn dll that demonstrates Inventor UI Customization API. 

  The AddIn puts up the follwing UI elements:
  1) Creates four button definitions (with icons) called "Command 1", "Command 2", "Command 3" and "Command 4" that serve to receive 
      button click callbacks and run commands corresponding to each of these four buttons in "Sketch" tab "Format" panel in part sketch environment only.
  2) Creates its own tab called "CustomUI" and the panel called "CustomUI" that has four controls (each representing one of the four button definitions).
      This tab is added for the part environment.
  3) Intercepts the OnContextMenu event and adds the commands "Command 1" and "Command 4"
      and a sub-popup with a caption "Command PopUp1" that groups "Command 2" and "Command 3" to the context menu.
      
      
  Language/Compiler: VC++ 
  Server: Inventor Server.

  How to Create This Sample: Build CustomUI Project. This is a self registering dll.