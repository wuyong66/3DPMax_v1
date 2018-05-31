// OpenGLDC.h: interface for the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLDC_H__30E692A3_4129_11D4_B1EE_0010B539EBC0__INCLUDED_)
#define AFX_OPENGLDC_H__30E692A3_4129_11D4_B1EE_0010B539EBC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"

#include "Camera.h"
#include "CadBase.h"

#define BUFFER_LENGTH 64

class  COpenGLDC
{
public:
	COpenGLDC(HWND hWnd);
	virtual ~COpenGLDC();


private:
	HWND	m_hWnd;
	HGLRC	m_hRC;
	HDC		m_hDC;
	COLORREF	m_clrBk;		//Background Color
	COLORREF	m_clr;			//Polygon Color for unshading
	COLORREF	m_clrHighlight; //for highlight using
	COLORREF	m_clrMaterial;  //for normal rendering
	BOOL		m_bShading;		//use material property
	GLfloat		m_vecLight[3];	//lighting direction

	//selection
	BOOL	m_bSelectionMode;
	GLuint	m_selectBuff[BUFFER_LENGTH];
public:
	GCamera		m_Camera;

protected:
	void ClearBkground();
	void CHClearBkground();
	void OnShading();

public:
	void DrawStringPos(const char *str ,CPoint3D p3d);
	//initialize
	BOOL InitDC();
	void GLResize(int cx,int cy);
	void GLSetupRC();

	//uMode :zero for normal rendering. non-zero for selection
	void Ready();
	void CHReady();
	void Finish();

	/////////////////////// light & color //////////////////////
	void Shading(BOOL bShading);
	BOOL IsShading();

	void Lighting(BOOL bLighting);
	BOOL IsLighting();

	//Light direction
	void SetLightDirection(float dx,float dy,float dz);
	void GetLightDirection(float& dx,float& dy,float& dz);

	//material
	void SetMaterialColor(COLORREF clr);
	void GetMaterialColor(COLORREF& clr);
	
	//back ground
	void SetBkColor(COLORREF rgb);
	void GetBkColor(COLORREF& rgb);
	
	//frame material
	void SetColor(COLORREF rgb);
	void GetColor(COLORREF& rgb);

	//high light setting
	void SetHighlightColor(COLORREF clr);
	void GetHighlightColor(COLORREF& clr);
	void Highlight(BOOL bLight = TRUE);


	void drawString(const char *str);
	void display();
	/////////////////// Drawing ////////////////////
	void DrawPoint(const CPoint3D&);

	//drawing curves
	void DrawCoord();

	void DrawLine(const CPoint3D& sp,const CPoint3D& ep);
	void DrawPolyline(const CPoint3D* pt,int size);
	
	//drawing surface
	void DrawTriChip(double n0,double n1,double n2,double v00,double v01,double v02,
					double v10,double v11,double v12,double v20,double v21,double v22);

	//drawing solid entities
	void DrawSphere(const CPoint3D& cen,double r,const CVector3D& vec);
	void DrawCylinder(const CPoint3D& cen,double r,const CVector3D& h);
	void DrawCone(const CPoint3D& cen,double r,const CVector3D& h);
	void DrawTorus(const CPoint3D& cen,const CVector3D& ax,double r_in,double r_out);

	//selection Mode
	void	BeginSelection(int xPos,int yPos);
	int		EndSelection(UINT* items);
	BOOL	IsSelectionMode();

	void	InitNames();
	void	LoadName(UINT name);
	void	PushName(UINT name);
	void    PopName();

};

class  CGLView : public CView
{
protected:
	COpenGLDC*	m_pGLDC;

protected: // create from serialization only
	CGLView();
	DECLARE_DYNCREATE(CGLView)

// Attributes
public:
	virtual void RenderScene(COpenGLDC* pDC);

	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1);
	
	void	Zoom(double dScale);
	void	ZoomAll();
	void	OnViewType(UINT type);
	void	MoveView(double dpx,double dpy);
	void	FenCeng(double fenCengZ);
};
#endif // !defined(AFX_OPENGLDC_H__30E692A3_4129_11D4_B1EE_0010B539EBC0__INCLUDED_)

