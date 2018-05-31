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

	int num;//�洢��ǰ�������������������еı��
	int numPrevious;//�洢ǰһ�������α��2n
	int numNext;//�洢��һ�������α��
	int cenNum;//�洢����
	int line1,line2;//���汻�и�ı����������еı��
	CPoint3D a1,a2;//�洢�����������еı��
	BOOL beUsed;//��Ǵ��������Ƿ�ʹ��

	BOOL beUsedToo;  //����������������ͨ������


};

////////////////////////2222222/////////////////////////////////////
class  CEntity : public CObject  //����������ѡ�еĵ���ģ�Ͷ���Entity����ʵ�����˼
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
	virtual void Draw(COpenGLDC* pDC)=0;      //�Ǹ����麯��

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
class  CTriChip:public CObject//��������Ƭ����Ĺ������Լ�������������Ƭ�����ĵ���
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
//��Ҫ����stl�ļ��Ķ�ȡ����������ֻ�������ı���ʽ�Ķ�ȡ�취��û�ж�������Ƹ�ʽ�Ķ�ȡ�취
class  CSTLModel: public CEntity            //�ֲ㽻������������
{
	DECLARE_SERIAL(CSTLModel)
//attribs
public:
	CTypedPtrArray<CObArray,CTriChip*>	m_TriList;//�洢����������
	CTypedPtrArray<CObArray,CTuoPu*>	m_Z_fenceng;//�洢�����ཻ�Ľ��㣨����Ž������еģ�
													//��ʲô��Ž�������
//	CTypedPtrArray<CObArray,CTuoPu*>	m_triTuoPu;//�洢�����ཻ�������α����Ϣ

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
class  CPart : public CEntity//��Ҫ�����洢����ģ�������������ڳ��򾫼��Ѿ�ʧȥ����
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




//��˵��������һ��ָ�����飬����ŵ�Ԫ����һ���������˽ṹ��ÿһ�����˽ṹ����ǰ���ͺ��Ԫ�أ���¼ǰ���ͺ�̵������������±꣩��
//���������������ɸ�Ԫ���ǹ�����һ�����ƾ�̬������Ϊ�������˽ṹ�д洢���������±꣬������ָ����
//��˫��ѭ���������ָ�������������ɸ�������˫��ѭ������Ŀǰ��֪��һ���������һ��Ԫ�ص�ַ�������±꣩
//���Է���������һ��ѭ��˫����������������������ô���ʣ�

//�����ľ���������ǣ�����һ������һ��CTypedPtrArray<CObArray,CTuoPu*>	m_Z_fenceng;ȥ�洢ÿһ����������㣬
//����ÿһ�������ɸ�����ͨ�������Ծ���������˫��ѭ�������ÿһ������ͨ����Ľ����������