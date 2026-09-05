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

// [!output IMPL_FILE] : Implementation of [!output CLASS_NAME]

#include "stdafx.h"
#include "[!output HEADER_FILE]"


// [!output CLASS_NAME]

[!if !ATTRIBUTED]
[!if SUPPORT_ERROR_INFO]
STDMETHODIMP [!output CLASS_NAME]::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_[!output INTERFACE_NAME]
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
[!endif]
[!endif]

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDeleteKeyUp (ObjectsEnumerator *pSelectedEntities, SelectionDeviceEnum SelectionDevice, View *pView, NameValueMap *pAdditionalInfo, CommandBar *pCommandBar, HandlingCodeEnum *pHandlingCode)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDrag (DragStateEnum DragState, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView, NameValueMap *pAdditionalInfo, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnActivateCommand (BSTR CommandName, NameValueMap *pContext)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnTerminateCommand (BSTR CommandName, NameValueMap *pContext)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDoubleClick (ObjectsEnumerator *pSelectedEntities, SelectionDeviceEnum *pSelectionDevice, MouseButtonEnum *pButton, ShiftStateEnum *pShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView,  NameValueMap *pAdditionalInfo, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnPreSelect (IDispatch** PreSelectEntity, VARIANT_BOOL* DoHighlight, ObjectCollection** MorePreSelectEntities, SelectionDeviceEnum SelectionDevice, Point* ModelPosition, Point2d* ViewPosition, View* View)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnStopPreSelect (Point* ModelPosition, Point2d* ViewPosition, View* View)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnSelect (ObjectsEnumerator* JustSelectedEntities, ObjectCollection** MoreSelectedEntities, SelectionDeviceEnum SelectionDevice, Point* ModelPosition, Point2d* ViewPosition, View* View)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnUnSelect (ObjectsEnumerator* UnSelectedEntities, SelectionDeviceEnum SelectionDevice, Point* ModelPosition, Point2d* ViewPosition, View* View)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnRadialMarkingMenu (ObjectsEnumerator* SelectedEntities, SelectionDeviceEnum SelectionDevice, RadialMarkingMenu* RadialMenu, NameValueMap* AdditionalInfo)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnLinearMarkingMenu (ObjectsEnumerator* SelectedEntities, SelectionDeviceEnum SelectionDevice, CommandControls* LinearMenu, NameValueMap* AdditionalInfo)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnContextualMiniToolbar (ObjectsEnumerator* SelectedEntities, NameValueMap* DisplayedCommands, NameValueMap* AdditionalInfo)
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}