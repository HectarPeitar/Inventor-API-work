//-----------------------------------------------------------------------------
//----- ChangeProcessor.h : Declaration of the CChangeProcessor
//-----------------------------------------------------------------------------
#ifndef _ChangeProcessor_h_
#define _ChangeProcessor_h_

#include "resource.h"

class CChangeRequest;

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CChangeProcessor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<0, CChangeProcessor, &DIID_ChangeProcessorSink, &LIBID_Inventor, 1, 0>
{
public:
	CChangeProcessor () {

		m_pChangeProcessorObj = NULL;

		m_pParentRequest = NULL;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CChangeProcessor)
	END_COM_MAP()

	BEGIN_SINK_MAP(CChangeProcessor)
		SINK_ENTRY_EX (0, DIID_ChangeProcessorSink, ChangeProcessorSink_OnExecuteMeth, ChangeProcessorEvents_OnExecute)
		SINK_ENTRY_EX (0, DIID_ChangeProcessorSink, ChangeProcessorSink_OnTerminateMeth, ChangeProcessorEvents_OnTerminate)
	END_SINK_MAP()

private:
	//ChangeProcessor object
	CComPtr<ChangeProcessorObject> m_pChangeProcessorObj;

	//parent ChangeRequest object
	CChangeRequest *m_pParentRequest;

public:

	//----- ChangeProcessorSink
	STDMETHOD(ChangeProcessorEvents_OnExecute) (Document *pDocument, NameValueMap *pContext, VARIANT_BOOL *pSucceeded) ;
	STDMETHOD(ChangeProcessorEvents_OnTerminate) () ;

	HRESULT Connect(Application *pApplication, VARIANT varChangeDefinition, Document *pDocument);
	HRESULT Disconnect();

	void SetParentRequest(CChangeRequest *m_pParentRequest);

} ;

//-----------------------------------------------------------------------------
#endif //----- _ChangeProcessor_h_
