// CheckView.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "MainFrm.h"
#include "CheckView.h"

#include "3DPMaxView.h"
#include "3DPMaxDoc.h"  //用文档进行信息交换


#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckView

IMPLEMENT_DYNCREATE(CCheckView, CGLView)

CCheckView::CCheckView()
{
	
}

CCheckView::~CCheckView()
{
}


BEGIN_MESSAGE_MAP(CCheckView, CGLView )
	//{{AFX_MSG_MAP(CCheckView)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckView drawing

void CCheckView::OnInitialUpdate()
{
	CGLView::OnInitialUpdate();

	CSize sizeTotal;

}



void CCheckView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
		if(m_pGLDC)
		{
			m_pGLDC->CHReady();
			RenderScene(m_pGLDC);
			m_pGLDC->Finish();
		}
	
	
}

BOOL CCheckView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CGLView ::PreCreateWindow(cs);
}


//待加入代码
void CCheckView::RenderScene(class COpenGLDC *pDC)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	if(pDoc->m_paint_flag)
	{
		for(int j = 0; j <pDoc->pSTLModel->m_Z_fenceng.GetSize(); j++)
			{
				if(pDoc->pSTLModel->m_Z_fenceng[j]->cenNum == pDoc->m_Nceng)     //m_Z_fenceng[j] 是按顺序存储的，
				{
					CPoint3D   a1 ;
					CPoint3D   a2 ;
					a1 = pDoc->pSTLModel->m_Z_fenceng[j]->a1;//取出a1、a2两个交点
					a2 = pDoc->pSTLModel->m_Z_fenceng[j]->a2;

						
					COLORREF old_clr;
					pDC->GetColor(old_clr);

					pDC->SetColor(RGB(255,0,0));//黄色
					pDC->DrawLine(a1,a2);//变色，画线

					pDC->SetColor(old_clr);	
				}
			}
	}
	else
	{
		AfxMessageBox("您还没有分层！请先分层");;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CCheckView diagnostics

#ifdef _DEBUG
void CCheckView::AssertValid() const
{
	CView::AssertValid();
}

void CCheckView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG




void CCheckView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CGLView ::OnRButtonDown(nFlags, point);
}

BOOL CCheckView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(zDelta > 100){
		Zoom(0.9);
		Invalidate();
	}
	if(zDelta < -100){
		Zoom(1.1);
		Invalidate();}
	return CGLView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCheckView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	SetFocus();
	CGLView ::OnLButtonDown(nFlags, point);

}
