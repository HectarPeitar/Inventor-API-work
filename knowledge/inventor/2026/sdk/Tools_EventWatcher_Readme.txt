EventWatcher
 ========

This tool allows you to monitor most of the events that Inventor provides through the API.
The events not supported by this utility are those that are associated with commands
(buttons, selection, mouse, etc.)

This tool is very useful for any program that needs to use any of Inventor's events.  It's
not always intuitive about which events are fired, when they're fired, or what information
is provided with the event.  This tool allows you to see what events are fired in response
to user interaction within Inventor.  Using this information you can best determine which
events to use and how to take advantage of them for your particular program.

To use the utility, Inventor must be running and then run EventWatcher.exe.  On the left
side of the dialog is a list of all of the events that can be monitored.  Selecting an
event shows the various input arguments on the right side of the dialog.  You can change
these arguments and for events that are fired before and after, the EventWatcher utility
will respond in the before event with the values you provide.

The event information is shown in the list box on the right side of the dialog.  As events
occurr in Inventor they will be added to the list.  You can use the "Clear List" button to
clear the list box.  The "Add Marker" button inserts a line at the bottom of the current list.
This allows you to mark a position so you can track it better as additional events are
reported and added to the list.

To edit and rebuild this sample:
1) Open the EventWatcher.vbproj project in Microsoft Visual Studio 2010.
2) Edit the source code and rebuild the project.

Language/Compiler: VB (.NET)/Microsoft Visual Studio 2010.
Server: Inventor