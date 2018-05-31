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

//	AfxMessageBox("Tri类中画图");
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
	for(int i=0;i<m_TriList.GetSize();i++){//此处双重循环，遍历了所有三角形面片，获得了最大点和最小点的坐标，获得最大BOX
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
		//AfxMessageBox("文件格式错误");
		//Sleep(1000);
		return FALSE;
	}

	char str[80];
	CTriChip* tri = NULL;
	while(fscanf(file,"%s",str)==1){
		if(strncmp(str,"normal",6)==0){
			tri = new CTriChip();
			fscanf(file,"%lf %lf %lf",&(tri->normal.dx),&(tri->normal.dy),&(tri->normal.dz));  //向量坐标值
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

//	AfxMessageBox("STL类中画三角形");
	for(int i=0;i<m_TriList.GetSize();i++){
		m_TriList[i]->Draw(pDC);
		//最终都要落到三角形面片的画法上，因为只有这一个draw函数直接调用opengl库函数画三角形进行画图
	
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
//	AfxMessageBox("Part类中画图");
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
				*m_pBox += box;//此处在CBox3D重载了+=运算符，因此可以获得最大的那个BOX
			else{
				m_pBox = new CBox3D();
				*m_pBox = box;
			}
		}
	}
	m_bModified = FALSE;
}


//此处zN为层厚度
void CSTLModel::GetZfenceng(double zN)//计算与分层处的交点（在哪一层里有记录cenNum），并将交点编号信息存储于拓扑表中
{
	CString str;//做测试使用

	//double z=10;//切片位置的z坐标，测试用，后换为zN
	CPoint3D p3D;
	CPoint3D p3D1;
	CPoint3D p3D2;
	CPoint3D p3D3;
	int n = m_TriList.GetSize();      //所有三角形的数目


	UpdateBox();   //求最大的BOX，m_pBox最大的BOX


	int cenN;
	cenN =(int)floor((m_pBox->z1 - m_pBox->z0)/zN);//层数


	for(int z =0 ; z < cenN ; z++)//层数循环
	{
			
	for(int i=0;i<n;i++)//遍历所有三角形
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
				//AfxMessageBox("相交!");
				//对相交进行测试
				//这段代码又臭又长，编写了一整天，是个败笔，没办法，指针的基本原理不理解，瞎折腾了一天
				//简直在摸着石头过河，还静不下心来看教程，太慢

				if(cross1 && cross2 && cross3)
				{
					//AfxMessageBox("三个交点，不可能吧!");
					//但实际情况是，只要顶点位于平面，就发生了	
					//经程序测试，是因为，三角形位于要切片的z平面上面。哈哈

				}

				CTuoPu* tuoPu = new CTuoPu;

				tuoPu->num=i;//存储被切割的三角形的编号
				tuoPu->cenNum=z;//存储切割层数

				if(cross1 && cross2 && !cross3)//即【0】【1】点的连线与z切割面相交
				{
					tuoPu->a1=p3D1;       //a1，a2交点，，，，
					tuoPu->a2=p3D2;
					m_Z_fenceng.Add(tuoPu);  //存储所有相交坐标
				}
				if(cross1 && cross3 && !cross2)//即【0】【2】点的连线与z切割面相交
				{
					tuoPu->a1=p3D1;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}
				if(cross2 && cross3 && !cross1)//即【1】【2】点的连线与z切割面相交
				{
					tuoPu->a1=p3D2;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}
				cross=cross1=cross2=cross3=FALSE;//这句话可有可无，加在这里是为了让我更放心，有病。	
			}
		}
	}
}

void CSTLModel::GetZfenceng(int cenN)//切片层数
{	
	CPoint3D p3D;
	CPoint3D p3D1;
	CPoint3D p3D2;
	CPoint3D p3D3;
	int n = m_TriList.GetSize();

	UpdateBox();
	double zN;
	//m_pBox是CEntity类中定义的一个BOX，里面存储了模型的最大和最小点，而CSTLModel
	//是由CEntity派生的子类，因此可以随意访问此变量
	zN =(m_pBox->z1 - m_pBox->z0)/cenN;//得到层的厚度
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

			if(CrossZ(&tri->vex[0],&tri->vex[1],startpoint + z*zN, p3D))  //判断是否相交01
			{

				p3D1 = p3D;
				cross1=TRUE;
				cross=TRUE;

			}
			if(CrossZ(&tri->vex[0],&tri->vex[2], startpoint + z*zN, p3D))   //判断是否相交02
			{

				p3D2 = p3D;
				cross2=TRUE;
				cross=TRUE;

			}
			if(CrossZ(&tri->vex[1],&tri->vex[2], startpoint + z*zN, p3D))   //判断是否相交12
			{

				p3D3 = p3D;
				cross3=TRUE;
				cross=TRUE;
			}
			//这样的判断相交，如果面片顶点位于相交面上，就会出现两个相同的交点

			if(cross)
			{
				//AfxMessageBox("相交!");
				//对相交进行测试
				//这段代码又臭又长，编写了一整天，是个败笔，没办法，指针的基本原理不理解，瞎折腾了一天
				//简直在摸着石头过河，还静不下心来看教程，太慢


				

				if(cross1 && cross2 && cross3)
				{
					//AfxMessageBox("三个交点，不可能吧!");
					//但实际情况是，只要顶点位于平面，就发生了	
					//经程序测试，是因为，三角形位于要切片的z平面上面。哈哈
					//这种情况经常发生，而且影响轮廓线的画出，所以给忽略了，因为不知道如何表达，这个三角形面被切割了

				}

				CTuoPu* tuoPu = new CTuoPu;
				tuoPu->num=i;//存储被切割的三角形的编号
				tuoPu->cenNum=z;//存储被切割的三角形的编号

				if(cross1 && cross2 && !cross3)//即【0】【1】点的连线与z切割面相交
				{
					tuoPu->line1=0;//表明是00,01两条线相交
					tuoPu->line2=1;

					tuoPu->a1=p3D1;
					tuoPu->a2=p3D2;
					m_Z_fenceng.Add(tuoPu);
				}
				if(cross1 && cross3 && !cross2)//即【0】【2】点的连线与z切割面相交
				{
					tuoPu->line1=0;//表明是00,02两条线相交
					tuoPu->line2=2;

					tuoPu->a1=p3D1;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}
				if(cross2 && cross3 && !cross1)//即【1】【2】点的连线与z切割面相交
				{
					tuoPu->line1=1;//表明是01,02两条线相交
					tuoPu->line2=2;

					tuoPu->a1=p3D2;
					tuoPu->a2=p3D3;
					m_Z_fenceng.Add(tuoPu);
				}

				cross=cross1=cross2=cross3=FALSE;//这句话可有可无，加在这里是为了让我更放心
					
				//m_Z_fenceng每一层连续存在一起，但不是首尾顺次相连
			}

			

		}

	}

}


//自己写的判断一个三角形面片与一个Z平面有无交点，并将交点返回p3D(是不是就是交点坐标啊啊)，是提供两个点，来判断这个边是否相交，只判断这一条边
BOOL CSTLModel::CrossZ(CPoint3D *p1,CPoint3D *p2, double z, CPoint3D& p3D)
{
	double min,max;   //min max分别是这一条边的z向的差值

	min=p1->z;
	max=p1->z;

	if(p2->z<min)  min = p2->z;
	if(p2->z>max)  max = p2->z;

	double k;

	k=(z - p1->z)/(p2->z - p1->z);   //比例系数	

	if(min<=z && max>=z)           //z分层高度 
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
	beUsed=0;    //是否被用过，，，
	beUsedToo = 0;   //是否被用过，，，
}

CTuoPu::~CTuoPu()
{
}

void CSTLModel::sortCenTri(int cenNum)    //整理每一层交点数
{
//	int triNum;
//	triNum = m_Z_fenceng[0]->num;//将分层拓扑数组中的第一个三角形定为起始三角形

	int SizeAll;
	SizeAll=m_Z_fenceng.GetSize();  //相交交点对数总数
	int i;//标记被分割层的最后一个号码
	int Size;
	Size=0;
	for(int j = 0 ; j < SizeAll ; j++)   //遍历整个交点指针列表，cenNum，需要排序的那一层，
	{
		if(m_Z_fenceng[j]->cenNum == cenNum)//取出要排序的那一层，层号，由分层程序可知，每层的交点是连续排列的
			                                //那么取出这一层的交点个数，再获得这一层的最后一点的交点编号，即可访问所有交点
		{
			//AfxMessageBox("找到第一层的点!");
			Size++;//获得这一层的点数
			
			i=j;
			//首先应对交点里边的a1,a2进行排序，确认a1为起点，a2为终点。
		//	for(int i =0 ;i < Size ; i++)
		//	{
				int triNum;   
				triNum = m_Z_fenceng[i]->num;
				double nx,ny;
				nx = m_TriList[triNum]->normal.dx;   //nx ny是啥？
				ny = m_TriList[triNum]->normal.dy;	 //nx ny是啥？   //判断交叉相乘，

				if((nx*(m_Z_fenceng[i]->a2.y  -  m_Z_fenceng[i]->a1.y)-\
					ny*(m_Z_fenceng[i]->a2.x  -  m_Z_fenceng[i]->a1.x)) <= 0)
				{
					CPoint3D temp;
					temp=m_Z_fenceng[i]->a1;
					m_Z_fenceng[i]->a1=m_Z_fenceng[i]->a2;
					m_Z_fenceng[i]->a2=temp;
				}
		//	}	
		}//对每个三角形内的顶点排序完毕，即叉乘小于0的，a1a2换位置
		//将a1,a2已经排好的，拓扑结构进行排序	
	
	}

		int numTemp,numTemp2;
		int temp = 0,temp1 = 0;
		
		for(int k =0 ;k < Size ; k++)
		{
			//AfxMessageBox("开始找a1=a2，第一重循环!");
			numTemp = i - Size + k + 1;
			if(m_Z_fenceng[numTemp]->a2 == m_Z_fenceng[numTemp]->a1)			
			{
				AfxMessageBox("三角形的顶点刚好位于截面上,此种情况会出错!");//三角形的顶点刚好位于截面上
				//ExitProcess(0);
				exit(0);
			//	PostQuitMessage(0);
			}
			else
			{
				for(int l =0 ;l < Size ; l++)
				{
				//	AfxMessageBox("开始找a1=a2的点!");
					numTemp2 =  i - Size + l + 1;
					
					
					if(m_Z_fenceng[numTemp]->a2 == m_Z_fenceng[numTemp2]->a1)
					{
						//m_Z_fenceng[numTemp]->numNext = numTemp2;
						//m_Z_fenceng[numTemp2]->numPrevious=numTemp;

						m_Z_fenceng[numTemp2]->numNext = numTemp;
						m_Z_fenceng[numTemp]->numPrevious=numTemp2;

						//AfxMessageBox("找到a1=a2的点!");
						temp++;            //这里是把每一层所有点都连起来了
										   //双重循环，完毕之后，应该该层的，tuoPu中前后都有值了
					}					   //一直以为这里有问题，这里没有什么问题，都连成圈了
										   //外循环每循环一次，内循环循环Size次,if语句进去一次，也就是说，每大循环一次找到下一个节点
					temp1++;               
				}
			}
		}        //temp1 = Size^2 = temp^2;
	//AfxMessageBox("排好序了");
	CString str1,str2,str;

	str1.Format("%d",temp1);
	str2.Format("%d",temp);
	str = str1+'_'+str2;
	//AfxMessageBox(str);
}


