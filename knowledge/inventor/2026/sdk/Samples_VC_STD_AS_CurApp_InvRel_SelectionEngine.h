/*
  DESCRIPTION

  This class defines the object that performs the query on the Inventor file during
  the 'pick' process. The geometry enquiry that determines the object that got 'hit' 
  by the pick-ray as well as the obtaining of the polyline to display for the purpose of
  the highlight during the pick process are the parts that call into the Inventor
  API. The rest of the selection process is entirely application-specific (manufacturing
  the pick-ray and the actual rendering for the highlighting, etc.).
  
  An object of this class is held by the 'controller' Reference File Manager. There 
  is one Reference File Manager per Document.

  This functionality has been encapsulated into this class mainly to separate out
  and highlight the Inventor-related API calls that may need to be made for such
  purposes. This may not be the best way to structure your application though.

  See the corresponding .cpp file for details on the method


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#ifndef INCLUDED_SELECTION_ENGINE_H
#define INCLUDED_SELECTION_ENGINE_H

interface IRxReferenceKey;
enum AppSelectMode;

class CSelectionEngine 
{
  public:
    CSelectionEngine();
    ~CSelectionEngine();

  public:
    void Clean(bool bCleanForUpdate = false);
    HRESULT PerformSelection(IRxComponentDocument * pDoc, AppSelectMode eSelectMode, double dLocateRadius, double chordHeightTol, double *dBoreVecPt1, double *dBoreVecPt2);
    HRESULT BuildSelectStrokes(double chordHeightTol);

    ULONG GetNumWFSelVertices() const { return m_dwNumWFSelVertices; }
    double* GetWFSelVertices() const { return m_WFSelVertices; }
    ULONG GetNumWFSelIndices() const { return m_dwNumWFSelIndices; }
    ULONG* GetWFSelIndices() const { return m_WFSelIndices; }

    IRxReferenceKey* GetLastSelectedObject();                 // non counting
	IRxReferenceKey* GetFirstVertex();						  // non counting
    HRESULT SetLastSelectedObject(IRxReferenceKey *pRefKey);  //counting

  protected:
	  ULONG m_dwNumWFSelVertices;
	  double* m_WFSelVertices{ nullptr };
    ULONG m_dwNumWFSelIndices;
	  ULONG* m_WFSelIndices{ nullptr };
    
    //Used to hold the previous selected vertex.
    //Two vertices needed to use MeasureDistance.
	IRxReferenceKey* m_pFirstVertex{ nullptr };

    IRxReferenceKey* m_pRefKey{ nullptr };

	HRESULT GetDocument(IUnknown *pServer, IRxComponentDocument **  ppDoc);

  // Method(s) that focus on calling into the Inventor API to obtain the information
  // required by this application.

  public:
    HRESULT GetSelection(/* [in]  */ IRxComponentDocument * pDoc,
                         /* [in]  */ AppSelectMode eSelectMode,
                         /* [in]  */ double dLocateRadius,                                          
                         /* [in]  */ double *pBoreVecPt1,
                         /* [in]  */ double *pBoreVecPt2,
                         /* [out] */ IRxReferenceKey **ppSelObjKey);

    HRESULT GetSelectStrokes(/* [in]  */ IRxReferenceKey *pSelObjKey, 
                             /* [in]  */ double chordHeightTol,
                             /* [out] */ ULONG *pNumSelVertices, 
                             /* [out] */ double **ppSelVertices,
                             /* [out] */ ULONG *pNumSelIndices, 
                             /* [out] */ ULONG **ppSelIndices);
};

#endif