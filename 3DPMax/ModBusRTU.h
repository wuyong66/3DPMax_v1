#if !defined(AFX_MODBUSRTU_H__E3ACDCF5_2849_45F7_937D_562AE40575B0__INCLUDED_)
#define AFX_MODBUSRTU_H__E3ACDCF5_2849_45F7_937D_562AE40575B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModBusRTU.h : header file
//

#include "stdio.h"
#include "3DPMaxView.h"
/////////////////////////////////////////////////////////////////////////////
// CModBusRTU dialog

class CCoordinate: public CObject
{
public :
	float  floatNum;
};

class CModBusRTU : public CDialog
{
// Construction
public:
	CModBusRTU(CWnd* pParent = NULL);   // standard constructor
public:
	char GetstrOutOfDB();
public:
	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

public:
	CTypedPtrArray<CObArray,CCoordinate*> coordinate; //要发送的坐标信息

// Dialog Data
	//{{AFX_DATA(CModBusRTU)
	enum { IDD = IDD_DIALOG_MODBUSRTU };
	CEdit	m_value;
	CEdit	m_rtu;
	CEdit	m_regcount;
	CEdit	m_regadd;
	CRichEditCtrl	m_r_text;
	CButton	m_b_write;
	CButton	m_b_read;
	CButton	m_b_close;
	short	m_cengNum;
	int		m_RtuAdd;
	int		m_RegAdd;
	int		m_RegCount;
	int		m_RegValue;
	int 	m_CommSelect_RTU;
	int 	m_BaudRateSelect_RTU;
	int 	m_DataSelect_RTU;
	int 	m_ParityCheck_RTU;
	int 	m_StopBit_RTU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModBusRTU)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModBusRTU)
	virtual BOOL OnInitDialog();
	afx_msg void OnBClose();
	afx_msg void OnClose();
	afx_msg void OnBRead();
	afx_msg void OnBWrite();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnButOpenrtu();
	afx_msg void OnButClosertu();
	afx_msg void OnButOpenMscom();
	afx_msg void OnButCloseMscom();
	afx_msg void OnSelchangeCOMBOCommSelectRTU();
	afx_msg void OnSelchangeCOMBOBaudRateSelectRTU();
	afx_msg void OnSelchangeCOMBODataSelectRTU();
	afx_msg void OnSelchangeCOMBOParityCheckRTU();
	afx_msg void OnSelchangeCOMBOStopBitRTU();
	afx_msg void OnButClearRichedit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AsciiToHex(CString buff, CString Hex);
	void ShowCommFrame(LPCTSTR Msg);
	UINT m_timer;
	short int cengNum;      //当前请求的层数
	BOOL updateFlag;   //从机请求层数是否更新
	BOOL printFlag;     //打印
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODBUSRTU_H__E3ACDCF5_2849_45F7_937D_562AE40575B0__INCLUDED_)
