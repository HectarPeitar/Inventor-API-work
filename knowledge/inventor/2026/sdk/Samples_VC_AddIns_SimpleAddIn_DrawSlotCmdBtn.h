#pragma once
#include "commandbutton.h"

class CDrawSlotCommandButton :
	public CCommandButton
{
public:

	//----- ButtonDefinitionSink
	STDMETHOD(ButtonDefinitionEvents_OnExecute) (NameValueMap *pContext);
};
