// ThumbnailProvider.cpp : Implementation of CThumbnailProvider

#include "StdAfx.h"
#include "ThumbnailProvider.h"


// CThumbnailProvider

//////////////////////////////////////////////////////////////////////////
#include <InitGuid.h>

// Inventor Summary Information Properties 
// Replaces (as from 6.0) use of Microsoft Property Set.
// {3D38DE39-0588-4c14-BB37-18F4D5DD31C7}
DEFINE_GUID(FMTID_SummaryInformation_Inventor, 
			0x3d38de39, 0x588, 0x4c14, 0xbb, 0x37, 0x18, 0xf4, 0xd5, 0xdd, 0x31, 0xc7);

#define OnErrorReturn(badsts, errorcode) if (badsts) return errorcode;
//////////////////////////////////////////////////////////////////////////

// Helper class and functions to help transfer png to bitmap
class Bitmap
{
public:
	Bitmap();
	~Bitmap();

	bool IsEmpty() const;
	void Clear();

	void Set(HMETAFILE metaFile, int width, int height);
	void Set(HBITMAP bitmap);

	const BITMAPINFO* GetBitmapInfo() const;
	void* GetBitmapData() const;

	// The caller is responsible for freeing the returned object.
	HMETAFILE GetMetaFile(int& width, int& height) const;

private:
	BITMAPINFO* m_gdiBitmapInfo{ nullptr };
	void* m_gdiBitmapData{ nullptr };
};

Bitmap::Bitmap() : m_gdiBitmapInfo(NULL), m_gdiBitmapData(NULL)
{
}

Bitmap::~Bitmap()
{
	Clear();
}

bool Bitmap::IsEmpty() const
{
	return !(m_gdiBitmapInfo && m_gdiBitmapData);
}

void Bitmap::Clear()
{
	delete[] reinterpret_cast<unsigned char*>(m_gdiBitmapInfo);
	delete[] static_cast<unsigned char*>(m_gdiBitmapData);
	m_gdiBitmapInfo = NULL;
	m_gdiBitmapData = NULL;
}

void Bitmap::Set(HMETAFILE metaFile, int width, int height)
{
	HDC screenDC = ::GetDC(NULL);
	HDC memoryDC = ::CreateCompatibleDC(screenDC);
	HBITMAP bitmap = NULL;

	if (memoryDC)
	{
		bitmap = ::CreateCompatibleBitmap(screenDC, width, height);

		if (bitmap)
		{
			SIZE size;
			HGDIOBJ oldBitmap = ::SelectObject(memoryDC, bitmap);
			int mapMode = ::SetMapMode(memoryDC, MM_ANISOTROPIC);
			::SetViewportExtEx(memoryDC, width, height, &size);
			RECT rect = { 0, 0, width, height };

			// FillSolidRect
			COLORREF color = ::SetBkColor(memoryDC, RGB(255, 255, 255));
			::ExtTextOut(memoryDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
			::SetBkColor(memoryDC, color);

			::PlayMetaFile(memoryDC, metaFile);

			::SetViewportExtEx(memoryDC, size.cx, size.cy, &size);
			::SetMapMode(memoryDC, mapMode);
			::SelectObject(memoryDC, oldBitmap);
		}
		::DeleteDC(memoryDC);
	}

	::ReleaseDC(NULL, screenDC);

	if (bitmap)
	{
		Set(bitmap);
		::DeleteObject(bitmap);
	}
	else
		Clear();
}

static unsigned int BitmapInfoSize(const BITMAPINFO* gdiBitmapInfo)
{
	unsigned int size = gdiBitmapInfo->bmiHeader.biSize;
	switch (gdiBitmapInfo->bmiHeader.biBitCount)
	{
	case 1:
	case 2:
	case 4:
	case 8:
		size += ((unsigned int)gdiBitmapInfo->bmiHeader.biBitCount << 1) * sizeof(RGBQUAD);
		break;
	case 24:
		size += (gdiBitmapInfo->bmiHeader.biClrUsed ? gdiBitmapInfo->bmiHeader.biClrUsed : 1) * sizeof(RGBQUAD);
		break;
	case 16:
	case 32:
		switch (gdiBitmapInfo->bmiHeader.biCompression)
		{
		case BI_BITFIELDS:
			size += 3 * sizeof(RGBQUAD); // color masks
			break;
		case BI_RGB:
		default:
			size += (gdiBitmapInfo->bmiHeader.biClrUsed ? gdiBitmapInfo->bmiHeader.biClrUsed : 1) * sizeof(RGBQUAD); // 1 for NULL
			break;
		}
		break;
	default:
		return 0;
	}
	return size;
}

static unsigned int BitmapDataSize(const BITMAPINFO* gdiBitmapInfo)
{
	unsigned int size = gdiBitmapInfo->bmiHeader.biSizeImage;
	if (!size)
	{
		int width = gdiBitmapInfo->bmiHeader.biWidth; 
		int height = gdiBitmapInfo->bmiHeader.biHeight;
		int scanWidth = 0; 
		if (height < 0)
			height = -height;
		switch (gdiBitmapInfo->bmiHeader.biBitCount)
		{
		case 1: // 16 bits - 16 pixels
			scanWidth = (width / 16 + (width % 16 ? 1 : 0)) * 2; // 16 bits = 2 bytes
			break;
		case 2: // 16 bits - 8 pixels
			scanWidth = (width / 8 + (width % 8 ? 1 : 0)) * 2; // 16 bits = 2 bytes
			break;
		case 4: // 16 bits - 4 pixels
			scanWidth = (width / 4 + (width % 4 ? 1 : 0)) * 2; // 16 bits = 2 bytes
			break;
		case 8: // 16 bits - 2 pixels
			scanWidth = (width + 1) & ~((int)1);
			break;
		case 16: // 16 bits - 1 pixel
			scanWidth = width * 2;
			break;
		case 24: // 24 bits - 1 pixel
			scanWidth = ((width * 3) + 1) & ~((int)1);
			break;
		case 32: // 32 bits - 1 pixel
			scanWidth = width * 4;
			break;
		default:
			return 0;
		}
		size = (unsigned int)scanWidth * height;
	}
	return size;
}

void Bitmap::Set(HBITMAP hbm)
{
	Clear();

	HDC screenDC = ::GetDC(NULL);
	BITMAPINFO bitmapInfo; memset(&bitmapInfo, 0, sizeof BITMAPINFO);
	bitmapInfo.bmiHeader.biSize = sizeof BITMAPINFOHEADER;
	int success = ::GetDIBits(screenDC, hbm, 0, 0, NULL, &bitmapInfo, DIB_RGB_COLORS);

	if (success)
	{
		unsigned int infoSize = BitmapInfoSize(&bitmapInfo);
		unsigned int dataSize = BitmapDataSize(&bitmapInfo);

		m_gdiBitmapInfo = reinterpret_cast<BITMAPINFO*>(new unsigned char[infoSize]);
		m_gdiBitmapData = new unsigned char[dataSize];
		*m_gdiBitmapInfo = bitmapInfo;

		unsigned int scanLines = (unsigned int)(bitmapInfo.bmiHeader.biHeight < 0 ? -bitmapInfo.bmiHeader.biHeight : bitmapInfo.bmiHeader.biHeight);
		success = ::GetDIBits(screenDC, hbm, 0, scanLines, m_gdiBitmapData, m_gdiBitmapInfo, DIB_RGB_COLORS);
	}
	::ReleaseDC(NULL, screenDC);

	if (!success)
		Clear();
}

// The returned value is owned by this object.
const BITMAPINFO* Bitmap::GetBitmapInfo() const
{
	return m_gdiBitmapInfo;
}

void* Bitmap::GetBitmapData() const
{
	return m_gdiBitmapData;
}

HMETAFILE Bitmap::GetMetaFile(int& width, int& height) const
{
	if (!m_gdiBitmapInfo || !m_gdiBitmapData)
		return NULL;

	HDC dc = ::CreateMetaFile(NULL);
	if (!dc)
		return NULL;

	width = m_gdiBitmapInfo->bmiHeader.biWidth;
	height = m_gdiBitmapInfo->bmiHeader.biHeight;
	if (height < 0)
		height = -height;

	::SetWindowOrgEx(dc, 0, 0, NULL);
	::SetWindowExtEx(dc, width, height, NULL);

	::StretchDIBits(dc, 0, 0, width, height, 0, 0, width, height, m_gdiBitmapData, m_gdiBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	return ::CloseMetaFile(dc);
}

class GdiPlusInit
{
public:
	GdiPlusInit(); 
	~GdiPlusInit();
	bool Startup();		// this method is required to be called before any other GDI+ calls
	void Shutdown();	// call this method when done using GDI+
	bool IsInitialized() const { return m_bInit; }

private:
	Gdiplus::GdiplusStartupInput* m_pGdiplusStartupInput;
	ULONG_PTR m_puGdiplusToken;
	UINT m_uCount{0};
	bool m_bInit{false};
};

class GdiPlusInitHelper
{
public:
	GdiPlusInitHelper() { init.Startup(); }
	~GdiPlusInitHelper() { init.Shutdown(); }

	bool IsInitialized() const { return init.IsInitialized(); }

private:
	static GdiPlusInit init;
};

GdiPlusInit GdiPlusInitHelper::init;
GdiPlusInit::GdiPlusInit(): m_puGdiplusToken(0), m_uCount(0), m_bInit(false) 
{
	m_pGdiplusStartupInput = new Gdiplus::GdiplusStartupInput();
}
GdiPlusInit::~GdiPlusInit()
{
	delete m_pGdiplusStartupInput;
	m_pGdiplusStartupInput = NULL;
}
bool GdiPlusInit::Startup()
{
	if (++m_uCount == 1)
		m_bInit = (Gdiplus::GdiplusStartup(&m_puGdiplusToken, m_pGdiplusStartupInput, NULL) == Gdiplus::Ok);
	return m_bInit;
}

void GdiPlusInit::Shutdown()
{
	if (--m_uCount == 0 && m_bInit)
	{
		Gdiplus::GdiplusShutdown(m_puGdiplusToken);
		m_bInit = false;
	}
}

static bool DecodeBitmap(/*[in]*/CLIPDATA encodeClipData, /*[out]*/Bitmap& bitmap)
{
	if (encodeClipData.cbSize <= 0)
		return false;			
	// Create a temporary stream to read the png from.
	IStreamPtr tempDataStream;
	HRESULT result = ::CreateStreamOnHGlobal(NULL, TRUE, &tempDataStream);
	if (FAILED(result))
		return false;		
	const BYTE headerSize = (sizeof(DWORD) + 4*sizeof(WORD));						
	const BYTE fmtSize = sizeof(long);
	//Just skip the header information
	tempDataStream->Write(encodeClipData.pClipData + headerSize, encodeClipData.cbSize - headerSize - fmtSize, NULL);				
	//Initialize GDI+ toolkits.
	GdiPlusInitHelper init;
	if (!init.IsInitialized())
		return false;						
	Gdiplus::Bitmap image(tempDataStream);
	HBITMAP hBitmap;
	const Gdiplus::Status status = image.GetHBITMAP((Gdiplus::ARGB)Gdiplus::Color::Black, &hBitmap);
	if (status != Gdiplus::Ok)
	{
		HMETAFILE hMetafile = SetMetaFileBitsEx(encodeClipData.cbSize - headerSize - fmtSize, encodeClipData.pClipData + headerSize);
		if (hMetafile == NULL)
			return false;
		int width = (int)(*((WORD*)(encodeClipData.pClipData + sizeof(DWORD) + sizeof(WORD))));
		int height = (int)(*((WORD*)(encodeClipData.pClipData + sizeof(DWORD) + 2*sizeof(WORD))));
		bitmap.Set(hMetafile,width ,height);
		::DeleteMetaFile(hMetafile);
	}else
	{
		bitmap.Set(hBitmap);
		::DeleteObject(hBitmap);	
	}			
	return true;
}

STDMETHODIMP CThumbnailProvider::GetThumbnail(BSTR FullFileName, IPictureDisp** ppPicture)
{
	HRESULT hr = S_OK;
	LPSTORAGE pIStorage = NULL;

	// Get the storage
	hr = StgOpenStorage (FullFileName, 0, 
		STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE, NULL, 0, &pIStorage);
	OnErrorReturn(FAILED(hr), hr);

	PROPSPEC				propSpec;
	PROPVARIANT				propVar;
	IPropertySetStorage*	pPropertySetStorage = NULL;
	IPropertyStorage*		pPropertyStorage = NULL;

	// Get the Storage interface
	hr = pIStorage->QueryInterface(IID_IPropertySetStorage, 
		(void**)&pPropertySetStorage);
	OnErrorReturn(FAILED(hr), hr);

	// Get the summary information
	hr = pPropertySetStorage->Open(FMTID_SummaryInformation_Inventor,
		STGM_READ|STGM_SHARE_EXCLUSIVE,
		&pPropertyStorage);
	OnErrorReturn(FAILED(hr), hr);

	propSpec.ulKind = PRSPEC_PROPID;
	propSpec.propid = PIDSI_THUMBNAIL;

	hr = pPropertyStorage->ReadMultiple(1, &propSpec, &propVar);
	OnErrorReturn(FAILED(hr), hr);

	if (propVar.vt == VT_CF) 
	{
		// Get clipboard format
		CLIPDATA pClipdata = *propVar.pclipdata;
		hr = GetIPictureDispFromClipdata(&pClipdata, ppPicture);
	}

	// Deletes summaray information property set contained in the property set storage object 
	pPropertySetStorage->Delete(FMTID_SummaryInformation_Inventor);

	// Decrements the reference count for the calling interfaces
	pPropertySetStorage->Release();
	pIStorage->Release();

	return S_OK;
}

// Get IPictureDisp data from clipdata
HRESULT CThumbnailProvider::GetIPictureDispFromClipdata(CLIPDATA* pClipdata, IPictureDisp** ppPicture)
{
	OnErrorReturn(!pClipdata || !ppPicture, E_INVALIDARG);

	//make sure pclipdata points to a valid clipdata object.
	OnErrorReturn(pClipdata->pClipData == NULL || pClipdata->cbSize == 0, E_INVALIDARG);
	*ppPicture = NULL;

	//Get the bitmap from the Clipdata
	Bitmap bitmap;
	HMETAFILE hMetaFile = NULL;
	if(DecodeBitmap(*pClipdata, bitmap))
	{
		//Get the dimension of bitmap
		int cx = *(WORD*)(pClipdata->pClipData + sizeof(DWORD) + sizeof(WORD));
		int cy = *(WORD*)(pClipdata->pClipData + sizeof(DWORD) + 2*sizeof(WORD));	

		//Turn the bits into a metafile
		hMetaFile = bitmap.GetMetaFile(cx, cy);
	}

	PICTDESC pdesc;
	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.wmf.hmeta  = (HMETAFILE)hMetaFile;
	pdesc.wmf.xExt = 3200;	// corresponds to 180 pixels
	pdesc.wmf.yExt = 3200;
	pdesc.picType = PICTYPE_METAFILE;

	CComPtr<IPictureDisp> pPicDisp;
	//The hematfile will be destroyed when the picture object's ref count drops to zero;
	HRESULT hr = OleCreatePictureIndirect(&pdesc, IID_IPictureDisp, TRUE, (LPVOID*)& pPicDisp);	
	OnErrorReturn(FAILED(hr), hr);
	return pPicDisp.CopyTo(ppPicture);
}
