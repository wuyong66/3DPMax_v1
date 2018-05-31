#if !defined(AFX_CHECKDLG_H__AD6D2E57_88BA_408B_A24C_24DDE2AEFBB9__INCLUDED_)
#define AFX_CHECKDLG_H__AD6D2E57_88BA_408B_A24C_24DDE2AEFBB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHECKDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCHECKDLG dialog

class CCHECKDLG : public CDialog
{
// Construction
public:
	CCHECKDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCHECKDLG)
	enum { IDD = IDD_DIALOG_CHECK };
	CSliderCtrl	m_slider_ceng;
	int		m_editCeng;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHECKDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CCHECKDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButcengcheck();
	afx_msg void OnButcengscan();
	afx_msg void OnReleasedcaptureSliderCeng(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderCeng(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKDLG_H__AD6D2E57_88BA_408B_A24C_24DDE2AEFBB9__INCLUDED_)
