using System;
using System.Runtime.InteropServices;
using Inventor;

namespace CustomCommand
{
	internal class ChangeProcessor
	{	
		private Inventor.ChangeProcessor m_changeProcessor;

		//parent ChangeRequest object
		private CustomCommand.ChangeRequest m_parentRequest;

		private ChangeProcessorSink_OnExecuteEventHandler m_changeProcessor_OnExecute_Delegate;
		private ChangeProcessorSink_OnTerminateEventHandler m_changeProcessor_OnTerminate_Delegate; 
	
		public ChangeProcessor()
		{
			m_changeProcessor = null;
			m_parentRequest = null;
		}
		
		public void Connect(Application application, object changeDefinition, Inventor._Document document)
		{
			//get the change manager object
			ChangeManager changeManager = application.ChangeManager;

			//get the change definitions collection for this AddIn
			ChangeDefinitions changeDefinitions = changeManager["{140918FF-668A-435a-BD5E-57EF81CA5C5D}"];

			//create the change processor associated with the change definition
			m_changeProcessor = changeDefinitions[changeDefinition].CreateChangeProcessor();

			//connect event handler in order to receive change processor events
			m_changeProcessor_OnExecute_Delegate = new ChangeProcessorSink_OnExecuteEventHandler(ChangeProcessorEvents_OnExecute);
			m_changeProcessor.OnExecute += m_changeProcessor_OnExecute_Delegate;

			m_changeProcessor_OnTerminate_Delegate = new ChangeProcessorSink_OnTerminateEventHandler(ChangeProcessorEvents_OnTerminate);
			m_changeProcessor.OnTerminate += m_changeProcessor_OnTerminate_Delegate;

			//execute the change processor
			m_changeProcessor.Execute(document);
		}

		public void Disconnect()
		{
			//disconnect change processor events sink
			if (m_changeProcessor != null)
			{
				m_changeProcessor.OnExecute -= m_changeProcessor_OnExecute_Delegate;
				m_changeProcessor.OnTerminate -= m_changeProcessor_OnTerminate_Delegate;

				m_changeProcessor = null;
			}
		}

		public void SetParentRequest(CustomCommand.ChangeRequest parentRequest)
		{
			//store the parent request object
			m_parentRequest = parentRequest;
		}

		//-----------------------------------------------------------------------------
		//----- Implementation of ChangeProcessor Events sink methods
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		public void ChangeProcessorEvents_OnExecute (Inventor._Document document, NameValueMap context, ref bool succeeded)
		{
			m_parentRequest.OnExecute(document, context, succeeded);
		}

		//-----------------------------------------------------------------------------
		public void ChangeProcessorEvents_OnTerminate ()
		{	
			m_parentRequest.Terminate();
		}				
	}
}
