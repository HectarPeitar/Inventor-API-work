/*
	Copyright © 1998 by Autodesk, Inc.


	DESCRIPTION

	This file contains utilities for dealing with common Dispatch operations


	HISTORY

	KK  :  6/20/01  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_DISPATCHUTILS_
#define _AUTODESK_INVENTOR_DISPATCHUTILS_

#include <atlbase.h>
enum ObjectTypeEnum;

namespace Rx
{
	// Obtain the object type (if the property exists) of a given object.
	//
	// E.g.:
	//
	// SurfaceBody* pBody = ...
	// ObjectTypeEnum type;
	// hr = Rx::GetObjectType(pBody, &type);
	//
	inline HRESULT GetObjectType(IDispatch* pDisp, ObjectTypeEnum* pResult)
	{
		if (!pDisp || !pResult)
			return E_INVALIDARG;

		CComVariant result;
		VariantClear(&result);
		DISPPARAMS params = {nullptr, nullptr, 0, 0};
		HRESULT hr = pDisp->Invoke(0x7f000003, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &result, nullptr, nullptr);
		if (hr == DISP_E_MEMBERNOTFOUND)
		{
			DISPID typeID;
			OLECHAR* name = const_cast<OLECHAR*>(OLESTR("Type"));
			hr = pDisp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &typeID);
			if (SUCCEEDED(hr))
				hr = pDisp->Invoke(typeID, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &result, nullptr, nullptr);
		}
		if (FAILED(hr))
			return hr;

		hr = result.ChangeType(VT_I4);
		if (FAILED(hr))
			return hr;

		*pResult = static_cast<ObjectTypeEnum>(V_I4(&result));

		return S_OK;
	}

	// Obtain the parent object (if the property exists) of a given object.
	//
	// E.g.:
	//
	// SurfaceBody* pBody = ...
	// CComPtr<IDispatch> pParent;
	// hr = Rx::GetParentObject(pBody, &pParent);
	//
	inline HRESULT GetParentObject(IDispatch* pDisp, IDispatch** ppResult)
	{
		if (!pDisp || !ppResult)
			return E_INVALIDARG;
		*ppResult = nullptr;

		CComVariant result;
		VariantClear(&result);
		DISPPARAMS params = {nullptr, nullptr, 0, 0};
		HRESULT hr = pDisp->Invoke(0x7f000002, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &result, nullptr, nullptr);
		if (FAILED(hr))
			return hr;

		hr = result.ChangeType(VT_DISPATCH);
		if (FAILED(hr))
			return hr;

		*ppResult = V_DISPATCH(&result);
		if (*ppResult)
			(*ppResult)->AddRef();

		return S_OK;
	}

	// Obtain the application object (if the property exists) of a given object.
	//
	// E.g.:
	//
	// AssemblyComponentDefinition* pDef = ...
	// CComPtr<IDispatch> pApp;
	// hr = Rx::GetApplicationObject(pDef, &pApp);
	//
	inline HRESULT GetApplicationObject(IDispatch* pDisp, IDispatch** ppResult)
	{
		if (!pDisp || !ppResult)
			return E_INVALIDARG;
		*ppResult = nullptr;

		CComVariant result;
		VariantClear(&result);
		DISPPARAMS params = {nullptr, nullptr, 0, 0};
		HRESULT hr = pDisp->Invoke(0x7f000001, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &result, nullptr, nullptr);
		if (FAILED(hr))
			return hr;

		hr = result.ChangeType(VT_DISPATCH);
		if (FAILED(hr))
			return hr;

		*ppResult = V_DISPATCH(&result);
		if (*ppResult)
			(*ppResult)->AddRef();

		return S_OK;
	}

	// Licenses the AddIn for the product.
	//
	// E.g.:
	//
	// ApplicationAddInSite* pAddInSite = ...
	// _bstr_t bstrLicenseKey("[license key]");
	// VARIANT_BOOL bSucceeded = VARIANT_FALSE;
	// hr = Rx::License(pAddInSite, bstrLicenseKey, &bSucceeded);
	// if (VARIANT_FALSE != bSucceeded) { ... }
	//
	inline HRESULT License(IDispatch* pDisp, BSTR bstrLicenseKey, VARIANT_BOOL* pResult)
	{
		if (!pDisp || !bstrLicenseKey || !pResult)
			return E_INVALIDARG;

		USES_CONVERSION;

		*pResult = VARIANT_FALSE;

		// The License method was not added until the Inventor LT product
		// edition was available.  So if this method does not exist that is an
		// anticipated case which indicates the product edition can not be Inventor LT
		// therefore an AddIn does not require licensing.  
		LPOLESTR licenseName = T2OLE(const_cast<LPTSTR>(_T("License")));
		DISPID licenseDispid = 0;
		HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, &licenseName, 1, LOCALE_SYSTEM_DEFAULT, &licenseDispid );
		if (FAILED(hr))
			return S_OK;

		CComVariant licenseKey(bstrLicenseKey);
		DISPPARAMS licenseKeyParams = { &licenseKey, nullptr, 1, 0};
		CComVariant result;
		::VariantClear( &result );
		hr = pDisp->Invoke(licenseDispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &licenseKeyParams, &result, nullptr, nullptr);
		if (FAILED(hr))
			return hr;

		hr = result.ChangeType(VT_I4);
		if (FAILED(hr))
			return hr;

		if (0x00012a02 == V_I4(&result))	// kAddInLicenseStatusAvailable
			*pResult = VARIANT_TRUE;

		return S_OK;
	}
}

#endif // _AUTODESK_INVENTOR_DISPATCHUTILS_
