// CurvatureAppDoc.h : interface of the CCurvatureAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVATUREAPPDOC_H__B4B9ABCB_6F88_11D3_AE45_00C04F681329__INCLUDED_)
#define AFX_CURVATUREAPPDOC_H__B4B9ABCB_6F88_11D3_AE45_00C04F681329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum AppHilightMode;
enum AppSelectMode;

class CCurvatureAppView;
class CReferenceFileMgr;
class CCurvatureDialog;

class CCurvatureAppDoc : public CDocument
{
protected: // create from serialization only
	CCurvatureAppDoc();
	DECLARE_DYNCREATE(CCurvatureAppDoc)

// Attributes
public:
  //eMeasureDistanceCommand == 0x4
  typedef enum { eFaceCurvatureCommand, eMeasureFaceCommand, eMeasureEdgeCommand, eMeasureDistanceCommand,
                 eUnknownCommand } ECommand;

  CReferenceFileMgr* GetReferenceFileMgr() { return m_pReferenceFileMgr; }

  bool InCommandMode() { return m_eCommand != eUnknownCommand; }
  ECommand GetCurrentCommand() const { return m_eCommand; }
  void ProcessCommand();
  void CancelCommand();
  void RefreshAllViews(bool bRefreshForUpdate = true);
  void ShowCurvature();
  void MeasureFace();
  void MeasureEdge();
  void MeasureDistance();

  // Are we showing a pin cushion curvature display or a color gradient display?
  bool ShowingPinCushion() const;

  CCurvatureAppView* GetFirstView();

  ULONG GetNumCurvaturePoints();
  double* GetCurvaturePoints();
  double* GetCurvatureNormals();

  double* GetCurvatureGradientPoints();
  double* GetCurvatureGradientNormals();
  ULONG GetNumCurvatureGradientFacets();
  ULONG* GetCurvatureGradientIndices();

  bool GetLiveConnection();

public:
  WCHAR* m_lpReferencedFileName{ nullptr };
  CTime m_lastModifiedTime;
  CReferenceFileMgr* m_pReferenceFileMgr{ nullptr };

  AppSelectMode m_eSelectFilter;
  double m_chordHtTol{0.0};
  BOOL m_shadedDisplayOn;
  BOOL m_edgeDisplayOn;
  UINT m_uDensity{0};
  UINT m_vDensity{0};
  UINT m_selectionTolerance{0};
  bool m_bUseLiveConnection{false};
  bool m_bConnectionTypeSelected{false};

  CCurvatureDialog* m_pCurvatureDlg{ nullptr };
  CString m_curvatureType; // Is it "Pin Cushion" or "Color Gradient"

  ECommand m_eCommand;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvatureAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurvatureAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurvatureAppDoc)
	afx_msg void OnReferenceInventorFile();
	afx_msg void OnToolsMeasureFace();
	afx_msg void OnUpdateToolsMeasureFace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsMeasureDistance(CCmdUI* pCmdUI);
	afx_msg void OnToolsMeasureDistance();
	afx_msg void OnUpdateToolsMeasureEdge(CCmdUI* pCmdUI);
	afx_msg void OnToolsMeasureEdge();
	afx_msg void OnUpdateToolsDisplayShadedImage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsShowCurvature(CCmdUI* pCmdUI);
	afx_msg void OnToolsDisplayImageType();
	afx_msg void OnToolsSpecifyCHT();
	afx_msg void OnToolsOption();
	afx_msg void OnToolsShowCurvature();
	afx_msg void OnRefresh();
  afx_msg void OnDebugbody();
	afx_msg void OnUpdateToolsDebugbody(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandUpdateInventorFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorFile();
	afx_msg void OnDebugState();
	afx_msg void OnUpdateDebugState(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVATUREAPPDOC_H__B4B9ABCB_6F88_11D3_AE45_00C04F681329__INCLUDED_)
