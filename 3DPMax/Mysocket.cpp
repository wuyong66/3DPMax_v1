// Mysocket.cpp : implementation file
//

#include "stdafx.h"
#include "3dpmax.h"
#include "Mysocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysocket

CMysocket::CMysocket(CModBusTcp *pDlg)
{
	pModBusTcp = pDlg;
}

CMysocket::~CMysocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMysocket, CSocket)
	//{{AFX_MSG_MAP(CMysocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMysocket member functions

void CMysocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pModBusTcp)
	{
		//pModBusTcp->ReceieveData();
	}
	CSocket::OnReceive(nErrorCode);
}
