#include "dataioexepch.h"

#include <clipboardformats.h>

using namespace std;

typedef map<long, CComPtr<IRxEdge> > TransIDEdgeMap;

void test(const char* filename);


///////////////////////////////////////////////////////////
//
// main entry point
//
// The app expects one argument, a part file name.
//
int main(int argc, char* argv[])
{
	// Validate command line arguments
	if (argc < 2)
	{
		cout << "Invalid argument to main." << endl;
		return 1;
	}
	const char* filename = argv[1];
	if (!filename)
	{
		cout << "Invalid argument to main." << endl;
		return 2;
	}

	if (!strcmp(filename, "/?"))
	{
		cout << "Usage: DATAIOUNIT partFileName" << endl;
		return 0;
	}

	// Initialize the COM library and the pid husk.
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		cout << "Failed to initialize com library." << endl;
		return 3;
	}

	outcome rc = api_start_modeller(0);
	if (rc.ok())
		outcome rc = api_initialize_persistent_id();
	if (!rc.ok())
	{
		cout << "Failed to initialize the modeller or persistent id husk." << endl;
		CoUninitialize();
		return 4;
	}

	// run the actual test
	test(filename);

	// clean up and exit
	CoUninitialize();

	rc = api_terminate_persistent_id();
	rc = api_stop_modeller();

	cout << "Done." << endl;

	return 0;
}

void test(const char* filename)
{
	// Create the apprentice server component instance.

	CComPtr<IRxApprenticeServer> pApp;
	HRESULT hr = pApp.CoCreateInstance(CLSID_ApprenticeServerComponent);
	if (FAILED(hr))
	{
		cout << "Failed to create apprentice server instance - " << hr << endl;
		return;
	}

	// Open the specified file with the apprentice server.

	CComBSTR file(filename);
	if (!file)
	{
		cout << "Failed to allocate filename BSTR." << endl;
		return;
	}

	CComPtr<IRxComponentDocument> pDoc;
	hr = pApp->Open(file, &pDoc);
	if (FAILED(hr))
	{
		cout << "Failed to Open " << filename << " file - " << hr << endl;
		return;
	}


	CComPtr<IRxEnumComponentDefinitions> pEnum;
	hr = pDoc->get_Definitions(&pEnum);
	if (FAILED(hr))
	{
		cout << "Failed to get definitions from document - " << hr << endl;
		return;
	}

	CComPtr<IRxComponentDefinition> pDef;
	hr = pEnum->Next(1, &pDef, NULL);
	if (FAILED(hr) || !pDef)
	{
		cout << "Failed to get definition from the definitions enumerator." << endl;
		return;
	}

	// Get the DataIO object from the definition.  The DataIO property is only
	// exported on the ComponentDefinition dispinterface.

	CComQIPtr<ComponentDefinition> pDispDef(pDef);
	if (!pDispDef)
	{
		cout << "Failed to query for the ComponentDefinition dispinterface." << endl;
		return;
	}

	CComPtr<DataIO> pDataIO;
	hr = pDispDef->get_DataIO(&pDataIO);
	if (FAILED(hr))
	{
		cout << "Failed to get DataIO object from definition - " << hr << endl;
		return;
	}

	// Get the solid body from the definition.

	CComPtr<IRxEnumSurfaceBodies> pEnumBodies;
	hr = pDef->get_SurfaceBodies(&pEnumBodies);
	if (FAILED(hr))
	{
		cout << "Failed to get body enumerator from definition - " << hr << endl;
		return;
	}

	CComPtr<IRxSurfaceBody> pBody;
	hr = pEnumBodies->Next(1, &pBody, NULL);
	if (FAILED(hr) || !pBody)
	{
		cout << "Failed to get body from body enumerator." << endl;
		return;
	}

	// Get all of the edges on the body.

	CComPtr<IRxEnumEdges> pEnumEdges;
	hr = pBody->get_Edges(&pEnumEdges);
	if (FAILED(hr))
	{
		cout << "Failed to get edge enumerator from body." << endl;
		return;
	}

	// Build a map of the transient ID's for each edge of the body
	// and the interface pointer to the edge.

	TransIDEdgeMap originalIDMap;
	pair<TransIDEdgeMap::iterator, bool> insertRes;
	long transId;

	CComPtr<IRxEdge> pEdge;
	CComQIPtr<IRxReferenceKey> pRefKey;
	for (;(hr = pEnumEdges->Next(1, &pEdge, NULL)) == S_OK;pEdge.Release())
	{
		// Query for the IRxReferenceKey interface for each
		// edge and get the transient key.

		pRefKey = pEdge;
		if (!pRefKey)
		{
			cout << "Failed to query for IRxReferenceKey on an edge." << endl;
			return;
		}

		hr = pRefKey->get_TransientKey(&transId);
		if (FAILED(hr))
		{
			cout << "Failed to get transient key for edge." << endl;
			return;
		}

		// Insert the transient ID and the edge interface into the map.

		insertRes = originalIDMap.insert(TransIDEdgeMap::value_type(transId, pEdge));
		if (!insertRes.second)
		{
			// the transient ID is a duplicate or we hit this edge twice (which shouldn't happen).
			cout << "Failed to insert from edge data into the map." << endl;
			return;
		}

	}

	// Use the DataIO object to dump the part's body to a SAT file with the transient
	// key values attached as PID attributes ('ACIS_SAT_with_TransientKeys').

	char tempFilename[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(filename, drive, dir, fname, ext);
	strcat(fname, "_SATPID");
	_makepath(tempFilename, drive, dir, fname, "SAT");
	CComBSTR format(LACIS_SAT_with_TransientKeys);
	CComBSTR name(tempFilename);
	if (!format || !name)
	{
		cout << "Failed to allocate format and/or filename string." << endl;
		return;
	}

	hr = pDataIO->WriteDataToFile(format, name);
	if (FAILED(hr))
	{
		cout << "Failed to write SATPID data to file - " << hr << endl;
		return;
	}

	// Open the file and read in the body with ACIS.

	FILE* pFile = acis_fopen(tempFilename, "rt");
	if (!pFile)
	{
		cout << "Failed to open temporary SAT file." << endl;
		return;
	}

	ENTITY_LIST ents;
	outcome rc = api_restore_entity_list(pFile, true, ents);
	acis_fclose(pFile);
	if (!rc.ok() || ents.count() != 1 || ents[0]->identity(BODY_LEVEL) != BODY_TYPE)
	{
		cout << "Failed to restore SAT file or invalid number of restored bodies." << endl;
		return;
	}
	BODY* pAcisBody = static_cast<BODY*>(ents[0]);

	// Get the edges from the body.

	ENTITY_LIST edge_list;
	rc = api_get_edges(pAcisBody, edge_list);
	if (!rc.ok())
	{
		cout << "Failed to get edge list from acix body." << endl;
		return;
	}

	// Query for the IRxReferenceKeyManager interface on the Apprentice document
	// to bind the transient keys obtained from the pids to interfaces.

	CComQIPtr<IRxReferenceKeyManager> pRef(pDoc);
	if (!pRef)
	{
		cout << "Failed to query for IRxReferenceKeyManager interface on document." << endl;
		return;
	}

	// Build a map of the transient ID's for each edge of the body
	// and the edge interface pointer that the transient ID binds to.

	TransIDEdgeMap resultIDMap;

	const pid_base* pid = NULL;
	EDGE* pAcisEdge = NULL;
	while (pAcisEdge = static_cast<EDGE*>(edge_list.next()))
	{
		// Get the pid for the edge.

		rc = api_pidget(pAcisEdge, pid);
		if (!rc.ok() || !pid)
		{
			cout << "Failed to get pid from acis edge." << endl;
			return;
		}

		transId = pid->get_index();

		// Bind the transient id (pid) back into an interface.

		pEdge.Release();
		hr = pRef->BindTransientKeyToInterface(const_cast<GUID*>(&IID_IRxEdge), transId, reinterpret_cast<void**>(&pEdge));
		if (FAILED(hr))
		{
			cout << "Failed to bind transient key into an interface - " << hr << endl;
			return;
		}

		insertRes = resultIDMap.insert(TransIDEdgeMap::value_type(transId, pEdge));
		if (!insertRes.second)
		{
			// the pid is a duplicate or we hit this edge twice.
			cout << "Failed to insert to edge data into the map." << endl;
			return;
		}

	}

	// Walk through the maps and verify that the transient id obtained
	// from api_pidget() bound back to the IRxEdge that provides the same
	// transient key.

	for (TransIDEdgeMap::const_iterator it = originalIDMap.begin();it != originalIDMap.end();++it)
	{
		TransIDEdgeMap::const_iterator it2 = resultIDMap.find((*it).first);
		if (it2 == resultIDMap.end())
		{
			cout << "Item in original map not found in result map.  Id - " << (*it).first << endl;
			return;
		}

		if ((*it).second != (*it2).second)
		{
			cout << "Items found in map are not equivalent." << endl;
			return;
		}
		cout << "Transient key " << hex << (*it).first << " matched." << endl;
	}
}
