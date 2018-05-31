// 3DPMaxView.h : interface of the CMy3DPMaxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DPMAXVIEW_H__F71B8420_AD10_4D82_9BA6_29D946B640F3__INCLUDED_)
#define AFX_3DPMAXVIEW_H__F71B8420_AD10_4D82_9BA6_29D946B640F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//header file
#include "CadBase.h"
#include "OPenGLDC.h"

#include "3DPMaxDoc.h"

//#include "CheckView.h"
class CP3d : public CObject
{
public:
	CPoint3D a1,a2,a3;
	int cengNum;
	int areaNum;
};

class CRound : public CObject
{
public:
	int cengNum;
	int roundNum;
	double rMax;
	double rMin;

};

class CMy3DPMaxView : public CGLView
{
protected: // create from serialization only
	CMy3DPMaxView();
	DECLARE_DYNCREATE(CMy3DPMaxView)

// Attributes
public:
	CMy3DPMaxDoc* GetDocument();

	CTypedPtrArray<CObArray,CP3d*>	m_p3d;//存储已排序过的交点
	CTypedPtrArray<CObArray,CP3d*>	m_a3;//补加的点

	CTypedPtrArray<CObArray,CRound*> m_round; //每一层大小圆半径

	virtual void RenderScene(COpenGLDC* pDC);
	float m_xRotate;
	float m_yRotate;
	
	CPoint m_LeftDownPos;
	
	BOOL m_LeftButtonDown;
	BOOL m_bool,m_fen_bool1,m_fen_bool2;//第一个用来和doc类产生互锁，达到标记文件打开的目的
	//第二、三个用来标记点击了哪个，分层按钮

	BOOL m_bool_flag;//这个用来标记是否已经分层

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DPMaxView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	protected:
	//}}AFX_VIRTUAL


public: 
	//半径求取

	double GetRound(double x,double y);
	void GetCengRound(int cengNum,int& Rnum, double& Rmax,double& Rmin);
	void GetEveRound();


// Implementation
public:
	int pointNum;
	BOOL m_addPointOver;
	BOOL m_addPoint;
	void addPoint();
	void clearAll();
	int sotCen;
	BOOL m_Sort;
	void SortPoint(int sortCen);
	void viewClear();
	int cenN;
	double zN;
	void FenCeng(COpenGLDC* pDC);

	virtual ~CMy3DPMaxView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3DPMaxView)
	afx_msg void OnFileClear();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBin2asc();
	afx_msg void OnButtonFill();
	afx_msg void OnButtonProcess();
	afx_msg void OnButtonSlice();
	afx_msg void OnViewBehind();
	afx_msg void OnViewBottom();
	afx_msg void OnViewFront();
	afx_msg void OnViewLeft();
	afx_msg void OnViewNeIsometric();
	afx_msg void OnViewRight();
	afx_msg void OnViewTop();
	afx_msg void OnModalProperty();
	afx_msg void OnMenuoutline();
	afx_msg void OnMenuprinter();
	afx_msg void OnPrinting();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnButtonChkpla();
	afx_msg void OnUpdateButtonSlice(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonFill(CCmdUI* pCmdUI);
	afx_msg void OnViewShade();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnButmodbus();
	afx_msg void OnButtonModbusTcp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL	GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1);
private:
	void initRotate();//自己加的，在变换显示方向时，将视图归正
};



#ifndef _DEBUG  // debug version in 3DPMaxView.cpp
inline CMy3DPMaxDoc* CMy3DPMaxView::GetDocument()
   { return (CMy3DPMaxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPMAXVIEW_H__F71B8420_AD10_4D82_9BA6_29D946B640F3__INCLUDED_)
