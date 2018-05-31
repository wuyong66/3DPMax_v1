#if !defined(AFX_MYSOCKET_H__A8FF5167_1194_4349_BB6E_046DE2994F27__INCLUDED_)
#define AFX_MYSOCKET_H__A8FF5167_1194_4349_BB6E_046DE2994F27__INCLUDED_
#include "ModBusTcp.h"
#include "Afxsock.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mysocket.h : header file
//

class CModBusTcp;

/////////////////////////////////////////////////////////////////////////////
// CMysocket command target

class CMysocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMysocket(CModBusTcp *pDlg);
	virtual ~CMysocket();
	CModBusTcp *pModBusTcp;

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMysocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__A8FF5167_1194_4349_BB6E_046DE2994F27__INCLUDED_)
