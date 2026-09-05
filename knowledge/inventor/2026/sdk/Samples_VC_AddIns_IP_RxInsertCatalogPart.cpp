/*
  DESCRIPTION

  This file contains the implementation of the class that offers the first contact with
  Inventor.

*/

#include "stdafx.h"

#include <io.h>

#include "rxinsertcatalogpart.h"
#include "insertcatalogpart.h"
#include <safearrayutil.h>
#include <clipboardformats.h>
#include "AfxCtl.h"

#include <initguid.h>
#include <docclsids.h>

#define CMD_DEFINE_CACHE 1
#define CMD_INSERT_SAT   2

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxInsertCatalogPart::InternalQueryInterface (REFIID riid, void **ppv)
{
    OnErrorReturn (!ppv, E_INVALIDARG);

    HRESULT Result = NOERROR;
    *ppv = NULL;

    if (IsEqualIID (riid, __uuidof (IRxApplicationAddInServer)))
        *ppv = static_cast<void *> (static_cast<IRxApplicationAddInServer *> (this));
    else
        Result = E_NOINTERFACE;

    if (SUCCEEDED (Result))
        ((LPUNKNOWN)*ppv)->AddRef();

    return (Result);
}

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/

CRxInsertCatalogPart::CRxInsertCatalogPart () : CUnknown (NULL)
{ 
    m_pSite = NULL;

    m_pButtonEvents1 = new CButtonDefEvents(this, CMD_DEFINE_CACHE);
    m_pButtonEvents2 = new CButtonDefEvents(this, CMD_INSERT_SAT);
    
    m_btnDefCookie1 = 0;
    m_btnDefCookie2 = 0;
    
    m_pAppEventHandler = NULL;

    ::IncrementObjectCount();
}

CRxInsertCatalogPart::~CRxInsertCatalogPart()
{
    AFX_MANAGE_STATE (AfxGetAppModuleState());

    if(m_pSite)
        m_pSite= NULL;

    if(m_pButtonEvents1)
        delete m_pButtonEvents1;

    if(m_pButtonEvents2)
        delete m_pButtonEvents2;

    m_pBtnDef1 = NULL;
    m_pBtnDef2 = NULL;

    if(m_pAppEventHandler)
    {
        m_pAppEventHandler->Release();
        m_pAppEventHandler= NULL;
    }

    ::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/


HRESULT CRxInsertCatalogPart::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
{
    AFX_MANAGE_STATE (AfxGetStaticModuleState()); 

    HRESULT Result=NOERROR;

    variant_t vInTools(VARIANT_TRUE);

    CComPtr<IUnknown> pAppUnk;

    m_pSite = pAddInSite;

    Result = pAddInSite->get_Application(&pAppUnk);
    OnErrorReturn (FAILED (Result), Result);

    Result = pAppUnk->QueryInterface(DIID_Application, (void **) &m_pApplication);
    OnErrorReturn (FAILED (Result), Result);

    pAppUnk = NULL;

    CreateCommands();

    m_pAppEventHandler = new CRxAppEventHandler (this);
    OnErrorReturn (!m_pAppEventHandler, E_OUTOFMEMORY);
    m_pAppEventHandler->AddRef();

    Result = m_pAppEventHandler->Connect (m_pApplication);
    OnErrorReturn (FAILED (Result), Result);

    return Result;
}
    
HRESULT CRxInsertCatalogPart::Deactivate ()
{
    AFX_MANAGE_STATE (AfxGetStaticModuleState());

    HRESULT Result=NOERROR;

    // disconnect event sinks
    if(m_btnDefCookie1)
    {
        BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
                                              m_pButtonEvents1->GetInterface(&IID_IUnknown),
                                              TRUE, m_btnDefCookie1);
        m_btnDefCookie1 = 0;
    }

    if(m_btnDefCookie2)
    {
        BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
                                              m_pButtonEvents2->GetInterface(&IID_IUnknown),
                                              TRUE, m_btnDefCookie2);
        m_btnDefCookie2 = 0;
    }

    m_pBtnDef1 = NULL;
    m_pBtnDef2 = NULL;
    
    if (m_pAppEventHandler)
        m_pAppEventHandler->Disconnect();

    // Cleanup up of interfaces supplied by Inventor and held on by this AddIn 
    // at initialization or load.
    m_pApplication = NULL;
    m_pSite = NULL;

    return Result;
}


HRESULT CRxInsertCatalogPart::ExecuteCommand (long CommandID)
{
    AFX_MANAGE_STATE (AfxGetStaticModuleState());

    HRESULT Result=NOERROR;

    // Handle the command to defined the Catalog Parts Cache library
    if(CommandID == CMD_DEFINE_CACHE)
    {
        bool bCacheDefined=false;

        Result = DefinePartsCatalogCache (&bCacheDefined);
        OnErrorReturn (FAILED (Result), Result);

        if (bCacheDefined)
        {
            // Once this is defined, disable the command
            Result = m_pBtnDef1->put_Enabled (FALSE);
            OnErrorReturn (FAILED (Result), Result);
        }
        else
            AfxMessageBox (_T("You will not be able to Insert SAT Catalog files into Assembly"));
    }
    else if (CommandID == CMD_INSERT_SAT)   // Handle the command to insert a SAT Part from the Catalog
    {
        Result = InsertSat();
        OnErrorReturn (FAILED (Result), Result);
    }
    else
        Result = E_NOTIMPL;
    
    return Result;
}

HRESULT CRxInsertCatalogPart::get_Automation (IUnknown **ppUnk)
{
    if(!ppUnk)
        return E_INVALIDARG;

    *ppUnk = NULL;

    return E_NOINTERFACE;
}

//----------------------- Helper Methods ---------------------------------------//

HRESULT CRxInsertCatalogPart::HasPartsCatalogCache (bool *pbLibraryFound)
{
    HRESULT Result = NOERROR;

    OnErrorReturn (!pbLibraryFound, E_INVALIDARG);

    *pbLibraryFound = false;

    // Obtain the File Locations object. Through this object you can look up (and manipulate)
    // all of the search paths that Inventor uses to look for referenced files
    CComPtr<FileLocations> pFileLocations;
    Result = m_pApplication->get_FileLocations(&pFileLocations);
    OnErrorReturn(FAILED (Result), Result);

    // Obtain all the current Libraries known to Inventor at this time
    long nLibraries=0;

    CComSafeArray<BSTR> *pbstrLibraryNames;
    pbstrLibraryNames = new CComSafeArray<BSTR>;

    CComSafeArray<BSTR> *pbstrLibraryPaths;
    pbstrLibraryPaths = new CComSafeArray<BSTR>;

    Result = pFileLocations->Libraries (&nLibraries, (*pbstrLibraryNames).GetSafeArrayPtr(), (*pbstrLibraryPaths).GetSafeArrayPtr());
    OnErrorReturn (FAILED (Result), Result);

    // Cycle through the Library names to see if "Catalog Parts Cache" is one of them
    CComBSTR bstrCatalogPartsCache(L"Catalog Parts Cache");
    for (long i=0; i<nLibraries; i++)
    {
        if ((*pbstrLibraryNames)[i] == bstrCatalogPartsCache)
        {
            *pbLibraryFound = true;
            break;
        }
    }

    return Result;
}

HRESULT CRxInsertCatalogPart::DefinePartsCatalogCache (bool *pbLibraryDefined)
{
    HRESULT Result = NOERROR;

    OnErrorReturn (!pbLibraryDefined, E_INVALIDARG);

    *pbLibraryDefined = false;

    // Obtain the File Locations object. Through this object you can look up (and manipulate)
    // all of the search paths that Inventor uses to look for referenced files
    CComPtr<FileLocations> pFileLocations;
    Result = m_pApplication->get_FileLocations(&pFileLocations);
    OnErrorReturn(FAILED (Result), Result);

    // Warn the user if we are working with a readOnly project file.
    CComBSTR bstrProjectFile;
    CComBSTR rawBstrProjectFile;

    // Get the project file.
    Result = pFileLocations->get_FileLocationsFile(&rawBstrProjectFile);
    OnErrorReturn (FAILED (Result), Result);

    bstrProjectFile = rawBstrProjectFile;

    CComBSTR bstrCatalogPartsCache(_T("Catalog Parts Cache"));
    CComBSTR bstrCatalogPartsCacheDir(_T("C:\\Temp\\CatalogPartsCache"));

    // If Inventor is set to read from a Project file and it is readOnly
    // then we warn the user about this.

    if((bstrProjectFile.Length() > 0) && (_taccess(OLE2W(bstrProjectFile), 2) != 0))
    {
        CString strWarn = _T("Warning: Project file ") + CString(bstrProjectFile) + 
                          _T(" is readOnly.\nCatalog Parts Library cache: ") + 
                          CString(bstrCatalogPartsCache) + _T("=") + CString(bstrCatalogPartsCacheDir) + 
                          _T(" could not be added");

        AfxMessageBox(strWarn, MB_ICONEXCLAMATION|MB_OK);

        return E_FAIL;
    }

    if (AfxMessageBox (_T("Defining Cache as 'C:\\Temp\\CatalogPartsCache'.\nIf directory does not exist, please create one"), MB_YESNOCANCEL) == IDYES)
    {
        Result = pFileLocations->AddLibrary(bstrCatalogPartsCache, bstrCatalogPartsCacheDir);
        OnErrorReturn (FAILED (Result), Result);

        *pbLibraryDefined = true;
    }

    return Result;
}

HRESULT CRxInsertCatalogPart::HandleDocumentActivation(Document *pDoc)
{
    DocumentTypeEnum eDocType=kUnknownDocumentObject;
    VARIANT_BOOL varBool = VARIANT_TRUE;

    OnErrorReturn (!pDoc, E_INVALIDARG);

    HRESULT Result = pDoc->get_DocumentType(&eDocType);
    OnErrorReturn(FAILED (Result), Result);

    if (eDocType == kAssemblyDocumentObject)
        varBool = VARIANT_TRUE;
    else
        varBool = VARIANT_FALSE;

    Result = m_pBtnDef2->put_Enabled(varBool);
    OnErrorReturn(FAILED (Result), Result);

    return Result;
}


HRESULT CRxInsertCatalogPart::InsertSat()
{
    HRESULT Result = NOERROR;
    
    // Check if the 'Place Component' command is enabled in the current
    // environment. If it is not, we cannot go through with the insert command.
    CComPtr<CommandManager> pCommandManager;
    VARIANT_BOOL bEnabled;

    Result= m_pApplication->get_CommandManager(&pCommandManager);
    OnErrorReturn (FAILED (Result), Result);

    Result = pCommandManager->get_CommandEnabled (kPlaceComponentCommand, &bEnabled);
    OnErrorReturn (FAILED (Result), Result);

    if (bEnabled == VARIANT_FALSE)
    {
        AfxMessageBox (_T("You cannot Insert SAT Catalog files in the current environment"));
        OnErrorReturn (FAILED (Result), Result);
    }

    // Obtain Inventor's Language. This string can be used to display in the
    // title of the Dialog Boxes. 
    long LocaleId=0;
    Result = m_pApplication->get_Locale(&LocaleId);
    OnErrorReturn (FAILED (Result), Result);

    int nCharCount = ::GetLocaleInfo(LocaleId, LOCALE_SENGLANGUAGE, NULL, 0);
    TCHAR *pChar = (TCHAR *) alloca (nCharCount * sizeof (TCHAR));
    OnErrorReturn (!pChar, E_OUTOFMEMORY);

    nCharCount = ::GetLocaleInfo(LocaleId, LOCALE_SENGLANGUAGE, pChar, nCharCount);
    OnErrorReturn (!nCharCount, E_FAIL);

    m_CatalogBrowserDlg.m_Title = pChar;

    // Allow the user to Browse in our database to select the particular
    // Part from the catalog
    CComBSTR SelectedSATPartName, SelectedSATPartFile;
    if (m_CatalogBrowserDlg.DoModal () == IDOK)
    {    
        SelectedSATPartName = m_CatalogBrowserDlg.GetCatalogPartFile();      
        SelectedSATPartFile = L"c:\\Temp\\StandardParts\\";
        SelectedSATPartFile += SelectedSATPartName;
        SelectedSATPartFile += L".sat";
    }
    else
        return NOERROR;

    // Determine the Part Number from the Part selected
    CComBSTR PartNumber;
    if (SelectedSATPartName == L"Box")
        PartNumber = L"123-BOX";
    else if (SelectedSATPartName == L"Cylinder")
        PartNumber = L"123-CYL";
    else if (SelectedSATPartName == L"Cone")
        PartNumber = L"123-CON";
    else if (SelectedSATPartName == L"Sphere")
        PartNumber = L"123-SPH";
    else 
        PartNumber = L"123-TOR";


    // Create a deterministic filename out of the Catalog Part attributes. We can use Inventor's
    // API that generates a deterministic internal name (a 'GUID') out of a set of strings that 
    // uniquely identify the Part. This is the filename with which the proxy file is to be generated.
    // This way, the Proxy filename can be relied upon as an identifier for the catalog data
    // stored within.

    CComBSTR bstrInternalName;
    Result = m_pApplication->CreateInternalName (_bstr_t(L"ABC Catalog Parts"), PartNumber, _bstr_t(L"Version 1.0"), &bstrInternalName);
    OnErrorReturn (FAILED (Result), Result);

    CComBSTR InternalName (bstrInternalName);
    CComBSTR ProxyFullFileName(L"c:\\temp\\CatalogPartsCache\\");
    ProxyFullFileName += InternalName ;
    ProxyFullFileName += L".ipt";

    //
    // Check to see if the selected Catalog Part is already available in the cache.
    // In case it is, use this file to invoke the Insert Component command. Else,
    // create a new, corresponding Inventor file in the Cache library, and use it.
    //

    WIN32_FIND_DATA FindFileData;
    bool bFoundInCache = true;

    HANDLE hFind = FindFirstFile (OLE2W(ProxyFullFileName), &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        bFoundInCache = false;
    else
        ::FindClose(hFind);
    if (!bFoundInCache)
    {
        // Create an empty Part Document. It is created from the part template and in the
        // user's default system of measurement.  The subtype is set to a catalog part.
        CComPtr<Documents> pDocuments;
        Result = m_pApplication->get_Documents(&pDocuments);
        OnErrorReturn (FAILED (Result), Result);
            
        CComPtr<Document> pDocument;
        Result = pDocuments->Add (kPartDocumentObject, L"", VARIANT_FALSE, &pDocument);
        OnErrorReturn (FAILED (Result), Result);
            
        Result = pDocument->put_SubType(_bstr_t(L"{9C88D3AF-C3EB-11d3-B79E-0060B0F159EF}"));
        OnErrorReturn (FAILED (Result), Result);
            
        CComQIPtr<PartDocument> pPartDocument(pDocument);
        OnErrorReturn (!pPartDocument, E_FAIL);

        // Create the 'base feature' with the SAT data. The sample uses a SAT file. 
        // But SAT or SAB data in an IStream could also have been used.
            
        // Obtain the Data-IO object for the Document
        CComPtr<PartComponentDefinition> pCompDef;
        Result = pPartDocument->get_ComponentDefinition(&pCompDef);
        OnErrorReturn (FAILED (Result), Result);
            
        CComPtr<DataIO> pDataIO;
        Result = pCompDef->get_DataIO(&pDataIO);
        OnErrorReturn (FAILED (Result), Result);
            
        // Load the SAT data in, creating the Base Feature
        Result = pDataIO->ReadDataFromFile (_bstr_t(LACIS_SAT), SelectedSATPartFile);
        OnErrorReturn (FAILED (Result), Result);
            
        // Set the various Properties. Only Part-Number shown here in sample.

        // Obtain the 'Design Tracking Properties' Property Set from the Property Sets collection. 
        CComPtr<PropertySets> pPropSets;
        Result = pPartDocument->get_PropertySets(&pPropSets);
        OnErrorReturn (FAILED (Result), Result);
            
        // Get the 'Design Tracking Properties' using its internal name
        CComPtr<PropertySet> pPropSet;
        Result = pPropSets->get_Item(CComVariant(L"{32853F0F-3444-11d1-9E93-0060B03C1CA6}"), &pPropSet);
        OnErrorReturn (FAILED (Result), Result);
            
        // Obtain the Part-Number Property from the Property Set
        CComPtr<Property> pProp;
        Result = pPropSet->get_ItemByPropId(kPartNumberDesignTrackingProperties, &pProp);
        OnErrorReturn (FAILED (Result), Result);
            
        // Edit the value of the property
        CComVariant vtPartNumber(PartNumber);
        Result = pProp->put_Value(vtPartNumber);
        OnErrorReturn (FAILED (Result), Result);
            
        // Set the InternalName on the document
        CComBSTR bstrInternalName;
        Result = pPartDocument->PutInternalName(PartNumber, NULL, NULL, &bstrInternalName);
        OnErrorReturn((FAILED (Result) || !InternalName), Result);

        // Save this Document in the Cache Library and Close. This ensures that Inventor
        // is in the state it would have been had the cached 'proxy' file already been 
        // present in the Cache library location
            
        // Get previous MRU and disable MRU handling. 
        VARIANT_BOOL vtBoolPreviousMRU = VARIANT_TRUE;
        Result = m_pApplication->get_MRUEnabled(&vtBoolPreviousMRU);
        OnErrorReturn (FAILED (Result), Result);
        
        if(vtBoolPreviousMRU != VARIANT_FALSE)
        {
            Result = m_pApplication->put_MRUEnabled(VARIANT_FALSE);
            OnErrorReturn (FAILED (Result), Result);
            m_pApplication->put_MRUEnabled(VARIANT_TRUE);
        }
            
        // put the display name same as the part number
        Result = pPartDocument->put_DisplayName(PartNumber);
        OnErrorReturn (FAILED (Result), Result);
            
        // Set the graphics faceting to a coarser level than default saving space in the cache
        Result = pPartDocument->PutGraphicsLevelsOfDetail(kCoarseRes);
        OnErrorReturn (FAILED (Result), Result);
            
        // Save the Part Document off into the Cache Library location
        Result = pPartDocument->SaveAs (ProxyFullFileName, VARIANT_FALSE);
        OnErrorReturn (FAILED (Result), Result);
            
        // Shut the Part Document down
        Result = pPartDocument->Close(VARIANT_FALSE);
        OnErrorReturn (FAILED (Result), Result);
    }

    // Invoke the Insert Component command with the 'proxy' filename

    // Place the filename on Inventor's Private Event Queue
    Result = pCommandManager->PostPrivateEvent (kFileNameEvent, CComVariant(ProxyFullFileName));
    OnErrorReturn (FAILED (Result), Result);

    // Initiate the Insert Component command
    CComPtr<ControlDefinitions> pControlDefinitions;
    Result = pCommandManager->get_ControlDefinitions(&pControlDefinitions);
    OnErrorReturn (FAILED (Result), Result);

    // Get the place component control definition
    CComPtr<ControlDefinition> pPlaceCompCtrlDef;
    Result = pControlDefinitions->get_Item(CComVariant(_T("AssemblyPlaceComponentCmd")), &pPlaceCompCtrlDef);
    OnErrorReturn (FAILED (Result), Result);

    // Execute the place component control definition
    Result = pPlaceCompCtrlDef->Execute();
    OnErrorReturn (FAILED (Result), Result);
    
    return Result;
}

void CRxInsertCatalogPart::CreateCommands()
{
    ATLASSERT(m_pApplication);

    if(!m_pApplication)
        return;

    CComPtr<CommandManager> pCommandMgr;
    HRESULT hr = m_pApplication->get_CommandManager(&pCommandMgr);

    CComPtr<ControlDefinitions> pCtrlDefs;
    hr = pCommandMgr->get_ControlDefinitions(&pCtrlDefs);
    
    bool bHasCacheLibrary=false;

    CComVariant vtAddInId;
    CComBSTR InternalNameBSTR;
    CComBSTR displayNameBSTR;
    CComBSTR DesTextBSTR;
    CComBSTR TooltipTextBSTR;
    CComVariant vtEmpty;
    CommandTypesEnum eCmdType;
    ButtonDisplayEnum eCmdDisplayType;

    // common button parameters
    // client Id for the buttons
    vtAddInId	      = _T("{04859830-A5FA-11D3-B799-0060B0F159EF}");
    // command type
    eCmdType = kQueryOnlyCmdType;
    // button display type
    eCmdDisplayType = kAlwaysDisplayText;

    
    // Create the command that defines the cache library. If one already present, disable
    // the command, since it that library is expected to last for the entire session.
    InternalNameBSTR  =	_T("InsertCatalogPartAddIn.DefineCmd");
    displayNameBSTR	  =	_T("DefineCacheLibrary");
    DesTextBSTR		  =	_T("Execute Define Cache Library Command");
    TooltipTextBSTR	  =	_T("Define Cache Library");
    
    hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef1); 

    ATLASSERT(SUCCEEDED(hr));
    ATLASSERT(m_pBtnDef1 != NULL);

    hr = HasPartsCatalogCache (&bHasCacheLibrary);
    if(FAILED (hr))
        return;

    if (bHasCacheLibrary)
    {
        hr = m_pBtnDef1->put_Enabled (FALSE);
        if(FAILED (hr))
            return;
    }
    else
        m_pBtnDef1->put_Enabled(VARIANT_TRUE);

    if(m_pBtnDef1)
    {
        BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
                                m_pButtonEvents1->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie1);

        ATLASSERT(bBrwsrAdvised == TRUE);
    }

    hr = m_pBtnDef1->AutoAddToGUI();
    ATLASSERT(SUCCEEDED(hr));

    

    // Create the command that will insert the SAT Part from the catalog. If no Assembly
    // Document is currently active, disable the command. Set up the listener (event sink)
    // to Documents being activated. The moment an Assembly Document comes active, this command
    // will be enabled.
    InternalNameBSTR  =	_T("InsertCatalogPartAddIn.InsertCmd");
    displayNameBSTR	  =	_T("InsertSATPart");
    DesTextBSTR		  =	_T("Execute Insert SAT Part Command");
    TooltipTextBSTR	  =	_T("Insert SAT Part");
    

    hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef2); 

    ATLASSERT(SUCCEEDED(hr));
    ATLASSERT(m_pBtnDef2 != NULL);

    CComPtr<Document> pDoc;
    DocumentTypeEnum eDocType = kUnknownDocumentObject;

    hr = m_pApplication->get_ActiveDocument(&pDoc);
    if(FAILED (hr))
        return;

    if (pDoc)
    {
        hr = pDoc->get_DocumentType(&eDocType);
        if(FAILED (hr))
            return;
    }

    if (eDocType != kAssemblyDocumentObject || !bHasCacheLibrary)
    {
        hr = m_pBtnDef2->put_Enabled (FALSE);
        if(FAILED (hr))
            return;
    }
    else
        m_pBtnDef2->put_Enabled(VARIANT_TRUE);

    if(m_pBtnDef2)
    {
        BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
                                m_pButtonEvents2->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie2);

        ATLASSERT(bBrwsrAdvised == TRUE);
    }

    hr = m_pBtnDef2->AutoAddToGUI();
    ATLASSERT(SUCCEEDED(hr));

}


/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CRxInsertCatalogPart* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
{
   EnableAutomation();  // Needed in order to sink events.
}

CButtonDefEvents::~CButtonDefEvents()
{
}


BEGIN_MESSAGE_MAP(CButtonDefEvents, CCmdTarget)
    //{{AFX_MSG_MAP(CButtonDefEvents)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CButtonDefEvents, CCmdTarget)
    DISP_FUNCTION_ID(CButtonDefEvents, "OnExecute", 0x03009c81, OnExecuteEvent, VT_EMPTY, VTS_DISPATCH)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CButtonDefEvents, CCmdTarget)
    INTERFACE_PART(CButtonDefEvents, DIID_ButtonDefinitionSink, Dispatch)
END_INTERFACE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents event handlers

void CButtonDefEvents::OnExecuteEvent(NameValueMap *context) 
{
    AFX_MANAGE_STATE (AfxGetStaticModuleState());

    if (m_pAddIn)
        m_pAddIn->ExecuteCommand(m_nID);
}
