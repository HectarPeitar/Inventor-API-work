// ThumbnailProvider.h : Declaration of the CThumbnailProvider

#pragma once
#include "resource.h"       // main symbols

#include "InventorThumbnailView.h"

// CThumbnailProvider

class ATL_NO_VTABLE CThumbnailProvider : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CThumbnailProvider, &CLSID_ThumbnailProvider>,
	public IDispatchImpl<IThumbnailProvider, &IID_IThumbnailProvider, &LIBID_InventorThumbnailViewLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CThumbnailProvider()
	{
	}

	virtual ~CThumbnailProvider()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_THUMBNAILPROVIDER)


BEGIN_COM_MAP(CThumbnailProvider)
	COM_INTERFACE_ENTRY(IThumbnailProvider)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(GetThumbnail)(BSTR FullFileName, IPictureDisp** ppPicture);

private:
	// Get IPictureDisp data from clipdata
	HRESULT GetIPictureDispFromClipdata(CLIPDATA* pClipdata, IPictureDisp** ppPicture);
};

OBJECT_ENTRY_AUTO(__uuidof(ThumbnailProvider), CThumbnailProvider)
