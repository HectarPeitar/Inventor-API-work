/*
  DESCRIPTION

  Implementation of the management methods of the CMeasureEngine class. 


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include <math.h>
#include "../AppRelated/MeasureDlg.h"
#include "measureengine.h"
#include "referencekeyengine.h"


/*--------------- Constructor(s), destructor and initializers ----------------------*/

CMeasureEngine::CMeasureEngine():
m_pMeasureDlg(0), m_LengthUnits (kCentimeterLengthUnits)
{
    m_pMeasureDlg = new CMeasureDlg();
    BOOL ret = m_pMeasureDlg->Create(IDD_MEASURE_DIALOG, NULL);
    ASSERT(ret);
}

CMeasureEngine::~CMeasureEngine()
{
  Clean();
  if(m_pMeasureDlg) { m_pMeasureDlg->DestroyWindow(); }
}

void CMeasureEngine::Clean()
{
  if(m_pMeasureDlg)
    m_pMeasureDlg->ShowWindow(SW_HIDE); 
}

void CMeasureEngine::CancelCommand()
{
  if(m_pMeasureDlg)
    m_pMeasureDlg->ShowWindow(SW_HIDE); 
}


/*------------------- Management functions ---------------------------------*/

HRESULT CMeasureEngine::MeasureFace(CReferenceKey& refKeyFace)
{
  double value=0.0;
  CString property;
  HRESULT hr = NOERROR;
  IRxReferenceKey *pRefKey = NULL;

  pRefKey = refKeyFace.get_Object();
  if(!pRefKey)
    return S_OK;
  
  // show the dlg
  //
  m_pMeasureDlg->ShowWindow(SW_SHOW); 

  // Fire off to the worker
  //
  hr = MeasureFace(pRefKey, &value);
  OnError(FAILED(hr), wrapup);
    
  property = "Face Area";

  // stuff the dlg controls with right prop/value texts
  //
  if (m_LengthUnits == kInchLengthUnits)
    m_pMeasureDlg->m_MeasureValue.Format("%5.3f in**2", value / (2.54 * 2.54));
  else
    m_pMeasureDlg->m_MeasureValue.Format("%5.3f cm**2", value);
  m_pMeasureDlg->m_MeasureProperty = property;

  // Update the controls
  //
  m_pMeasureDlg->UpdateData(FALSE);

wrapup:

  return hr;
}

HRESULT CMeasureEngine::MeasureEdge(CReferenceKey& refKeyEdge)
{
  double value=0.0;
  CString property;
  HRESULT hr=NOERROR;
  IRxReferenceKey *pRefKey=NULL;

  pRefKey = refKeyEdge.get_Object();
  if(!pRefKey)
    return S_OK;

  // show the dlg
  //
  m_pMeasureDlg->ShowWindow(SW_SHOW); 


  // Fire it off to the worker
  //
  hr = MeasureEdge(pRefKey, &value);
  OnError(FAILED(hr), wrapup);
  
  property = "Edge Length";

  // stuff the dlg controls with right prop/value texts
  //
  m_pMeasureDlg->m_MeasureValue.Format("%5.3f cm", value);
  m_pMeasureDlg->m_MeasureProperty = property;

  // Update the controls
  //
  m_pMeasureDlg->UpdateData(FALSE);

wrapup:

  return hr;
}

HRESULT CMeasureEngine::MeasureDistance(CReferenceKey& refKeyVtx1, CReferenceKey &refKeyVtx2)
{
  double value=0.0;
  CString property;
  HRESULT hr=NOERROR;
  IRxReferenceKey *pRefKeyVtx1=NULL, *pRefKeyVtx2=NULL;

  pRefKeyVtx1 = refKeyVtx1.get_Object();
  if(!pRefKeyVtx1)
    return S_OK;

  pRefKeyVtx2 = refKeyVtx2.get_Object();
  if(!pRefKeyVtx2)
    return S_OK;
  
  // show the dlg
  //
  m_pMeasureDlg->ShowWindow(SW_SHOW); 

  // Fire it off to the worker
  //
  hr = MeasureDistance(pRefKeyVtx1, pRefKeyVtx2, &value);
  OnError(FAILED(hr), wrapup);
    
  property = "Distance";

  // stuff the dlg controls with right prop/value texts
  //
  m_pMeasureDlg->m_MeasureValue.Format("%5.3f cm", value);
  m_pMeasureDlg->m_MeasureProperty = property;

  // Update the controls
  //
  m_pMeasureDlg->UpdateData(FALSE);

wrapup:

  return hr;
}
