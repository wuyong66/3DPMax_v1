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
	pDlg->Create(IDD_DIALOG_MODBUSRTU);   //������ģ̬�Ի���
	pDlg->ShowWindow(SW_SHOW);        //��ʾ�Ի���
//	m_pMainWnd = pDlg;                

	return TRUE;
}

int CModBusThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	if(m_pMainWnd!= NULL)
		delete m_pMainWnd;	//ɾ����ָ̬��
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CModBusThread, CWinThread)
	//{{AFX_MSG_MAP(CModBusThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModBusThread message handlers
