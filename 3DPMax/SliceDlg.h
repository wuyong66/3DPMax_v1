#if !defined(AFX_SLICEDLG_H__4A744009_F808_4F90_B56C_736D2EE50736__INCLUDED_)
#define AFX_SLICEDLG_H__4A744009_F808_4F90_B56C_736D2EE50736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SliceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSliceDlg dialog

class CSliceDlg : public CDialog
{
// Construction
public:
	CSliceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSliceDlg)
	enum { IDD = IDD_SLICE };
	CEdit	m_cenCtrl;
	CEdit	m_houCtrl;
	double	m_hou;
	int		m_cen;
	int		m_sel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSliceDlg)
	afx_msg void OnOk();
	afx_msg void OnCancel();
	afx_msg void OnHeight();
	afx_msg void OnNumber();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLICEDLG_H__4A744009_F808_4F90_B56C_736D2EE50736__INCLUDED_)
