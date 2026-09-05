// CurvatureAppDisplay.h
// Contains methods useful for displaying Inventor parts using OpenGL.
//

// Includes for OpenGL support
#include <gl/gl.h>
#include <gl/glu.h>
//#include <gl\glaux.h>
#include <windows.h> 

class CReferenceFileMgrMgr;

class CCurvatureAppDisplay
{
public:
  CCurvatureAppDisplay();
  ~CCurvatureAppDisplay();

  void Init(HDC hDC);
  void Clean(bool bPreserveCameraPos = false);

  boolean GetBorelineVector(HWND hWnd, HDC hDC, CPoint point, GLdouble *pt1, GLdouble *pt2);
  boolean GetBorelineDia(HDC hDC, HWND hWnd, UINT nPixels, double *pBorelineDia);

	BOOL CreateViewGLContext(HDC hDC);
	void RenderScene(BOOL bShadedDisplayOn, BOOL bEdgeDisplayOn);
	void Rotate(CSize rotate);
  void Scale(float factor);

 	void BuildListWFDisplay(ULONG numVertices, double* pVertices, ULONG numPolylines, ULONG* pPolylineLengths);
 	void BuildListShadedDisplay(ULONG numFacets, double* pVertices, double* pNormals, ULONG* pVertexIndices);
  void BuildDisplayList(HDC hDC, ULONG numFacets, double* pVertices, double* pNormals,
                        ULONG* pVertexIndices, ULONG numWFVertices, double* pWFVertices,
                        ULONG numWFPolylines, ULONG* pWFPolylineLengths);
  void BuildSelectList(CCurvatureAppView* pView, HDC hDC, ULONG numVertices, double* pVertices, ULONG numIndices, ULONG* pVertexIndices);
  void DeleteSelectList(HDC hDC);
  void BuildCurvatureDisplayList(HDC hDC, ULONG numPoints, double* pPoints, double* pNormals);
  void BuildCurvatureGradientDisplayList(HDC hDC, ULONG numFacets, double* pPoints, double* pNormals, ULONG* pPointIndices);
  void DeleteCurvatureList(HDC hDC);

  void PaintGraphics(HWND hWnd, CPaintDC* pDC, BOOL bShadedDisplayOn, BOOL bEdgeDisplayOn);
  void ResizeGraphics(HDC hDC, int cx, int cy);
  void DestroyGraphics();

  void DrawArrow(double start[3], double normal[3]);

  void GetColor (unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue)
    { *pucRed = m_ucRed; *pucBlue = m_ucBlue; *pucGreen = m_ucGreen; }
  void PutColor (unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue)
    { m_ucRed = ucRed; m_ucBlue = ucBlue; m_ucGreen = ucGreen; }
  void GetLengthUnits (UnitsTypeEnum *pLengthUnits)
    { *pLengthUnits = m_LengthUnits; }
  void PutLengthUnits (UnitsTypeEnum LengthUnits)
    { m_LengthUnits = LengthUnits; }

protected:
  static unsigned int GetNextListId();

protected:
	BOOL m_Rotate;

	HGLRC m_hGLContext;

	double m_transY{0.0};
	double m_transX{0.0};
	double m_angle1{0.0};
	double m_angle2{0.0};

	float m_ScaleX{0.0F};
	float m_ScaleY{0.0F};
	float m_ScaleZ{0.0F};

	unsigned char m_ucRed;
	unsigned char m_ucGreen;
	unsigned char m_ucBlue;
	UnitsTypeEnum m_LengthUnits;

	GLdouble m_xRotate;
	GLdouble m_yRotate;

	unsigned int m_wfListNumber{ 0 };
	unsigned int m_shadedListNumber{ 0 };

  // selection display list
  unsigned int m_selectListNumber{ 0 };
  boolean m_bSelectListOn;

  // curvature display list
  unsigned int m_curvatureListNumber{ 0 };
  bool m_bCurvatureDisplayOn{false};
  unsigned int m_curvatureGradientListNumber{ 0 };
  bool m_bCurvatureGradientDisplayOn{false};
};
