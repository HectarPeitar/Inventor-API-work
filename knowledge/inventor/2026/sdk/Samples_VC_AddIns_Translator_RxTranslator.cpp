/*
	DESCRIPTION

	This file contains the implementation of the class that offers the first contact with
	Autodesk Inventor (R).

*/

#include "stdafx.h"

#include "rxtranslator.h"
#include "translator.h"
#include <io.h>

const TCHAR DataFilePattern[] =
	{L"Sphere Radius - %lf\n"
	 L"Part Number - %s\n"};

// The addin wizard adds command id definitions here.

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxTranslator::InternalQueryInterface (REFIID riid, void **ppv)
{
	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	if (IsEqualIID(riid, __uuidof(IRxApplicationAddInServer)) ||
		IsEqualIID(riid, __uuidof(IRxTranslatorAddInServer)) ||
		IsEqualIID(riid, __uuidof(IRxTranslatorAddInServer2)))
			*ppv = static_cast<IRxTranslatorAddInServer2*>(this);

	if (*ppv)
		static_cast<IUnknown*>(*ppv)->AddRef();

	return *ppv ? S_OK : E_NOINTERFACE;
}

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/

CRxTranslator::CRxTranslator () : CUnknown (NULL)
{
	m_pSite = NULL;

	::IncrementObjectCount();
}

CRxTranslator::~CRxTranslator()
{
	if (m_pApplication)
			m_pApplication = NULL;

	if (m_pSite)
		m_pSite = NULL;

	::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/

HRESULT CRxTranslator::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	// High-level interfaces supplied directly and implicitly by Autodesk Inventor (R) to the
	// AddIn. These may be held right up until the directive to shutdown (Deactivate) is received.

	m_pSite = pAddInSite;

	CComPtr<IUnknown> pAppUnk;
	HRESULT Result = pAddInSite->get_Application (&pAppUnk);
	OnErrorReturn(FAILED(Result), Result);

	Result = pAppUnk.QueryInterface(&m_pApplication);
	OnErrorReturn(FAILED(Result), Result);

	return S_OK;
}

HRESULT CRxTranslator::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	m_pApplication.Release();

	m_pSite.Release();

	return S_OK;
}


HRESULT CRxTranslator::ExecuteCommand (long CommandID)
{
	return E_NOTIMPL;
}

HRESULT CRxTranslator::get_Automation (IUnknown **ppUnk)
{
	return E_NOINTERFACE;
}

/*---------------------- IRxTranslatorAddInServer interface ---------------------------------*/

HRESULT CRxTranslator::get_HasOpenOptions(DataMedium* pSourceData, TranslationContext* pContext,
	NameValueMap* pDefaultOptions, char* pHasOptionsUI)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!pHasOptionsUI)
		return E_INVALIDARG;

	// TODO:
	// If this AddIn wanted to enable the open options button, set pEnableOpenOptions to true
	// and ShowOpenOptions will be called if the user selects the Options button.
	// If an options map is provided and if we wish to expose public options for this operation,
	// we can fill the name-value map with options and their default or current values.

	*pHasOptionsUI = false;

	return S_OK;
}

HRESULT CRxTranslator::ShowOpenOptions(DataMedium* pSourceData, TranslationContext* pContext,
	NameValueMap* pChosenOptions)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:
	// If this AddIn wanted to enable open options and set pHasOptionsUI to true
	// in get_HasOpenOptions, display it's open options dialog here.
	// If an options map is provided and if we wish to expose public options for this operation,
	// we can fill the name-value map with the options chosen through our options dialog.

	return E_NOTIMPL;
}

HRESULT ImportFile(BSTR bstrFileName, PartDocument* pDoc)
{
	ASSERT(bstrFileName != NULL && pDoc != NULL);

	// Construct the required data from the data in the file specified using
	// whatever means necessary.	For this sample, a temporary SAT file is
	// created with the sphere radius obtained from the file and imported
	// into the part's component definition through the DataIO object.

	// Open and read the sphere radius and part number from the specified file.

	USES_CONVERSION;
	FILE* pFile{ nullptr };
	_tfopen_s(&pFile, bstrFileName, L"rt");
	if (!pFile)
		return E_FAIL;

	double radius{0.0};
	TCHAR buffer[MAX_PATH] = {L'\0'};
	int ret = _ftscanf_s(pFile, DataFilePattern, &radius, buffer, MAX_PATH);
	fclose(pFile);
	if (ret != 2)
		return E_FAIL;

	CComBSTR partNum(buffer);
	if (!partNum)
		return E_OUTOFMEMORY;

	// Get the Component Definition for the document.

	CComPtr<PartComponentDefinition> pCompDef;
	HRESULT hr = pDoc->get_ComponentDefinition(&pCompDef);
	if (FAILED(hr))
		return hr;

	// Get the DataIO object from the component definition.

	CComPtr<DataIO> pDataIO;
	hr = pCompDef->get_DataIO(&pDataIO);
	if (FAILED(hr))
		return hr;

	// Construct a (trivial) temporary SAT file and set the sphere radius.

	const TCHAR* SATData =
		L"400 0 1 0\n"
		L"7 Unknown 11 ACIS 6.0 NT 24 Fri Mar 03 12:55:15 2000\n"
		L"10 9.9999999999999995e-007 1e-010\n"
		L"body $-1 $1 $-1 $-1 #\n"
		L"lump $-1 $-1 $2 $0 #\n"
		L"shell $-1 $-1 $-1 $3 $-1 $1 #\n"
		L"face $-1 $-1 $-1 $2 $-1 $4 forward single #\n"
		L"sphere-surface $-1 0 0 0 %lf 1 0 0 0 0 1 forward_v I I I I #\n"
		L"End-of-ACIS-data";

	TCHAR file[L_tmpnam_s];
	_ttmpnam_s(file, L_tmpnam_s);
	if (file != NULL)
		_tfopen_s(&pFile, file, L"wt");
	else
		pFile = NULL;

	if (!pFile || _ftprintf(pFile, SATData, radius) <= 0 || fclose(pFile) != 0)
		return E_FAIL;

	// Read the SAT file into the part file and then delete the temporary file.
	// ACIS_SAT is the clipboard format that DatIO understands as a SAT file format.

	CComBSTR bstrFile(file);
	CComBSTR format(LACIS_SAT);
	if (!format || !bstrFile)
		return E_OUTOFMEMORY;

	hr = pDataIO->ReadDataFromFile(format, bstrFile);
	_tremove(file);
	if (FAILED(hr))
		return hr;

	// Set the part number in the property sets.
	CComPtr<PropertySets> pPropSets;
	hr = pDoc->get_PropertySets(&pPropSets);
	if (FAILED(hr))
		return hr;

	CComPtr<PropertySet> pPropSet;
	hr = pPropSets->get_Item(CComVariant(L"{32853F0F-3444-11d1-9E93-0060B03C1CA6}"), &pPropSet);
	if (FAILED(hr))
		return hr;
		
	CComPtr<Property> pProp;
	hr = pPropSet->get_ItemByPropId(kPartNumberDesignTrackingProperties, &pProp);
	if (FAILED(hr))
		return hr;

	CComVariant partNumber(partNum);
	return pProp->put_Value(partNumber);
}

HRESULT CRxTranslator::Open(DataMedium* pSourceData, TranslationContext* pContext,
	NameValueMap* pOptions, IUnknown** ppTargetObject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!pSourceData || !pContext || !ppTargetObject)
		return E_INVALIDARG;

	*ppTargetObject = NULL;

	if(!m_pApplication)
		return E_FAIL;

	// Check that this is a desired translation context.  This sample supports only file dialog operations.
	IOMechanismEnum type;
	HRESULT hr = pContext->get_Type(&type);
	if (FAILED(hr) || (type != kFileBrowseIOMechanism && type != kDataDropIOMechanism))
		return E_UNEXPECTED;

	// Obtain the file name from the data medium
	CComBSTR fileName;
	hr = pSourceData->get_FileName(&fileName);
	if (FAILED(hr) || !fileName)
		return E_INVALIDARG;

	// If our translators supports options, option values may be obtained from the optionally specified
	// options map, with a format consistent with what we specified from the Has*Options and Show*Options members.

	// Create a new document.

	CComPtr<Document> pDoc;
	hr = m_pApplication->GetDocuments()->Add(kPartDocumentObject, L"", VARIANT_TRUE/*VARIANT_FALSE*/, &pDoc);
	if (SUCCEEDED(hr))
	{
		CComQIPtr<PartDocument> pPartDoc(pDoc);

		if (!pPartDoc)
			hr = E_FAIL;
		else
			hr = ImportFile(fileName, pPartDoc);

		// If anything failed, close (destroy) the created document.
		if (FAILED(hr))
			pDoc->Close(VARIANT_TRUE);
	}

	if (FAILED(hr))
		AfxMessageBox(_T("Failed to Open Document."));
	else
		*ppTargetObject = pDoc.Detach();

	return S_OK;
}

HRESULT CRxTranslator::get_HasSaveCopyAsOptions(IUnknown* pSourceObject, TranslationContext* pContext,
	NameValueMap* pDefaultOptions, char* pHasOptionsUI)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!pHasOptionsUI)
		return E_INVALIDARG;

	// TODO:
	// If this AddIn wanted to enable the save options button, set pEnableOptions to true
	// and ShowSaveCopyAsOptions will be called if the user selects the Options button.
	// If an options map is provided and if we wish to expose public options for this operation,
	// we can fill the name-value map with options and their default or current values.

	*pHasOptionsUI = false;

	return S_OK;
}

HRESULT CRxTranslator::ShowSaveCopyAsOptions(IUnknown* pSourceObject, TranslationContext* pContext,
	NameValueMap* pChosenOptions)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:
	// If this AddIn wanted to enable save options and set pEnableOptions to true
	// in get_HasSaveCopyAsOptions, display it's save options dialog here.
	// If an options map is provided and if we wish to expose public options for this operation,
	// we can fill the name-value map with the options chosen through our options dialog.

	return E_NOTIMPL;
}

HRESULT SaveFile(PartDocument* pDoc, BSTR bstrFileName)
{
	ASSERT(pDoc != NULL && bstrFileName != NULL);

	// Construct the proprietary file specified using whatever means necessary.
	// For this sample, The radius of the first spherical surface on the body
	// is obtained from a temporary SAT file created from the part's component
	// definition's DataIO object.

	CComPtr<PartComponentDefinition> pPartDef;
	HRESULT hr = pDoc->get_ComponentDefinition(&pPartDef);
	if (FAILED(hr))
		return hr;

	CComPtr<DataIO> pDataIO;
	hr = pPartDef->get_DataIO(&pDataIO);
	if (FAILED(hr))
		return hr;

	// Write a SAT file to a temporary file name.  ACIS_SAT is the clipboard
	// format that DatIO understands as a SAT file format.

	TCHAR file[L_tmpnam_s];
	errno_t err = _ttmpnam_s(file, L_tmpnam_s);
	if (err)
		return E_FAIL;

	CComBSTR bstrFile(file);
	CComBSTR format(LACIS_SAT);
	if (!bstrFile || !format)
		return E_OUTOFMEMORY;

	hr = pDataIO->WriteDataToFile(format, bstrFile);
	if (FAILED(hr))
		return hr;

	// Open the temporary file and pull the first spherical surface's radius
	// out, and then delete the temporary file.

	hr = NOERROR;
	double radius{0.0};
	FILE* pFile{ nullptr };
	_tfopen_s(&pFile, file, L"rt,ccs=UTF-8");
	if (pFile)
	{
		long length = _filelength(_fileno(pFile)) * sizeof(TCHAR);
		TCHAR* buffer = new TCHAR[length];
		if (buffer)
		{
			fread(buffer, sizeof(TCHAR), length, pFile);
			if (!ferror(pFile))
			{
				const TCHAR* pattern = L"sphere-surface $-1 -1 $-1";
				TCHAR* temp = _tcsstr(buffer, pattern);
				if (temp)
				{
					temp += _tcslen(pattern);
					double tempVal{0.0};
					if (_stscanf_s(temp, L"%lf%lf%lf%lf", &tempVal, &tempVal, &tempVal, &radius) == 4)
						hr = S_OK;
				}
			}
			delete [] buffer;
		}
		fclose(pFile);
	}

	_tremove(file);

	if (FAILED(hr))
		return hr;

	// Obtain the part number from the property sets.

	CComPtr<PropertySets> pPropSets;
	hr = pDoc->get_PropertySets(&pPropSets);
	if (FAILED(hr))
		return hr;

	CComPtr<PropertySet> pPropSet;
	hr = pPropSets->get_Item(CComVariant(L"{32853F0F-3444-11d1-9E93-0060B03C1CA6}"), &pPropSet);
	if (FAILED(hr))
		return hr;
		
	CComPtr<Property> pProp;
	hr = pPropSet->get_ItemByPropId(kPartNumberDesignTrackingProperties, &pProp);
	if (FAILED(hr))
		return hr;

	CComVariant partNumber;
	hr = pProp->get_Value(&partNumber);
	if (FAILED(hr))
		return hr;

	hr = partNumber.ChangeType(VT_BSTR);
	if (FAILED(hr))
		return hr;

	CComBSTR bstrPartNum(V_BSTR(&partNumber));
	if (!bstrPartNum)
		return E_FAIL;

	// Construct the new file with the sphere radius and the part number.

	USES_CONVERSION;
	_tfopen_s(&pFile, bstrFileName, L"wt");
	if (!pFile)
		return E_FAIL;

	int ret = _ftprintf(pFile, DataFilePattern, radius, bstrPartNum);
	fclose(pFile);
	if (ret <= 0)
	{
		remove(W2A(bstrFileName));
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CRxTranslator::SaveCopyAs(IUnknown* pSourceObject, TranslationContext* pContext,
	NameValueMap* pOptions, DataMedium* pTargetData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!pSourceObject || !pContext || !pTargetData)
		return E_INVALIDARG;

	// Check that this is a desired translation context.  This sample supports only file dialog operations.

	IOMechanismEnum type;
	HRESULT hr = pContext->get_Type(&type);
	if (FAILED(hr) || type != kFileBrowseIOMechanism)
		return E_UNEXPECTED;

	// Obtain the file name from the data medium

	CComBSTR fileName;
	hr = pTargetData->get_FileName(&fileName);
	if (FAILED(hr) || !fileName)
		return E_INVALIDARG;

	// If our translators supports options, option values may be obtained from the optionally specified
	// options map, with a format consistent with what we specified from the Has*Options and Show*Options members.

	// Currently, only implemented to support part document types, even though the
	// translator is registered to support assembly files as well (to demonstrate
	// registering multiple base file type support).

	hr = E_FAIL;
	CComQIPtr<PartDocument> pPartDoc(pSourceObject);
	if (pPartDoc)
		hr = SaveFile(pPartDoc, fileName);

	if (FAILED(hr))
		AfxMessageBox(_T("Failed to Save Document."));

	return S_OK;
}

STDMETHODIMP CRxTranslator::GetThumbnail(DataMedium* pSourceData, VARIANT* pThumbnail)
{
	if (!pSourceData || !pThumbnail)
		return E_INVALIDARG;

	VariantInit(pThumbnail);

	CComBSTR file;
	HRESULT hr = pSourceData->get_FileName(&file);
	if (FAILED(hr) || !file)
		return E_FAIL;

	USES_CONVERSION;
	TCHAR* thumbFile = W2T(file);
	PathRemoveExtension(thumbFile);
	if (!PathAddExtension(thumbFile, _T(".wmf")))
		return E_FAIL;

	HANDLE hFile = CreateFile(thumbFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;

	HGLOBAL hGlobal = NULL;
	DWORD fileSize = GetFileSize(hFile, NULL);
	if (fileSize != -1)
	{
		void* pData = NULL;
		hGlobal = GlobalAlloc(GMEM_MOVEABLE, fileSize);
		if (hGlobal)
		{
			pData = GlobalLock(hGlobal);
			if (pData)
			{
				DWORD bytesRead = 0;
				BOOL bRead = ReadFile(hFile, pData, fileSize, &bytesRead, NULL);
				GlobalUnlock(hGlobal);
				if (!bRead)
				{
					GlobalFree(hGlobal);
					hGlobal = NULL;
				}
			}
		}
	}
	CloseHandle(hFile);
	if (!hGlobal)
		return E_FAIL;

	CComPtr<IStream> pStream;
	hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
	if (FAILED(hr))
		return E_FAIL;

	CComPtr<IPicture> pPict;
	hr = OleLoadPicture(pStream, fileSize, FALSE, __uuidof(pPict), reinterpret_cast<void**>(&pPict));
	if (FAILED(hr))
		return E_FAIL;

	V_VT(pThumbnail) = VT_UNKNOWN;
	V_UNKNOWN(pThumbnail) = pPict.Detach();

	return S_OK;
}
