// CurvatureAppDisplay.cpp
// Contains implementations for displaying Inventor documents using OpenGL
//

#include "stdafx.h"
#include <math.h>

#include "../CurvatureAppDoc.h"
#include "../CurvatureAppView.h"

#include "curvatureappdisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// define USE_FRONT_BUFFER_ONLY on NVIDIA RIVA TNT2 cards
// This will cause the display to flicker but you can continue to work.
// #define USE_FRONT_BUFFER_ONLY

#ifdef _DEBUG
#define CHECK_GL_ERROR \
  glEnum = ::glGetError(); //\
//  ASSERT(glEnum == GL_NO_ERROR);
#else
#define CHECK_GL_ERROR
#endif

// Utility vector class used elsewhere in this file
//
class CCurvatureAppVector
{
public:
  CCurvatureAppVector();
  CCurvatureAppVector(const CCurvatureAppVector&);
  CCurvatureAppVector(double, double, double);

  // The additive identity, x-axis, y-axis, and z-axis.
  //
  static const CCurvatureAppVector kIdentity;
  static const CCurvatureAppVector kXAxis;
  static const CCurvatureAppVector kYAxis;
  static const CCurvatureAppVector kZAxis;

  double length() const;
  bool IsZeroLength() const;
  CCurvatureAppVector normalize();
  double dotProduct(const CCurvatureAppVector&) const;
  CCurvatureAppVector crossProduct(const CCurvatureAppVector&) const;

  CCurvatureAppVector perpVector() const;

  double x, y, z;
};

// Initialize global constants.
//
const CCurvatureAppVector CCurvatureAppVector::kIdentity;
const CCurvatureAppVector CCurvatureAppVector::kXAxis(1.0,0.0,0.0);
const CCurvatureAppVector CCurvatureAppVector::kYAxis(0.0,1.0,0.0);
const CCurvatureAppVector CCurvatureAppVector::kZAxis(0.0,0.0,1.0);

CCurvatureAppVector::CCurvatureAppVector() : x(0.0), y(0.0), z(0.0)
{
}

CCurvatureAppVector::CCurvatureAppVector(const CCurvatureAppVector& src) : x(src.x),y(src.y),z(src.z)
{
}

// Creates a vector intialized to ( xx, yy, zz ).
//
CCurvatureAppVector::CCurvatureAppVector(double xx, double yy, double zz) : x(xx),y(yy),z(zz)
{
}

CCurvatureAppVector
CCurvatureAppVector::normalize()
{
  double	len = length(), lengthInv;
  lengthInv = 1.0 / len;
  x *= lengthInv;
  y *= lengthInv;
  z *= lengthInv;
  return *this;
}

// Returns the Euclidean length of this vector.
//
double
CCurvatureAppVector::length() const
{
    return sqrt(x*x + y*y + z*z);
}

// Returns true if this vector is within vector equality tolerance of
// the zero vector.
//
bool
CCurvatureAppVector::IsZeroLength() const
{
    return x == 0.0 && y == 0.0 && z == 0.0;
}

// Returns the dot product of this vector and `v'.
//
double
CCurvatureAppVector::dotProduct(const CCurvatureAppVector& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

// Returns the vector that is the cross product of this vector and `v'.
// That is the vector returned is `this Vector' cross `v' in that
// order.  If the vectors are parallel then the resultant vector is
// equivalent to the CCurvatureAppVector::kIdentity (or zero) vector.
//
CCurvatureAppVector
CCurvatureAppVector::crossProduct(const CCurvatureAppVector& v) const
{
    CCurvatureAppVector result(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x);
    return result;
}

const double kArbBound = 0.015625; // Exactly the value 1/64.

// Returns an arbitrary axis at right angle to
// the given 3d vector src.
//
CCurvatureAppVector CCurvatureAppVector::perpVector() const
{
  CCurvatureAppVector res;

  if (fabs(x) < kArbBound && fabs(y) < kArbBound) {
      // Quick cross product of src with y-axis.
      res.x =  z;
      res.y =  0.0;
      res.z = -x;
      if (res.IsZeroLength()) {
          res.x = -y;
          res.y =  x;
          res.z = 0.0;
      }
  } else {
      // Quick cross product of src with z-axis.
      res.x = -y;
      res.y =  x;
      res.z = 0.0;
  }

  return res;
}

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppDisplay construction/destruction

CCurvatureAppDisplay::CCurvatureAppDisplay()
{
	m_hGLContext = NULL;
	m_xRotate = 0.0;
	m_yRotate = 0.0;
	m_Rotate = FALSE;

	m_ScaleX = 1.0f;
	m_ScaleY = 1.0f;
	m_ScaleZ = 1.0f;

  m_shadedListNumber = CCurvatureAppDisplay::GetNextListId();
  m_wfListNumber = CCurvatureAppDisplay::GetNextListId();
  
  m_selectListNumber = CCurvatureAppDisplay::GetNextListId();
  m_bSelectListOn = false;

  m_curvatureListNumber = CCurvatureAppDisplay::GetNextListId();
  m_curvatureGradientListNumber = CCurvatureAppDisplay::GetNextListId();
  m_bCurvatureDisplayOn = false;
  m_bCurvatureGradientDisplayOn = false;
}

CCurvatureAppDisplay::~CCurvatureAppDisplay()
{
  ::glDeleteLists(m_shadedListNumber, 5); // Also deletes m_wfListNumber, m_selectListNumber, m_curvatureListNumber and m_curvatureGradientListNumber lists
}

void CCurvatureAppDisplay::Init(HDC hDC)
{
  if(CreateViewGLContext(hDC) == FALSE) {
    ASSERT(false);
		return;
  }

  // Background Color
  GLenum glEnum = GL_NO_ERROR;
  ::glClearColor((float)131/255.0f, (float)158/255.0f, (float)132/255.0f, 1.0);
  CHECK_GL_ERROR
}

void CCurvatureAppDisplay::Clean(bool bPreserveCameraPos /*= false*/)
{
  if(!bPreserveCameraPos) {
	  m_hGLContext = NULL;
	  m_xRotate = 0;
	  m_yRotate = 0;
	  m_Rotate = FALSE;

	  m_ScaleX = 1.0f;
	  m_ScaleY = 1.0f;
	  m_ScaleZ = 1.0f;
  }

  // Delete shaded, wf, select and curvature lists
  ::glDeleteLists(m_shadedListNumber, 4);
  GLenum glEnum = GL_NO_ERROR;
  CHECK_GL_ERROR;

  m_bSelectListOn = false;
  m_bCurvatureDisplayOn = false;
  m_bCurvatureGradientDisplayOn = false;
}

//static
unsigned int CCurvatureAppDisplay::GetNextListId()
{
  // static integer used to identify an OGL list
  static unsigned int s_iListId = 1;

  return s_iListId++;
}

BOOL CCurvatureAppDisplay::CreateViewGLContext(HDC hDC)
{
  if(m_hGLContext) {
    if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
      ASSERT(false);
		  return FALSE;
    }
    return TRUE;
  }

  m_hGLContext = ::wglCreateContext(hDC);

  if(m_hGLContext == NULL) {
    HRESULT hr = ::GetLastError();
    ASSERT(SUCCEEDED(hr));
		return FALSE;
  }

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return FALSE;
  }

  return TRUE;
}

void CCurvatureAppDisplay::PaintGraphics(HWND hWnd,
                                         CPaintDC* pDC,
                                         BOOL bShadedDisplayOn,
                                         BOOL bEdgeDisplayOn)
{

  RECT rectangle;
	::GetClientRect(hWnd, &rectangle);
	GLsizei width = rectangle.right;
	GLsizei height = rectangle.bottom;

	GLdouble aspect;
	if(height == 0)
		aspect = (GLdouble)width;
	else
		aspect = (GLdouble)width/(GLdouble)height;

  if(::wglMakeCurrent(pDC->m_ps.hdc, m_hGLContext) == FALSE) {
    ASSERT(false);
		return;
  }

  GLenum glEnum = GL_NO_ERROR;
	::glViewport(0, 0, width, height);
  CHECK_GL_ERROR

  ::glMatrixMode(GL_PROJECTION);
  CHECK_GL_ERROR

  ::glLoadIdentity();
  CHECK_GL_ERROR

  ::glOrtho(-5*aspect, 5*aspect, -5, 5, -200, 200);
  CHECK_GL_ERROR

  ::glMatrixMode(GL_MODELVIEW);
  CHECK_GL_ERROR

  ::glLoadIdentity();
  CHECK_GL_ERROR

#ifdef USE_FRONT_BUFFER_ONLY
	::glDrawBuffer(GL_FRONT);
#else
  ::glDrawBuffer(GL_BACK);
#endif

  CHECK_GL_ERROR

	// Lights, material properties
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};

	// Enable hidden surface removal
	::glEnable(GL_DEPTH_TEST);
  CHECK_GL_ERROR

	// CurvatureGradient can override ShadeDisplay
	if (m_bCurvatureGradientDisplayOn)
	{
		::glDepthFunc(GL_LEQUAL);
		CHECK_GL_ERROR
	}
	else
	{
		::glDepthFunc(GL_LESS);
		CHECK_GL_ERROR
	}

	// Do not calculate inside of the body
	::glEnable(GL_CULL_FACE);
  CHECK_GL_ERROR

	// Counter-clockwise polygons face out
	::glFrontFace(GL_CCW);
  CHECK_GL_ERROR

	// Renormalize normals to allow scaling of scene
	::glEnable(GL_NORMALIZE);
  CHECK_GL_ERROR

	// Enable OpenGL lighting
	::glEnable(GL_LIGHTING);
  CHECK_GL_ERROR

	// bright white light - full intensity RGB values
	::glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
  CHECK_GL_ERROR

	// Enable color tracking
	::glEnable(GL_COLOR_MATERIAL);
  CHECK_GL_ERROR

	// Front material ambient and diffuse colors track glColor
	::glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  CHECK_GL_ERROR

	// Set the material properties such that the polygons reflect our light
	::glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseProperties);
  CHECK_GL_ERROR

	// Lights, material properties
	GLfloat	ambientLight[]  = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat	diffuseLight[]  = {0.8f, 0.8f, 0.8f, 1.0f};

	// add a light at 1.0, 1.0, 1.0
	::glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  CHECK_GL_ERROR
	::glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  CHECK_GL_ERROR

	GLfloat position[4] = { 100.0f, 100.0f, 100.0f, 0.0f };
	::glLightfv(GL_LIGHT0, GL_POSITION, position);
  CHECK_GL_ERROR

	::glEnable(GL_LIGHT0);
  CHECK_GL_ERROR

	RenderScene(bShadedDisplayOn, bEdgeDisplayOn);

	// Tell OpenGL to flush its pipeline
	::glFinish();
  CHECK_GL_ERROR

#ifndef USE_FRONT_BUFFER_ONLY
	bool bSwapErrorCode = true;
   bSwapErrorCode = SwapBuffers(pDC->m_ps.hdc) ? true : false;
  if(!bSwapErrorCode)
  {
    DWORD dwError = ::GetLastError();
  }
#endif

  ::wglMakeCurrent(pDC->m_ps.hdc, NULL);
}

void CCurvatureAppDisplay::RenderScene(BOOL bShadedDisplayOn, BOOL bEdgeDisplayOn)
{
  GLenum glEnum = GL_NO_ERROR;
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  CHECK_GL_ERROR

	::glPushMatrix();
  CHECK_GL_ERROR

	// Position / translation (mouse rotation)
	::glRotated(m_xRotate, 1.0, 0.0, 0.0);
  CHECK_GL_ERROR
	::glRotated(m_yRotate, 0.0, 1.0, 0.0);
  CHECK_GL_ERROR
	::glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
  CHECK_GL_ERROR

  if(bShadedDisplayOn) {
	  ::glCallList(m_shadedListNumber);
    if(bEdgeDisplayOn)
  	  ::glCallList(m_wfListNumber);
  }
  else {
	  ::glCallList(m_wfListNumber);
  }
    
  if(m_bCurvatureGradientDisplayOn)
  {
    ::glCallList(m_curvatureGradientListNumber);
	CHECK_GL_ERROR
  }

  if(m_bCurvatureDisplayOn)
  {
    ::glCallList(m_curvatureListNumber);
	CHECK_GL_ERROR
  }

  ::glCallList(m_selectListNumber);

  CHECK_GL_ERROR

	::glPopMatrix();
  CHECK_GL_ERROR
}

void CCurvatureAppDisplay::ResizeGraphics(HDC hDC, int cx, int cy)
{
	GLsizei width = cx;
	GLsizei height = cy;

	GLdouble aspect;
	if(cy == 0)
		aspect = (GLdouble)width;
	else
		aspect = (GLdouble)width/(GLdouble)height;

  if(!m_hGLContext) // Are we ready yet
    return;

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return;

  GLenum glEnum = GL_NO_ERROR;
	::glViewport(0, 0, width, height);
  CHECK_GL_ERROR
	::glMatrixMode(GL_PROJECTION);
  CHECK_GL_ERROR
	::glLoadIdentity();
  CHECK_GL_ERROR
	::glOrtho(-5*aspect, 5*aspect, -5, 5, -200, 200);
  CHECK_GL_ERROR
	::glMatrixMode(GL_MODELVIEW);
  CHECK_GL_ERROR
	::glLoadIdentity();
  CHECK_GL_ERROR

  ::wglMakeCurrent(hDC, NULL);
}

void CCurvatureAppDisplay::DestroyGraphics()
{
  if(::wglGetCurrentContext() != NULL)
    ::wglMakeCurrent(NULL, NULL);

	if(m_hGLContext != NULL)
	{
    ::wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}

void CCurvatureAppDisplay::Rotate(CSize rotate)
{
  m_yRotate -= rotate.cx;
  m_xRotate -= rotate.cy;
}

void CCurvatureAppDisplay::Scale(float factor)
{
  m_ScaleX *= factor;
  m_ScaleY *= factor;
  m_ScaleZ *= factor;
}

void CCurvatureAppDisplay::BuildDisplayList(HDC hDC,
                                            ULONG numFacets,
                                            double* pVertices,
                                            double* pNormals,
                                            ULONG* pVertexIndices,
                                            ULONG numWFVertices,
                                            double* pWFVertices,
                                            ULONG numWFPolylines,
                                            ULONG* pWFPolylineLengths)
{
  if(!numFacets)
    return;

  ASSERT(pVertices && pNormals && pVertexIndices);

  BuildListShadedDisplay(numFacets, pVertices, pNormals, pVertexIndices);

  if(!numWFVertices)
    return;

  ASSERT(pWFVertices && numWFPolylines && pWFPolylineLengths);
  BuildListWFDisplay(numWFVertices, pWFVertices, numWFPolylines, pWFPolylineLengths);
}

void CCurvatureAppDisplay::BuildListShadedDisplay(ULONG numFacets,
                                                  double* pVertices,
                                                  double* pNormals,
                                                  ULONG* pVertexIndices)
{
  GLenum glEnum = GL_NO_ERROR;

  // delete the earlier list if any
  //
  ::glDeleteLists(m_shadedListNumber, 1);
  CHECK_GL_ERROR

	::glNewList(m_shadedListNumber, GL_COMPILE_AND_EXECUTE);
  CHECK_GL_ERROR

	::glColor4f(m_ucRed/255.0f, m_ucGreen/255.0f, m_ucBlue/255.0f, 1.0);
  CHECK_GL_ERROR

	// shaded display
	//
  ::glShadeModel(GL_SMOOTH);
  CHECK_GL_ERROR

  // Specify the mapping of z values from normalized device coords to window coords
  ::glDepthRange(0.0f, 1.0f);
  CHECK_GL_ERROR

/*
	::glBegin(GL_TRIANGLES);
	for(ULONG ii = 0; ii < numFacets*3; ++ii) {
		::glNormal3dv((GLdouble *)&pNormals[3 * pVertexIndices[ii]]);
    CHECK_GL_ERROR
		::glVertex3dv((GLdouble *)&pVertices[3 * pVertexIndices[ii]]);
    CHECK_GL_ERROR
	}

  ::glEnd();
  CHECK_GL_ERROR
*/
    ::glVertexPointer(3, GL_DOUBLE, 0, pVertices);
  CHECK_GL_ERROR
	::glEnableClientState(GL_VERTEX_ARRAY);
  CHECK_GL_ERROR

	::glNormalPointer(GL_DOUBLE, 0, pNormals);
  CHECK_GL_ERROR
	::glEnableClientState(GL_NORMAL_ARRAY);
  CHECK_GL_ERROR

	// The facets we have are triangles
	::glDrawElements(GL_TRIANGLES, numFacets * 3, GL_UNSIGNED_INT, pVertexIndices);
  CHECK_GL_ERROR

	::glEndList();
  CHECK_GL_ERROR
}

void CCurvatureAppDisplay::BuildListWFDisplay(ULONG numVertices,
                                              double* pVertices,
                                              ULONG numPolylines,
                                              ULONG* pPolylineLengths)
{
  GLenum glEnum = GL_NO_ERROR;

  // delete the earlier list if any
  //
  ::glDeleteLists(m_wfListNumber, 1);
  CHECK_GL_ERROR

	::glNewList(m_wfListNumber, GL_COMPILE_AND_EXECUTE);
  CHECK_GL_ERROR

	// flat display
	//
  ::glShadeModel(GL_FLAT);
  CHECK_GL_ERROR

	::glColor3f(0.0f, 0.0f, 0.0f); // Black color
  CHECK_GL_ERROR

  ::glLineWidth(1.0f);
  CHECK_GL_ERROR
  ::glPointSize(1.0f);
  CHECK_GL_ERROR
/*
	::glBegin(GL_LINES);
  CHECK_GL_ERROR
	for(ULONG ii = 0; ii < numIndices; ++ii) {
		::glVertex3dv((GLdouble *)&pVertices[3*pVertexIndices[ii]]);
    CHECK_GL_ERROR
		::glVertex3dv((GLdouble *)&pVertices[3*pVertexIndices[++ii]]);
    CHECK_GL_ERROR
	}
	::glEnd();
  CHECK_GL_ERROR
*/
//  ::glVertexPointer(3, GL_DOUBLE, 0, pVertices);
//  CHECK_GL_ERROR
//  ::glEnableClientState(GL_VERTEX_ARRAY);
//  CHECK_GL_ERROR

//  ::glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, pVertexIndices);
//  CHECK_GL_ERROR
  ULONG iVtx = 0;
  for (ULONG ii = 0; ii < numPolylines; ii++)
  {
    ::glBegin(GL_LINE_STRIP);
    CHECK_GL_ERROR
    for (ULONG jj = 0; jj < pPolylineLengths[ii]; jj++)
	{
      ::glVertex3dv((GLdouble*)&pVertices[iVtx]);
      iVtx += 3;
    }
    ::glEnd();
    CHECK_GL_ERROR
  }

  ::glEndList();
  CHECK_GL_ERROR
}

void CCurvatureAppDisplay::BuildSelectList(CCurvatureAppView* pView,
                                           HDC hDC,
                                           ULONG numVertices,
                                           double* pVertices,
                                           ULONG numIndices,
                                           ULONG* pVertexIndices)
{
  if(numVertices <= 0 || !pVertices || numIndices <= 0 || !pVertexIndices) {
    return;
  }

	GLenum glEnum = GL_NO_ERROR;

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return;
  }

  // delete the earlier list if any
  //
  ::glDeleteLists(m_selectListNumber, 1);
  CHECK_GL_ERROR

	::glNewList(m_selectListNumber, GL_COMPILE_AND_EXECUTE);
  CHECK_GL_ERROR

	// flat display
	//
  ::glShadeModel(GL_FLAT);
  CHECK_GL_ERROR

	::glColor3f(1.0f, 1.0f, 1.0f); // white color
  CHECK_GL_ERROR

  boolean bVertexDisplay = ((numVertices == 1) ? true : false);

  ::glLineWidth(4.0f);  // four times the size
  CHECK_GL_ERROR
  ::glPointSize(4.0f);
  CHECK_GL_ERROR

  if(!bVertexDisplay)
  {
    /*
	  ::glBegin(GL_LINES);
    CHECK_GL_ERROR
	  for(ULONG ii = 0; ii < numIndices; ++ii) 
    {
		  ::glVertex3dv(&pVertices[3*pVertexIndices[ii]]);
      CHECK_GL_ERROR
		  ::glVertex3dv(&pVertices[3*pVertexIndices[++ii]]);
      CHECK_GL_ERROR
	  }
  	::glEnd();
    CHECK_GL_ERROR
    */
	ULONG iVtx = 0;
	for (ULONG ii = 0; ii < numIndices; ii++)
	{
		::glBegin(GL_LINE_STRIP);
		CHECK_GL_ERROR
		for (ULONG jj = 0; jj < pVertexIndices[ii]; jj++)
		{
		  ::glVertex3dv((GLdouble*)&pVertices[iVtx]);
		  iVtx += 3;
		}
		::glEnd();
		CHECK_GL_ERROR
	}
  }
  else
  {
	  ::glBegin(GL_POINTS);
    CHECK_GL_ERROR
    ::glVertex3dv(pVertices);
  	::glEnd();
    CHECK_GL_ERROR
  }

	::glEndList();
  CHECK_GL_ERROR

  ::wglMakeCurrent(hDC, NULL);

  // we have some in the select list
  m_bSelectListOn = true;
}

void CCurvatureAppDisplay::BuildCurvatureGradientDisplayList(HDC hDC,
                                                             ULONG numFacets,
                                                             double* pPoints,
                                                             double* pNormals,
                                                             ULONG* pVertexIndices)
{
	GLenum glEnum = GL_NO_ERROR;

  if(!numFacets)
    return;

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return;
  }

  // delete the earlier list if any
  //
  ::glDeleteLists(m_curvatureGradientListNumber, 1);
  CHECK_GL_ERROR

	::glNewList(m_curvatureGradientListNumber, GL_COMPILE_AND_EXECUTE);
  CHECK_GL_ERROR

	// smooth display
	//
  ::glShadeModel(GL_SMOOTH);
  CHECK_GL_ERROR

  // Specify the mapping of z values from normalized device coords to window coords
  ::glDepthRange(0.0f, 1.0f);
  CHECK_GL_ERROR

	::glBegin(GL_TRIANGLES);
	for(ULONG ii = 0; ii < numFacets*3; ++ii) {
    // Calculate the length of the normal
    double length = sqrt(pNormals[3 * pVertexIndices[ii]] * pNormals[3 * pVertexIndices[ii]] +
                          pNormals[3 * pVertexIndices[ii]+1] * pNormals[3 * pVertexIndices[ii]+1] +
                          pNormals[3 * pVertexIndices[ii]+2] * pNormals[3 * pVertexIndices[ii]+2]);
    if(length < 0.1) {
	    ::glColor3f(1.0f, 0.0f, 0.0f); // Red color
      CHECK_GL_ERROR
    }
    else if(length >= 0.1 && length < 0.2) {
	    ::glColor3f(0.8f, 0.2f, 0.0f);
      CHECK_GL_ERROR
    }
    else if(length >= 0.2 && length < 0.3) {
	    ::glColor3f(0.8f, 0.0f, 0.2f);
      CHECK_GL_ERROR
    }
    else if(length >= 0.3 && length < 0.4) {
	    ::glColor3f(0.0f, 0.0f, 1.0f); // Blue color
      CHECK_GL_ERROR
    }
    else if(length >= 0.4 && length < 0.5) {
	    ::glColor3f(0.2f, 0.0f, 0.8f);
      CHECK_GL_ERROR
    }
    else if(length >= 0.5 && length < 0.6) {
	    ::glColor3f(0.0f, 0.2f, 0.8f);
      CHECK_GL_ERROR
    }
    else if(length >= 0.6 && length < 0.7) {
	    ::glColor3f(0.0f, 1.0f, 0.0f); // Green color
      CHECK_GL_ERROR
    }
    else if(length >= 0.7 && length < 0.8) {
	    ::glColor3f(0.2f, 0.8f, 1.0f);
      CHECK_GL_ERROR
    }
    else if(length >= 0.8 && length < 0.9) {
	    ::glColor3f(0.0f, 0.8f, 0.2f);
      CHECK_GL_ERROR
    }
    else {
	    ::glColor3f(0.2f, 0.6f, 0.2f);
      CHECK_GL_ERROR
    }

		::glNormal3dv((GLdouble *)&pNormals[3 * pVertexIndices[ii]]);
    CHECK_GL_ERROR
		::glVertex3dv((GLdouble *)&pPoints[3 * pVertexIndices[ii]]);
    CHECK_GL_ERROR
	}

  ::glEnd();
  CHECK_GL_ERROR

	::glEndList();
  CHECK_GL_ERROR

  if(::wglMakeCurrent(hDC, NULL) == FALSE) {
    ASSERT(false);
		return;
  }

  m_bCurvatureDisplayOn = false;
  m_bCurvatureGradientDisplayOn = true;
}

void CCurvatureAppDisplay::BuildCurvatureDisplayList(HDC hDC,
                                                     ULONG numPoints,
                                                     double* pPoints,
                                                     double* pNormals)
{
	GLenum glEnum = GL_NO_ERROR;

  if(!numPoints)
    return;

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return;
  }

  // delete the earlier list if any
  //
  ::glDeleteLists(m_curvatureListNumber, 1);
  CHECK_GL_ERROR

	::glNewList(m_curvatureListNumber, GL_COMPILE_AND_EXECUTE);
  CHECK_GL_ERROR

	// flat display
	//
  ::glShadeModel(GL_FLAT);
  CHECK_GL_ERROR

  ::glLineWidth(1.0f);
  CHECK_GL_ERROR
  ::glPointSize(1.0f);
  CHECK_GL_ERROR

  for(ULONG ii = 0; ii < numPoints; ++ii) {
    DrawArrow(&pPoints[3*ii], &pNormals[3*ii]);
  }

  ::glEndList();
  CHECK_GL_ERROR

  ::wglMakeCurrent(hDC, NULL);

  m_bCurvatureDisplayOn = true;
  m_bCurvatureGradientDisplayOn = false;
}

void CCurvatureAppDisplay::DeleteSelectList(HDC hDC)
{
	GLenum glEnum = GL_NO_ERROR;

  m_bSelectListOn = false;

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return;
  }

  ::glDeleteLists(m_selectListNumber, 1);
  CHECK_GL_ERROR

  ::wglMakeCurrent(hDC, NULL);
}

void CCurvatureAppDisplay::DeleteCurvatureList(HDC hDC)
{
	GLenum glEnum = GL_NO_ERROR;

  m_bCurvatureDisplayOn = false;
  m_bCurvatureGradientDisplayOn = false;

  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return;
  }

  ::glDeleteLists(m_curvatureListNumber, 1);
  CHECK_GL_ERROR    
  ::glDeleteLists(m_curvatureGradientListNumber, 1);
  CHECK_GL_ERROR    

  if(::wglMakeCurrent(hDC, NULL) == FALSE) {
    ASSERT(false);
		return;
  }
}

// Draw an arrow at the given position and with the given normal vector
void CCurvatureAppDisplay::DrawArrow(double start[3], double normal[3])
{
  CCurvatureAppVector normalVector(normal[0], normal[1], normal[2]);

  // Calculate the end point location
  double end[3];
  end[0] = start[0] + normal[0] / 2.0;
  end[1] = start[1] + normal[1] / 2.0;
  end[2] = start[2] + normal[2] / 2.0;

  // Calculate the length of the normal
  GLenum glEnum = GL_NO_ERROR;
  double length = normalVector.length();
  if(length - 0.0 <= PTEQTOL) {
    // Pathological case
    return;
  }

  if(length < 0.3) {
	  ::glColor3f(1.0f, 0.0f, 0.0f); // Red color
    CHECK_GL_ERROR
  }
  else if(length >= 0.3 && length < 0.7) {
	  ::glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    CHECK_GL_ERROR
  }
  else {
	  ::glColor3f(0.0f, 1.0f, 0.0f); // Green color
    CHECK_GL_ERROR
  }

  ::glBegin(GL_LINES);
  CHECK_GL_ERROR

  ::glVertex3dv(start);
  CHECK_GL_ERROR
  ::glVertex3dv(end);
  CHECK_GL_ERROR;

  ::glEnd();
  CHECK_GL_ERROR

  // Normalize the normal vector
  CCurvatureAppVector normalizedVector = normalVector.normalize();

  // Calculate the angle between the normal vector and the Z-Axis
  double angle = normalizedVector.dotProduct(CCurvatureAppVector::kZAxis);
  angle = acos(angle);
  angle *= (180.0 / M_PI);

  // Calculate a vector perpendicular to the normal vector and the Z-Axis
  CCurvatureAppVector perpVector = normalizedVector.crossProduct(CCurvatureAppVector::kZAxis);
  if(perpVector.IsZeroLength()) {
    ASSERT(angle == 0.0 || angle == 180.0);
    perpVector = CCurvatureAppVector::kXAxis;
  }

  double baseRadius = 0.1 * length;
  (baseRadius > 0.05) ? (baseRadius = 0.05) : 0;
  GLdouble height = baseRadius + 0.05;

  GLUquadricObj* pCyl = gluNewQuadric();
  ::gluQuadricDrawStyle(pCyl, GLU_FILL);
  CHECK_GL_ERROR;
  ::gluQuadricNormals(pCyl, GLU_SMOOTH);
  CHECK_GL_ERROR;

  // Draw the arrow
  ::glMatrixMode(GL_MODELVIEW);
  CHECK_GL_ERROR;
  ::glPushMatrix();
  CHECK_GL_ERROR;

  ::glTranslated(end[0], end[1], end[2]);
  CHECK_GL_ERROR;
  ::glRotated(-angle, perpVector.x, perpVector.y, perpVector.z);
  CHECK_GL_ERROR;
  ::gluCylinder(pCyl, baseRadius, 0.0, height, 6, 2);
  CHECK_GL_ERROR;

  ::glPopMatrix();
  CHECK_GL_ERROR
}

boolean CCurvatureAppDisplay::GetBorelineVector(HWND hWnd,
                                                HDC hDC,
                                                CPoint point,
                                                GLdouble *pt1,
                                                GLdouble *pt2)
{
	GLdouble model[16];			// modelview matrix
  GLdouble proj[16];      // projection matrix
	GLint vport[4];			    // viewport
	GLdouble wx, wy, wz;		// window coord
  RECT rect;              // window sizes
  GLint glRet = GL_TRUE;
	GLenum glEnum = GL_NO_ERROR;
  // set context to this window dc
  //
  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return false;
  }

  ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);

  ::glMatrixMode(GL_MODELVIEW);
  CHECK_GL_ERROR

	::glPushMatrix();
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);

  ::glLoadIdentity();
  CHECK_GL_ERROR

	// Position / translation (mouse rotation)
	::glRotated(m_xRotate, 1.0, 0.0, 0.0);
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);
	::glRotated(m_yRotate, 0.0, 1.0, 0.0);
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);
	::glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT,vport);

	::glPopMatrix();
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);
  
  // get the window size
  //
  ::GetClientRect(hWnd, &rect);

  // get a point on the near plane
  //
	wx = point.x;  wy = point.y;  wz = -1.0;

	glRet = gluUnProject(wx, rect.bottom - wy, wz, model, proj, vport, &pt1[0], &pt1[1], &pt1[2]);
  if(GL_FALSE == glRet) {
    ASSERT(false);
    return false;
  }

  // get a point on the far plane
  //
	wz = 1.0;

	glRet = gluUnProject(wx, rect.bottom - wy, wz, model, proj, vport, &pt2[0], &pt2[1], &pt2[2]);
  if(GL_FALSE == glRet) {
    ASSERT(false);
    return false;
  }
  ::wglMakeCurrent(hDC, NULL);
  return true;
}

boolean CCurvatureAppDisplay::GetBorelineDia(HDC hDC, HWND hWnd, UINT nPixels, double *pBorelineDia)
{
	GLdouble model[16];			// modelview matrix
  GLdouble proj[16];      // projection matrix
	GLint vport[4];			    // viewport
	GLdouble wx, wy, wz;		// window coord
  GLdouble pt1[3], pt2[3];
  RECT rect;              // window sizes
  GLint glRet = GL_TRUE;
	GLenum glEnum = GL_NO_ERROR;
  // set context to this window dc
  //
  if(::wglMakeCurrent(hDC, m_hGLContext) == FALSE) {
    ASSERT(false);
		return false;
  }

  ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);

  ::glMatrixMode(GL_MODELVIEW);
  CHECK_GL_ERROR

	::glPushMatrix();
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);

  ::glLoadIdentity();
  CHECK_GL_ERROR

	// Position / translation (mouse rotation)
	::glRotated(m_xRotate, 1.0, 0.0, 0.0);
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);
	::glRotated(m_yRotate, 0.0, 1.0, 0.0);
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);
	::glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT,vport);

	::glPopMatrix();
	glEnum = ::glGetError();
	ASSERT(glEnum == GL_NO_ERROR);
  
  // get the window size
  //
  ::GetClientRect(hWnd, &rect);

  // get a point on the near plane
  //
	wx = 0;  wy = 0;  wz = 0;
  
	glRet = gluUnProject(wx, rect.bottom - wy, wz, model, proj, vport, &pt1[0], &pt1[1], &pt1[2]);
  if(GL_FALSE == glRet) {
    ASSERT(false);
    return false;
  }

  // get a point on the far plane
  //
	wx = nPixels;

	glRet = gluUnProject(wx, rect.bottom - wy, wz, model, proj, vport, &pt2[0], &pt2[1], &pt2[2]);
  if(GL_FALSE == glRet) {
    ASSERT(false);
    return false;
  }

  double dx = pt2[0]-pt1[0], dy = pt2[1]-pt1[1], dz = pt2[2]-pt1[2];

  *pBorelineDia = sqrt(dx*dx + dy*dy + dz*dz);

  ::wglMakeCurrent(hDC, NULL);

  return true;
}
