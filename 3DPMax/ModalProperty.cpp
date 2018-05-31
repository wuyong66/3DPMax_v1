// ModalProperty.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "MainFrm.h"
#include "ModalProperty.h"

#include "3DPMaxView.h"
#include "3DPMaxDoc.h"  //用文档进行信息交换

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModalProperty dialog


CModalProperty::CModalProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CModalProperty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModalProperty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModalProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModalProperty)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModalProperty, CDialog)
	//{{AFX_MSG_MAP(CModalProperty)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModalProperty message handlers



BOOL CModalProperty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	CString str1 = "",str2 = "",str3 = "",str4 = "";
	str1.Format("%d",pDoc->infoArray[0]);
	str2.Format("%d",pDoc->infoArray[1]);
	str3.Format("%d",pDoc->infoArray[2]);
	str4.Format("%d",pDoc->infoArray[3]);

	SetDlgItemText(IDC_MODLENG,str1);
	SetDlgItemText(IDC_MODWID,str2);
	SetDlgItemText(IDC_MODHIGH,str3);
	SetDlgItemText(IDC_MODTRIA,str4);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
