// 3DPMaxDoc.h : interface of the CMy3DPMaxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DPMAXDOC_H__6FB0FF81_1769_46BF_84C1_500ED6E8DA5F__INCLUDED_)
#define AFX_3DPMAXDOC_H__6FB0FF81_1769_46BF_84C1_500ED6E8DA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Entity.h"      //����ʵ��ͷ�ļ�

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
	int infoArray[4];  //����ģ�ͻ�����Ϣ�Ľ�����
	BOOL m_paint_flag; //�Ƿ��������Ƭ��־
	int CengNumNow;    //��ǰ��ӡ��
	CString PrintNumNow;    //��ǰ��ӡ���� 


	int m_Nceng;       //ѡ���鿴

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

	BOOL m_stlRead;   //�ļ��Ƿ񱻶�ȡ��־λ
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
