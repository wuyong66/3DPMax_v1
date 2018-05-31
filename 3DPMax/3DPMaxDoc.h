// 3DPMaxDoc.h : interface of the CMy3DPMaxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DPMAXDOC_H__6FB0FF81_1769_46BF_84C1_500ED6E8DA5F__INCLUDED_)
#define AFX_3DPMAXDOC_H__6FB0FF81_1769_46BF_84C1_500ED6E8DA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Entity.h"      //包含实体头文件

class CMy3DPMaxDoc : public CDocument
{
protected: // create from serialization only
	CMy3DPMaxDoc();
	DECLARE_DYNCREATE(CMy3DPMaxDoc)

// Attributes
public:
	CPart	m_Part;
	CString ModalName;

// Operations

public:
	int infoArray[4];  //用于模型基本信息的交换。
	BOOL m_paint_flag; //是否进行了切片标志
	int CengNumNow;    //当前打印层
	CString PrintNumNow;    //当前打印层编号 


	int m_Nceng;       //选择层查看

public:
	CString GetSubStr(CString str);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DPMaxDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	BOOL m_stlRead;   //文件是否被读取标志位
	CSTLModel* pSTLModel;

	virtual ~CMy3DPMaxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3DPMaxDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnStlFilein();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPMAXDOC_H__6FB0FF81_1769_46BF_84C1_500ED6E8DA5F__INCLUDED_)
