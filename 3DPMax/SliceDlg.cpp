// SliceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "SliceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliceDlg dialog


CSliceDlg::CSliceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSliceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSliceDlg)
	m_hou = 1.0;
	m_cen = 100;
	m_sel = 0;
	//}}AFX_DATA_INIT
}


void CSliceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSliceDlg)
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_cenCtrl);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_houCtrl);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_hou);
	DDV_MinMaxDouble(pDX, m_hou, 1.e-017, 1.e+025);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_cen);
	DDV_MinMaxInt(pDX, m_cen, 1, 2147483647);
	DDX_Radio(pDX, IDC_HEIGHT, m_sel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSliceDlg, CDialog)
	//{{AFX_MSG_MAP(CSliceDlg)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_HEIGHT, OnHeight)
	ON_BN_CLICKED(IDC_NUMBER, OnNumber)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliceDlg message handlers

void CSliceDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialog::OnOK();
}

void CSliceDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	
	CDialog::OnCancel();
}

void CSliceDlg::OnHeight() 
{
	// TODO: Add your control notification handler code here
	m_houCtrl.EnableWindow(TRUE);
	m_cenCtrl.EnableWindow(FALSE);
	UpdateData();
}

void CSliceDlg::OnNumber() 
{
	// TODO: Add your control notification handler code here
	m_cenCtrl.EnableWindow(TRUE);
	m_houCtrl.EnableWindow(FALSE);
	UpdateData();
}

HBRUSH CSliceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_EDIT) 
	{
		pDC->SetTextColor(RGB(255,0,0));  
	//	pDC->SetBkColor(RGB(10,255,55));  
	}


	if(nCtlColor == CTLCOLOR_STATIC  ) 
	{
		pDC->SetTextColor(RGB(0,0,255));  
	//	pDC->SetBkColor(RGB(10,255,55));  
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CSliceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cenCtrl.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
