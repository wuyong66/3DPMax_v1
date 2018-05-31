// ModBusThread.cpp : implementation file
//

#include "stdafx.h"
#include "3dpmax.h"
#include "ModBusThread.h"
#include "ModBusRTU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModBusThread

IMPLEMENT_DYNCREATE(CModBusThread, CWinThread)

CModBusThread::CModBusThread()
{
}

CModBusThread::~CModBusThread()
{
}

BOOL CModBusThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	CModBusRTU *pDlg = new CModBusRTU;  
	pDlg->Create(IDD_DIALOG_MODBUSRTU);   //创建非模态对话框
	pDlg->ShowWindow(SW_SHOW);        //显示对话框
//	m_pMainWnd = pDlg;                

	return TRUE;
}

int CModBusThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	if(m_pMainWnd!= NULL)
		delete m_pMainWnd;	//删除动态指针
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CModBusThread, CWinThread)
	//{{AFX_MSG_MAP(CModBusThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModBusThread message handlers
