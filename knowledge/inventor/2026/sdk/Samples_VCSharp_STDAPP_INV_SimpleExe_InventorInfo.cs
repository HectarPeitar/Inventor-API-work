using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Inventor;

namespace SimpleExe
{
    public partial class InventorInfo : Form
    {
        public InventorInfo()
        {
            InitializeComponent();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
           this.Close();
        }

        private void InventorInfo_Load(object sender, EventArgs e)
        {
            Inventor.Application m_inventorApp = null;
            bool m_quitInventor = false;

            try
            {
                // Try to get an active instance of Inventor
                try
                {
                    m_inventorApp = MarshalCore.GetActiveObject("Inventor.Application") as Inventor.Application;
                }
                catch
                {
                }

                // If not active, create a new Inventor session
                if (m_inventorApp == null)
                {
                    Type inventorAppType = System.Type.GetTypeFromProgID("Inventor.Application");
                    m_inventorApp = System.Activator.CreateInstance(inventorAppType) as Inventor.Application;

                    m_quitInventor = true;
                }

                // Get some basic property information
                ListViewItem lstViewItem;
                lstViewItem = lstViewInvInfo.Items.Add("Caption");
                lstViewItem.SubItems.Add(m_inventorApp.Caption);

                lstViewItem = lstViewInvInfo.Items.Add("Sofware Version");
                lstViewItem.SubItems.Add(m_inventorApp.SoftwareVersion.DisplayName);

                lstViewItem = lstViewInvInfo.Items.Add("Install Path");
                lstViewItem.SubItems.Add(m_inventorApp.InstallPath);

                lstViewItem = lstViewInvInfo.Items.Add("Language");
                lstViewItem.SubItems.Add(m_inventorApp.LanguageName);

                lstViewItem = lstViewInvInfo.Items.Add("User Name");
                lstViewItem.SubItems.Add(m_inventorApp.UserName);

                lstViewItem = lstViewInvInfo.Items.Add("Active Color Scheme");
                lstViewItem.SubItems.Add(m_inventorApp.ActiveColorScheme.Name);

                lstViewItem = lstViewInvInfo.Items.Add("Active Project File");
                lstViewItem.SubItems.Add(m_inventorApp.FileLocations.FileLocationsFile);

                // Get the general options
                lstViewItem = lstViewInvInfo.Items.Add("Startup Project File");
                lstViewItem.SubItems.Add(m_inventorApp.GeneralOptions.StartupProjectFileName);

                lstViewItem = lstViewInvInfo.Items.Add("Startup Action");
                String startupAction = "";
                switch (m_inventorApp.GeneralOptions.StartupActionType)
                {
                    case StartupActionTypeEnum.kFileNewDialogStartupAction:
                        startupAction = "File New Dialog";
                        break;
                    case StartupActionTypeEnum.kFileOpenDialogStartupAction:
                        startupAction = "File Open Dialog";
                        break;
                    case StartupActionTypeEnum.kNewFileFromTemplateStartupAction:
                        startupAction = "New File From Template";
                        break;
                    case StartupActionTypeEnum.kNoStartupAction:
                        startupAction = "Nothing";
                        break;
                }
                lstViewItem.SubItems.Add(startupAction);

                // Get the general preferences
                ObjectsEnumeratorByVariant preferences;
                preferences = m_inventorApp.Preferences;

                foreach (Object userPrefObj in preferences)
                {
                    if (userPrefObj is GeneralPreferences)
                    {
                        GeneralPreferences generalPreferences;
                        generalPreferences = userPrefObj as GeneralPreferences;

                        lstViewItem = lstViewInvInfo.Items.Add("User Mode");
                        String multiUserMode = "";
                        switch (generalPreferences.MultiUserMode)
                        {
                            case MultiUserModeEnum.kSemiIsolatedMode:
                                multiUserMode = "Semi Isolated";
                                break;
                            case MultiUserModeEnum.kSemiIsolatedNoCheckoutMode:
                                multiUserMode = "Semi Isolated NoCheckout";
                                break;
                            case MultiUserModeEnum.kSharedMode:
                                multiUserMode = "Shared";
                                break;
                            case MultiUserModeEnum.kSingleUserMode:
                                multiUserMode = "Single User";
                                break;
                            case MultiUserModeEnum.kVaultMode:
                                multiUserMode = "Vault";
                                break;
                        }

                        lstViewItem.SubItems.Add(multiUserMode);

                        lstViewItem = lstViewInvInfo.Items.Add("Templates Directory");
                        lstViewItem.SubItems.Add(generalPreferences.TemplateDir);

                    }
                }
            }
            catch
            {
                System.Windows.Forms.MessageBox.Show("There was a problem getting some Inventor information", "Error", MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
            }
            finally
            {
                if (m_inventorApp != null && m_quitInventor == true)
                    m_inventorApp.Quit();

                m_inventorApp = null;
            }

        }
    }
}