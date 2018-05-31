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
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

	CMysocket *pMysocket;   //�׽��ֶ���
	int flag;   //���ӱ�־λ

	long cengNum;   //��ǰ�������
	BOOL updateFlag; //�����Ƿ���±�־

	CTypedPtrArray<CObArray,CCoordinate*> coordinate; //Ҫ���͵�������Ϣ
	

public:
	void ShowCommFrame(LPCTSTR Msg);   //����richEdit������
	char ReceieveData();
	char ModBus_readSingleRegData(long regAdd, long *list);  //���Ĵ�����ֵ��
	char ModBus_WriteSingleRegData(long regAdd, long sendData);  //���ͼĴ���ֵ
	char FloatToByte(float floatNum,unsigned char *byteArry);    //��float ת��Ϊʮ������
	char ModBus_WriteSingFloat(long regAdd, float floatNum);     //����һ��������float 32λ 
	char GetstrOutOfDB();    //�����ݿ����ȡ����
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
