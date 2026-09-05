// stdafx.cpp : source file that includes just the standard includes
//	SampleCommand.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

	#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

//USE_INV_REGDLL_PRETRANSLATEMESSAGE()

BOOL __stdcall InvProcessPreTranslateMessage(LPMSG lpMsg)
{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
						
        return AfxGetThread()->PreTranslateMessage(lpMsg);

}

