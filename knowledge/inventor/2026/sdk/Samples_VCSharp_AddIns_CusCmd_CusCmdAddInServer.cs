using System;
using System.Runtime.InteropServices;
using Inventor;
using Microsoft.Win32;

namespace CustomCommand
{
	/// <summary>
	/// This is the primary AddIn Server class that implements the ApplicationAddInServer interface
	/// that all Inventor AddIns are required to implement. The communication between Inventor and
	/// the AddIn is via the methods on this interface.
	/// </summary>
	[GuidAttribute("140918FF-668A-435a-BD5E-57EF81CA5C5D")]
	public class CustomCommandAddInServer : ApplicationAddInServer
	{
		#region Data Members
				
		//Inventor application object
		private Inventor.Application m_inventorApp;

		//Rack Face command
		private RackFaceCmd m_rackFaceCmd;
		
		private string m_addInCLSIDString;

        //user interface event
        private UserInterfaceEvents m_userInterfaceEvents;

        //event handler delegates
        private Inventor.UserInterfaceEventsSink_OnResetCommandBarsEventHandler UserInterfaceEventsSink_OnResetCommandBarsEventDelegate;
        private Inventor.UserInterfaceEventsSink_OnEnvironmentChangeEventHandler UserInterfaceEventsSink_OnEnvironmentChangeEventDelegate;
        private Inventor.UserInterfaceEventsSink_OnResetRibbonInterfaceEventHandler UserInterfaceEventsSink_OnResetRibbonInterfaceEventDelegate;            


		#endregion

		public CustomCommandAddInServer()
		{
			m_inventorApp = null;
			m_rackFaceCmd = null;
		}

		#region ApplicationAddInServer Members

		public void Activate(ApplicationAddInSite addInSiteObject, bool firstTime)
		{
			try
			{
				//the Activate method is called by Inventor when it loads the addin
				//the AddInSiteObject provides access to the Inventor Application object
				//the FirstTime flag indicates if the addin is loaded for the first time

				//initialize AddIn members
				m_inventorApp = addInSiteObject.Application;

                //initialize event delegates
                m_userInterfaceEvents = m_inventorApp.UserInterfaceManager.UserInterfaceEvents;

                UserInterfaceEventsSink_OnResetCommandBarsEventDelegate = new UserInterfaceEventsSink_OnResetCommandBarsEventHandler(UserInterfaceEvents_OnResetCommandBars);
                m_userInterfaceEvents.OnResetCommandBars += UserInterfaceEventsSink_OnResetCommandBarsEventDelegate;

                UserInterfaceEventsSink_OnEnvironmentChangeEventDelegate = new UserInterfaceEventsSink_OnEnvironmentChangeEventHandler(UserInterfaceEvents_OnEnvironmentChange);
                m_userInterfaceEvents.OnEnvironmentChange += UserInterfaceEventsSink_OnEnvironmentChangeEventDelegate;

                UserInterfaceEventsSink_OnResetRibbonInterfaceEventDelegate = new UserInterfaceEventsSink_OnResetRibbonInterfaceEventHandler(UserInterfaceEventsSink_OnResetRibbonInterface);
                m_userInterfaceEvents.OnResetRibbonInterface += UserInterfaceEventsSink_OnResetRibbonInterfaceEventDelegate;

				//retrieve the GUID for this class
				GuidAttribute addInCLSID;
				addInCLSID = (GuidAttribute)GuidAttribute.GetCustomAttribute(typeof(CustomCommandAddInServer), typeof(GuidAttribute));			
				m_addInCLSIDString = "{" + addInCLSID.Value + "}";

				//create the command button(s)
				//create instance of the "Rack Face" command class 
				m_rackFaceCmd = new RackFaceCmd();

				//create the "Rack Face" button
                m_rackFaceCmd.CreateButton(m_inventorApp, "Rack Face", "Autodesk:CustomCommand:RackFaceCmd", CommandTypesEnum.kShapeEditCmdType, m_addInCLSIDString, "Creates a rack feature", "Creates a rack feature", "", "", ButtonDisplayEnum.kDisplayTextInLearningMode, false);

				//create change definitons
				//get the change manager
				ChangeManager changeManager = m_inventorApp.ChangeManager;
				
				//create the change definitions collection for this AddIn
				ChangeDefinitions changeDefinitions = changeManager.Add(m_addInCLSIDString);

				//create the "Rack Face" change definition
                ChangeDefinition rackFaceChangeDefinition = changeDefinitions.Add("Autodesk:CustomCommand:RackFaceChgDef", "Rack Face");

                //create the command category
                CommandCategory rackFaceCmdCategory = m_inventorApp.CommandManager.CommandCategories.Add("Rack Face", "Autodesk:CustomCommand:RackFaceCmdCat", m_addInCLSIDString);
                rackFaceCmdCategory.Add(m_rackFaceCmd.ButtonDefinition);

				if (firstTime == true)
				{
					//add the button
					UserInterfaceManager userInterfaceMgr = m_inventorApp.UserInterfaceManager;

                    // Create the UI for classic interface
                    if (userInterfaceMgr.InterfaceStyle == InterfaceStyleEnum.kClassicInterface)
                    {
                        //get the commandbars collection
                        CommandBars commandBars;
                        commandBars = userInterfaceMgr.CommandBars;

                        //get the part features toolbar
                        Inventor.CommandBar partFeaturesToolbar;
                        partFeaturesToolbar = commandBars["PMxPartFeatureCmdBar"];

                        //add the "Rack Face" button to the toolbar
                        partFeaturesToolbar.Controls.AddButton(m_rackFaceCmd.ButtonDefinition, 0);
                    }
                    else // Create the UI for the ribbon interface
                    {
                         // Get Part Ribbon
                        Ribbons ribbons = userInterfaceMgr.Ribbons;
                        Ribbon partRibbon = ribbons["Part"];

                        // Get Modify Panel
                        RibbonTab modelRibbonTab = partRibbon.RibbonTabs["id_TabModel"];
                        RibbonPanel modifyRibbonPanel = modelRibbonTab.RibbonPanels["id_PanelP_ModelModify"];

                        // Add the "Rack Face" button to the Panel
                        modifyRibbonPanel.CommandControls.AddButton(m_rackFaceCmd.ButtonDefinition,
                                                                    false,
                                                                    true,
                                                                    "",
                                                                    false);
                    }
				}
			}
			catch (Exception ex)
			{
				System.Windows.Forms.MessageBox.Show(ex.ToString());
			}
		}

		public void Deactivate()
		{
			//the Deactivate method is called by Inventor when the AddIn is unloaded
			//the AddIn will be unloaded either manually by the user or
			//when the Inventor session is terminated

            m_userInterfaceEvents.OnResetCommandBars -= UserInterfaceEventsSink_OnResetCommandBarsEventDelegate;
            m_userInterfaceEvents.OnEnvironmentChange -= UserInterfaceEventsSink_OnEnvironmentChangeEventDelegate;
            m_userInterfaceEvents.OnResetRibbonInterface -= UserInterfaceEventsSink_OnResetRibbonInterfaceEventDelegate;

            UserInterfaceEventsSink_OnResetCommandBarsEventDelegate = null;
            UserInterfaceEventsSink_OnEnvironmentChangeEventDelegate = null;
            UserInterfaceEventsSink_OnResetRibbonInterfaceEventDelegate = null;
            m_userInterfaceEvents = null;

			//remove the command button(s)
			//remove the "Rack Face" button
			m_rackFaceCmd.RemoveButton();

			m_rackFaceCmd = null;
	
			//delete change definition(s)
			//get the change manager
			ChangeManager changeManager = m_inventorApp.ChangeManager;

			//get the change definitions collection
			ChangeDefinitions changeDefinitions = changeManager[m_addInCLSIDString];

			//get the "Rack Face" change definition
            ChangeDefinition rackFaceChangeDefinition = changeDefinitions["Autodesk:CustomCommand:RackFaceChgDef"];

			//delete the "Rack Face" change definition
			rackFaceChangeDefinition.Delete();

			Marshal.ReleaseComObject(m_inventorApp);
			m_inventorApp = null;

			GC.WaitForPendingFinalizers();
			GC.Collect();
		}

		public void ExecuteCommand(int commandID)
		{
			//this method was used to notify when an AddIn command was executed
			//the CommandID parameter identifies the command that was executed
    
			//Note:this method is now obsolete, you should use the new
			//ControlDefinition objects to implement commands, they have
			//their own event sinks to notify when the command is executed
		}

		public object Automation
		{
			//if you want to return an interface to another client of this addin,
			//implement that interface in a class and return that class object 
			//through this property

			get
			{
				// TODO:  Add ApplicationAddInServer.Automation getter implementation
				return null;
			}
		}

		#endregion

        private void UserInterfaceEvents_OnResetCommandBars(ObjectsEnumerator commandBars, NameValueMap context)
        {
            try
            {
                CommandBar commandBar;
                for (int commandBarCt = 1; commandBarCt <= commandBars.Count; commandBarCt++)
                {
                    commandBar = (Inventor.CommandBar)commandBars[commandBarCt];
                    if (commandBar.InternalName == "PMxPartFeatureCmdBar")
                    {
                        //add "Rack Face" button back to the part features toolbar
                        commandBar.Controls.AddButton(m_rackFaceCmd.ButtonDefinition, 0);

                        return;
                    }
                }
            }
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.ToString());
            }
        }

        private void UserInterfaceEvents_OnEnvironmentChange(Inventor.Environment environment, EnvironmentStateEnum environmentState, EventTimingEnum beforeOrAfter, NameValueMap context, out HandlingCodeEnum handlingCode)
        {
            try
            {
                String envInternalName;
                envInternalName = environment.InternalName;

                if (envInternalName == "PMxPartEnvironment")
                {
                    //enable the "Rack Face" button when the part environment is activated or resumed
                    if (environmentState == EnvironmentStateEnum.kActivateEnvironmentState || environmentState == EnvironmentStateEnum.kResumeEnvironmentState)
                        m_rackFaceCmd.ButtonDefinition.Enabled = true;


                    //disable the "Rack Face" button when the part environment is terminated or suspended
                    if (environmentState == EnvironmentStateEnum.kTerminateEnvironmentState || environmentState == EnvironmentStateEnum.kSuspendEnvironmentState)
                        m_rackFaceCmd.ButtonDefinition.Enabled = false;
                }

            }
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.ToString());
            }
            handlingCode = HandlingCodeEnum.kEventNotHandled;
        }

        private void UserInterfaceEventsSink_OnResetRibbonInterface(NameValueMap context)
        {
            try
            {
                // Add the button to the Modify panel on Model tab in Part Ribbon
                UserInterfaceManager userInterfaceMgr = m_inventorApp.UserInterfaceManager;

                // Get Part Ribbon
                Ribbons ribbons = userInterfaceMgr.Ribbons;
                Ribbon partRibbon = ribbons["Part"];

                // Get Modify Panel
                RibbonTab modelRibbonTab = partRibbon.RibbonTabs["id_TabModel"];
                RibbonPanel modifyRibbonPanel = modelRibbonTab.RibbonPanels["id_PanelP_ModelModify"];

                // Add the "Rack Face" button to the Panel
                modifyRibbonPanel.CommandControls.AddButton(m_rackFaceCmd.ButtonDefinition,
                                                            false,
                                                            true,
                                                            "",
                                                            false);
            }
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.ToString());
            }
        }
	}
}