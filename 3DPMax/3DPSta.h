#if !defined(AFX_3DPSTA_H__44E697A6_7068_4836_9E6C_0D77519A6EF7__INCLUDED_)
#define AFX_3DPSTA_H__44E697A6_7068_4836_9E6C_0D77519A6EF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DPSta.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DPSta dialog

class C3DPSta : public CDialog
{
// Construction
public:
	C3DPSta(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C3DPSta)
	enum { IDD = IDD_3DPSTA };
	int		m_cengNum;
	CString	m_printNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DPSta)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3DPSta)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPSTA_H__44E697A6_7068_4836_9E6C_0D77519A6EF7__INCLUDED_)
