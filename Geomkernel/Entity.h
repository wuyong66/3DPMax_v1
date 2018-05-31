// Entity.h: interface for the CEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITY_H__BE769D85_6C72_43F4_88FB_5521CA66FC8E__INCLUDED_)
#define AFX_ENTITY_H__BE769D85_6C72_43F4_88FB_5521CA66FC8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CadBase.h"

class COpenGLDC;
////////////////////////11111/////////////////////////////////////
class  CTuoPu : public CObject
{

public:
	CTuoPu();
	~CTuoPu();

	int num;//存储当前三角形在三角形数组中的编号
	int numPrevious;//存储前一个三角形编号2n
	int numNext;//存储下一个三角形编号
	int cenNum;//存储层编号
	int line1,line2;//储存被切割的边在三角形中的编号
	CPoint3D a1,a2;//存储交点在数组中的编号
	BOOL beUsed;//标记此三角形是否被使用

	BOOL beUsedToo;  //归属交点所属单连通区域用


};

////////////////////////2222222/////////////////////////////////////
class  CEntity : public CObject  //左侧零件树中选中的单个模型对象Entity单个实体的意思
{
protected:
	BOOL		m_bModified;

	UINT		m_id;
	CString		m_name;
	COLORREF	m_color;
	BOOL		m_bVisible;
	BOOL		m_bHighlight;

public:
	//constructor and destructor
	CEntity();
	virtual ~CEntity();

	//display
	virtual void Draw(COpenGLDC* pDC)=0;      //是个纯虚函数

	//serialize
	virtual	void Serialize(CArchive& ar);	

	//attrib accessing 
	BOOL		GetBox(CBox3D& box);	
	
	void		SetID(UINT nID);
	UINT		GetID();
	
	void		SetName(LPCTSTR name);
	CString		GetName();
	
	void		SetColor(COLORREF color);
	COLORREF	GetColor();

	void		SetVisible(BOOL bVisible);
	BOOL		IsVisible();

	void		SetHighlight(BOOL bHighlight);
	BOOL		IsHighlight();
	CBox3D*		m_pBox;

protected:
	virtual		void UpdateBox()=0;
};

////////////////////////333333/////////////////////////////////////
//triangle chip
class  CTriChip:public CObject//三角形面片对象的构建，以及绘制三角形面片函数的调用
{

	DECLARE_SERIAL(CTriChip)
public:
	//attribs
	CPoint3D  vex[3];
	CVector3D normal;

public:
	//constructor && destructor
	CTriChip();
	CTriChip(const CPoint3D& v0,const CPoint3D& v1,const CPoint3D& v2,const CVector3D& norm);
	virtual ~CTriChip();

	//display
	virtual void Draw(COpenGLDC* pDC);

	//serialize
	virtual void Serialize(CArchive& ar);
	
	//operator
	const CTriChip& operator=(const CTriChip&);

protected:
};

////////////////////////4444444/////////////////////////////////////
//tessellated model
//主要定义stl文件的读取函数，但是只定义了文本格式的读取办法，没有定义二进制格式的读取办法
class  CSTLModel: public CEntity            //分层交点就在这里存着
{
	DECLARE_SERIAL(CSTLModel)
//attribs
public:
	CTypedPtrArray<CObArray,CTriChip*>	m_TriList;//存储所有三角形
	CTypedPtrArray<CObArray,CTuoPu*>	m_Z_fenceng;//存储所有相交的交点（按序号进行排列的）
													//按什么序号进行排列
//	CTypedPtrArray<CObArray,CTuoPu*>	m_triTuoPu;//存储所有相交的三角形编号信息

public:
	void sortCenTri(int cenNum);
//	void DrawLine(COpenGLDC *pDC);
	BOOL CrossZ(CPoint3D *p1,CPoint3D *p2, double z, CPoint3D& p3D);
	void GetZfenceng(double zN);
	void GetZfenceng(int cenN);



	//constructor && destructor
	CSTLModel();
	virtual ~CSTLModel();

	//display
	void	Draw(COpenGLDC* pDC);

	//serialize
	void	Serialize(CArchive& ar);

	//		operation
	const   CSTLModel& operator=(const CSTLModel&);
	
	void	Add(CTriChip* tri);
	BOOL	LoadSTLFile(LPCTSTR file);
	void	Clear();


	//attrib accessing
	BOOL	IsEmpty();

	virtual void UpdateBox();
protected:

};


////////////////////////55555555/////////////////////////////////////
class  CPart : public CEntity//主要用来存储左侧的模型树，现在由于程序精简，已经失去作用
{
//attribs
protected:
	CTypedPtrArray<CObArray,CEntity*> m_EntList;

public:
	//constructor && destructor
	CPart();
	virtual ~CPart();

	//draw
	virtual void Draw(COpenGLDC* pDC);

	//serialize
	virtual void Serialize(CArchive& ar);

	//operation
	void	AddEntity(CEntity* ent);
	void	RemoveEntity(CEntity* ent);
	void	RemoveAllEntity();

	//attrib accessing
	BOOL	IsEmpty();
//	BOOL	GetBox(CBox3D& box);

	UINT		GetEntitySize();
	CEntity*	GetEntity(UINT i);
/*	CString		GetName();
	void		SetName(LPCTSTR name);
	*/
protected:
	virtual void	UpdateBox();
};







#endif // !defined(AFX_ENTITY_H__BE769D85_6C72_43F4_88FB_5521CA66FC8E__INCLUDED_)




//你说我现在有一个指针数组，存放着的元素是一个个的拓扑结构，每一个拓扑结构都有前驱和后继元素（记录前驱和后继的数据是数组下标），
//这个数组里面的若干个元素是构成了一个类似静态链表（因为是在拓扑结构中存储的是数组下标，而不是指针域）
//的双向循环链表，这个指针数组里有若干个这样的双向循环链表，目前我知道一个链表里的一个元素地址（数组下标）
//可以访问所有这一条循环双向链表，但是其他的链表怎么访问？

//描述的具体问题就是，我用一个这样一个CTypedPtrArray<CObArray,CTuoPu*>	m_Z_fenceng;去存储每一层的轮廓交点，
//但是每一层有若干个单连通区域，所以就用这样的双向循环链表把每一个单连通区域的交点存起来，