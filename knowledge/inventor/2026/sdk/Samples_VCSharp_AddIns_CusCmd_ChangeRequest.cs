using System;
using System.Runtime.InteropServices;
using Inventor;

namespace CustomCommand
{
	internal class ChangeRequest
	{
		private CustomCommand.ChangeProcessor m_changeProcessor;

		public ChangeRequest () 
		{
			m_changeProcessor = null;
		}

		virtual public void OnExecute (Document document, NameValueMap context, bool succeeded)
		{
			//
		}

		public void Execute(Application application, object changeDefinition, Inventor._Document document)
		{
			//create instance of ChangeProcessor class
			m_changeProcessor = new CustomCommand.ChangeProcessor();

			//set the parent to get the call back when change processor terminates
			m_changeProcessor.SetParentRequest(this);

			//connect change processor
			m_changeProcessor.Connect(application, changeDefinition, document);
		}

		public void Terminate()
		{
			//disconnect change processor
			if (m_changeProcessor != null)
			{
				m_changeProcessor.Disconnect();

				m_changeProcessor = null;
			}
		}
	}
}
