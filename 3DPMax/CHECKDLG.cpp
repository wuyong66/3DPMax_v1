// CHECKDLG.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "MainFrm.h"

#include "CHECKDLG.h"

#include "CheckView.h"

#include "3DPMaxView.h"
#include "3DPMaxDoc.h"  //用文档进行信息交换

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCHECKDLG dialog


CCHECKDLG::CCHECKDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CCHECKDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCHECKDLG)
	m_editCeng = 0;
	//}}AFX_DATA_INIT
}


void CCHECKDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHECKDLG)
	DDX_Control(pDX, IDC_SLIDER_CENG, m_slider_ceng);
	DDX_Text(pDX, IDC_EDIT_CENG, m_editCeng);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCHECKDLG, CDialog)
	//{{AFX_MSG_MAP(CCHECKDLG)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTCENGCHECK, OnButcengcheck)
	ON_BN_CLICKED(IDC_BUTCENGSCAN, OnButcengscan)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CENG, OnReleasedcaptureSliderCeng)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CENG, OnCustomdrawSliderCeng)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHECKDLG message handlers

BOOL CCHECKDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();


	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	m_slider_ceng.SetRange(1,pView->cenN);
	m_slider_ceng.SetPos(3);


	CRect rect;
    GetDlgItem(IDC_CHVIEW)->GetClientRect(&rect);
	
	CRuntimeClass *pViewClass=RUNTIME_CLASS(CCheckView);
	CCreateContext* pContext;
	pContext=new CCreateContext;
	pContext->m_pCurrentDoc=NULL;
	pContext->m_pCurrentFrame=NULL;
	pContext->m_pLastView=NULL;
	pContext->m_pNewDocTemplate=NULL;
	pContext->m_pNewViewClass=pViewClass;
	CWnd *pWnd=NULL;
	pWnd=DYNAMIC_DOWNCAST(CWnd,pViewClass->CreateObject());//创建视图窗口
	pWnd->Create(NULL,NULL,AFX_WS_DEFAULT_VIEW,CRect(0,0,0,0),this,0,pContext);
	delete pContext;

	CCheckView *m_pChView=DYNAMIC_DOWNCAST(CCheckView,pWnd);

	//设置视图的位置和大小
	m_pChView->MoveWindow(rect.left+55,rect.top+30,rect.Width()+10,rect.Height(),TRUE);

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCHECKDLG::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CCHECKDLG::OnButcengcheck() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());
	
	Invalidate(false);   //false刷新图，不刷新背景 true刷新背景
	
	UpdateData(TRUE);
	pDoc->m_Nceng = m_editCeng;
	m_slider_ceng.SetPos(m_editCeng);
}



void CCHECKDLG::OnCustomdrawSliderCeng(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	if(pView->m_bool_flag)
	{		
		pDoc->m_paint_flag = TRUE;
	//	AfxMessageBox("切割置位");
	}
	
	int npos = m_slider_ceng.GetPos();

	CString str1;
	str1.Format("%d",npos);
	m_editCeng = npos;

	UpdateData(false);
	
	*pResult = 0;
}

void CCHECKDLG::OnReleasedcaptureSliderCeng(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
void CCHECKDLG::OnButcengscan() 
{
	// TODO: Add your control notification handler code here
	
}



