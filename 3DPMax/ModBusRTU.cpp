// ModBusRTU.cpp : implementation file
//
#include "stdafx.h"
#include "3dpmax.h"
#include "ModBusRTU.h"
#include "MODBUS_SERVER.h"

#include "Communication.h"
#include "stdlib.h"

#include "MainFrm.h"

#include "3DPMaxDoc.h"
#include "3DPMaxView.h"
#include "stdio.h"
#include "PORT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMy3DPMaxApp theApp;       // �ڴ�����Ӧ�����е�theApp����ȡ������ָ��
/////////////////////////////////////////////////////////////////////////////
// CModBusRTU dialog
CModBusRTU::CModBusRTU(CWnd* pParent /*=NULL*/)
	: CDialog(CModBusRTU::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModBusRTU)
	m_cengNum = -1;
	m_RtuAdd = 01;
	m_RegAdd = 45002;
	m_RegCount = 1;
	m_RegValue = 0x0017;
	m_CommSelect_RTU = 0;
	m_BaudRateSelect_RTU = 1;
	m_DataSelect_RTU = 0;
	m_ParityCheck_RTU = 0;
	m_StopBit_RTU = 0;
	//}}AFX_DATA_INIT
	cengNum = -1;
	updateFlag = FALSE;
	printFlag = TRUE;
}



void CModBusRTU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModBusRTU)
	DDX_Control(pDX, IDC_E_VALUE, m_value);
	DDX_Control(pDX, IDC_E_RTU, m_rtu);
	DDX_Control(pDX, IDC_E_REGCOUNT, m_regcount);
	DDX_Control(pDX, IDC_E_REGADD, m_regadd);
	DDX_Control(pDX, IDC_R_TEXT, m_r_text);
	DDX_Control(pDX, IDC_B_WRITE, m_b_write);
	DDX_Control(pDX, IDC_B_READ, m_b_read);
	DDX_Control(pDX, IDC_B_CLOSE, m_b_close);
	DDX_Text(pDX, IDC_EDIT_CENGNUM, m_cengNum);
	DDX_Text(pDX, IDC_E_RTU, m_RtuAdd);
	DDX_Text(pDX, IDC_E_REGADD, m_RegAdd);
	DDX_Text(pDX, IDC_E_REGCOUNT, m_RegCount);
	DDX_Text(pDX, IDC_E_VALUE, m_RegValue);
	DDX_CBIndex(pDX, IDC_COMBO_CommSelect_RTU, m_CommSelect_RTU);
	DDX_CBIndex(pDX, IDC_COMBO_BaudRate_Select_RTU, m_BaudRateSelect_RTU);
	DDX_CBIndex(pDX, IDC_COMBO_Data_Select_RTU, m_DataSelect_RTU);
	DDX_CBIndex(pDX, IDC_COMBO_ParityCheck_RTU, m_ParityCheck_RTU);
	DDX_CBIndex(pDX, IDC_COMBO_StopBit_RTU, m_StopBit_RTU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModBusRTU, CDialog)
	//{{AFX_MSG_MAP(CModBusRTU)
	ON_BN_CLICKED(IDC_B_CLOSE, OnBClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_B_READ, OnBRead)
	ON_BN_CLICKED(IDC_B_WRITE, OnBWrite)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUT_OPENRTU, OnButOpenrtu)
	ON_BN_CLICKED(IDC_BUT_CLOSERTU, OnButClosertu)
	ON_BN_CLICKED(IDC_BUT_OPEN_MSCOM, OnButOpenMscom)
	ON_BN_CLICKED(IDC_BUT_CLOSE_MSCOM, OnButCloseMscom)
	ON_CBN_SELCHANGE(IDC_COMBO_CommSelect_RTU, OnSelchangeCOMBOCommSelectRTU)
	ON_CBN_SELCHANGE(IDC_COMBO_BaudRate_Select_RTU, OnSelchangeCOMBOBaudRateSelectRTU)
	ON_CBN_SELCHANGE(IDC_COMBO_Data_Select_RTU, OnSelchangeCOMBODataSelectRTU)
	ON_CBN_SELCHANGE(IDC_COMBO_ParityCheck_RTU, OnSelchangeCOMBOParityCheckRTU)
	ON_CBN_SELCHANGE(IDC_COMBO_StopBit_RTU, OnSelchangeCOMBOStopBitRTU)
	ON_BN_CLICKED(IDC_BUT_CLEAR_RICHEDIT, OnButClearRichedit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModBusRTU message handlers

BOOL CModBusRTU::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�رնԻ���
void CModBusRTU::OnBClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::EndDialog(0);
	MODBUS_S_UnInit();  //�ر�MODBUS
	KillTimer(1);
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

}


//�رնԻ���ʱ���رմ���
void CModBusRTU::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	MODBUS_S_UnInit();  //�ر�MODBUS
	KillTimer(1);
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

}

//���ٶԻ���ͬʱ���ټ�ʱ��
void CModBusRTU::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(1);  
	MODBUS_S_UnInit();  //�ر�MODBUS
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
	// TODO: Add your message handler code here
}
//ASCII to Hex�Զ����Ƶ�ת��
//�����ӿڣ�����asc���͵��ַ�����ת��Ϊʮ�����Ƶ��ַ���
//2x%����ʾ�����λʮ�����ƣ���ֻ��һλ���λ���㣬����ֹ��λ�����ȡ����λ
void CModBusRTU::AsciiToHex(CString buff, CString Hex)
{
	//ASCII to Hex
	Hex= "";
	CString str_temp;
	for(int i=0;i<buff.GetLength();i++)
	{
		str_temp.Format("%2x", buff[i]);
		Hex += str_temp;
	}
}
//��ͨѶ��Ϣ����richedit��ʾ
//LPCTSTR һ�ֲ��ɱ����������ı���ַ���������Unicode���뷽ʽ������Ϊ��wchar_t��ʮ��λ
void CModBusRTU::ShowCommFrame(LPCTSTR Msg)
{	
	//Append str To Rich;
	int nlength=m_r_text.GetTextLength();
	m_r_text.SetSel(nlength,  nlength);  
	m_r_text.ReplaceSel(Msg);
}

//���Ĵ�������
void CModBusRTU::OnBRead() 
{
	// TODO: Add your control notification handler code here
		//���Ͷ�ָ����ܷ���
	short int ilist[200];  //��������
	bool	  blist[200];  //��������
	CString rtu,regadd,regcount,strtmp;
	
	memset(ilist,0x00,200);   //��ʼ��Ϊ0
	memset(blist,0x00,200);   //��ʼ��ΪFALSE

	m_rtu.GetWindowText(rtu);  //��ȡ�ӻ���ַ    �ַ�������
	m_regadd.GetWindowText(regadd);//��ȡ�Ĵ�����ַ
	m_regcount.GetWindowText(regcount);//��ȡ��ȡ�Ĵ����ĸ���
	//�жϿؼ����Ƿ����в���
	if(rtu.IsEmpty())
	{
		MessageBox("PLC��ַ����Ϊ��","MODBUS����",MB_OK);
		return;
	}
	else if(regadd.IsEmpty())
	{
		MessageBox("������ַ����Ϊ��","MODBUS����",MB_OK);
		return;
	}
	else if(regcount.IsEmpty())
	{
		MessageBox("������������Ϊ��","MODBUS����",MB_OK);
		return;
	}

	//�ж�PLC��ַ�Ƿ�Ϊ����
	unsigned short int i_regadd, i_regcount;
	unsigned char i_rtu;

	for(int i=0; i<rtu.GetLength(); i++)
	{
		if(isdigit(rtu[i])==0)
		{
			MessageBox("PLC��ַ����Ϊ�ַ�","MODBUS����",MB_OK);
			return;
		}
	}
	i_rtu= atoi(rtu);  //ת��Ϊ���֣�����


	for(i=0; i<regadd.GetLength(); i++)
	{
		if(isdigit(regadd[i])==0)
		{
			MessageBox("������ַ����Ϊ�ַ�","MODBUS����",MB_OK);
			return;
		}
	}
	i_regadd= atoi(regadd);
	if(i_regadd > 50000 || i_regadd <= 0)
	{
			MessageBox("������ַ��Χ����ȷ","MODBUS����",MB_OK);
			return;
	}

	for(i=0; i<regcount.GetLength(); i++)
	{
		if(isdigit(regcount[i])==0)
		{
			MessageBox("������������Ϊ�ַ�","MODBUS����",MB_OK);
			return;
		}
	}
	i_regcount= atoi(regcount);

	if(i_regcount > 200)
	{
			MessageBox("�����������ܴ���200","MODBUS����",MB_OK);
			return;
	}

	//���ɲ���������
	char state= 0;
	ShowCommFrame("���Ͷ��Ĵ�������\r\n");	
		

	if(i_regadd >= 40001 && i_regadd <= 49999)
	{		
		state= MODBUS_S_ReadMultiRegD(i_rtu,i_regadd,i_regcount,ilist);   //�����ּĴ�������  ����short int ������ֵ
	}																	  //short int��32λ����������ռ16λ�� intռ32λ������16λ��������û������
	else if(i_regadd >= 10001 && i_regadd <= 19999)
	{		
		state= MODBUS_S_ReadMultiRegM_1x(i_rtu,i_regadd,i_regcount,blist);
	}	
	else if(i_regadd >= 1 && i_regadd <= 9999)
	{
		state= MODBUS_S_ReadMultiRegM(i_rtu,i_regadd,i_regcount,blist);
	}
	//����state -1 -2 �Լ� 1 ���б��Ƿ�������ɹ�
	if(state==-1)   
	{	
		ShowCommFrame("��ȡ����CRC����ʧ��\r\n");
	}
	else if(state==-2)
	{
		ShowCommFrame("��ȡ����ʧ��,��Ӧ��\r\n");
	}
	else if(state == -3)
	{
		ShowCommFrame("��������ʧ��.\r\n");		
	}
	else 
	{
		ShowCommFrame("��ȡ���ݳɹ�.\r\n");
	}

	//�Ĵ�����ַ��Ϊʮ���ƣ���ӻ�һ��
	CString str;
	if(i_regadd >= 40001 && i_regadd <= 49999)
	{
		for(i=0; i<i_regcount; i++)
		{			
			strtmp.Format("�Ĵ�����ַ%d--0x%04x\r\n", i_regadd+i,(unsigned short int)ilist[i]);	  //ʮ���������						
			str+= strtmp;

		}
	}

	else
	{
		for(i=0; i<i_regcount; i++)
		{			
			strtmp.Format("�Ĵ�����ַ%d--0x%2x\r\n", i_regadd+i,blist[i]);	  						
			str+= strtmp;
		}
	}		
	//Append str To Rich;
	ShowCommFrame(str);	
}

//д�Ĵ�������
void CModBusRTU::OnBWrite() 
{
	// TODO: Add your control notification handler code here
		//����дָ����ܷ���
	CString rtu,regadd,regcount,regvalue;
	
	m_rtu.GetWindowText(rtu);
	m_regadd.GetWindowText(regadd);
	m_regcount.GetWindowText(regcount);
	m_value.GetWindowText(regvalue);

	if(rtu.IsEmpty())
	{
		MessageBox("PLC��ַ����Ϊ��","MODBUS����",MB_OK);
		return;
	}
	else if(regadd.IsEmpty())
	{
		MessageBox("������ַ����Ϊ��","MODBUS����",MB_OK);
		return;
	}
	else if(regvalue.IsEmpty())
	{
		MessageBox("����ֵ����Ϊ��","MODBUS����",MB_OK);
		return;
	}

	//�ж��Ƿ�Ϊ����	
	unsigned short int i_regadd;
	unsigned char i_rtu;
	short int  i_regvalue;

	for(int i=0; i<rtu.GetLength(); i++)
	{
		if(isdigit(rtu[i])==0)
		{
			MessageBox("PLC��ַ����Ϊ�ַ�","MODBUS����",MB_OK);
			return;
		}
	}
	i_rtu= atoi(rtu);

	//�Ĵ���ֵд������
//	for(i=0; i<regvalue.GetLength(); i++)
//	{
//		if(isdigit(regvalue[i])==0)
//		{
//			MessageBox("����ֵ����Ϊ�ַ�","MODBUS����",MB_OK);
//			return;
//		}
//	}
//	i_regvalue= atoi(regvalue);
	
	if((regvalue.GetLength() > 4)||(regvalue.GetLength() < 1))
	{
		MessageBox("���ݳ��Ȳ��ԣ�ӦΪ1-4֮��ĳ���","MODBUS����",MB_OK);
		return ;
	}
	//ʮ�����ƴ���Ϊʮ������
	sscanf(regvalue,"%x",&i_regvalue);

	for(i=0; i<regadd.GetLength(); i++)
	{
		if(isdigit(regadd[i])==0)
		{
			MessageBox("������ַ����Ϊ�ַ�","MODBUS����",MB_OK);
			return;
		}
	}
	i_regadd= atoi(regadd);
	if(i_regadd > 50000 || i_regadd <= 0)
	{
			MessageBox("������ַ��Χ����ȷ","MODBUS����",MB_OK);
			return;
	}

	//���ɲ���������

	char state= 0;
	ShowCommFrame("��������\r\n");		
	//д���ּĴ���
	if(i_regadd >= 40001 && i_regadd <= 49999)
	{		
		state= MODBUS_S_WriteSingRegD(i_rtu,i_regadd,i_regvalue);  //д���ּĴ�����д�ļĴ���ֵΪ16����i_regvalue
	}
	//д��Ȧ
	else if(i_regadd >= 1 && i_regadd <= 9999)
	{
		if(i_regvalue > 0)  
		{			
			state= MODBUS_S_WriteSingRegM(i_rtu,i_regadd,true);
		}
		else
		{
			state= MODBUS_S_WriteSingRegM(i_rtu,i_regadd,false);
		}
	}	

	if(state > 0)
	{
		ShowCommFrame("�������ݳɹ�.\r\n");
	}
	else
	{
		ShowCommFrame("��������ʧ��\r\n");
	}
	
}


//////////////////////////�������ݴ��亯��/////////////////////////////
void CModBusRTU::OnTimer(UINT nIDEvent)      
{
	// TODO: Add your message handler code here and/or call default
	short int ilist[200];  //��������
	ilist[0] = 0;
	char state_r= 0,state_w = 0;       //����ͨѶ״̬

	state_r= MODBUS_S_ReadMultiRegD(01,45002,1,ilist);  //�����ּĴ�����ֵ��������״̬

	//����state -1 -2 �Լ� 1 ���б��Ƿ�������ɹ�
	if(state_r==-1)   
	{	
		ShowCommFrame("��ȡ����CRC����ʧ��\r\n");   //����û�жϿ������ǿ����ܵ����ţ�����У��ʧ��
													//����Ӧ��������������־�ļ�
		Beep( 650, 500);
		//exit(0);

	}
	else if(state_r==-2)
	{

		ShowCommFrame("��ȡ����ʧ��,��Ӧ��\r\n");   //�ӻ��˱��������Ͽ����ӣ�
													//
		Beep( 650, 500);
		//exit(0);
	}

	else if(state_r == -3)
	{
		ShowCommFrame("���ڴ�ʧ��.\r\n");	        //�����˴��ڱ���ǿ�ƶϿ�
		Beep( 650, 500);

	}
	else
	{
		if(printFlag == TRUE)
		{
			ShowCommFrame("�豸������,���ڴ�ӡ...\r\n");    //һ������
			printFlag = FALSE;
		}
		//m_r_text.SetWindowText("�豸������...\r\n");
	}
	
	if(cengNum != ilist[0])
	{
		cengNum = ilist[0];
		updateFlag = TRUE;   //�����ݷ��ͺ��������������ϲ��ұ�֤׼ȷ����󣬽��˱�־λ��λFALSE
		m_cengNum = cengNum;
		UpdateData(FALSE);
	}
	//��������ı�����������Ϣ
	if(updateFlag)
	{
		GetstrOutOfDB();

		int num = coordinate.GetSize();
		for(int i = 0; i < num; i++)
		{
			state_w = MODBUS_S_WriteSingFloat(1, (45010 + i*2), coordinate[i]->floatNum);
			//����state -1 -2 �Լ� 1 ���б��Ƿ�������ɹ�
			if(state_w > 0)
			{
				//ShowCommFrame("�������ݳɹ�.\r\n");
			}
			else
			{
				ShowCommFrame("��������ʧ��,\r\n");   //�и���־�ļ�
				//exit(0);
			}

		}
		for(i = 0; i < num; i++)
			delete coordinate[i];
		coordinate.RemoveAll();

		updateFlag = FALSE;
	}

	CDialog::OnTimer(nIDEvent);

}



//��ע��������Ҫ����������Ȼ��ͨ�������¼��ģ���ϧ���Զ��δ����//����ҪѰ��취��
//��ȡҪ������Ϣ���ַ���
char CModBusRTU::GetstrOutOfDB()
{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
		CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
		CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

		pDoc->CengNumNow = cengNum;
		pDoc->PrintNumNow = "";
		////////////////////////�鿴���ݿ��ܼ�¼����//////////////////

		m_pRecordset.CreateInstance(__uuidof(Recordset));
		try
		{
			m_pRecordset->Open("SELECT * FROM coordinate",                // ��ѯstudentinfo���������ֶ�
								theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
								adOpenDynamic,
								adLockOptimistic,
								adCmdText);
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}

		int nCount = 0;
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			nCount++;
			m_pRecordset->MoveNext();
		}
		if((cengNum >= nCount)||(cengNum < 0))
		{
			//AfxMessageBox("���������������������...");
			return (-1);
		}

		////////////////////////�������ݿⲿ�ִ���//////////////////
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		CString strSql;

		strSql.Format("select * from coordinate where cengNum = %d ",cengNum);    //Ϊʲô����������%d ���˵����ţ�
	                                                    //�����ǲ��еģ������ڴ˾Ͱ����Ÿ�ȥ����

	//	strSql = strSql + "select * from coordinate where cengNum = " + strTest;
	//	AfxMessageBox(strSql);  
		BSTR bsSql = strSql.AllocSysString();
		try
		{
			m_pRecordset->Open(bsSql,                                    // ��ѯcoordinate���������ֶ�
								theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
								adOpenDynamic,
								adLockOptimistic,
								adCmdText);
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}

		float floatNum[56];
		//�洢1��ӡͷ��Ϣ
        floatNum[0] = 1.0f;                       
		floatNum[1] = (float)m_pRecordset->GetCollect("x1o");      
		floatNum[2] = (float)m_pRecordset->GetCollect("y1o"); 
		floatNum[3] = (float)m_pRecordset->GetCollect("z1o"); 

		floatNum[4] = (float)m_pRecordset->GetCollect("x1i");      
		floatNum[5] = (float)m_pRecordset->GetCollect("y1i"); 
		floatNum[6] = (float)m_pRecordset->GetCollect("z1i"); 
		if(floatNum[3] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "1��";				
		}

		//�洢2��ӡͷ��Ϣ
        floatNum[7] = 2.0f;                       
		floatNum[8] = (float)m_pRecordset->GetCollect("x2o");      
		floatNum[9] = (float)m_pRecordset->GetCollect("y2o"); 
		floatNum[10] = (float)m_pRecordset->GetCollect("z2o"); 

		floatNum[11] = (float)m_pRecordset->GetCollect("x2i");      
		floatNum[12] = (float)m_pRecordset->GetCollect("y2i"); 
		floatNum[13] = (float)m_pRecordset->GetCollect("z2i");
		if(floatNum[10] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "2��";				
		}

		//�洢3��ӡͷ��Ϣ
        floatNum[14] = 3.0f;                       
		floatNum[15] = (float)m_pRecordset->GetCollect("x3o");      
		floatNum[16] = (float)m_pRecordset->GetCollect("y3o"); 
		floatNum[17] = (float)m_pRecordset->GetCollect("z3o"); 

		floatNum[18] = (float)m_pRecordset->GetCollect("x3i");      
		floatNum[19] = (float)m_pRecordset->GetCollect("y3i"); 
		floatNum[20] = (float)m_pRecordset->GetCollect("z3i"); 
		if(floatNum[17] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "3��";				
		}

		//�洢4��ӡͷ��Ϣ
        floatNum[21] = 4.0f;                       
		floatNum[22] = (float)m_pRecordset->GetCollect("x4o");      
		floatNum[23] = (float)m_pRecordset->GetCollect("y4o"); 
		floatNum[24] = (float)m_pRecordset->GetCollect("z4o"); 

		floatNum[25] = (float)m_pRecordset->GetCollect("x4i");      
		floatNum[26] = (float)m_pRecordset->GetCollect("y4i"); 
		floatNum[27] = (float)m_pRecordset->GetCollect("z4i");
		if(floatNum[24] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "4��";				
		}

		//�洢5��ӡͷ��Ϣ
        floatNum[28] = 5.0f;                       
		floatNum[29] = (float)m_pRecordset->GetCollect("x5o");      
		floatNum[30] = (float)m_pRecordset->GetCollect("y5o"); 
		floatNum[31] = (float)m_pRecordset->GetCollect("z5o"); 

		floatNum[32] = (float)m_pRecordset->GetCollect("x5i");      
		floatNum[33] = (float)m_pRecordset->GetCollect("y5i"); 
		floatNum[34] = (float)m_pRecordset->GetCollect("z5i");
		if(floatNum[31] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "5��";				
		}

		//�洢6��ӡͷ��Ϣ
        floatNum[35] = 6.0f;                       
		floatNum[36] = (float)m_pRecordset->GetCollect("x6o");      
		floatNum[37] = (float)m_pRecordset->GetCollect("y6o"); 
		floatNum[38] = (float)m_pRecordset->GetCollect("z6o"); 

		floatNum[39] = (float)m_pRecordset->GetCollect("x6i");      
		floatNum[40] = (float)m_pRecordset->GetCollect("y6i"); 
		floatNum[41] = (float)m_pRecordset->GetCollect("z6i"); 
		if(floatNum[38] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "6��";				
		}

		//�洢7��ӡͷ��Ϣ
        floatNum[42] = 7.0f;                       
		floatNum[43] = (float)m_pRecordset->GetCollect("x7o");      
		floatNum[44] = (float)m_pRecordset->GetCollect("y7o"); 
		floatNum[45] = (float)m_pRecordset->GetCollect("z7o"); 

		floatNum[46] = (float)m_pRecordset->GetCollect("x7i");      
		floatNum[47] = (float)m_pRecordset->GetCollect("y7i"); 
		floatNum[48] = (float)m_pRecordset->GetCollect("z7i");
		if(floatNum[45] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "7��";				
		}		

		//�洢8��ӡͷ��Ϣ
        floatNum[49] = 8.0f;                       
		floatNum[50] = (float)m_pRecordset->GetCollect("x8o");      
		floatNum[51] = (float)m_pRecordset->GetCollect("y8o"); 
		floatNum[52] = (float)m_pRecordset->GetCollect("z8o"); 

		floatNum[53] = (float)m_pRecordset->GetCollect("x8i");      
		floatNum[54] = (float)m_pRecordset->GetCollect("y8i"); 
		floatNum[55] = (float)m_pRecordset->GetCollect("z8i"); 
		if(floatNum[52] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "8��";				
		}

		for(int m = 0; m < 56; m++)
		{
			CCoordinate* pCoordinate = new CCoordinate;
			pCoordinate->floatNum = floatNum[m];
			coordinate.Add(pCoordinate);			
		}
		//AfxMessageBox(m_str);
	return 1;
}

void CModBusRTU::OnButOpenrtu() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,500,NULL);
	ShowCommFrame("�ѿ�ʼ��ӡ...\r\n");
	GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(TRUE);
	printFlag = TRUE;
}

void CModBusRTU::OnButClosertu() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	ShowCommFrame("�ѹرմ�ӡ...\r\n");
	GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(TRUE);
}



void CModBusRTU::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
}


void CModBusRTU::OnButOpenMscom() 
{
	// TODO: Add your control notification handler code here
	/*
	Parity :
	EVENPARITY Even 
	MARKPARITY Mark 
	NOPARITY No parity 
	ODDPARITY Odd 
	SPACEPARITY Space 
	*/	
	/*BaudRate:
	CBR_110
	CBR_19200
	CBR_300
	CBR_38400
	CBR_600
	CBR_56000
	CBR_1200
	CBR_57600
	CBR_2400
	CBR_115200
	CBR_4800
	CBR_128000
	CBR_9600
	CBR_256000
	CBR_14400	
	*/
	/*
	ONESTOPBIT 1 stop bit 
	ONE5STOPBITS 1.5 stop bits 
	TWOSTOPBITS 
	*/
	char mscomState;
	unsigned int mscomNum,baudRate,dataNum,orParity,stopBits;
	UpdateData(TRUE);
	switch(m_CommSelect_RTU)
	{
		case 0 : mscomNum = 1; break;
		case 1 : mscomNum = 2; break;
		case 2 : mscomNum = 3; break;
		case 3 : mscomNum = 4; break;
		case 4 : mscomNum = 5; break;
		case 5 : mscomNum = 6; break;
		case 6 : mscomNum = 7; break;
		case 7 : mscomNum = 8; break;
		case 8 : mscomNum = 9; break;

		default : break;
	}
	switch(m_BaudRateSelect_RTU)
	{
		case 0 : baudRate = 9600;   break;
		case 1 : baudRate = 115200; break;
		case 2 : baudRate = 128000; break;
		case 3 : baudRate = 256000; break;

		default : break;
	}
	switch(m_DataSelect_RTU)
	{
		case 0 : dataNum = 8; break;
		case 1 : dataNum = 7; break;

		default : break;
	}
	switch(m_ParityCheck_RTU)
	{
		case 0 : orParity = 0; break;
		case 1 : orParity = 1; break;
		case 2 : orParity = 2; break;

		default : break;
	}

	switch(m_StopBit_RTU)
	{
		case 0 : stopBits = 0; break;
		case 1 : stopBits = 1; break;

		default : break;
	}



	mscomState = MODBUS_S_Init(mscomNum,baudRate,dataNum,orParity,stopBits);
	if(mscomState >0 )
	{
		ShowCommFrame("���ڳɹ���...\r\n");
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(TRUE);
	}
	else
	{
		ShowCommFrame("���ڴ�ʧ�������´�...\r\n");
	}
	
}

void CModBusRTU::OnButCloseMscom() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //�رմ���
	if(IsOpen())
	{
		ShowCommFrame("���ڹر�ʧ�ܣ������¹ر�...\r\n");
	}
	else
	{
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);
		ShowCommFrame("�����ѳɹ��ر�...\r\n");
	}
}

void CModBusRTU::OnSelchangeCOMBOCommSelectRTU() 
{
	// TODO: Add your control notification handler code here	
	ClosePort();  //�رմ���	
	if(IsOpen())
	{
		ShowCommFrame("���ڲ�������ʧ�ܣ����������...\r\n");
	}
	else
	{
		ShowCommFrame("���ں��Ѹ��ģ����ڱ��ȹر�...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}
}

void CModBusRTU::OnSelchangeCOMBOBaudRateSelectRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //�رմ���	
	if(IsOpen())
	{
		ShowCommFrame("���ڲ�������ʧ�ܣ����������...\r\n");
	}
	else
	{
		ShowCommFrame("�������Ѹ��ģ����ڱ��ȹر�...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnSelchangeCOMBODataSelectRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //�رմ���
	if(IsOpen())
	{
		ShowCommFrame("���ڲ�������ʧ�ܣ����������...\r\n");
	}
	else
	{

		ShowCommFrame("����λ�Ѹ��ģ����ڱ��ȹر�...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnSelchangeCOMBOParityCheckRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //�رմ���
	if(IsOpen())
	{
		ShowCommFrame("���ڲ�������ʧ�ܣ����������...\r\n");
	}
	else
	{
		ShowCommFrame("У��λ�Ѹ��ģ����ڱ��ȹر�...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnSelchangeCOMBOStopBitRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //�رմ���
	if(IsOpen())
	{
		ShowCommFrame("���ڲ�������ʧ�ܣ����������...\r\n");
	}
	else
	{
		ShowCommFrame("ֹͣλ�Ѹ��ģ����ڱ��ȹر�...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnButClearRichedit() 
{
	// TODO: Add your control notification handler code here
	m_r_text.SetWindowText("");
	
}



