/*
  DESCRIPTION

  This class defines the object that encapsulates the actual 'Reference' being
  held to the file. This reference ends up being the pointer to the server that
  has been CoCreated and initialized with the Inventor file. The server is more
  of an analogue of the Application object, but because it handles just one file 
  at a time, it can be seen as the analogue of the file itself.
 
  Using this pointer to the dedicated server (dedicated to service the specified
  Inventor file), one can close and open files. 
  
  In addition, this class also provides the functionality to obtain facets and 
  strokes to perform display of the file. Some simple traversal through the 
  BRep objects is also implemented here.
    
  An object of this class is held by the 'controller' Reference
  File Manager. There is one Reference File Manager per Document.

  This functionality has been encapsulated into this class mainly to separate out
  and highlight the Inventor-related API calls that may need to be made for such
  purposes. This may not be the best way to structure your application though.

  See the corresponding .cpp file for details on the method. 


  HISTORY

  AA  :  10/15/99  :  Creation
*/

#ifndef INCLUDED_REFERENCE_FILE_H
#define INCLUDED_REFERENCE_FILE_H

class CReferenceFile 
{
  public:
    CReferenceFile(bool bUseLiveConnection);
   ~CReferenceFile();

  public:
    void Clean();

  public:
    IRxApprenticeServer* GetApprenticeServer() { return m_pApprenticeServer; }
    Application* GetInventorApplication() { return m_spInventorApplication; }

	// Wrappers that use Apprentice or Inventor, depending on the connection
	bool IsConnected();
    IUnknown * GetServer();
	IRxComponentDocument * GetDocument();

	HRESULT GetDocument(IRxComponentDocument **  ppDoc);
	HRESULT OpenDocument(BSTR bstrFileName, IRxComponentDocument **  ppDoc);

    void SetNumVertices(ULONG numVertices) { m_dwNumVertices = numVertices; }
    ULONG GetNumFacets() const { return m_dwNumFacets; }
    void SetNumFacets(ULONG numFacets) { m_dwNumFacets = numFacets; }
    double* GetVertices() const { return m_vertices; }
    void SetVertices(double* vertices) { m_vertices = vertices; }
    ULONG* GetVertexIndices() const { return m_vertexIndices; }
    void SetVertexIndices(ULONG* vertexIndices) { m_vertexIndices = vertexIndices; }
    double* GetNormals() const { return m_normals; }
    void SetNormals(double* normals) { m_normals = normals; }

    ULONG GetNumWFVertices() const { return m_dwNumWFVertices; }
    void SetNumWFVertices(ULONG numWFVertices) { m_dwNumWFVertices = numWFVertices; }
    double* GetWFVertices() const { return m_WFVertices; }
    void SetWFVertices(double* pWFVertices) { m_WFVertices = pWFVertices; }
    ULONG GetNumWFPolylines() const { return m_dwNumWFPolylines; }
    void SetNumWFPolylines(ULONG numWFPolylines) { m_dwNumWFPolylines = numWFPolylines; }
    ULONG* GetWFPolylineLengths() const { return m_WFPolylineLengths; }
    void SetWFPolylineLengths(ULONG* pWFPolylineLengths) { m_WFPolylineLengths = pWFPolylineLengths; }
    void GetColor (unsigned char *pRed, unsigned char *pGreen, unsigned char *pBlue) 
      { *pRed = m_ucRed; *pGreen= m_ucGreen; *pBlue= m_ucBlue; }
    void SetColor (unsigned char Red, unsigned char Green, unsigned char Blue)
      { m_ucRed = Red; m_ucGreen = Green; m_ucBlue = Blue; }
    void GetLengthUnits (UnitsTypeEnum *pLengthUnits)
      { *pLengthUnits = m_LengthUnits; }
    void SetLengthUnits (UnitsTypeEnum LengthUnits)
      { m_LengthUnits = LengthUnits; }

    HRESULT _ReferenceFile(LPCOLESTR lpFileName);
    HRESULT _CalculateFacets(double chordTol, ULONG* pNumVertices, double** ppVertices,
                             double** ppNormals, ULONG* pNumFacets, ULONG** ppVertexIndices);
    HRESULT _CalculateStrokes(double chordTol, ULONG* pNumWFVertices, double** ppWFVertices,
                              ULONG* pNumWFPolylines, ULONG** ppWFPolylineLengths);
    HRESULT _GetBodyInfo(int& nFaceShellCount, int& nFaceCount, int& nEdgeCount, int& nVertexCount, double& fVolume);

  protected:
	CReferenceFile();

	bool m_bUseLiveConnection{false};
    IRxApprenticeServer* m_pApprenticeServer{ nullptr };
    CComPtr<Application> m_spInventorApplication;
	CComPtr<Document> m_spDocument;
    CString m_strFileName;

    // Data members for caching the facet information for this document
    ULONG m_dwNumVertices; // number of vertices. corresponds with m_vertices and m_normals
    ULONG m_dwNumFacets; // number of facets. corresponds with m_indexArray
    double* m_vertices{ nullptr }; // array of vertices arranged in [x,y,z] values
    double* m_normals{ nullptr }; // array of normals arranged in [x,y,z] values
    ULONG* m_vertexIndices{ nullptr }; // array of vertex indices that form facets

    // Data members for caching the strokes information for this document
    ULONG m_dwNumWFVertices; // number of vertices. corresponds with m_vertices and m_normals
    double* m_WFVertices{ nullptr }; // array of vertices arranged in [x,y,z] values
    ULONG m_dwNumWFPolylines; // number of polylines in the m_WFPolylineLengths array
    ULONG* m_WFPolylineLengths{ nullptr }; // array of lengths of each polyline

    // Data members for caching color and units of length for this file.
    unsigned char m_ucRed;
    unsigned char m_ucGreen;
    unsigned char m_ucBlue;
    UnitsTypeEnum m_LengthUnits;

    HRESULT FacetsFromOccurrence(/* [in]  */ IRxComponentOccurrence* pOccurrence,
                                 /* [in]  */ double chordTol,
                                 /* [out] */ ULONG* pNumVertices,
                                 /* [out] */ double** ppVertices,
                                 /* [out] */ double** ppNormals,
                                 /* [out] */ ULONG* pNumFacets,
                                 /* [out] */ ULONG** ppVertexIndices);

    HRESULT FacetsFromSurfBodies(/* [in]  */ IRxEnumSurfaceBodies* pEnumSurfBodies,
                                 /* [in]  */ double chordTol,
                                 /* [out] */ ULONG* pNumVertices,
                                 /* [out] */ double** ppVertices,
                                 /* [out] */ double** ppNormals,
                                 /* [out] */ ULONG* pNumFacets,
                                 /* [out] */ ULONG** ppVertexIndices);

    HRESULT StrokesFromOccurrence(/* [in]  */ IRxComponentOccurrence* pOccurrence,
                                  /* [in]  */ double chordTol,
                                  /* [out] */ ULONG* pNumWFVertices,
                                  /* [out] */ double** ppWFVertices,
                                  /* [out] */ ULONG* pNumWFPolylines,
                                  /* [out] */ ULONG** ppWFPolylineLengths);

    HRESULT StrokesFromSurfBodies(/* [in]  */ IRxEnumSurfaceBodies* pEnumSurfBodies,
                                  /* [in]  */ double chordTol,
                                  /* [out] */ ULONG* pNumWFVertices,
                                  /* [out] */ double** ppWFVertices,
                                  /* [out] */ ULONG* pNumWFPolyines,
                                  /* [out] */ ULONG** ppWFPolylineLengths);

  // Method(s) that focus on calling into the Inventor API to obtain the information
  // required by this application.

  public:

    HRESULT ConnectToServer(/* [out] */ IRxApprenticeServer **ppServer);
    HRESULT ConnectToInventor(/* [out] */ Application **ppServer);

    HRESULT ReferenceFile(/* [in] */ IUnknown *pServer,
                          /* [in] */ LPCOLESTR lpFileName);
    
    HRESULT CalculateFacets(/* [in]  */ IUnknown *pServer,
                            /* [in]  */ double chordTol,
                            /* [out] */ ULONG* pNumVertices,
                            /* [out] */ double** ppVertices,
                            /* [out] */ double** ppNormals,
                            /* [out] */ ULONG* pNumFacets,
                            /* [out] */ ULONG** ppVertexIndices);

    HRESULT CalculateStrokes(/* [in]  */ IUnknown *pServer,
                             /* [in]  */ double chordTol,
                             /* [out] */ ULONG* pNumWFVertices,
                             /* [out] */ double** ppWFVertices,
                             /* [out] */ ULONG* pNumWFPolylines,
                             /* [out] */ ULONG** ppWFPolylineLengths);

    HRESULT GetBodyInfo(/* [in]  */ IUnknown *pServer,
                        /* [out] */ int& nFaceShellCount, 
                        /* [out] */ int& nFaceCount, 
                        /* [out] */ int& nEdgeCount, 
                        /* [out] */ int& nVertexCount, 
                        /* [out] */ double& fVolume);
	
	HRESULT IterateOccurrence(/* [in]  */ ComponentOccurrence *pCompOcce,
							  /* [out] */ int& nFaceShellCount,
							  /* [out] */ int& nFaceCount,
							  /* [out] */ int& nEdgeCount,
							  /* [out] */ int& nVertexCount,
							  /* [out] */ double& fVolume);

	HRESULT CalculateBodyInfo(/* [in]  */ SurfaceBodies *pSurfBodies,
							  /* [out] */ int& nFaceShellCount,
							  /* [out] */ int& nFaceCount,
							  /* [out] */ int& nEdgeCount,
							  /* [out] */ int& nVertexCount,
							  /* [out] */ double& fVolume);

  
};

#endif
