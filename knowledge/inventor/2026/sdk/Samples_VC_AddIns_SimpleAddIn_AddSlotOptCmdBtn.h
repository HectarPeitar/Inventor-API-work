#pragma once
#include "commandbutton.h"

class CAddSlotOptionCommandButton :
	public CCommandButton
{
public:
	
	//----- ButtonDefinitionSink
	STDMETHOD(ButtonDefinitionEvents_OnExecute) (NameValueMap *pContext);
};
