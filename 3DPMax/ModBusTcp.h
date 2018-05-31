#if !defined(AFX_MODBUSTCP_H__9DBD9CA7_0E1C_4947_8CCC_66B308B4DB44__INCLUDED_)
#define AFX_MODBUSTCP_H__9DBD9CA7_0E1C_4947_8CCC_66B308B4DB44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModBusTcp.h : header file
//
#include "Mysocket.h"
#include "ModBusRTU.h"
class CMysocket;
/////////////////////////////////////////////////////////////////////////////
// CModBusTcp dialog

class CModBusTcp : public CDialog
{
// Construction
public:
	CModBusTcp(CWnd* pParent = NULL);   // standard constructor

public:
	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

	CMysocket *pMysocket;   //套接字对象
	int flag;   //连接标志位

	long cengNum;   //当前请求层数
	BOOL updateFlag; //层数是否更新标志

	CTypedPtrArray<CObArray,CCoordinate*> coordinate; //要发送的坐标信息
	

public:
	void ShowCommFrame(LPCTSTR Msg);   //更新richEdit的内容
	char ReceieveData();
	char ModBus_readSingleRegData(long regAdd, long *list);  //读寄存器的值。
	char ModBus_WriteSingleRegData(long regAdd, long sendData);  //发送寄存器值
	char FloatToByte(float floatNum,unsigned char *byteArry);    //把float 转换为十六进制
	char ModBus_WriteSingFloat(long regAdd, float floatNum);     //发送一个浮点数float 32位 
	char GetstrOutOfDB();    //从数据库里获取数据
public:	

// Dialog Data
	//{{AFX_DATA(CModBusTcp)
	enum { IDD = IDD_DIALOG_MODBUS_TCP };
	CRichEditCtrl	m_r_text;
	CEdit	m_dataWrite;
	CString	m_port;
	long	m_cengNum;
	long	m_dataAddr;
	double	m_percent;
	CString	m_serverAddr;
	float	m_wirteFloat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModBusTcp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModBusTcp)
	afx_msg void OnButtonCreatLink();
	afx_msg void OnButtonBreakLink();
	afx_msg void OnButtonCleanText();
	afx_msg void OnDestroy();
	afx_msg void OnButtonRead();
	afx_msg void OnButtonWrite();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStartDownload();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStopDownload();
	afx_msg void OnChangeEditServerAddr();
	afx_msg void OnChangeEditPort();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnButtonWriteFloat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODBUSTCP_H__9DBD9CA7_0E1C_4947_8CCC_66B308B4DB44__INCLUDED_)
