/*
  DESCRIPTION

  This class defines the object that performs measurement computations for the Area
  of a Face, Length of an Edge and the Distance between two Vertices. These values
  are then displayed to the end-user via a command. 
  
  An object of this class is held by the 'controller' Reference File Manager. There 
  is one Reference File Manager per Document.

  This functionality has been encapsulated into this class mainly to separate out
  and highlight the Inventor-related API calls that may need to be made for such
  purposes. This may not be the best way to structure your application though.

  See the corresponding .cpp file for details on the method

  
  NOTE

  This class ends up holding the dialog box to perform the display as well. 


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#ifndef INCLUDED_MEASURE_ENGINE_H
#define INCLUDED_MEASURE_ENGINE_H

interface IRxReferenceKey;
class CMeasureDlg;
class CReferenceKey;

class CMeasureEngine 
{
  protected:
    IRxReferenceKey* m_pFaceRefKey{ nullptr };
    IRxReferenceKey* m_pEdgeRefKey{ nullptr };
    IRxReferenceKey* m_pVtx1RefKey{ nullptr };
    IRxReferenceKey* m_pVtx2RefKey{ nullptr };
    CMeasureDlg* m_pMeasureDlg{ nullptr };
    UnitsTypeEnum m_LengthUnits;

  public:
    CMeasureEngine();
    ~CMeasureEngine();

  public:
    void Clean();
    void CancelCommand();
    UnitsTypeEnum GetLengthUnits ()
      { return m_LengthUnits; }
    void PutLengthUnits (UnitsTypeEnum LengthUnits)
      { m_LengthUnits = LengthUnits; }
    HRESULT MeasureFace(CReferenceKey& refKeyFace);
    HRESULT MeasureEdge(CReferenceKey& refKeyEdge);
    HRESULT MeasureDistance(CReferenceKey& refKeyVtx1, CReferenceKey &refKeyVtx2);

  // Method(s) that focus on calling into the Inventor API to obtain the information
  // required by this application.

  public:
    HRESULT MeasureFace(/* [in]  */ IRxReferenceKey *pFaceRefKey, 
                        /* [out]  */ double *area);

    HRESULT MeasureEdge(/* [in]  */ IRxReferenceKey *pEdgeRefKey, 
                        /* [out]  */ double *length);

    HRESULT MeasureDistance(/* [in]  */ IRxReferenceKey *pVtx1RefKey, 
                            /* [in]  */ IRxReferenceKey *pVtx2RefKey, 
                            /* [out]  */ double *distance);
};

#endif