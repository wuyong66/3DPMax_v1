// 3DPMax.h : main header file for the 3DPMAX application
//

#if !defined(AFX_3DPMAX_H__1D4E4229_7BED_4B76_A49F_D1F22E38B74E__INCLUDED_)
#define AFX_3DPMAX_H__1D4E4229_7BED_4B76_A49F_D1F22E38B74E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxApp:
// See 3DPMax.cpp for the implementation of this class
//

class CMy3DPMaxApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMy3DPMaxApp();
	// 定义ADO连接变量指针
	_ConnectionPtr	m_pConnection;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DPMaxApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3DPMaxApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPMAX_H__1D4E4229_7BED_4B76_A49F_D1F22E38B74E__INCLUDED_)
