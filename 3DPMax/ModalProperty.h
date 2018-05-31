#if !defined(AFX_MODALPROPERTY_H__5B986971_36C8_4D05_8E29_0331A7F28345__INCLUDED_)
#define AFX_MODALPROPERTY_H__5B986971_36C8_4D05_8E29_0331A7F28345__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModalProperty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModalProperty dialog

class CModalProperty : public CDialog
{
// Construction
public:
	CModalProperty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModalProperty)
	enum { IDD = IDD_MODAL_PROPERTY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModalProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModalProperty)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODALPROPERTY_H__5B986971_36C8_4D05_8E29_0331A7F28345__INCLUDED_)
