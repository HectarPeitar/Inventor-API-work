using Inventor;
using System.Runtime.InteropServices;

namespace MyAddIn
{
    /// <summary>
    /// Startpunt van de Inventor add-in. Implementeer ApplicationAddInServer
    /// zoals vereist door de Inventor API.
    /// </summary>
    [Guid("00000000-0000-0000-0000-000000000000")] // TODO: vervang door een eigen gegenereerde GUID
    public class MyAddInServer : ApplicationAddInServer
    {
        private Inventor.Application _inventorApplication;

        public void Activate(ApplicationAddInSite addInSiteObject, bool firstTime)
        {
            _inventorApplication = addInSiteObject.InventorApplication;
            // TODO: UI-elementen, ribbon-knoppen, event-handlers registreren
        }

        public void Deactivate()
        {
            _inventorApplication = null;
        }

        public void ExecuteCommand(int commandID)
        {
            // Legacy command handling, meestal niet meer nodig bij ButtonDefinition-gebruik
        }

        public object Automation => null;
    }
}
