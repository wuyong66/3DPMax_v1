#if !defined(AFX_MODBUSTHREAD_H__C83314E7_CEC1_49DB_B57F_6682AC10B7D6__INCLUDED_)
#define AFX_MODBUSTHREAD_H__C83314E7_CEC1_49DB_B57F_6682AC10B7D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModBusThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CModBusThread thread

class CModBusThread : public CWinThread
{
	DECLARE_DYNCREATE(CModBusThread)
protected:
	CModBusThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModBusThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CModBusThread();

	// Generated message map functions
	//{{AFX_MSG(CModBusThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODBUSTHREAD_H__C83314E7_CEC1_49DB_B57F_6682AC10B7D6__INCLUDED_)
