//{{AFX_INCLUDES()
#include "mscomm3.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMMUNICATION_H__1A186D93_BCF9_4294_8BEA_E0D6F8D60A30__INCLUDED_)
#define AFX_COMMUNICATION_H__1A186D93_BCF9_4294_8BEA_E0D6F8D60A30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Communication.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommunication dialog

class CCommunication : public CDialog
{
// Construction
public:
	CCommunication(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommunication)
	enum { IDD = IDD_COMMUNICATION };
	CComboBox	m_Date_Select_M;
	CComboBox	m_ParityCheck_M;
	CComboBox	m_StopBit_M;
	CComboBox	m_BaudRate_M;
	CComboBox	m_ComboBox;
	CMSComm	m_ctrlComm;
	int	m_BaudRate;
	int	m_Index;
	int	m_Date_Select;
	int	m_ParityCheck;
	int	m_StopBit;
	//}}AFX_DATA

public:
	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunication)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommunication)
	afx_msg char OnOnCommMscomm();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOCommSelect();
	afx_msg void OnSelchangeCOMBOBaudRateSelect();
	afx_msg void OnSelchangeCOMBODateSelect();
	afx_msg void OnSelchangeCOMBOParityCheck();
	afx_msg void OnSelchangeCOMBOStopBit();
	afx_msg void OnScomOn();
	afx_msg void OnButcancel();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMUNICATION_H__1A186D93_BCF9_4294_8BEA_E0D6F8D60A30__INCLUDED_)
