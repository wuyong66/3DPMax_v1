#if !defined(AFX_CHECKTHREAD_H__02E2D496_62F4_4E59_90CF_CA9B35339F6C__INCLUDED_)
#define AFX_CHECKTHREAD_H__02E2D496_62F4_4E59_90CF_CA9B35339F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCheckThread thread

class CCheckThread : public CWinThread
{
	DECLARE_DYNCREATE(CCheckThread)
protected:
	CCheckThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCheckThread();

	// Generated message map functions
	//{{AFX_MSG(CCheckThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKTHREAD_H__02E2D496_62F4_4E59_90CF_CA9B35339F6C__INCLUDED_)
