#pragma once
#include "commandbutton.h"

class CToggleSlotStateCommandButton :
	public CCommandButton
{
public:
	
	//----- ButtonDefinitionSink
	STDMETHOD(ButtonDefinitionEvents_OnExecute) (NameValueMap *pContext);
};