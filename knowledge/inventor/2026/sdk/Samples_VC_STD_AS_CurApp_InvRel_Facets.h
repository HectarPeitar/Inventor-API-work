/*
  DESCRIPTION

  The functions declared in  this file deal with the retrieval/generation of the facets and strokes pertaining
  to a SurfaceBOdy, Face or an Edge.


  HISTORY

  SS  05/10/01  :  Modified
*/

HRESULT GetFacets (IRxFacets *pFacets, 
                   ULONG* pNumVertices, double** ppVertices, double** ppNormals,
                   ULONG* pNumFacets, ULONG** ppVertexIndices,
                   double AltChordTol);

HRESULT GetStrokes (IRxStrokes *pStrokes, 
                    ULONG* pNumVertices, double** ppVertices,
                    ULONG* pNumPolylines, ULONG** ppPolylineLengths,
                    double AltChordTol);

HRESULT GetDocColor (IRxComponentDocument *pDoc, 
                     unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue);

HRESULT GetDocUnits (IRxComponentDocument *pDoc, 
                     UnitsTypeEnum *pLengthUnits);
