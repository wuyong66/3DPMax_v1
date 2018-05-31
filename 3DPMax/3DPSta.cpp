// 3DPSta.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "3DPSta.h"


#include "MainFrm.h"
#include "3DPMaxDoc.h"
#include "3DPMaxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DPSta dialog


C3DPSta::C3DPSta(CWnd* pParent /*=NULL*/)
	: CDialog(C3DPSta::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DPSta)
	m_cengNum = 0;
	m_printNum = _T("");
	//}}AFX_DATA_INIT
}


void C3DPSta::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DPSta)
	DDX_Text(pDX, IDC_CENG_NUM, m_cengNum);
	DDX_Text(pDX, IDC_PRINT_NUM, m_printNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DPSta, CDialog)
	//{{AFX_MSG_MAP(C3DPSta)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL C3DPSta::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetTimer(1,100,NULL);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DPSta::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	m_cengNum = pDoc->CengNumNow;
	m_printNum = pDoc->PrintNumNow;
	UpdateData(FALSE);

	
	CDialog::OnTimer(nIDEvent);
}
