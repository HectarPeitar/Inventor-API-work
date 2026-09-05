//-----------------------------------------------------------------------------
//----- ChangeRequest.h : Declaration of the CChangeRequest
//-----------------------------------------------------------------------------
#ifndef _ChangeRequest_h_
#define _ChangeRequest_h_

#include "ChangeProcessor.h"

//-----------------------------------------------------------------------------
class CChangeRequest 
{
public:
	CChangeRequest () {

		m_pChangeProcessor = NULL;

	}

protected:
	//ChangeProcessor object
	CComObject<CChangeProcessor> *m_pChangeProcessor;
	
public:
	//change processor connection methods
	HRESULT Execute(Application *pApplication, VARIANT varChangeDefinition, Document* pDocument);
	HRESULT Terminate();

	//change processor callbacks
	virtual HRESULT ChangeProcessorEvents_OnExecute (Document *pDocument, NameValueMap *pContext, VARIANT_BOOL *pSucceeded) = 0;

} ;

//-----------------------------------------------------------------------------
#endif //----- _ChangeRequest_h_
