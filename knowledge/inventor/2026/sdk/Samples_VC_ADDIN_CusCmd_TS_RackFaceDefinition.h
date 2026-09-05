//-----------------------------------------------------------------------------
//----- RackFaceDefinition.h : Declaration of the CRackFaceDefinition
//-----------------------------------------------------------------------------
#ifndef _RackFaceDefinition_h_
#define _RackFaceDefinition_h_

#include "ChangeDefinition.h"
#include "RackFaceRequest.h"

//-----------------------------------------------------------------------------
class CRackFaceDefinition : public CChangeDefinition
{
public:
	CRackFaceDefinition () {

		m_pRackFaceRequest = NULL;
	}

	//----- ChangeDefinitionSink
	STDMETHOD(OnReplay) (NameValueMap *pContext, ChangeProcessorObject **ppResultProcessor);

	void TerminateReplay();

private:
	//rack face request
	CRackFaceRequest* m_pRackFaceRequest{ nullptr };
	
} ;

//-----------------------------------------------------------------------------
#endif //----- _RackFaceRequest_h_