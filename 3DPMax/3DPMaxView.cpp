// 3DPMaxView.cpp : implementation of the CMy3DPMaxView class
//

#include "stdafx.h"
#include "3DPMax.h"
#include "MainFrm.h"

#include "3DPMaxDoc.h"
#include "3DPMaxView.h"

#include "3DPSta.h"
#include "Bin2AscOfSTLDlg.h"
#include "CHECKDLG.h"
#include "Communication.h"
#include "ModalProperty.h"
#include "SliceDlg.h"
#include "PritMod.h"
#include "ChkPlace.h"
#include "CheckThread.h"
#include "ModBusThread.h"
#include "ModBusRTU.h"
#include "ModBusTcp.h"

#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxView

IMPLEMENT_DYNCREATE(CMy3DPMaxView, CGLView)

BEGIN_MESSAGE_MAP(CMy3DPMaxView, CGLView)
	//{{AFX_MSG_MAP(CMy3DPMaxView)
	ON_COMMAND(ID_FILE_CLEAR, OnFileClear)
	ON_WM_TIMER()
	ON_COMMAND(ID_BIN2ASC, OnBin2asc)
	ON_COMMAND(ID_BUTTON_FILL, OnButtonFill)
	ON_COMMAND(ID_BUTTON_PROCESS, OnButtonProcess)
	ON_COMMAND(ID_BUTTON_SLICE, OnButtonSlice)
	ON_COMMAND(ID_VIEW_BEHIND, OnViewBehind)
	ON_COMMAND(ID_VIEW_BOTTOM, OnViewBottom)
	ON_COMMAND(ID_VIEW_FRONT, OnViewFront)
	ON_COMMAND(ID_VIEW_LEFT, OnViewLeft)
	ON_COMMAND(ID_VIEW_NE_ISOMETRIC, OnViewNeIsometric)
	ON_COMMAND(ID_VIEW_RIGHT, OnViewRight)
	ON_COMMAND(ID_VIEW_TOP, OnViewTop)
	ON_COMMAND(ID_MODAL_PROPERTY, OnModalProperty)
	ON_COMMAND(ID_MENUOUTLINE, OnMenuoutline)
	ON_COMMAND(ID_MENUPRINTER, OnMenuprinter)
	ON_COMMAND(ID_PRINTING, OnPrinting)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_BUTTON_CHKPLA, OnButtonChkpla)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SLICE, OnUpdateButtonSlice)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FILL, OnUpdateButtonFill)
	ON_COMMAND(ID_VIEW_SHADE, OnViewShade)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BUTMODBUS, OnButmodbus)
	ON_COMMAND(ID_BUTTON_MODBUS_TCP, OnButtonModbusTcp)
	//}}AFX_MSG_MAP
	// Standard printing commands

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxView construction/destruction

CMy3DPMaxView::CMy3DPMaxView()
{
	m_xRotate = 0.0;           //��������ת��
	m_yRotate = 0.0;

    m_LeftButtonDown = FALSE;   //����꽨�����£�����־ģ����������ƶ����ӽ���֮�����仯��    
	m_bool = FALSE;             //��My3DPrinter ����ļ��򿪺���������

	m_fen_bool1 = FALSE;
	m_fen_bool2 = FALSE;

	m_bool_flag = FALSE;        //��������Ƿ��Ѿ����ֹ��㡣

	zN = 10;       
	cenN = 10;

	m_Sort = 0;                   //��ֲ��йء�
	sotCen = 1;

	m_addPoint = 0;             //�Ƿ���ӽ���
	m_addPointOver = 0; 

	pointNum = 0;                //������


	// TODO: add construction code here
}

CMy3DPMaxView::~CMy3DPMaxView()
{
}

BOOL CMy3DPMaxView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}




/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxView diagnostics

#ifdef _DEBUG
void CMy3DPMaxView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DPMaxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DPMaxDoc* CMy3DPMaxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DPMaxDoc)));
	return (CMy3DPMaxDoc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////
// CSTLViewerView message handlers
//����opengl�⺯��������ͼ��ת��Ⱦ�������û�ͼ����
//�Ӹ������ع����ĺ���,��������ִ��    //����������
void CMy3DPMaxView::RenderScene(COpenGLDC* pDC)  
{

	//AfxMessageBox("����RenderScene");//�˴����Ա��������RenderSceneһ��Ҳû�б�����
	glRotatef(m_yRotate,0.0f, 1.0f, 0.0f); // Rock Z
	glRotatef(m_xRotate,1.0f, 0.0f, 0.0f); // Roll X

	glPushMatrix();

	CMy3DPMaxDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	pDoc->SetTitle(pDoc->ModalName);

	pDC->DrawCoord();

	if(!pDoc->m_Part.IsEmpty())
	{
	//	AfxMessageBox("STLViewRenderScene ����m_Part.Draw");
		pDoc->m_Part.Draw(pDC);
		if(m_fen_bool1 | m_fen_bool2)//�жϷֲ㰴ť�Ƿ񱻵��
		{
			FenCeng(pDC);
		}		
	}		

    glPopMatrix();

}

BOOL CMy3DPMaxView::GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1)
{
	CMy3DPMaxDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	if(!pDoc->m_Part.IsEmpty()){
		CBox3D box;
		if(pDoc->m_Part.GetBox(box)){
			x0 = box.x0; y0 = box.y0;	z0 = box.z0;
			x1 = box.x1; y1 = box.y1;   z1 = box.z1;
			return TRUE;
		}
	}

	return FALSE;

}

void CMy3DPMaxView::initRotate()
{
	m_yRotate = 0;
	m_xRotate = 0;
}

/************************************************************************/

void CMy3DPMaxView::OnFileClear() 
{

	// TODO: Add your command handler code here
	CMy3DPMaxDoc* pDoc = GetDocument();
	pDoc->m_Part.RemoveAllEntity();
	//pDoc->pSTLModel = NULL;
	//delete pDoc->pSTLModel ;


	m_bool=0;//�ļ��Ƿ��
	m_bool_flag=0;//�Ƿ��Ѿ��ֹ���
	m_fen_bool1=0;//����ֲ㰴ť1
	m_fen_bool2=0;//����ֲ㰴ť2
	m_Sort = 0 ;
	Invalidate();
	
}

/************************************************************************/
void CMy3DPMaxView::FenCeng(COpenGLDC* pDC)
{
	
		if(m_bool)//�ж��Ѿ���ȡ��stl�ļ�
		{
			CMy3DPMaxDoc* pDoc = GetDocument();
			ASSERT(pDoc);
			if(!m_bool_flag)//�ж��Ƿ��Ѿ��ֲ����		
			{
				if(m_fen_bool1)//����ֲ㰴ť1
				{
					pDoc->pSTLModel->GetZfenceng(zN);	//���㽻�㣬������洢�ڽ����б���
					cenN=(int)floor((pDoc->pSTLModel->m_pBox->z1 - pDoc->pSTLModel->m_pBox->z0)/zN);//����

				}

				else if(m_fen_bool2)//����ֲ㰴ť2
					pDoc->pSTLModel->GetZfenceng(cenN);	//���㽻�㣬������洢�ڽ����б��У�Ϊ���ֲ�����׼��
					
				else
					return;
				m_bool_flag = TRUE;//�����ֲ��־��Ϊ�Էֲ�
			}
			
			for(int i=0;i<pDoc->pSTLModel->m_Z_fenceng.GetSize();i++)//���ô�ѭ�����ֲ���
			{
				
				CPoint3D   a1 ;
				CPoint3D   a2 ;
				a1 = pDoc->pSTLModel->m_Z_fenceng[i]->a1;//ȡ��a1��a2��������
				a2 = pDoc->pSTLModel->m_Z_fenceng[i]->a2;				
				
				COLORREF old_clr;
				pDC->GetColor(old_clr);

				pDC->SetColor(RGB(255,255,0));//��ɫ
				pDC->DrawLine(a1,a2);//��ɫ������


				pDC->SetColor(old_clr);							

			}	
						
		}
		else
		{
			AfxMessageBox("Stl�ļ���δ����!");
		}

}


/************************************************************************/

void CMy3DPMaxView::viewClear()
{
	m_bool=0;//�ļ��Ƿ��
	m_bool_flag=0;//�Ƿ��Ѿ��ֹ���
	m_fen_bool1=0;//����ֲ㰴ť1
	m_fen_bool2=0;//����ֲ㰴ť2
	Invalidate();
}
/*********************************************************************/
void CMy3DPMaxView::SortPoint(int sortCen)
{

	CMy3DPMaxDoc* pDoc = GetDocument();
	pDoc->pSTLModel->sortCenTri(sortCen);
	char   str[8]; 
	int num;
	for(int i=0;i<pDoc->pSTLModel->m_Z_fenceng.GetSize();i++)
	{
		if(pDoc->pSTLModel->m_Z_fenceng[i]->cenNum == sortCen)
		{
			num=i;
			break;	
		}
	}
	sprintf(str, "%ld ",(long)num); 
	m_pGLDC->DrawStringPos(str,pDoc->pSTLModel->m_Z_fenceng[num]->a1);
	CP3d* p3d;
	if(!m_addPoint)
	{
	//////////////////////////////////////////////////////////////////
	p3d = new CP3d;
	m_p3d.Add(p3d);
	p3d->a1 = pDoc->pSTLModel->m_Z_fenceng[num]->a1;
	p3d->a2 = pDoc->pSTLModel->m_Z_fenceng[num]->a2;
	//////////////////////////////////////////////////////////////////
	}
	int startNum;
	startNum = num;
	int next;
	next = pDoc->pSTLModel->m_Z_fenceng[num]->numNext;
	while(next != startNum)
	{		
		num++;
		sprintf(str, "%ld ",(long)num); 
		m_pGLDC->DrawStringPos(str,pDoc->pSTLModel->m_Z_fenceng[next]->a1);
		
		if(!m_addPoint)
		{
		//////////////////////////////////////////////////////////////////
		p3d = new CP3d;
		m_p3d.Add(p3d);
		p3d->a1 = pDoc->pSTLModel->m_Z_fenceng[next]->a1;
		p3d->a2 = pDoc->pSTLModel->m_Z_fenceng[next]->a2;
		//////////////////////////////////////////////////////////////////
		}

		next = pDoc->pSTLModel->m_Z_fenceng[next]->numNext;
	}

}


/************************************************************************/
void CMy3DPMaxView::clearAll()
{

	CMy3DPMaxDoc* pDoc = GetDocument();
	pDoc->m_Part.RemoveAllEntity();
	//pDoc->pSTLModel = NULL;
	//delete pDoc->pSTLModel ;

	for(int i=0;i<m_p3d.GetSize();i++)
	delete m_p3d[i];
	m_p3d.RemoveAll();

	for(i=0;i<m_a3.GetSize();i++)
	delete m_a3[i];
	m_a3.RemoveAll();

	for(i = 0; i < m_round.GetSize(); i++)
	{
		delete m_round[i];
	}
	m_round.RemoveAll();

	m_bool=0;//�ļ��Ƿ��
	m_bool_flag=0;//�Ƿ��Ѿ��ֹ���
	m_fen_bool1=0;//����ֲ㰴ť1
	m_fen_bool2=0;//����ֲ㰴ť2

	pDoc->m_paint_flag = FALSE;  //�����Ƭ��־

	m_Sort = 0 ;

	m_addPoint=0;
	m_addPointOver=0;
	
	pointNum = 0;


	Invalidate();

}


void CMy3DPMaxView::addPoint()
{

	m_addPointOver = TRUE;

	CPoint3D temp;
	double   tempBox,tempBox1;
	double Interval;
	


	CString str;
	//str.Format("����󽻵����%d",m_p3d.GetSize());
	//AfxMessageBox(str);



	for(int i = 0;i < m_p3d.GetSize();i++)
	{
		Interval=0;

	//	AfxMessageBox("ѭ��");
	
		do
		{

			tempBox=(m_p3d[i]->a2.x - m_p3d[i]->a1.x)*(m_p3d[i]->a2.x - m_p3d[i]->a1.x) + (m_p3d[i]->a2.y - m_p3d[i]->a1.y)*(m_p3d[i]->a2.y - m_p3d[i]->a1.y) + (m_p3d[i]->a2.z - m_p3d[i]->a1.z)*(m_p3d[i]->a2.z - m_p3d[i]->a1.z);

			temp.x=(m_p3d[i]->a2.x  -  m_p3d[i]->a1.x)*Interval/tempBox + m_p3d[i]->a1.x ;
			temp.y=(m_p3d[i]->a2.y  -  m_p3d[i]->a1.y)*Interval/tempBox + m_p3d[i]->a1.y ;
			temp.z=(m_p3d[i]->a2.z  -  m_p3d[i]->a1.z)*Interval/tempBox + m_p3d[i]->a1.z ;

			Interval=Interval+1;
			tempBox1=(temp.x - m_p3d[i]->a1.x)*(temp.x - m_p3d[i]->a1.x) + (temp.y - m_p3d[i]->a1.y)*(temp.y - m_p3d[i]->a1.y) + (temp.z - m_p3d[i]->a1.z)*(temp.z - m_p3d[i]->a1.z);


	//		AfxMessageBox("����δ���");

			if(tempBox1 < tempBox)
			{
				CP3d* p3d = new CP3d;
				m_a3.Add(p3d);
				p3d->a3 = temp;	
	//			AfxMessageBox("�������");
			}
				
		}while(tempBox1 < tempBox);		
	}


	//str.Format("��Ӻ󽻵����%d",m_a3.GetSize());
//	AfxMessageBox(str);
	SetTimer(1,10,NULL);

}



void CMy3DPMaxView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(m_addPointOver)
	{
		pointNum = pointNum + 10;
		UpdateWindow( );
		Invalidate();

	}
	CGLView::OnTimer(nIDEvent);
}

void CMy3DPMaxView::OnBin2asc() 
{
	// TODO: Add your command handler code here
	CBin2AscOfSTLDlg dlg;
	dlg.DoModal();
	
}

void CMy3DPMaxView::OnButtonFill() 
{
	// TODO: Add your command handler code here
	CPritMod dlg;
	dlg.DoModal();
	
}

void CMy3DPMaxView::OnButtonProcess() 
{
	// TODO: Add your command handler code here

	C3DPSta *dlg = new C3DPSta;
	dlg->Create(IDD_3DPSTA);   //������ģ̬�Ի���
	dlg->ShowWindow(SW_SHOW);        //��ʾ�Ի���

	
}

void CMy3DPMaxView::OnButtonSlice() 
{
	// TODO: Add your command handler code here
	CMy3DPMaxDoc* pDoc = GetDocument();

	if(m_bool && !m_bool_flag)
	{
		CSliceDlg dlg;
		dlg.DoModal();

		switch (dlg.m_sel)
		{
			case 0://�������Ƭ
				zN = dlg.m_hou;		
				m_fen_bool1 = TRUE;
				m_fen_bool2 = FALSE;
				Invalidate();
				break;
			case 1://��������Ƭ
				cenN = dlg.m_cen;		
				m_fen_bool2 = TRUE;
				m_fen_bool1 = FALSE;
				Invalidate();	
				break;
			default:
				break;
		}
	}
	pDoc->m_paint_flag = TRUE;

}

/**************************�ӽǱ任***********************/

void CMy3DPMaxView::OnViewBehind() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_BACK);
	
}

void CMy3DPMaxView::OnViewBottom() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_BOTTOM);
	
}

void CMy3DPMaxView::OnViewFront() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_FRONT);

}

void CMy3DPMaxView::OnViewLeft() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_LEFT);	
}

void CMy3DPMaxView::OnViewNeIsometric() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_NE_ISOMETRIC);
	
}

void CMy3DPMaxView::OnViewRight() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_RIGHT);
}

void CMy3DPMaxView::OnViewTop() 
{
	// TODO: Add your command handler code here
	initRotate();
	OnViewType(VIEW_TOP);
}



void CMy3DPMaxView::OnModalProperty() 
{
	// TODO: Add your command handler code here

	CModalProperty *dlg = new CModalProperty;
	dlg->Create(IDD_MODAL_PROPERTY);   //������ģ̬�Ի���
	dlg->ShowWindow(SW_SHOW);        //��ʾ�Ի���

	
}

void CMy3DPMaxView::OnMenuoutline() 
{
	// TODO: Add your command handler code here

	CWinThread *pThread=AfxBeginThread(RUNTIME_CLASS(CCheckThread),0,0,NULL);

	
}

void CMy3DPMaxView::OnMenuprinter() 
{
	// TODO: Add your command handler code here

	CWinThread *pThread=AfxBeginThread(RUNTIME_CLASS(CCheckThread),0,0,NULL);
	
}

void CMy3DPMaxView::OnPrinting() 
{
	// TODO: Add your command handler code here
	CCommunication *dlg = new CCommunication;
	dlg->Create(IDD_COMMUNICATION);   //������ģ̬�Ի���
	dlg->ShowWindow(SW_SHOW);        //��ʾ�Ի���
}

void CMy3DPMaxView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case VK_UP:
		MoveView(0.0,0.02);
		break;
	case VK_DOWN:
		MoveView(0.0,-0.02);
		break;
	case VK_RIGHT:
		MoveView(0.02,0);
		break;
	case VK_LEFT:
		MoveView(-0.02,0);
		break;
	}
	CGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMy3DPMaxView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_LeftButtonDown = TRUE;
	m_LeftDownPos = point;	
	CGLView::OnLButtonDown(nFlags, point);
	//AfxMessageBox("������");
}

void CMy3DPMaxView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    m_LeftButtonDown = FALSE;	
	CGLView::OnLButtonUp(nFlags, point);
}

void CMy3DPMaxView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//MK_CONTROL	
	if(m_LeftButtonDown)
  
	{CSize rotate = m_LeftDownPos - point;//�������갴�µ�ʱ�������ڣ���������Ĳ�
		m_LeftDownPos = point;
		//if(nFlags==MK_CONTROL)
		if(nFlags & MK_CONTROL)
			MoveView(-0.001*rotate.cx,0.001*rotate.cy);
	
       else
	   {m_yRotate -= rotate.cx;
	   m_xRotate -= rotate.cy;}
        InvalidateRect(NULL,FALSE);
		
	}	
	
	CGLView::OnMouseMove(nFlags, point);
}

BOOL CMy3DPMaxView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
		// TODO: Add your message handler code here and/or call default
	if(zDelta > 100){
		Zoom(0.9);
		Invalidate();
	}
	if(zDelta < -100){
		Zoom(1.1);
		Invalidate();}
	return CGLView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMy3DPMaxView::OnButtonChkpla() 
{
	// TODO: Add your command handler code here
	CChkPlace *dlg = new CChkPlace;
	dlg->Create(IDD_CHKPLA);   //������ģ̬�Ի���
	dlg->ShowWindow(SW_SHOW);        //��ʾ�Ի���	
}

void CMy3DPMaxView::OnUpdateButtonSlice(CCmdUI* pCmdUI) 
{

	// TODO: Add your command update UI handler code here
	if(!m_bool_flag)

		pCmdUI->Enable(m_bool);
	else

		pCmdUI->Enable(FALSE);
	

}

void CMy3DPMaxView::OnUpdateButtonFill(CCmdUI* pCmdUI) 
{
	
	CMy3DPMaxDoc* pDoc = GetDocument();
	
	// TODO: Add your command update UI handler code here
	if(pDoc->m_paint_flag)	 //��Ϊ�Ƿ��Ϊ��
	{
		//pCmdUI->Enable(m_bool);
		pCmdUI->Enable(m_bool);

	}
	else
	{		
		pCmdUI->Enable(FALSE);
	}	

}

void CMy3DPMaxView::OnViewShade() 
{
	// TODO: Add your command handler code here
	m_pGLDC->Shading(!m_pGLDC->IsShading());
	Invalidate();
	
}

//******************************��ȡ�뾶*************************************************
double CMy3DPMaxView::GetRound(double  x,double y)
{
	double round;
	round = sqrt(pow(x,2)+pow(y,2));
	return round;
}

void CMy3DPMaxView::GetCengRound(int cengNum,int& Rnum,double& Rmax,double& Rmin)
{
	CMy3DPMaxDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	double rMax, rMin, r;
	int rNum ,num ;
	rMax = 0.0;
	r = 0.0;
	rMin = 0.0;
	rNum = 0;
	num = 0;
		for(int i = 0; i < pDoc->pSTLModel->m_Z_fenceng.GetSize(); i++)
		{
			if(pDoc->pSTLModel->m_Z_fenceng[i]->cenNum == cengNum)
			{
				rMax = GetRound(pDoc->pSTLModel->m_Z_fenceng[i]->a1.x,pDoc->pSTLModel->m_Z_fenceng[i]->a1.y);
				num = i;
				break;
			}
		}
		for(int j = num+1; j < pDoc->pSTLModel->m_Z_fenceng.GetSize(); j++)
		{
			if(pDoc->pSTLModel->m_Z_fenceng[j]->cenNum == cengNum)
			{
				rMin = GetRound(pDoc->pSTLModel->m_Z_fenceng[j]->a1.x,pDoc->pSTLModel->m_Z_fenceng[j]->a1.y);
				if((rMax-rMin)>5)
				{
					num = 2;
				//	AfxMessageBox("aa");
					break;
				}
				else if((rMin-rMax)>5)
				{
					num = 2;
					r = rMax;
					rMax = rMin;
					rMin = r;
				//	AfxMessageBox("bb");
					break;
				}
				else
				{
					num = 1;
					rMin = 0.0;
				//	AfxMessageBox("cc");
				}
			}
		}

		Rnum = num;
		Rmax = rMax;
		Rmin = rMin;

//************�����ô���************
//		CString str1,str2,str3,str;
//		str1.Format("%d",Rnum);
//		str2.Format("%lf",Rmax);
//		str3.Format("%lf",Rmin);
//
//		str = str1+ "_" + str2 + "_" + str3;
//		AfxMessageBox(str);
//***********************************
}


//Rֵû�д�������
//�����ô��ݵ���Ҫ��:��ֵ����ʱ���β�Ҳ�ᱻ�����ڴ棬
//Ȼֵ��û�и���ʵ�εģ����Ա�����������ʱ���βα��ͷţ�ʵ�ξ�û�л��ֵ
//�ܽᣬ���������в�����Ҫ������ʱһ��ʹ�ô�ֵ���ݣ�����������Ҫ����ʱ��
//һ����Ҫ��ַ����
void CMy3DPMaxView::GetEveRound()
{
	CMy3DPMaxDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	double Rmax, Rmin;
	int Rnum;
	Rmax = 0.0;
	Rmin = 0.0;

	Rnum = 0;

	if(m_bool_flag)//�ж��Ƿ��Ѿ��ֲ����		
	{
		for(int i = 0; i < cenN; i++)
		{
			GetCengRound(i,Rnum,Rmax,Rmin);  
								
			CRound* pround = new CRound;
			pround->cengNum = i;
			pround->roundNum = Rnum;
			pround->rMax = Rmax;
			pround->rMin = Rmin;

			m_round.Add(pround);
		}
	}
}

void CMy3DPMaxView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

//	GetEveRound();
//	CString str1,str2,str3,str4,str;
//	int num = 0;
//	num = m_round.GetSize();
//	str1.Format("%d",m_round[9]->cengNum);
//	str2.Format("%d",m_round[9]->roundNum);
//	str3.Format("%lf",m_round[9]->rMax);
//	str4.Format("%lf",m_round[9]->rMin);
//	str.Format("%d",num);
//	str = str1+ "_" + str2 + "_" + str3 + "_" + str4;
//	AfxMessageBox(str);

	CGLView::OnLButtonDblClk(nFlags, point);

}


void CMy3DPMaxView::OnButmodbus() 
{
	// TODO: Add your command handler code here
	//CWinThread *pThread=AfxBeginThread(RUNTIME_CLASS(CModBusThread),0,0,NULL);	

		// TODO: Add your command handler code here
	CModBusRTU *dlg = new CModBusRTU;
	dlg->Create(IDD_DIALOG_MODBUSRTU);   //������ģ̬�Ի���
	dlg->ShowWindow(SW_SHOW);        //��ʾ�Ի���
}

void CMy3DPMaxView::OnButtonModbusTcp() 
{
	// TODO: Add your command handler code here
	CModBusTcp dlg;
	dlg.DoModal();
	
}
