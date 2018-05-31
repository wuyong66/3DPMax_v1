#if !defined(AFX_CHKPLACE_H__80E99632_8274_40A0_8B5E_9C0D10A3F946__INCLUDED_)
#define AFX_CHKPLACE_H__80E99632_8274_40A0_8B5E_9C0D10A3F946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChkPlace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChkPlace dialog

class CChkPlace : public CDialog
{
// Construction
public:
	CChkPlace(CWnd* pParent = NULL);   // standard constructor

public:
	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;


// Dialog Data
	//{{AFX_DATA(CChkPlace)
	enum { IDD = IDD_CHKPLA };
	int		m_cengNum;
	CString	m_roundNum;
	CString	m_1o;
	CString	m_2o;
	CString	m_3o;
	CString	m_4o;
	CString	m_5o;
	CString	m_6o;
	CString	m_7o;
	CString	m_8o;
	CString	m_1i;
	CString	m_2i;
	CString	m_3i;
	CString	m_4i;
	CString	m_5i;
	CString	m_6i;
	CString	m_7i;
	CString	m_8i;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChkPlace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChkPlace)
	afx_msg char OnButCheckpla();
	afx_msg void OnButCancelpla();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHKPLACE_H__80E99632_8274_40A0_8B5E_9C0D10A3F946__INCLUDED_)
