// CheckThread.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "CheckThread.h"
#include "CHECKDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckThread

IMPLEMENT_DYNCREATE(CCheckThread, CWinThread)

CCheckThread::CCheckThread()
{
}

CCheckThread::~CCheckThread()
{
}

BOOL CCheckThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	CCHECKDLG *pDlg = new CCHECKDLG;  
	pDlg->Create(IDD_DIALOG_CHECK);   //创建非模态对话框
	pDlg->ShowWindow(SW_SHOW);        //显示对话框
	m_pMainWnd = pDlg;                

	return TRUE;
}

int CCheckThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	if(m_pMainWnd!= NULL)
		delete m_pMainWnd;	//删除动态指针
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCheckThread, CWinThread)
	//{{AFX_MSG_MAP(CCheckThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckThread message handlers
