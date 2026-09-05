//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
//----- Inventor Utils
//-----------------------------------------------------------------------------
#pragma once

#define Wizard_Version "18.0.0.0"

//-----------------------------------------------------------------------------
#ifdef _AFXDLL
#include "AfxInventor.h"
#endif
#include "CATIDs.h"
#include "ClipboardFormats.h"
//#include "CommandNames.h"
#include "DispatchUtils.h"
#include "DocCLSIDs.h"
#include "EnvInternalNames.h"
#include "EventsDispIds.h"
#include "MiscConstants.h"
#include "PropFMTIDs.h"
#include "PropVariantProperty.h"
#include "SafeArrayUtil.h"
#include "ServerCLSIDs.h"
#include "ToolBarInternalNames.h"

//-----------------------------------------------------------------------------
//----- Commands
//-----------------------------------------------------------------------------
#define DECLARE_INV_COMMAND_MAP(className) \
public: \
	typedef HRESULT (className::*INV_PCMD) (void) ; \
	struct INV_CMD_ENTRY \
	{ \
		long ID ; \
		bool bTransaction ; \
		INV_PCMD pCommandMethod ; \
	} ; \
private: \
	static const struct INV_CMD_ENTRY mAddInCommandMap [] ;

#define BEGIN_INV_COMMAND_MAP(className) \
	const struct className::INV_CMD_ENTRY className::mAddInCommandMap [] = \
	{
#define INV_COMMAND(ID, TR, FCT) \
	{ ID, TR, (INV_PCMD)&FCT },
#define END_INV_COMMAND_MAP() \
		{ -1, false, NULL } \
	} ;

#define CREATE_INV_COMMAND(name, ID, inTools, obj, visible, enabled, tooltip, desc) \
	{ \
		HRESULT hr##ID## ; \
		hr##ID## =m_pAddInSite->CreateCommand (name, ID, CComVariant((bool)inTools), &obj) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =obj->put_ToolTipText (tooltip) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =obj->put_DescriptionText (desc) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =obj->put_Visible (visible ? VARIANT_TRUE : VARIANT_FALSE) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =obj->put_Enabled (enabled ? VARIANT_TRUE : VARIANT_FALSE) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
	}
	
#define CREATE_INV_COMMAND_SHORT(name, ID, inTools, obj) \
	CREATE_INV_COMMAND(name, ID, inTools, obj, true, true, L"", L"")

#define CREATE_INV6_COMMAND(classname, name, ID, dispName, enabled, tooltip, desc) \
	{ \
		HRESULT hr##ID## ; \
		hr##ID## =CComObject<C##classname##CommandHandler>::CreateInstance (&m_##name##Hdlr) ; \
		ATLASSERT ( SUCCEEDED( hr##ID## ) && m_##name##Hdlr != NULL ) ; \
		m_##name##Hdlr->AddRef () ; \
		m_##name##Hdlr->m_pAddInServer =this ; \
		m_##name##Hdlr->m_nCommandID =ID ; \
		hr##ID## =m_pAddInSite->CreateButtonDefinitionHandler ( \
			CComBSTR ( L#classname L"." L#name ), kShapeEditCmdType, CComBSTR (dispName), \
			CComVariant (desc), CComVariant (tooltip), \
			CComVariant (), CComVariant (), &m_##name##Cmd \
		) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =m_##name##Cmd->put_Enabled (enabled ? VARIANT_TRUE : VARIANT_FALSE) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =m_##name##Hdlr->DispEventAdvise (m_##name##Cmd) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		CComPtr<ControlDefinition> pBtnDef##ID## =NULL ; \
		hr##ID## =m_##name##Cmd->get_ControlDefinition (&pBtnDef##ID##) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		CComPtr<CommandBarControls> pCmdBarControls##ID## ; \
		hr##ID## =m_pAppToolBar->get_Controls (&pCmdBarControls##ID##) ; \
		ATLASSERT( SUCCEEDED( hr ) ) ; \
		hr##ID## =pCmdBarControls##ID##->Add (kBarControlButton, CComVariant (pBtnDef##ID##), CComVariant (), &m_##name##Ctrl) ; \
		ATLASSERT( SUCCEEDED( hr ) ) ; \
	}

#define CREATE_INV8_COMMAND(classname, name, ID, dispName, enabled, tooltip, desc, hIcon, cmdType) \
	{ \
		HRESULT hr##ID## ; \
		HICON h1##ID## =NULL, h2##ID## =NULL ; \
		CComPtr<IPictureDisp> pPictureDisp1##ID##, pPictureDisp2##ID## ; \
		CComVariant vtIcon1##ID##, vtIcon2##ID## ; \
		if ( hIcon != -1 ) { \
			PICTDESC pdesc1##ID## ; \
			pdesc1##ID##.cbSizeofstruct =sizeof (pdesc1##ID##) ; \
			pdesc1##ID##.picType =PICTYPE_ICON ; \
			h1##ID## =(HICON)::LoadImage (_Module.GetResourceInstance (), MAKEINTRESOURCE(hIcon), IMAGE_ICON, 15, 14, LR_LOADTRANSPARENT) ; \
			pdesc1##ID##.icon.hicon =h1##ID## ; \
			hr##ID## =::OleCreatePictureIndirect (&pdesc1##ID##, IID_IPictureDisp, FALSE, (LPVOID *)&pPictureDisp1##ID##) ; \
			ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
			vtIcon1##ID## =CComVariant (pPictureDisp1##ID##) ; \
			PICTDESC pdesc2##ID## ; \
			pdesc2##ID##.cbSizeofstruct =sizeof (pdesc2##ID##) ; \
			pdesc2##ID##.picType =PICTYPE_ICON ; \
			h2##ID## =(HICON)::LoadImage (_Module.GetResourceInstance (), MAKEINTRESOURCE(hIcon), IMAGE_ICON, 23, 21, LR_LOADTRANSPARENT) ; \
			pdesc2##ID##.icon.hicon =h2##ID## ; \
			hr##ID## =::OleCreatePictureIndirect (&pdesc2##ID##, IID_IPictureDisp, FALSE, (LPVOID *)&pPictureDisp2##ID##) ; \
			ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
			vtIcon2##ID## =CComVariant (pPictureDisp2##ID##) ; \
		} \
		hr##ID## =CComObject<C##classname##CommandHandler>::CreateInstance (&m_##name##Hdlr) ; \
		ATLASSERT ( SUCCEEDED( hr##ID## ) && m_##name##Hdlr != NULL ) ; \
		m_##name##Hdlr->AddRef () ; \
		m_##name##Hdlr->m_pAddInServer =this ; \
		m_##name##Hdlr->m_nCommandID =ID ; \
		hr##ID## =m_pAddInSite->CreateButtonDefinitionHandler ( \
			CComBSTR ( L#classname L"." L#name ), (CommandTypesEnum)(cmdType), CComBSTR (dispName), \
			CComVariant (desc), CComVariant (tooltip), \
			vtIcon1##ID##, vtIcon2##ID##, &m_##name##Cmd \
		) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =m_##name##Cmd->put_Enabled (enabled ? VARIANT_TRUE : VARIANT_FALSE) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =m_##name##Hdlr->DispEventAdvise (m_##name##Cmd) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		CComPtr<ControlDefinition> pBtnDef##ID## =NULL ; \
		hr##ID## =m_##name##Cmd->get_ControlDefinition (&pBtnDef##ID##) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		CComPtr<CommandBarControls> pCmdBarControls##ID## ; \
		hr##ID## =m_pAppToolBar->get_Controls (&pCmdBarControls##ID##) ; \
		ATLASSERT( SUCCEEDED( hr ) ) ; \
		hr##ID## =pCmdBarControls##ID##->Add (kBarControlButton, CComVariant (pBtnDef##ID##), CComVariant (), &m_##name##Ctrl) ; \
		ATLASSERT( SUCCEEDED( hr ) ) ; \
		if ( hIcon != -1 ) { \
			::DestroyIcon (h1##ID##) ; \
			::DestroyIcon (h2##ID##) ; \
		} \
	}

#define CREATE_INV9_COMMAND(classname, name, ID, dispName, enabled, tooltip, desc, hIcon, cmdType, cmdDisplayType, internalName, clientID) \
	{ \
		HRESULT hr##ID## ; \
		CComPtr<CommandManager> pCommandMgr##ID## ; \
		hr##ID## =m_pApplication->get_CommandManager (&pCommandMgr##ID##) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		CComPtr<ControlDefinitions> pControlDefs##ID## ; \
		hr##ID## =pCommandMgr##ID##->get_ControlDefinitions (&pControlDefs##ID##) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		HICON h1##ID## =NULL, h2##ID## =NULL ; \
		CComPtr<IPictureDisp> pPictureDisp1##ID##, pPictureDisp2##ID## ; \
		CComVariant vtIcon1##ID##, vtIcon2##ID## ; \
		if ( hIcon != -1 ) { \
			PICTDESC pdesc1##ID## ; \
			pdesc1##ID##.cbSizeofstruct =sizeof (pdesc1##ID##) ; \
			pdesc1##ID##.picType =PICTYPE_ICON ; \
			h1##ID## =(HICON)::LoadImage (_Module.GetResourceInstance (), MAKEINTRESOURCE(hIcon), IMAGE_ICON, 15, 14, LR_LOADTRANSPARENT) ; \
			pdesc1##ID##.icon.hicon =h1##ID## ; \
			hr##ID## =::OleCreatePictureIndirect (&pdesc1##ID##, IID_IPictureDisp, FALSE, (LPVOID *)&pPictureDisp1##ID##) ; \
			ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
			vtIcon1##ID## =CComVariant (pPictureDisp1##ID##) ; \
			PICTDESC pdesc2##ID## ; \
			pdesc2##ID##.cbSizeofstruct =sizeof (pdesc2##ID##) ; \
			pdesc2##ID##.picType =PICTYPE_ICON ; \
			h2##ID## =(HICON)::LoadImage (_Module.GetResourceInstance (), MAKEINTRESOURCE(hIcon), IMAGE_ICON, 23, 21, LR_LOADTRANSPARENT) ; \
			pdesc2##ID##.icon.hicon =h2##ID## ; \
			hr##ID## =::OleCreatePictureIndirect (&pdesc2##ID##, IID_IPictureDisp, FALSE, (LPVOID *)&pPictureDisp2##ID##) ; \
			ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
			vtIcon2##ID## =CComVariant (pPictureDisp2##ID##) ; \
		} \
		LPOLESTR ppsz =NULL ; \
		hr##ID## =::StringFromCLSID (clientID, &ppsz) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =pControlDefs##ID##->AddButtonDefinition (CComBSTR (dispName), CComBSTR (internalName), (CommandTypesEnum)(cmdType), CComVariant(ppsz), CComBSTR (desc), CComBSTR (tooltip), vtIcon1##ID##, vtIcon2##ID##, (ButtonDisplayEnum)(cmdDisplayType), &m_##name##Cmd) ; \
		::CoTaskMemFree (ppsz) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =m_##name##Cmd->put_Enabled (enabled ? VARIANT_TRUE : VARIANT_FALSE) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		hr##ID## =CComObject<C##classname##CommandHandler>::CreateInstance (&m_##name##Hdlr) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) && m_##name##Hdlr != NULL ) ; \
		m_##name##Hdlr->AddRef () ; \
		m_##name##Hdlr->m_pAddInServer =this ; \
		m_##name##Hdlr->m_nCommandID =ID ; \
		hr##ID## =m_##name##Hdlr->DispEventAdvise (m_##name##Cmd) ; \
		ATLASSERT( SUCCEEDED( hr##ID## ) ) ; \
		if ( hIcon != -1 ) { \
			::DestroyIcon (h1##ID##) ; \
			::DestroyIcon (h2##ID##) ; \
		} \
	}

#define DELETE_INV_COMMAND(obj) \
	{ \
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ; \
		HRESULT hr =obj->Delete () ; \
		ATLASSERT( SUCCEEDED( hr ) ) ; \
	}

#define DELETE_INV6_COMMAND(name) \
	{ \
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ; \
		HRESULT hr =m_##name##Hdlr->DispEventUnadvise (m_##name##Cmd) ; \
		ATLASSERT( SUCCEEDED( hr ) ) ; \
		m_##name##Hdlr->Release () ; \
		m_##name##Hdlr =NULL ; \
		m_##name##Cmd.Release () ; \
		m_##name##Cmd =NULL ; \
	}

#define DELETE_INV8_COMMAND(name) \
	DELETE_INV6_COMMAND(name)

#define DELETE_INV9_COMMAND(name) \
	{ \
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ; \
		HRESULT hr_x_ =m_##name##Hdlr->DispEventUnadvise (m_##name##Cmd) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		hr_x_ =m_##name##Cmd->Delete () ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		m_##name##Cmd.Release () ; \
		m_##name##Cmd =NULL ; \
		m_##name##Hdlr->Release () ; \
		m_##name##Hdlr =NULL ; \
	}

#define CALL_INV_COMMAND(CmdID) \
	for ( int iInvCmdIter =0 ;; iInvCmdIter++ ) \
	{ \
		if ( mAddInCommandMap [iInvCmdIter].ID == -1 || mAddInCommandMap [iInvCmdIter].pCommandMethod == NULL ) \
			break ; \
		if ( mAddInCommandMap [iInvCmdIter].ID == CmdID ) \
			hResult =(this->*mAddInCommandMap [iInvCmdIter].pCommandMethod) () ; \
	}

#define CREATE_INV8_APPTOOLBAR(pToolBar, name, internalName) \
	{ \
		CComPtr<EnvironmentBaseCollection> pEnvDefs_x_ ; \
		HRESULT hr_x_ =m_pApplication->get_EnvironmentBaseCollection (&pEnvDefs_x_) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		CComPtr<CommandBarBaseCollection> pCmdBarDefs_x_ ; \
		hr_x_ =pEnvDefs_x_->get_CommandBarBaseCollection (&pCmdBarDefs_x_) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		hr_x_ =pCmdBarDefs_x_->Add (CComBSTR (name), CComVariant (internalName), &pToolBar) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
	}

#define CREATE_INV9_APPTOOLBAR(pToolBar, name, internalName, clientID) \
	if ( FirstTime != VARIANT_FALSE ) \
	{ \
		CComPtr<UserInterfaceManager> pUserInterfaceMgr_x_ ; \
		HRESULT hr_x_ =m_pApplication->get_UserInterfaceManager (&pUserInterfaceMgr_x_) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		CComPtr<CommandBars> pCmdBars_x_ ; \
		hr_x_ =pUserInterfaceMgr_x_->get_CommandBars (&pCmdBars_x_) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		LPOLESTR ppsz =NULL ; \
		::StringFromCLSID (clientID, &ppsz) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		hr_x_ =pCmdBars_x_->Add (CComBSTR (name), CComBSTR (internalName), kRegularCommandBar, CComVariant (ppsz), &pToolBar) ; \
		::CoTaskMemFree (ppsz) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
	} else { \
		CComPtr<UserInterfaceManager> pUserInterfaceMgr_x_ ; \
		HRESULT hr_x_ =m_pApplication->get_UserInterfaceManager (&pUserInterfaceMgr_x_) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		CComPtr<CommandBars> pCmdBars_x_ ; \
		hr_x_ =pUserInterfaceMgr_x_->get_CommandBars (&pCmdBars_x_) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		LPOLESTR ppsz =NULL ; \
		::StringFromCLSID (clientID, &ppsz) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		pCmdBars_x_->get_Item (CComVariant (internalName), &pToolBar) ; \
	}

#define ADDCOMMAND_TO_APPTOOLBAR(pToolBar, name) \
	if ( FirstTime != VARIANT_FALSE ) \
	{ \
		CComPtr<CommandBarControls> pCmdBarControls ; \
		HRESULT hr_x_ =pToolBar->get_Controls (&pCmdBarControls) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
		CComPtr<CommandBarControl> pCmdBarCtrl ; \
		hr_x_ =pCmdBarControls->AddButton (m_##name##Cmd, 0, &pCmdBarCtrl) ; \
		ATLASSERT( SUCCEEDED( hr_x_ ) ) ; \
	}
