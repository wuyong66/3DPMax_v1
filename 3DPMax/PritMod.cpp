// PritMod.cpp : implementation file
//

#include "stdafx.h"
#include "3dpmax.h"
#include "PritMod.h"

#include "MainFrm.h"

#include "3DPMaxDoc.h"
#include "3DPMaxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMy3DPMaxApp theApp;       // �ڴ�����Ӧ�����е�theApp����ȡ������ָ��
/////////////////////////////////////////////////////////////////////////////
// CPritMod dialog


CPritMod::CPritMod(CWnd* pParent /*=NULL*/)
	: CDialog(CPritMod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPritMod)
	m_modChose = 0;
	m_distance1 = 200;
	m_distance2 = 200;
	//}}AFX_DATA_INIT
}


void CPritMod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPritMod)
	DDX_Radio(pDX, IDC_RADIO_01, m_modChose);
	DDX_Text(pDX, IDC_EDIT2, m_distance1);
	DDX_Text(pDX, IDC_EDIT4, m_distance2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPritMod, CDialog)
	//{{AFX_MSG_MAP(CPritMod)
	ON_BN_CLICKED(IDC_DataOk, OnDataOk)
	ON_BN_CLICKED(IDC_DataWrt, OnDataWrt)
	ON_BN_CLICKED(IDC_DataCancel, OnDataCancel)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPritMod message handlers

void CPritMod::OnDataCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


BOOL CPritMod::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	break_flag = FALSE;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPritMod::OnDataWrt() 
{
	// TODO: Add your control notification handler code here
	//ɾ�����ݿ���������
//	int nCount = m_pRecordset->GetRecordCount();    //����-1������ȡ��
/*
	int nCount = 0;

	m_pRecordset->MoveFirst();
	while(!m_pRecordset->adoEOF)
	{
		nCount ++;
		m_pRecordset->MoveNext();
	}

	CString strNum;
	strNum.Format("%d",nCount);
	AfxMessageBox(strNum);

*/
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	try
	{
		m_pRecordset->Open("DELETE * FROM coordinate",                // ɾ��coordinate���������ֶ�
							theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
							adOpenDynamic,
							adLockOptimistic,
							adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}

	try
	{
		m_pRecordset->Open("SELECT * FROM coordinate",                // ��ѯcoordinate���������ֶ�
							theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
							adOpenDynamic,
							adLockOptimistic,
							adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}

	CString str;
	//����д�����ݿ����
	for(int j = 0; j < m_pData.GetSize(); j++)
	{
		try
		{
			m_pRecordset->AddNew();

			//�������Ϣ
			str.Format("%d",m_pData[j]->cengNum);
			m_pRecordset->PutCollect("cengNum", _variant_t(str));
			str.Format("%d",m_pData[j]->roundNum);
			m_pRecordset->PutCollect("roundNum", _variant_t(str));
			str.Format("%d",m_pData[j]->pritNum);
			m_pRecordset->PutCollect("pritNum", _variant_t(str));

			//��ͷ1����
			str.Format("%lf",m_pData[j]->x1o);
			m_pRecordset->PutCollect("x1o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y1o);
			m_pRecordset->PutCollect("y1o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z1o);
			m_pRecordset->PutCollect("z1o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x1i);
			m_pRecordset->PutCollect("x1i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y1i);
			m_pRecordset->PutCollect("y1i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z1i);
			m_pRecordset->PutCollect("z1i", _variant_t(str));

			//��ͷ2����
			str.Format("%lf",m_pData[j]->x2o);
			m_pRecordset->PutCollect("x2o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y2o);
			m_pRecordset->PutCollect("y2o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z2o);
			m_pRecordset->PutCollect("z2o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x2i);
			m_pRecordset->PutCollect("x2i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y2i);
			m_pRecordset->PutCollect("y2i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z2i);
			m_pRecordset->PutCollect("z2i", _variant_t(str));

			//��ͷ3����
			str.Format("%lf",m_pData[j]->x3o);
			m_pRecordset->PutCollect("x3o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y3o);
			m_pRecordset->PutCollect("y3o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z3o);
			m_pRecordset->PutCollect("z3o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x3i);
			m_pRecordset->PutCollect("x3i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y3i);
			m_pRecordset->PutCollect("y3i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z3i);
			m_pRecordset->PutCollect("z3i", _variant_t(str));

			//��ͷ4����
			str.Format("%lf",m_pData[j]->x4o);
			m_pRecordset->PutCollect("x4o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y4o);
			m_pRecordset->PutCollect("y4o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z4o);
			m_pRecordset->PutCollect("z4o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x4i);
			m_pRecordset->PutCollect("x4i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y4i);
			m_pRecordset->PutCollect("y4i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z4i);
			m_pRecordset->PutCollect("z4i", _variant_t(str));

			//��ͷ5����
			str.Format("%lf",m_pData[j]->x5o);
			m_pRecordset->PutCollect("x5o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y5o);
			m_pRecordset->PutCollect("y5o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z5o);
			m_pRecordset->PutCollect("z5o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x5i);
			m_pRecordset->PutCollect("x5i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y5i);
			m_pRecordset->PutCollect("y5i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z5i);
			m_pRecordset->PutCollect("z5i", _variant_t(str));

			//��ͷ6����
			str.Format("%lf",m_pData[j]->x6o);
			m_pRecordset->PutCollect("x6o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y6o);
			m_pRecordset->PutCollect("y6o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z6o);
			m_pRecordset->PutCollect("z6o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x6i);
			m_pRecordset->PutCollect("x6i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y6i);
			m_pRecordset->PutCollect("y6i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z6i);
			m_pRecordset->PutCollect("z6i", _variant_t(str));

			//��ͷ7����
			str.Format("%lf",m_pData[j]->x7o);
			m_pRecordset->PutCollect("x7o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y7o);
			m_pRecordset->PutCollect("y7o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z7o);
			m_pRecordset->PutCollect("z7o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x7i);
			m_pRecordset->PutCollect("x7i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y7i);
			m_pRecordset->PutCollect("y7i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z7i);
			m_pRecordset->PutCollect("z7i", _variant_t(str));

			//��ͷ8����
			str.Format("%lf",m_pData[j]->x8o);
			m_pRecordset->PutCollect("x8o", _variant_t(str));
			str.Format("%lf",m_pData[j]->y8o);
			m_pRecordset->PutCollect("y8o", _variant_t(str));
			str.Format("%lf",m_pData[j]->z8o);
			m_pRecordset->PutCollect("z8o", _variant_t(str));
			str.Format("%lf",m_pData[j]->x8i);
			m_pRecordset->PutCollect("x8i", _variant_t(str));
			str.Format("%lf",m_pData[j]->y8i);
			m_pRecordset->PutCollect("y8i", _variant_t(str));
			str.Format("%lf",m_pData[j]->z8i);
			m_pRecordset->PutCollect("z8i", _variant_t(str));

		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
	}
	//ɾ�����ж�̬���飬�ͷ��ڴ�
	for (int i = 0; i < m_pData.GetSize(); i++)
		delete m_pData[i];
	m_pData.RemoveAll();
	AfxMessageBox("����д�����ݿ���ϣ�");
	GetDlgItem(IDC_DataWrt)->EnableWindow(FALSE);

}


void CPritMod::OnDataOk() 
{
	// TODO: Add your control notification handler code here
	//��ȡ�ĵ���ͼָ��
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	for (int i = 0; i < m_pData.GetSize(); i++)
		delete m_pData[i];
	m_pData.RemoveAll();

	for(i = 0; i < pView->m_round.GetSize(); i++)
		delete pView->m_round[i];
	pView->m_round.RemoveAll();

	pView->GetEveRound();   //�������꺯��

	UpdateData(true);

	switch(m_modChose)
	{
		case 0 : PritMod1(0);	break;
		case 1 : PritMod2(0);	break;
		case 2 : PritMod3(0);	break;
		case 3 : PritMod4(0);	break;
		case 4 : PritMod5(0);	break;
		case 5 : PritMod6(0);	break;
		case 6 : PritMod7(0);   break;
		case 7 : PritMod8(0);	break;
		default :   break;
	}
              
	AfxMessageBox("����������ϣ�");
	GetDlgItem(IDC_DataOk)->EnableWindow(FALSE);
}


//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod1(int cenN)
{
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	for(int i = cenN; i < pView->cenN; i++)   
	{
		CDataLib *pData = new CDataLib;

		pData->cengNum = i;
		pData->roundNum = pView->m_round[i]->roundNum;
		pData->pritNum = 1;
		
		//ǹͷ6����
		pData->x6o = 0.0;
		pData->y6o = pView->m_round[i]->rMax;
		pData->z6o = (i)*pView->zN;

		pData->x6i = 0.0;
		pData->y6i = pView->m_round[i]->rMin;
		pData->z6i = (i)*pView->zN;

		//ǹͷ5����
		pData->x5o = 0.0;
		pData->y5o = 0.0;
		pData->z5o = 0.0;

		pData->x5i = 0.0;
		pData->y5i = 0.0;
		pData->z5i = 0.0;
			
		//ǹͷ7����
		pData->x7o = 0.0;
		pData->y7o = 0.0;
		pData->z7o = 0.0;

		pData->x7i = 0.0;
		pData->y7i = 0.0;
		pData->z7i = 0.0;
			
		//ǹͷ4����
		pData->x4o = 0.0;
		pData->y4o = 0.0;
		pData->z4o = 0.0;

		pData->x4i = 0.0;
		pData->y4i = 0.0;
		pData->z4i = 0.0;
			
		//ǹͷ8����
		pData->x8o = 0.0;
		pData->y8o = 0.0;
		pData->z8o = 0.0;

		pData->x8i = 0.0;
		pData->y8i = 0.0;
		pData->z8i = 0.0;

		//ǹͷ3����
		pData->x3o = 0.0;
		pData->y3o = 0.0;
		pData->z3o = 0.0;

		pData->x3i = 0.0;
		pData->y3i = 0.0;
		pData->z3i = 0.0;

		//ǹͷ1����
		pData->x1o = 0.0;
		pData->y1o = 0.0;
		pData->z1o = 0.0;

		pData->x1i = 0.0;
		pData->y1i = 0.0;
		pData->z1i = 0.0;

		//ǹͷ2����
		pData->x2o = 0.0;
		pData->y2o = 0.0;
		pData->z2o = 0.0;

		pData->x2i = 0.0;
		pData->y2i = 0.0;
		pData->z2i = 0.0;

		m_pData.Add(pData);
	}

	break_flag = TRUE;  //�˳���־		
}

//***********************˫��ͷ��ӡģʽ*****************//
void CPritMod::PritMod2(int cenN)
{

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());	

	double r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;
	r = (pView->m_round[cenN]->rMin)*2;

	UpdateData(TRUE);
	if(r >= m_distance2)
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
			if(break_flag)
			{
				break;
			} 
			//�����R,r��ֵ
			r = (pView->m_round[i]->rMin)*2;
			if(r >= m_distance2)
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->roundNum = pView->m_round[i]->roundNum;
				pData->pritNum = 2;	

				//ǹͷ6����	
				pData->x6o = 0.0;
				pData->y6o = pView->m_round[i]->rMax;
				pData->z6o = (i)*pView->zN;

				pData->x6i = 0.0;
				pData->y6i = pView->m_round[i]->rMin;
				pData->z6i = (i)*pView->zN;

				//ǹͷ5����
				pData->x5o = 0.0;
				pData->y5o = -pView->m_round[i]->rMax;
				pData->z5o = (i)*pView->zN;

				pData->x5i = 0.0;
				pData->y5i = -pView->m_round[i]->rMin;
				pData->z5i = (i)*pView->zN;

				//ǹͷ7����
				pData->x7o = 0.0;
				pData->y7o = 0.0;
				pData->z7o = 0.0;

				pData->x7i = 0.0;
				pData->y7i = 0.0;
				pData->z7i = 0.0;
			
				//ǹͷ4����
				pData->x4o = 0.0;
				pData->y4o = 0.0;
				pData->z4o = 0.0;

				pData->x4i = 0.0;
				pData->y4i = 0.0;
				pData->z4i = 0.0;
			
				//ǹͷ8����
				pData->x8o = 0.0;
				pData->y8o = 0.0;
				pData->z8o = 0.0;

				pData->x8i = 0.0;
				pData->y8i = 0.0;
				pData->z8i = 0.0;

				//ǹͷ3����
				pData->x3o = 0.0;
				pData->y3o = 0.0;
				pData->z3o = 0.0;

				pData->x3i = 0.0;
				pData->y3i = 0.0;
				pData->z3i = 0.0;

				//ǹͷ1����
				pData->x1o = 0.0;
				pData->y1o = 0.0;
				pData->z1o = 0.0;

				pData->x1i = 0.0;
				pData->y1i = 0.0;
				pData->z1i = 0.0;

				//ǹͷ2����
				pData->x2o = 0.0;
				pData->y2o = 0.0;
				pData->z2o = 0.0;

				pData->x2i = 0.0;
				pData->y2i = 0.0;
				pData->z2i = 0.0;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod1(num);
			}

		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ�����Ϊ��һ��");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod1(num);
	}



}

//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod3(int cenN)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());	

	double R,r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;

	R = (pView->m_round[cenN]->rMin)*1.5;
	r = (pView->m_round[cenN]->rMin)*1.73205;

	UpdateData(TRUE);
	if((R >= m_distance1)&&(r >= m_distance2))
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
			if(break_flag)
			{
				break;
			} 
			//�����R,r��ֵ
			R = (pView->m_round[i]->rMin)*1.5;
			r = (pView->m_round[i]->rMin)*1.73205;
			if((R >= m_distance1)&&(r >= m_distance2))
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->roundNum = pView->m_round[i]->roundNum;
				pData->pritNum = 3;	

				//ǹͷ6����	
				pData->x6o = -(pView->m_round[i]->rMax)*0.5;
				pData->y6o = (pView->m_round[i]->rMax)*0.86603;
				pData->z6o = (i)*pView->zN;

				pData->x6i = -(pView->m_round[i]->rMin)*0.5;
				pData->y6i = (pView->m_round[i]->rMin)*0.86603;
				pData->z6i = (i)*pView->zN;

				//ǹͷ5����
				pData->x5o = -(pView->m_round[i]->rMax)*0.5;
				pData->y5o = -(pView->m_round[i]->rMax)*0.86603;
				pData->z5o = (i)*pView->zN;

				pData->x5i = -(pView->m_round[i]->rMin)*0.5;
				pData->y5i = -(pView->m_round[i]->rMin)*0.86603;
				pData->z5i = (i)*pView->zN;
			
				//ǹͷ7����
				pData->x7o = pView->m_round[i]->rMax;
				pData->y7o = 0.0;
				pData->z7o = (i)*pView->zN;

				pData->x7i = pView->m_round[i]->rMin;
				pData->y7i = 0;
				pData->z7i = (i)*pView->zN;

				//ǹͷ4����
				pData->x4o = 0.0;
				pData->y4o = 0.0;
				pData->z4o = 0.0;

				pData->x4i = 0.0;
				pData->y4i = 0.0;
				pData->z4i = 0.0;
			
				//ǹͷ8����
				pData->x8o = 0.0;
				pData->y8o = 0.0;
				pData->z8o = 0.0;

				pData->x8i = 0.0;
				pData->y8i = 0.0;
				pData->z8i = 0.0;

				//ǹͷ3����
				pData->x3o = 0.0;
				pData->y3o = 0.0;
				pData->z3o = 0.0;

				pData->x3i = 0.0;
				pData->y3i = 0.0;
				pData->z3i = 0.0;

				//ǹͷ1����
				pData->x1o = 0.0;
				pData->y1o = 0.0;
				pData->z1o = 0.0;

				pData->x1i = 0.0;
				pData->y1i = 0.0;
				pData->z1i = 0.0;

				//ǹͷ2����
				pData->x2o = 0.0;
				pData->y2o = 0.0;
				pData->z2o = 0.0;

				pData->x2i = 0.0;
				pData->y2i = 0.0;
				pData->z2i = 0.0;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod2(num);

			}

		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ����͵ڶ���");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod2(num);
	}


}



//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod4(int cenN)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());	

	double R,r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;

	R = (pView->m_round[cenN]->rMin)*1.41421;
	r = (pView->m_round[cenN]->rMin)*1.41421;

	UpdateData(TRUE);
	if((R >= m_distance1)&&(r >= m_distance2))
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
			if(break_flag)
			{
				break;
			} 
			//�����R,r��ֵ
			R = (pView->m_round[i]->rMin)*1.41421;
			r = (pView->m_round[i]->rMin)*1.41421;

			if((R >= m_distance1)&&(r >= m_distance2))
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->roundNum = pView->m_round[i]->roundNum;
				pData->pritNum = 4;	

				//ǹͷ6����	
				pData->x6o = -(pView->m_round[i]->rMax)*0.70711;
				pData->y6o = (pView->m_round[i]->rMax)*0.70711;
				pData->z6o = (i)*pView->zN;

				pData->x6i = -(pView->m_round[i]->rMin)*0.70711;
				pData->y6i = (pView->m_round[i]->rMin)*0.70711;
				pData->z6i = (i)*pView->zN;

				//ǹͷ5����
				pData->x5o = -(pView->m_round[i]->rMax)*0.70711;
				pData->y5o = -(pView->m_round[i]->rMax)*0.70711;
				pData->z5o = (i)*pView->zN;

				pData->x5i = -(pView->m_round[i]->rMin)*0.70711;
				pData->y5i = -(pView->m_round[i]->rMin)*0.70711;
				pData->z5i = (i)*pView->zN;
			
				//ǹͷ7����
				pData->x7o = (pView->m_round[i]->rMax)*0.70711;
				pData->y7o = (pView->m_round[i]->rMax)*0.70711;
				pData->z7o = (i)*pView->zN;

				pData->x7i = (pView->m_round[i]->rMin)*0.70711;
				pData->y7i = (pView->m_round[i]->rMin)*0.70711;
				pData->z7i = (i)*pView->zN;
			
				//ǹͷ4����
				pData->x4o = (pView->m_round[i]->rMax)*0.70711;
				pData->y4o = -(pView->m_round[i]->rMax)*0.70711;
				pData->z4o = (i)*pView->zN;

				pData->x4i = (pView->m_round[i]->rMin)*0.70711;
				pData->y4i = -(pView->m_round[i]->rMin)*0.70711;
				pData->z4i = (i)*pView->zN;

				//ǹͷ8����
				pData->x8o = 0.0;
				pData->y8o = 0.0;
				pData->z8o = 0.0;

				pData->x8i = 0.0;
				pData->y8i = 0.0;
				pData->z8i = 0.0;

				//ǹͷ3����
				pData->x3o = 0.0;
				pData->y3o = 0.0;
				pData->z3o = 0.0;

				pData->x3i = 0.0;
				pData->y3i = 0.0;
				pData->z3i = 0.0;

				//ǹͷ1����
				pData->x1o = 0.0;
				pData->y1o = 0.0;
				pData->z1o = 0.0;

				pData->x1i = 0.0;
				pData->y1i = 0.0;
				pData->z1i = 0.0;

				//ǹͷ2����
				pData->x2o = 0.0;
				pData->y2o = 0.0;
				pData->z2o = 0.0;

				pData->x2i = 0.0;
				pData->y2i = 0.0;
				pData->z2i = 0.0;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod3(num);

			}

		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ�����Ϊ������");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod3(num);
	}


}



//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod5(int cenN)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());	

	double R,r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;
	R = (pView->m_round[cenN]->rMin)*0.69098;
	r = (pView->m_round[cenN]->rMin)*1.17557;

	UpdateData(TRUE);
	if((R >= m_distance1)&&(r >= m_distance2))
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
			if(break_flag)
			{
				break;
			} 
			//�����R,r��ֵ
			R = (pView->m_round[i]->rMin)*0.69098;
			r = (pView->m_round[i]->rMin)*1.17557;
			if((R >= m_distance1)&&(r >= m_distance2))
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->roundNum = pView->m_round[i]->roundNum;
				pData->pritNum = 5;	

				//ǹͷ6����	
				pData->x6o = -(pView->m_round[i]->rMax)*0.80902;
				pData->y6o = (pView->m_round[i]->rMax)*0.58779;
				pData->z6o = (i)*pView->zN;

				pData->x6i = -(pView->m_round[i]->rMin)*0.80902;
				pData->y6i = (pView->m_round[i]->rMin)*0.58779;
				pData->z6i = (i)*pView->zN;

				//ǹͷ5����
				pData->x5o = -(pView->m_round[i]->rMax)*0.80902;
				pData->y5o = -(pView->m_round[i]->rMax)*0.58779;
				pData->z5o = (i)*pView->zN;

				pData->x5i = -(pView->m_round[i]->rMin)*0.80902;
				pData->y5i = -(pView->m_round[i]->rMin)*0.58779;
				pData->z5i = (i)*pView->zN;
			
				//ǹͷ7����
				pData->x7o = (pView->m_round[i]->rMax)*0.30902;
				pData->y7o = (pView->m_round[i]->rMax)*0.95106;
				pData->z7o = (i)*pView->zN;

				pData->x7i = (pView->m_round[i]->rMin)*0.30902;
				pData->y7i = (pView->m_round[i]->rMin)*0.95106;
				pData->z7i = (i)*pView->zN;
			
				//ǹͷ4����
				pData->x4o = (pView->m_round[i]->rMax)*0.30902;
				pData->y4o = -(pView->m_round[i]->rMax)*0.95106;
				pData->z4o = (i)*pView->zN;

				pData->x4i = (pView->m_round[i]->rMin)*0.30902;
				pData->y4i = -(pView->m_round[i]->rMin)*0.95106;
				pData->z4i = (i)*pView->zN;
			
				//ǹͷ8����
				pData->x8o = (pView->m_round[i]->rMax);
				pData->y8o = 0.0;
				pData->z8o = (i)*pView->zN;

				pData->x8i = (pView->m_round[i]->rMin);
				pData->y8i = 0.0;
				pData->z8i = (i)*pView->zN;

				//ǹͷ3����
				pData->x3o = 0.0;
				pData->y3o = 0.0;
				pData->z3o = 0.0;

				pData->x3i = 0.0;
				pData->y3i = 0.0;
				pData->z3i = 0.0;

				//ǹͷ1����
				pData->x1o = 0.0;
				pData->y1o = 0.0;
				pData->z1o = 0.0;

				pData->x1i = 0.0;
				pData->y1i = 0.0;
				pData->z1i = 0.0;

				//ǹͷ2����
				pData->x2o = 0.0;
				pData->y2o = 0.0;
				pData->z2o = 0.0;

				pData->x2i = 0.0;
				pData->y2i = 0.0;
				pData->z2i = 0.0;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod4(num);

			}

		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ�����Ϊ���ļ�");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod4(num);
	}


}


//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod6(int cenN)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());	

	double R,r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;
	R = (pView->m_round[cenN]->rMin)*0.86603;
	r = (pView->m_round[cenN]->rMin)*1.00000;

	UpdateData(TRUE);
	if((R >= m_distance1)&&(r >= m_distance2))
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
			if(break_flag)
			{
				break;
			} 
			//�����R,r��ֵ
			R = (pView->m_round[i]->rMin)*0.86603;
			r = (pView->m_round[i]->rMin)*1.00000;
			if((R >= m_distance1)&&(r >= m_distance2))
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->roundNum = pView->m_round[i]->roundNum;
				pData->pritNum = 6;	

				//ǹͷ6����	
				pData->x6o = -(pView->m_round[i]->rMax)*0.86603;
				pData->y6o = (pView->m_round[i]->rMax)*0.50000;
				pData->z6o = (i)*pView->zN;

				pData->x6i = -(pView->m_round[i]->rMin)*0.86603;
				pData->y6i = (pView->m_round[i]->rMin)*0.50000;
				pData->z6i = (i)*pView->zN;

				//ǹͷ5����
				pData->x5o = -(pView->m_round[i]->rMax)*0.86603;
				pData->y5o = -(pView->m_round[i]->rMax)*0.50000;
				pData->z5o = (i)*pView->zN;

				pData->x5i = -(pView->m_round[i]->rMin)*0.86603;
				pData->y5i = -(pView->m_round[i]->rMin)*0.50000;
				pData->z5i = (i)*pView->zN;
			
				//ǹͷ7����
				pData->x7o = 0.0;
				pData->y7o = (pView->m_round[i]->rMax);
				pData->z7o = (i)*pView->zN;

				pData->x7i = 0.0;
				pData->y7i = (pView->m_round[i]->rMin);
				pData->z7i = (i)*pView->zN;
			
				//ǹͷ4����
				pData->x4o = 0.0;
				pData->y4o = -(pView->m_round[i]->rMax);
				pData->z4o = (i)*pView->zN;

				pData->x4i = 0.0;
				pData->y4i = -(pView->m_round[i]->rMin);
				pData->z4i = (i)*pView->zN;
			
				//ǹͷ8����
				pData->x8o = (pView->m_round[i]->rMax)*0.86603;
				pData->y8o = (pView->m_round[i]->rMax)*0.50000;
				pData->z8o = (i)*pView->zN;

				pData->x8i = (pView->m_round[i]->rMin)*0.86603;
				pData->y8i = (pView->m_round[i]->rMin)*0.50000;
				pData->z8i = (i)*pView->zN;

				//ǹͷ3����
				pData->x3o = (pView->m_round[i]->rMax)*0.86603;
				pData->y3o = -(pView->m_round[i]->rMax)*0.50000;
				pData->z3o = (i)*pView->zN;

				pData->x3i = (pView->m_round[i]->rMin)*0.86603;
				pData->y3i = -(pView->m_round[i]->rMin)*0.50000;
				pData->z3i = (i)*pView->zN;

				//ǹͷ1����
				pData->x1o = 0.0;
				pData->y1o = 0.0;
				pData->z1o = 0.0;

				pData->x1i = 0.0;
				pData->y1i = 0.0;
				pData->z1i = 0.0;

				//ǹͷ2����
				pData->x2o = 0.0;
				pData->y2o = 0.0;
				pData->z2o = 0.0;

				pData->x2i = 0.0;
				pData->y2i = 0.0;
				pData->z2i = 0.0;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod5(num);

			}

		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ�����Ϊ���弶");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod5(num);
	}
}

//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod7(int cenN)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());	

	double R,r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;

	R = (pView->m_round[cenN]->rMin)*0.37653;
	r = (pView->m_round[cenN]->rMin)*0.86779;

	UpdateData(TRUE);
	if((R >= m_distance1)&&(r >= m_distance2))
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
 			if(break_flag)
			{
				break;
			}
			//�����R,r��ֵ
			R = (pView->m_round[i]->rMin)*0.37653;
			r = (pView->m_round[i]->rMin)*0.86779;
			if((R >= m_distance1)&&(r >= m_distance2))
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->roundNum = pView->m_round[i]->roundNum;
				pData->pritNum = 7;				

				//ǹͷ6����	
				pData->x6o = -(pView->m_round[i]->rMax)*0.90108;
				pData->y6o = (pView->m_round[i]->rMax)*0.43366;
				pData->z6o = (i)*pView->zN;

				pData->x6i = -(pView->m_round[i]->rMin)*0.90108;
				pData->y6i = (pView->m_round[i]->rMin)*0.43366;
				pData->z6i = (i)*pView->zN;

				//ǹͷ5����
				pData->x5o = -(pView->m_round[i]->rMax)*0.90108;
				pData->y5o = -(pView->m_round[i]->rMax)*0.43366;
				pData->z5o = (i)*pView->zN;

				pData->x5i = -(pView->m_round[i]->rMin)*0.90108;
				pData->y5i = -(pView->m_round[i]->rMin)*0.43366;
				pData->z5i = (i)*pView->zN;
			
				//ǹͷ7����
				pData->x7o = -(pView->m_round[i]->rMax)*0.22240;
				pData->y7o = (pView->m_round[i]->rMax)*0.97496;
				pData->z7o = (i)*pView->zN;

				pData->x7i = -(pView->m_round[i]->rMin)*0.22240;
				pData->y7i = (pView->m_round[i]->rMin)*0.97496;
				pData->z7i = (i)*pView->zN;
			
				//ǹͷ4����
				pData->x4o = -(pView->m_round[i]->rMax)*0.22240;
				pData->y4o = -(pView->m_round[i]->rMax)*0.97496;
				pData->z4o = (i)*pView->zN;

				pData->x4i = -(pView->m_round[i]->rMin)*0.22240;
				pData->y4i = -(pView->m_round[i]->rMin)*0.97496;
				pData->z4i = (i)*pView->zN;
			
				//ǹͷ8����
				pData->x8o = (pView->m_round[i]->rMax)*0.62347;
				pData->y8o = (pView->m_round[i]->rMax)*0.78185;
				pData->z8o = (i)*pView->zN;

				pData->x8i = (pView->m_round[i]->rMin)*0.62347;
				pData->y8i = (pView->m_round[i]->rMin)*0.78185;
				pData->z8i = (i)*pView->zN;

				//ǹͷ3����
				pData->x3o = (pView->m_round[i]->rMax)*0.62347;
				pData->y3o = -(pView->m_round[i]->rMax)*0.78185;
				pData->z3o = (i)*pView->zN;

				pData->x3i = (pView->m_round[i]->rMin)*0.62347;
				pData->y3i = -(pView->m_round[i]->rMin)*0.78185;
				pData->z3i = (i)*pView->zN;

				//ǹͷ1����
				pData->x1o = (pView->m_round[i]->rMax);
				pData->y1o = 0;
				pData->z1o = (i)*pView->zN;

				pData->x1i = (pView->m_round[i]->rMin);
				pData->y1i = 0;
				pData->z1i = (i)*pView->zN;

				//ǹͷ2����
				pData->x2o = 0.0;
				pData->y2o = 0.0;
				pData->z2o = 0.0;

				pData->x2i = 0.0;
				pData->y2i = 0.0;
				pData->z2i = 0.0;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod6(num);

			}

		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ�����Ϊ������");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod6(num);
	}


}



//***********************����ͷ��ӡģʽ*****************//
void CPritMod::PritMod8(int cenN)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());
	
	//�ڸ�ģʽ�ȼ��¼����R��r��ֵ�������������ѭ����������������ʾ������ѡ�����һ�ȼ� 
	double R,r;  //���޾���ֵ��R����۸��漫ֵ��r����ǹ���漫ֵ
	int num = cenN;
	R = (pView->m_round[cenN]->rMin)*0.54120;   //��0Ȧ����ֵ 
	r = (pView->m_round[cenN]->rMin)*0.76537;   //

	UpdateData(TRUE);
	if((R >= m_distance1)&&(r >= m_distance2))
	{
		for(int i = cenN; i < pView->cenN; i++)
		{
 
			//�����R,r��ֵ
			if(break_flag)
			{
				break;
			}
			R = (pView->m_round[i]->rMin)*0.54120;
			r = (pView->m_round[i]->rMin)*0.76537;
			
			if((R >= m_distance1)&&(r >= m_distance2))
			{
				CDataLib *pData = new CDataLib;
				//��������������
				//��Ȧ����������
				pData->cengNum = i;
				pData->pritNum = 8;
				pData->roundNum = pView->m_round[i]->roundNum;

				pData->x1o = (pView->m_round[i]->rMax)*0.92388;
				pData->y1o = (pView->m_round[i]->rMax)*0.38268;
				pData->z1o = i*pView->zN;

				pData->x2o = (pView->m_round[i]->rMax)*0.92388;
				pData->y2o = -(pView->m_round[i]->rMax)*0.38268;
				pData->z2o = i*pView->zN;

				pData->x8o = (pView->m_round[i]->rMax)*0.38268;
				pData->y8o = (pView->m_round[i]->rMax)*0.92388;
				pData->z8o = i*pView->zN;

				pData->x3o = (pView->m_round[i]->rMax)*0.38268;
				pData->y3o = -(pView->m_round[i]->rMax)*0.92388;
				pData->z3o = i*pView->zN;

				pData->x7o = -(pView->m_round[i]->rMax)*0.38268;
				pData->y7o = (pView->m_round[i]->rMax)*0.92388;
				pData->z7o = i*pView->zN;

				pData->x4o = -(pView->m_round[i]->rMax)*0.38268;
				pData->y4o = -(pView->m_round[i]->rMax)*0.92388;
				pData->z4o = i*pView->zN;

				pData->x6o = -(pView->m_round[i]->rMax)*0.92388;
				pData->y6o = (pView->m_round[i]->rMax)*0.38268;
				pData->z6o = i*pView->zN;

				pData->x5o = -(pView->m_round[i]->rMax)*0.92388;
				pData->y5o = -(pView->m_round[i]->rMax)*0.38268;
				pData->z5o = i*pView->zN;

				//��Ȧ����������

				pData->x1i = (pView->m_round[i]->rMin)*0.92388;
				pData->y1i = (pView->m_round[i]->rMin)*0.38268;
				pData->z1i = i*pView->zN;

				pData->x2i = (pView->m_round[i]->rMin)*0.92388;
				pData->y2i = -(pView->m_round[i]->rMin)*0.38268;
				pData->z2i = i*pView->zN;

				pData->x8i = (pView->m_round[i]->rMin)*0.38268;
				pData->y8i = (pView->m_round[i]->rMin)*0.92388;
				pData->z8i = i*pView->zN;

				pData->x3i = (pView->m_round[i]->rMin)*0.38268;
				pData->y3i = -(pView->m_round[i]->rMin)*0.92388;
				pData->z3i = i*pView->zN;

				pData->x7i = -(pView->m_round[i]->rMin)*0.38268;
				pData->y7i = (pView->m_round[i]->rMin)*0.92388;
				pData->z7i = i*pView->zN;

				pData->x4i = -(pView->m_round[i]->rMin)*0.38268;
				pData->y4i = -(pView->m_round[i]->rMin)*0.92388;
				pData->z4i = i*pView->zN;

				pData->x6i = -(pView->m_round[i]->rMin)*0.92388;
				pData->y6i = (pView->m_round[i]->rMin)*0.38268;
				pData->z6i = i*pView->zN;

				pData->x5i = -(pView->m_round[i]->rMin)*0.92388;
				pData->y5i = -(pView->m_round[i]->rMin)*0.38268;
				pData->z5i = i*pView->zN;

				m_pData.Add(pData);
			}
			else
			{
				num = i;
				PritMod7(num);
			}
		}
	}
	else
	{
		AfxMessageBox("��ǰģʽ�ȼ����ߣ����Զ�����Ϊ���߼�");
		//��̬��radiobuttonѡ����һ���ȼ�
		PritMod7(num);
	}

}


void CPritMod::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CPritMod::OnDestroy() 
{	
	// TODO: Add your message handler code here
	if(m_pRecordset!=NULL)
	{
		m_pRecordset->Close();//�رռ�¼������
		m_pRecordset=NULL;
	}
	if(m_pConnection->State)
	{
		m_pConnection->Close();//�ر����Ӷ���
		m_pConnection=NULL;
	}

	CDialog::OnDestroy();

	
}
