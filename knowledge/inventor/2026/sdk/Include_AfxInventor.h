#define INVENTOR_SDK_REGDLL_ADDIN_DLG_CONTSTRUCT _T("Autodesk Inventor AddIn Dialog Constructed")
#define INVENTOR_SDK_REGDLL_ADDIN_DLG_DESTRUCT   _T("Autodesk Inventor AddIn Dialog Destructed")
#define INVENTOR_SDK_REGDLL_PRETRANSLATEMESSAGE  "InvProcessPreTranslateMessage"


#define USE_INV_REGDLL_PRETRANSLATEMESSAGE() \
EXTERN_C __declspec(dllexport) BOOL __stdcall InvProcessPreTranslateMessage(LPMSG lpMsg) \
{ \
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); \
	return AfxGetThread()->PreTranslateMessage(lpMsg); \
} \
\

#define USE_INV_REGDLL_HANDLING(localClass) \
private: \
	class localClass\
	{ \
	public: \
		localClass() \
		{ \
			DWORD thrdID = GetCurrentThreadId(); \
			UINT invAddInDlgStartUp =  ::RegisterWindowMessage(INVENTOR_SDK_REGDLL_ADDIN_DLG_CONTSTRUCT); \
			\
			::PostThreadMessage(thrdID, invAddInDlgStartUp, (WPARAM)AfxGetInstanceHandle(), 0L);\
		}; \
		\
		~localClass() \
		{ \
			DWORD thrdID = GetCurrentThreadId(); \
			UINT invAddInDlgShutDown = ::RegisterWindowMessage(INVENTOR_SDK_REGDLL_ADDIN_DLG_DESTRUCT); \
			\
			::PostThreadMessage(thrdID, invAddInDlgShutDown, (WPARAM)AfxGetInstanceHandle(), 0L); \
		}; \
	} m_Inv##localClass; \
 \


