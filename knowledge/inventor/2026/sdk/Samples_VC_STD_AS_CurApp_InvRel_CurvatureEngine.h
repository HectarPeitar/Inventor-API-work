/*
  DESCRIPTION

  This class defines the object that governs the computation of the Barry Curvatures
  on a supplied Face. An object of this class is held by the 'controller' Reference
  File Manager. There is one Reference File Manager per Document.

  This functionality has been encapsulated into this class mainly to separate out
  and highlight the Inventor-related API calls that may need to be made for such
  purposes. This may not be the best way to structure your application though.

  See the corresponding .cpp file for details on the method. The Curvatures are returned
  in a form ready for display (point and a vector with the magnitude of the curvature)


  HISTORY

  AA  :  10/15/99  :  Creation
*/

#ifndef INCLUDED_CURVATURE_ENGINE_H
#define INCLUDED_CURVATURE_ENGINE_H

struct IRxReferenceKey;
class CReferenceKey;

class CCurvatureEngine 
{
  public:
    CCurvatureEngine();
    ~CCurvatureEngine();

  public:
    void Clean();

  public:
    HRESULT _CalculateCurvatureGradient(CReferenceKey& refKeyFace, double chordTol, double cutOff,
              ULONG* pNumVertices, double** ppVertices, double** ppNormals, ULONG* pNumFacets, ULONG** ppVertexIndices);

    HRESULT _CalculatePinCushion(CReferenceKey& refKeyFace, int uDensity, int VDensity, double CutOff,
              ULONG* pNumPoints, double** ppPoints, double** ppNormals);

  public:
    ULONG m_numCurvaturePoints;
    double* m_pCurvaturePoints{ nullptr };
    double* m_pCurvatureNormals{ nullptr };

    double* m_pCurvatureGradientPoints{ nullptr };
    double* m_pCurvatureGradientNormals{ nullptr };
    ULONG m_numCurvatureGradientFacets;
    ULONG* m_pCurvatureGradientIndices{ nullptr };


  // Method(s) that focus on calling into the Inventor API to obtain the information
  // required by this application.

  public:
    HRESULT CalculateCurvatureGradient(/* [in]  */ IRxReferenceKey *pKeyFace,
                                       /* [in]  */ double chordTol,
                                       /* [in]  */ double cutOff,
                                       /* [out]  */ ULONG* pNumVertices,
                                       /* [out]  */ double** ppVertices,
                                       /* [out]  */ double** ppNormals,
                                       /* [out]  */ ULONG* pNumFacets,
                                       /* [out]  */ ULONG** ppVertexIndices);

    HRESULT CalculatePinCushion(/* [in]  */ IRxReferenceKey *pKeyFace, 
                                /* [in]  */ int uDensity, 
                                /* [in]  */ int VDensity, 
                                /* [in]  */ double CutOff,
                                /* [out]  */ ULONG* pNumPoints, 
                                /* [out]  */ double** ppPoints, 
                                /* [out]  */ double** ppNormals);
};

#endif