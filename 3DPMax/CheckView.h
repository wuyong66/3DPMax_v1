#if !defined(AFX_CHECKVIEW_H__FE09C415_0954_4BBB_BD19_B23BDB02F27F__INCLUDED_)
#define AFX_CHECKVIEW_H__FE09C415_0954_4BBB_BD19_B23BDB02F27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckView view
#include "CHECKDLG.h"
#include "CadBase.h"
#include "OPenGLDC.h"


class CCheckView : public CGLView 
{
protected:

	DECLARE_DYNCREATE(CCheckView)

// Attributes
public:
	CCheckView();           // protected constructor used by dynamic creation
	virtual ~CCheckView();
	virtual void RenderScene(COpenGLDC* pDC);
// Operations
public:
	virtual void OnInitialUpdate();     // first time after construct

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckView)
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
// Implementation
protected:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCheckView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKVIEW_H__FE09C415_0954_4BBB_BD19_B23BDB02F27F__INCLUDED_)
