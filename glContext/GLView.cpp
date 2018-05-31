#include "stdafx.h"
#include "OpenGLDC.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView construction/destruction

CGLView::CGLView()
{
	m_pGLDC = NULL;
}

CGLView::~CGLView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGLView drawing

void CGLView::OnDraw(CDC* pDC)
{
//	AfxMessageBox("父类OnDraw()");
	if(m_pGLDC){
		m_pGLDC->Ready();
		RenderScene(m_pGLDC);
		m_pGLDC->Finish();
	}
	
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs)
{

	//  Add Window style required for OpenGL before window is created
	cs.style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers
void CGLView::RenderScene(COpenGLDC* pDC)
{

	AfxMessageBox("父类RenderScene");//此处做一个标记，看看父类的这个函数RenderScene有没有被执行，废话重载了呀
	pDC->DrawCoord();
}

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pGLDC = new COpenGLDC(this->GetSafeHwnd());
	m_pGLDC->InitDC();
//	AfxMessageBox("1111");先于OnDraw函数对m_pGLDC赋予初始化值
	return 0;
}

void CGLView::OnDestroy() 
{
	CView::OnDestroy();
	if(m_pGLDC)	delete m_pGLDC;	
}

void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if(m_pGLDC)	
		m_pGLDC->GLResize(cx,cy);
}

BOOL CGLView::OnEraseBkgnd(CDC* pDC) 
{
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CGLView::OnViewType(UINT type)
{
	ASSERT(type >= VIEW_FRONT && type <= VIEW_NW_ISOMETRIC);
	m_pGLDC->m_Camera.set_view_type(type);
	Invalidate();
}

BOOL CGLView::GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1)
{
	return FALSE;
}

void CGLView::ZoomAll()
{
	
	double x0,y0,z0,x1,y1,z1;
	if(GetBox(x0,y0,z0,x1,y1,z1)){//经过多次父子类函数调用的分析，可以表明，此处调用的是子类的GetBox信息，与父类无关
		m_pGLDC->m_Camera.zoom_all(x0,y0,z0,x1,y1,z1);
	//	AfxMessageBox("ZoomAll");不知道为什么GetBox总是能使if语句执行
		Invalidate();
	}
}

void CGLView::Zoom(double dScale)
{
	m_pGLDC->m_Camera.zoom(dScale);
	Invalidate();
}

void CGLView::MoveView(double dpx,double dpy)
{
	m_pGLDC->m_Camera.move_view(dpx,dpy);
	Invalidate();
}


