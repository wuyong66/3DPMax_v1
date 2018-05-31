#if !defined(AFX_PRITMOD_H__ABB50BD3_4CC8_4716_98BD_D44E9F806572__INCLUDED_)
#define AFX_PRITMOD_H__ABB50BD3_4CC8_4716_98BD_D44E9F806572__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PritMod.h : header file
//

#include "3DPMaxDoc.h"

//class CDataLib 要存入数据库的数据
class CDataLib : public CObject
{
public:
	int cengNum;
	int roundNum;
	int pritNum;
	double x1o, y1o, z1o, x1i, y1i, z1i;
	double x2o, y2o, z2o, x2i, y2i, z2i;
	double x3o, y3o, z3o, x3i, y3i, z3i;
	double x4o, y4o, z4o, x4i, y4i, z4i;
	double x5o, y5o, z5o, x5i, y5i, z5i;
	double x6o, y6o, z6o, x6i, y6i, z6i;
	double x7o, y7o, z7o, x7i, y7i, z7i;
	double x8o, y8o, z8o, x8i, y8i, z8i;
};

/////////////////////////////////////////////////////////////////////////////
// CPritMod dialog

class CPritMod : public CDialog
{
// Construction
public:
	CPritMod(CWnd* pParent = NULL);   // standard constructor


public:
	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

public:
	//退出循环flag
	BOOL break_flag;
// Dialog Data
	//{{AFX_DATA(CPritMod)
	enum { IDD = IDD_PRIMOD };
	int		m_modChose;
	double	m_distance1;
	double	m_distance2;
	//}}AFX_DATA
public:
    void	PritMod1(int cenN);
	void	PritMod2(int cenN);
	void	PritMod3(int cenN);
	void	PritMod4(int cenN);
	void	PritMod5(int cenN);
	void	PritMod6(int cenN);
	void	PritMod7(int cenN);
	void	PritMod8(int cenN);
public:

	CTypedPtrArray<CObArray,CDataLib*> m_pData;
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPritMod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPritMod)
	afx_msg void OnDataOk();
	afx_msg void OnDataWrt();
	afx_msg void OnDataCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRITMOD_H__ABB50BD3_4CC8_4716_98BD_D44E9F806572__INCLUDED_)

