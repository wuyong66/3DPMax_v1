#if !defined(AFX_BIN2ASCOFSTLDLG_H__31DD1DBE_D8DA_4B1F_BFB5_8F638A95B42D__INCLUDED_)
#define AFX_BIN2ASCOFSTLDLG_H__31DD1DBE_D8DA_4B1F_BFB5_8F638A95B42D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Bin2AscOfSTLDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBin2AscOfSTLDlg dialog

class CBin2AscOfSTLDlg : public CDialog
{
// Construction
public:
	CBin2AscOfSTLDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBin2AscOfSTLDlg)
	enum { IDD = IDD_DIALOG_STL };
	CListBox	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBin2AscOfSTLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HBRUSH m_hbrush;
	// Generated message map functions
	//{{AFX_MSG(CBin2AscOfSTLDlg)
	afx_msg void OnButCancel();
	afx_msg void OnButClear();
	afx_msg void OnButGetFile();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIN2ASCOFSTLDLG_H__31DD1DBE_D8DA_4B1F_BFB5_8F638A95B42D__INCLUDED_)
