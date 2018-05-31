// Entity.cpp: implementation of the CEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Entity.h"
#include "OPenGLDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntity::CEntity()
{
	m_bModified = FALSE;
	m_id = -1;
	m_pBox = NULL;
	m_color = RGB(128,128,128);
	m_name = _T("Unknow");
	m_bVisible = TRUE;
	m_bHighlight = FALSE;
}

CEntity::~CEntity()
{
}

void CEntity::Serialize(CArchive& ar)
{
	if(ar.IsStoring()){
		ar << m_id;
		ar << m_name;
		ar << m_color;
		ar << m_bVisible;
	}
	else{ //loading
		ar >> m_id;
		ar >> m_name;
		ar >> m_color;
		ar >> m_bVisible;
	}
}	

BOOL	CEntity::GetBox(CBox3D& box)
{
	if(m_bModified)
		UpdateBox();

	if( m_pBox){
		box = *m_pBox;
		return TRUE;
	}
	else
		return FALSE;
}

void	CEntity::SetID(UINT nID)
{
	m_id = nID;
}

UINT	CEntity::GetID()
{
	return m_id;
}

void	CEntity::SetName(LPCTSTR name)
{
	m_name = name;
}

CString	CEntity::GetName()
{
	return m_name;
}

void	CEntity::SetColor(COLORREF color)
{
	m_color = color;
}

COLORREF CEntity::GetColor()
{
	return m_color;
}

void CEntity::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}

BOOL CEntity::IsVisible()
{
	return m_bVisible;
}

void CEntity::SetHighlight(BOOL bHighlight)
{
	m_bHighlight = bHighlight;
}

BOOL CEntity::IsHighlight()
{
	return m_bHighlight;
}

///////////////////////////
//class tri chip 
IMPLEMENT_SERIAL(CTriChip,CObject,0)
CTriChip::CTriChip()
{
}

CTriChip::CTriChip(const CPoint3D& v0,const CPoint3D& v1,const CPoint3D& v2,const CVector3D& nor)
{
	vex[0] = v0;
	vex[1] = v1;
	vex[2] = v2;
	normal = nor;
}

CTriChip::~CTriChip()
{
}

const CTriChip& CTriChip::operator=(const CTriChip& tri)
{
	normal = tri.normal;
	for(int i=0;i<3;i++)
		vex[i] = tri.vex[i];
	return *this;
}

void CTriChip::Draw(COpenGLDC* pDC)
{

//	AfxMessageBox("Tri���л�ͼ");
	pDC->DrawTriChip(normal.dx,normal.dy,normal.dz,
		vex[0].x,vex[0].y,vex[0].z,
		vex[1].x,vex[1].y,vex[1].z,
		vex[2].x,vex[2].y,vex[2].z);
	
}

void CTriChip::Serialize(CArchive& ar)
{
	if(ar.IsStoring()){
		ar << normal.dx << normal.dy << normal.dz;
		for(int i=0;i<3;i++)
			ar << vex[i].x << vex[i].y << vex[i].z;
	}
	else{
		ar >> normal.dx >> normal.dy >> normal.dz;
		for(int i=0;i<3;i++)
			ar >> vex[i].x >> vex[i].y >> vex[i].z;
	}
}

//////////////////////////////////////////
//class  CSTLModel

IMPLEMENT_SERIAL(CSTLModel,CObject,0)

CSTLModel::CSTLModel()
{
}

CSTLModel::~CSTLModel()
{
	Clear();
}

void CSTLModel::Add(CTriChip* tri)
{
	m_TriList.Add(tri);
}

void CSTLModel::UpdateBox()
{
	if(m_pBox){
		delete m_pBox;
		m_pBox = NULL;
	}

	if(m_TriList.GetSize()==0) 
		return;
	
	double x0,y0,z0,x1,y1,z1;
//	x0=y0=z0=10000;
//	x1=y1=z1=-10000;
	x0 = x1 = m_TriList[1]->vex->x;
	y0 = y1 = m_TriList[1]->vex->y;
	z0 = z1 = m_TriList[1]->vex->z;

	CTriChip* tri;
	for(int i=0;i<m_TriList.GetSize();i++){//�˴�˫��ѭ����������������������Ƭ��������������С������꣬������BOX
		tri = m_TriList[i];
		for(int n=0;n<3;n++){
			if(tri->vex[n].x<x0)  x0 = tri->vex[n].x;
			if(tri->vex[n].x>x1)  x1 = tri->vex[n].x;

			if(tri->vex[n].y<y0)  y0 = tri->vex[n].y;
			if(tri->vex[n].y>y1)  y1 = tri->vex[n].y;

			if(tri->vex[n].z<z0)  z0 = tri->vex[n].z;
			if(tri->vex[n].z>z1)  z1 = tri->vex[n].z;
		}
	}

	m_pBox = new CBox3D(x0,y0,z0,x1,y1,z1);
	m_bModified = FALSE;
}


//load with STL File
BOOL CSTLModel::LoadSTLFile(LPCTSTR stlfile)
{
	FILE* file;
	int type=0;
	if((file = fopen(stlfile, "r")) == NULL){
		//AfxMessageBox("�ļ���ʽ����");
		//Sleep(1000);
		return FALSE;
	}

	char str[80];
	CTriChip* tri = NULL;
	while(fscanf(file,"%s",str)==1){
		if(strncmp(str,"normal",6)==0){
			tri = new CTriChip();
			fscanf(file,"%lf %lf %lf",&(tri->normal.dx),&(tri->normal.dy),&(tri->normal.dz));  //��������ֵ
			fscanf(file,"%*s %*s");
			fscanf(file,"%*s %lf %lf %lf",&(tri->vex[0].x),&(tri->vex[0].y),&(tri->vex[0].z));
			fscanf(file,"%*s %lf %lf %lf",&(tri->vex[1].x),&(tri->vex[1].y),&(tri->vex[1].z));
			fscanf(file,"%*s %lf %lf %lf",&(tri->vex[2].x),&(tri->vex[2].y),&(tri->vex[2].z));
			Add(tri);
		}
	}

	char title[80];
	if(GetFileTitle(stlfile,title,80)==0){
		SetName(title);
	}

	m_bModified = TRUE;
	return TRUE;
}

//Serialize
void	CSTLModel::Serialize(CArchive& ar)
{
	CEntity::Serialize(ar);
	
	if(ar.IsStoring()){
		m_TriList.Serialize(ar);
	}
	else{ //IsLoading()
		m_TriList.Serialize(ar);
		m_bModified = TRUE;
	}
}



void CSTLModel::Draw(COpenGLDC* pDC)
{
	if(!m_bVisible)	return;
	
	if(m_bHighlight)
		pDC->Highlight(TRUE);
	else
		pDC->SetMaterialColor(m_color);

	if(pDC->IsSelectionMode()){
		pDC->LoadName((UINT)this);
	}

//	AfxMessageBox("STL���л�������");
	for(int i=0;i<m_TriList.GetSize();i++){
		m_TriList[i]->Draw(pDC);
		//���ն�Ҫ�䵽��������Ƭ�Ļ����ϣ���Ϊֻ����һ��draw����ֱ�ӵ���opengl�⺯���������ν��л�ͼ
	
	}
}

void	CSTLModel::Clear()
{
	for(int i=0;i<m_TriList.GetSize();i++)
		delete m_TriList[i];
	m_TriList.RemoveAll();


	for(i=0;i<m_Z_fenceng.GetSize();i++)
		delete m_Z_fenceng[i];
	m_Z_fenceng.RemoveAll();



	m_bModified = TRUE;
}

BOOL	CSTLModel::IsEmpty()
{
	return m_TriList.GetSize() == 0;
}

//////////////////////////////////////////
CPart::CPart()
{
}

CPart::~CPart()
{
	RemoveAllEntity();
}

//draw
void CPart::Draw(COpenGLDC* pDC)
{
//	AfxMessageBox("Part���л�ͼ");
	for(int i=0;i<m_EntList.GetSize();i++)
		m_EntList[i]->Draw(pDC);
	
}

//serialize
void CPart::Serialize(CArchive& ar)
{
	CEntity::Serialize(ar);
	if(ar.IsStoring()){
		m_EntList.Serialize(ar);
	}
	else{
		m_EntList.Serialize(ar);
		m_bModified = TRUE;
	}
}

//operation
void CPart::AddEntity(CEntity* ent)
{
	m_EntList.Add(ent);
	m_bModified = TRUE;
}

void CPart::RemoveEntity(CEntity* ent)
{
	for(int i=0;i<m_EntList.GetSize();i++){
		if(ent == m_EntList[i]){
			m_EntList.RemoveAt(i);
			m_bModified = TRUE;
			break;
		}
	}
}

void CPart::RemoveAllEntity()
{
	for(int i=0;i<m_EntList.GetSize();i++)
		delete m_EntList[i];
	m_EntList.RemoveAll();
	m_bModified = TRUE;
}

//attrib accessing
BOOL CPart::IsEmpty()
{
	return m_EntList.GetSize() == 0 ;
}

UINT	CPart::GetEntitySize()
{
	return m_EntList.GetSize();
}

CEntity* CPart::GetEntity(UINT i)
{
	ASSERT(i<m_EntList.GetSize());
	return m_EntList[i];
}

void CPart::UpdateBox()
{
	if(m_pBox){
		delete m_pBox;
		m_pBox = NULL;
	}

	CBox3D box;
	for(int i=0;i<m_EntList.GetSize();i++){
		if(m_EntList[i]->GetBox(box)){
			if(m_pBox)
				*m_pBox += box;//�˴���CBox3D������+=���������˿��Ի�������Ǹ�BOX
			else{
				m_pBox = new CBox3D();
				*m_pBox = box;
			}
		}
	}
	m_bModified = FALSE;
}


//�˴�zNΪ����
void CSTLModel::GetZfenceng(double zN)//������ֲ㴦�Ľ��㣨����һ�����м�¼cenNum����������������Ϣ�洢�����˱���
{
	CString str;//������ʹ��

	//double z=10;//��Ƭλ�õ�z���꣬�����ã���ΪzN
	CPoint3D p3D;
	CPoint3D p3D1;
	CPoint3D p3D2;
	CPoint3D p3D3;
	int n = m_TriList.GetSize();      //���������ε���Ŀ


	UpdateBox();   //������BOX��m_pBox����BOX


	int cenN;
	cenN =(int)floor((m_pBox->z1 - m_pBox->z0)/zN);//����


	for(int z =0 ; z < cenN ; z++)//����ѭ��
	{
			
	for(int i=0;i<n;i++)//��������������
		{

			CTriChip* tri;
			tri = m_TriList[i];	
			
			BOOL cross1,cross2,cross3,cross;
			cross=cross1=cross2=cross3=FALSE;
			double startpoint;
			startpoint = m_pBox->z0;

			if(CrossZ(&tri->vex[0],&tri->vex[1],startpoint + z*zN, p3D))  
			{

				p3D1 = p3D;
				cross1=TRUE;
				cross=TRUE;

			}
			if(CrossZ(&tri->vex[0],&tri->vex[2], startpoint + z*zN, p3D))   
			{

				p3D2 = p3D;
				cross2=TRUE;
				cross=TRUE;

			}
			if(CrossZ(&tri->vex[1],&tri->vex[2], startpoint + z*zN, p3D))   
			{

				p3D3 = p3D;
				cross3=TRUE;
				cross=TRUE;
			}

			if(cross)
			{
				//AfxMessageBox("�ཻ!");
				//���ཻ���в���
				//��δ����ֳ��ֳ�����д��һ���죬�Ǹ��ܱʣ�û�취��ָ��Ļ���ԭ����⣬Ϲ������һ��
				//��ֱ������ʯͷ���ӣ����������������̳̣�̫��

				if(cross1 && cross2 && cross3)
				{
					//AfxMessageBox("�������㣬�����ܰ�!");
					//��ʵ������ǣ�ֻҪ����λ��ƽ�棬�ͷ�����	
					//��������ԣ�����Ϊ��������λ��Ҫ��Ƭ��zƽ�����档����

				}

				CTuoPu* tuoPu = new CTuoPu;

				tuoPu->num=i;//�洢���и�������εı��
				tuoPu->cenNum=z;//�洢�и����

				if(cross1 && cross2 && !cross3)//����0����1�����������z�и����ཻ
				{
					tuoPu->a1=p3D1;       //a1��a2���㣬������
					tuoPu->a2=p3D2;
					m_Z_fenceng.Add(tuoPu);  //�洢�����ཻ����
				}
				if(cross1 && cross3 && !cross2)//����0����2�����������z�и����ཻ
				{
					tuoPu->a1=p3D1;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}
				if(cross2 && cross3 && !cross1)//����1����2�����������z�и����ཻ
				{
					tuoPu->a1=p3D2;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}
				cross=cross1=cross2=cross3=FALSE;//��仰���п��ޣ�����������Ϊ�����Ҹ����ģ��в���	
			}
		}
	}
}

void CSTLModel::GetZfenceng(int cenN)//��Ƭ����
{	
	CPoint3D p3D;
	CPoint3D p3D1;
	CPoint3D p3D2;
	CPoint3D p3D3;
	int n = m_TriList.GetSize();

	UpdateBox();
	double zN;
	//m_pBox��CEntity���ж����һ��BOX������洢��ģ�͵�������С�㣬��CSTLModel
	//����CEntity���������࣬��˿���������ʴ˱���
	zN =(m_pBox->z1 - m_pBox->z0)/cenN;//�õ���ĺ��
	for(int z =0 ; z < cenN ; z++)
	{
			
		for(int i=0;i<n;i++)
		{

			CTriChip* tri;
			tri = m_TriList[i];				
			BOOL cross1,cross2,cross3,cross;
			cross=cross1=cross2=cross3=FALSE;
			double startpoint;
			startpoint = m_pBox->z0;

			if(CrossZ(&tri->vex[0],&tri->vex[1],startpoint + z*zN, p3D))  //�ж��Ƿ��ཻ01
			{

				p3D1 = p3D;
				cross1=TRUE;
				cross=TRUE;

			}
			if(CrossZ(&tri->vex[0],&tri->vex[2], startpoint + z*zN, p3D))   //�ж��Ƿ��ཻ02
			{

				p3D2 = p3D;
				cross2=TRUE;
				cross=TRUE;

			}
			if(CrossZ(&tri->vex[1],&tri->vex[2], startpoint + z*zN, p3D))   //�ж��Ƿ��ཻ12
			{

				p3D3 = p3D;
				cross3=TRUE;
				cross=TRUE;
			}
			//�������ж��ཻ�������Ƭ����λ���ཻ���ϣ��ͻ����������ͬ�Ľ���

			if(cross)
			{
				//AfxMessageBox("�ཻ!");
				//���ཻ���в���
				//��δ����ֳ��ֳ�����д��һ���죬�Ǹ��ܱʣ�û�취��ָ��Ļ���ԭ����⣬Ϲ������һ��
				//��ֱ������ʯͷ���ӣ����������������̳̣�̫��


				

				if(cross1 && cross2 && cross3)
				{
					//AfxMessageBox("�������㣬�����ܰ�!");
					//��ʵ������ǣ�ֻҪ����λ��ƽ�棬�ͷ�����	
					//��������ԣ�����Ϊ��������λ��Ҫ��Ƭ��zƽ�����档����
					//���������������������Ӱ�������ߵĻ��������Ը������ˣ���Ϊ��֪����α�����������汻�и���

				}

				CTuoPu* tuoPu = new CTuoPu;
				tuoPu->num=i;//�洢���и�������εı��
				tuoPu->cenNum=z;//�洢���и�������εı��

				if(cross1 && cross2 && !cross3)//����0����1�����������z�и����ཻ
				{
					tuoPu->line1=0;//������00,01�������ཻ
					tuoPu->line2=1;

					tuoPu->a1=p3D1;
					tuoPu->a2=p3D2;
					m_Z_fenceng.Add(tuoPu);
				}
				if(cross1 && cross3 && !cross2)//����0����2�����������z�и����ཻ
				{
					tuoPu->line1=0;//������00,02�������ཻ
					tuoPu->line2=2;

					tuoPu->a1=p3D1;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}
				if(cross2 && cross3 && !cross1)//����1����2�����������z�и����ཻ
				{
					tuoPu->line1=1;//������01,02�������ཻ
					tuoPu->line2=2;

					tuoPu->a1=p3D2;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}

				cross=cross1=cross2=cross3=FALSE;//��仰���п��ޣ�����������Ϊ�����Ҹ�����
					
				//m_Z_fencengÿһ����������һ�𣬵�������β˳������
			}

			

		}

	}

}


//�Լ�д���ж�һ����������Ƭ��һ��Zƽ�����޽��㣬�������㷵��p3D(�ǲ��Ǿ��ǽ������갡��)�����ṩ�����㣬���ж�������Ƿ��ཻ��ֻ�ж���һ����
BOOL CSTLModel::CrossZ(CPoint3D *p1,CPoint3D *p2, double z, CPoint3D& p3D)
{
	double min,max;   //min max�ֱ�����һ���ߵ�z��Ĳ�ֵ

	min=p1->z;
	max=p1->z;

	if(p2->z<min)  min = p2->z;
	if(p2->z>max)  max = p2->z;

	double k;

	k=(z - p1->z)/(p2->z - p1->z);   //����ϵ��	

	if(min<=z && max>=z)           //z�ֲ�߶� 
	{
		p3D.x = k*(p2->x - p1->x) + p1->x ;
		p3D.y = k*(p2->y - p1->y) + p1->y ;
		p3D.z = k*(p2->z - p1->z) + p1->z ;
		return TRUE;
	}
	else	
		return FALSE;	
}

CTuoPu::CTuoPu()
{
	beUsed=0;    //�Ƿ��ù�������
	beUsedToo = 0;   //�Ƿ��ù�������
}

CTuoPu::~CTuoPu()
{
}

void CSTLModel::sortCenTri(int cenNum)    //����ÿһ�㽻����
{
//	int triNum;
//	triNum = m_Z_fenceng[0]->num;//���ֲ����������еĵ�һ�������ζ�Ϊ��ʼ������

	int SizeAll;
	SizeAll=m_Z_fenceng.GetSize();  //�ཻ�����������
	int i;//��Ǳ��ָ������һ������
	int Size;
	Size=0;
	for(int j = 0 ; j < SizeAll ; j++)   //������������ָ���б�cenNum����Ҫ�������һ�㣬
	{
		if(m_Z_fenceng[j]->cenNum == cenNum)//ȡ��Ҫ�������һ�㣬��ţ��ɷֲ�����֪��ÿ��Ľ������������е�
			                                //��ôȡ����һ��Ľ���������ٻ����һ������һ��Ľ����ţ����ɷ������н���
		{
			//AfxMessageBox("�ҵ���һ��ĵ�!");
			Size++;//�����һ��ĵ���
			
			i=j;
			//����Ӧ�Խ�����ߵ�a1,a2��������ȷ��a1Ϊ��㣬a2Ϊ�յ㡣
		//	for(int i =0 ;i < Size ; i++)
		//	{
				int triNum;   
				triNum = m_Z_fenceng[i]->num;
				double nx,ny;
				nx = m_TriList[triNum]->normal.dx;   //nx ny��ɶ��
				ny = m_TriList[triNum]->normal.dy;	 //nx ny��ɶ��   //�жϽ�����ˣ�

				if((nx*(m_Z_fenceng[i]->a2.y  -  m_Z_fenceng[i]->a1.y)-\
					ny*(m_Z_fenceng[i]->a2.x  -  m_Z_fenceng[i]->a1.x)) <= 0)
				{
					CPoint3D temp;
					temp=m_Z_fenceng[i]->a1;
					m_Z_fenceng[i]->a1=m_Z_fenceng[i]->a2;
					m_Z_fenceng[i]->a2=temp;
				}
		//	}	
		}//��ÿ���������ڵĶ���������ϣ������С��0�ģ�a1a2��λ��
		//��a1,a2�Ѿ��źõģ����˽ṹ��������	
	
	}

		int numTemp,numTemp2;
		int temp = 0,temp1 = 0;
		
		for(int k =0 ;k < Size ; k++)
		{
			//AfxMessageBox("��ʼ��a1=a2����һ��ѭ��!");
			numTemp = i - Size + k + 1;
			if(m_Z_fenceng[numTemp]->a2 == m_Z_fenceng[numTemp]->a1)			
			{
				AfxMessageBox("�����εĶ���պ�λ�ڽ�����,������������!");//�����εĶ���պ�λ�ڽ�����
				//ExitProcess(0);
				exit(0);
			//	PostQuitMessage(0);
			}
			else
			{
				for(int l =0 ;l < Size ; l++)
				{
				//	AfxMessageBox("��ʼ��a1=a2�ĵ�!");
					numTemp2 =  i - Size + l + 1;
					
					
					if(m_Z_fenceng[numTemp]->a2 == m_Z_fenceng[numTemp2]->a1)
					{
						//m_Z_fenceng[numTemp]->numNext = numTemp2;
						//m_Z_fenceng[numTemp2]->numPrevious=numTemp;

						m_Z_fenceng[numTemp2]->numNext = numTemp;
						m_Z_fenceng[numTemp]->numPrevious=numTemp2;

						//AfxMessageBox("�ҵ�a1=a2�ĵ�!");
						temp++;            //�����ǰ�ÿһ�����е㶼��������
										   //˫��ѭ�������֮��Ӧ�øò�ģ�tuoPu��ǰ����ֵ��
					}					   //һֱ��Ϊ���������⣬����û��ʲô���⣬������Ȧ��
										   //��ѭ��ÿѭ��һ�Σ���ѭ��ѭ��Size��,if����ȥһ�Σ�Ҳ����˵��ÿ��ѭ��һ���ҵ���һ���ڵ�
					temp1++;               
				}
			}
		}        //temp1 = Size^2 = temp^2;
	//AfxMessageBox("�ź�����");
	CString str1,str2,str;

	str1.Format("%d",temp1);
	str2.Format("%d",temp);
	str = str1+'_'+str2;
	//AfxMessageBox(str);
}


