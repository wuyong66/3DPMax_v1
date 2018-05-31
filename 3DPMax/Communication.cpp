// Communication.cpp : implementation file
//

#include "stdafx.h"
#include "3DPMax.h"
#include "Communication.h"
#include "stdlib.h"

#include "MainFrm.h"

#include "3DPMaxDoc.h"
#include "3DPMaxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CMy3DPMaxApp theApp;       // 在此引用应用类中的theApp来获取库连接指针
/////////////////////////////////////////////////////////////////////////////
// CCommunication dialog


CCommunication::CCommunication(CWnd* pParent /*=NULL*/)
	: CDialog(CCommunication::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommunication)
	m_BaudRate = -1;
	m_Index = -1;
	m_Date_Select = -1;
	m_ParityCheck = -1;
	m_StopBit = -1;
	//}}AFX_DATA_INIT
}


void CCommunication::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommunication)
	DDX_Control(pDX, IDC_COMBO_Date_Select, m_Date_Select_M);
	DDX_Control(pDX, IDC_COMBO_ParityCheck, m_ParityCheck_M);
	DDX_Control(pDX, IDC_COMBO_StopBit, m_StopBit_M);
	DDX_Control(pDX, IDC_COMBO_BaudRate_Select, m_BaudRate_M);
	DDX_Control(pDX, IDC_COMBO_CommSelect, m_ComboBox);
	DDX_Control(pDX, IDC_MSCOMM, m_ctrlComm);
	DDX_CBIndex(pDX, IDC_COMBO_BaudRate_Select, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_CommSelect, m_Index);
	DDX_CBIndex(pDX, IDC_COMBO_Date_Select, m_Date_Select);
	DDX_CBIndex(pDX, IDC_COMBO_ParityCheck, m_ParityCheck);
	DDX_CBIndex(pDX, IDC_COMBO_StopBit, m_StopBit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommunication, CDialog)
	//{{AFX_MSG_MAP(CCommunication)
	ON_CBN_SELCHANGE(IDC_COMBO_CommSelect, OnSelchangeCOMBOCommSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_BaudRate_Select, OnSelchangeCOMBOBaudRateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_Date_Select, OnSelchangeCOMBODateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_ParityCheck, OnSelchangeCOMBOParityCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_StopBit, OnSelchangeCOMBOStopBit)
	ON_BN_CLICKED(IDScomOn, OnScomOn)
	ON_BN_CLICKED(IDC_BUTCANCEL, OnButcancel)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommunication message handlers

BEGIN_EVENTSINK_MAP(CCommunication, CDialog)
    //{{AFX_EVENTSINK_MAP(CCommunication)
	ON_EVENT(CCommunication, IDC_MSCOMM, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CCommunication::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ComboBox.SetCurSel(0);
	m_BaudRate_M.SetCurSel(0);
	m_Date_Select_M.SetCurSel(0);
	m_StopBit_M.SetCurSel(0);
	m_ParityCheck_M.SetCurSel(0);
	if(m_ctrlComm.GetPortOpen())
	{
		m_ctrlComm.SetPortOpen(FALSE);  //关闭串口
	}
	m_ctrlComm.SetCommPort(1);//默认串口1
	if(!m_ctrlComm.GetPortOpen())
	{
		m_ctrlComm.SetPortOpen(TRUE); //打开串口
	}
	else
	{
		AfxMessageBox("打开串口失败！");
	}
	m_ctrlComm.SetSettings("9600,n,8,1"); //9600波特率 无校验位，8位数据位，1位停止位
	m_ctrlComm.SetInputMode(1); //二进制方式检取数据
	m_ctrlComm.SetRThreshold(1);//每当串口接收缓冲区中多于等于1个字符时，引发Oncomm()时间
	m_ctrlComm.SetInputLen(0);
	m_ctrlComm.GetInput();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCommunication::OnSelchangeCOMBOCommSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true); 
	 m_Index=((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();//当前选中的行
	 ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->SetCurSel(m_Index);//设置当前选中的行的内容为显示的内容
	if(m_ctrlComm.GetPortOpen())
	{
		m_ctrlComm.SetPortOpen(FALSE);
	}
	SetDlgItemText(IDScomOn,"打开串口");//将打开或关才按钮改为"打开串口"显示状态
	UpdateData(false);
}

void CCommunication::OnSelchangeCOMBOBaudRateSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_BaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BaudRate_Select))->GetCurSel();//当前选中的行
	////***********************************************************/ 
	///根据当前选中的值进行波特率设置
	///************************************************************/ 
	switch(m_BaudRate)
	{
		case 1 :  m_ctrlComm.SetSettings("14400,,,");   break;
		case 2 :  m_ctrlComm.SetSettings("19200,,,");   break;
		case 3 :  m_ctrlComm.SetSettings("38400,,,");   break;
		case 4 :  m_ctrlComm.SetSettings("56000,,,");   break;
		case 5 :  m_ctrlComm.SetSettings("57600,,,");   break;
		case 6 :  m_ctrlComm.SetSettings("115200,,,");   break;
		case 7 :  m_ctrlComm.SetSettings("128000,,,");   break;
		case 8 :  m_ctrlComm.SetSettings("256000,,,");   break;
		default :  m_ctrlComm.SetSettings("9600,,,");   break;
	}
	UpdateData(false);

}

void CCommunication::OnSelchangeCOMBODateSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_Date_Select=((CComboBox*)GetDlgItem(IDC_COMBO_Date_Select))->GetCurSel();//当前选中的行

	switch(m_Date_Select)
	{
		case 1 :  m_ctrlComm.SetSettings(",,7,");   break;
		case 2 :  m_ctrlComm.SetSettings(",,6,");   break;
		case 3 :  m_ctrlComm.SetSettings(",,5,");   break;
		case 4 :  m_ctrlComm.SetSettings(",,4,");   break;
		default : m_ctrlComm.SetSettings(",,8,");   break;
	}
	UpdateData(false);	
}

void CCommunication::OnSelchangeCOMBOStopBit() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	 m_StopBit=((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->GetCurSel();//当前选中的行

	switch(m_StopBit)
	{
		case 1 :  m_ctrlComm.SetSettings(",,,2");   break;
		default : m_ctrlComm.SetSettings(",,,1");   break;
	}
	UpdateData(false);
	
}


void CCommunication::OnSelchangeCOMBOParityCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_ParityCheck=((CComboBox*)GetDlgItem(IDC_COMBO_ParityCheck))->GetCurSel();//当前选中的行

	switch(m_ParityCheck)
	{
		case 1 :  m_ctrlComm.SetSettings(",O,,");   break;
		case 2 :  m_ctrlComm.SetSettings(",E,,");   break;
		default : m_ctrlComm.SetSettings(",N,,");   break;
	}
	UpdateData(false);	
}

void CCommunication::OnScomOn() 
{
	// TODO: Add your control notification handler code here
	if(m_Index < 0)
	{
		//AfxMessageBox("aaa");
		switch(m_ctrlComm.GetPortOpen())
		{
			case 1 : 
				m_ctrlComm.SetPortOpen(FALSE);//关闭串口
				SetDlgItemText(IDScomOn,"打开串口"); //更改按键指示
				UpdateData(FALSE);
				break;
			case 0 :
				m_ctrlComm.SetCommPort(1);//如果要打开串口则应先选择哪个串口
				m_ctrlComm.SetPortOpen(TRUE);// 打开串口
				SetDlgItemText(IDScomOn,"关闭串口");//更改按键指示
				UpdateData(FALSE);
				break; 
			default : AfxMessageBox("不能打开关闭串口");

		}
	}
	else
	{
		//AfxMessageBox("bbb");
		switch(m_ctrlComm.GetPortOpen())
		{
			case 0 : 
				m_ctrlComm.SetCommPort(m_Index+1);
				m_ctrlComm.SetPortOpen(TRUE);//打开串口
				SetDlgItemText(IDScomOn,"关闭串口"); //更改按键指示
				UpdateData(FALSE);
				break;
			case 1 :
				m_ctrlComm.SetPortOpen(FALSE);// 关闭串口

				SetDlgItemText(IDScomOn,"打开串口");//更改按键指示
				UpdateData(FALSE);
				break; 
			default :AfxMessageBox("不能打开串口");
		}		
	}
	if(m_Index<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->SetCurSel(0);
	if(m_BaudRate<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_BaudRate_Select))->SetCurSel(0);
	if(m_Date_Select<0) 
		((CComboBox*)GetDlgItem(IDC_COMBO_Date_Select))->SetCurSel(0);
	if(m_StopBit<0) 
		((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->SetCurSel(0);
	if(m_ParityCheck<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_ParityCheck))->SetCurSel(0);
}

void CCommunication::OnButcancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	
}
void CCommunication::OnDestroy() 
{
	if(m_pRecordset!=NULL)
	{
		m_pRecordset->Close();//关闭记录集对象
		m_pRecordset=NULL;
	}
	if(m_pConnection->State)
	{
		m_pConnection->Close();//关闭连接对象
		m_pConnection=NULL;
	}

	CDialog::OnDestroy();

}

//每当接收到一个数据后进入该函数，相当于串口中断服务程序
char CCommunication::OnOnCommMscomm() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

	char *str,*str1;
	CString str2;
	int i,k;
	int cengNum;
	CString strTest;

	VARIANT m_input;
	int nEvent = m_ctrlComm.GetCommEvent();

	if(2 == nEvent)  //缓冲区内有数据则进入
	{
		//加入处理数据
		k = m_ctrlComm.GetInBufferCount();   //接收缓冲区字符数
		if(k > 0)
		{
			m_input = m_ctrlComm.GetInput();
			str = (char*)(unsigned char*)m_input.parray->pvData;
		}
		i = 0;
		str1 = str;
		while(i < k)
		{
			i++;
			str1++;
		}
		*str1 = '\0';
		str2 = (const char*)str;
		cengNum = atoi(str2);

		pDoc->CengNumNow = cengNum;
		strTest.Format("%d",cengNum);
	//	AfxMessageBox(strTest);
		////////////////////////查看数据库总记录条数//////////////////

		m_pRecordset.CreateInstance(__uuidof(Recordset));
		try
		{
			m_pRecordset->Open("SELECT * FROM coordinate",                // 查询studentinfo表中所有字段
								theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
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
			AfxMessageBox("请求层数有误，请重新请求...");
			return (-1);
		}
		////////////////////////检索数据库部分代码//////////////////
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		CString strSql;

		strSql.Format("select * from coordinate where cengNum = %d ",cengNum);    //为什么在例程里面%d 加了单引号，
	                                                    //测试是不行的，所以在此就把引号给去掉了

	//	strSql = strSql + "select * from coordinate where cengNum = " + strTest;
	//	AfxMessageBox(strSql);  
		BSTR bsSql = strSql.AllocSysString();
		try
		{
			m_pRecordset->Open(bsSql,                                    // 查询coordinate表中所有字段
								theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
								adOpenDynamic,
								adLockOptimistic,
								adCmdText);
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}

		pDoc->PrintNumNow = "";

		/////////////////////////通讯格式设置部分代码///////////////
		_variant_t vFieldValue;
		CString m_str = "";
		CString x1o, y1o, z1o, x1i, y1i, z1i;
		CString x2o, y2o, z2o, x2i, y2i, z2i;
		CString x3o, y3o, z3o, x3i, y3i, z3i;
		CString x4o, y4o, z4o, x4i, y4i, z4i;
		CString x5o, y5o, z5o, x5i, y5i, z5i;
		CString x6o, y6o, z6o, x6i, y6i, z6i;
		CString x7o, y7o, z7o, x7i, y7i, z7i;
		CString x8o, y8o, z8o, x8i, y8i, z8i;

			//******************************************喷头1显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x1o");
		x1o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y1o");
		y1o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z1o");
		z1o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x1i");
		x1i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("y1i");
		y1i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z1i");
		z1i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		if((x1i == "0.000000")&&(y1i == "0.000000")&&(z1i == "0.000000"))
		{
	
		}
		else
		{
			m_str = m_str + "1" + "\n" + x1o + "\n" + y1o + "\n" + z1o + "\n" + x1i + "\n" + y1i + "\n" + z1i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "1、";			
		}

		//******************************************喷头2显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x2o");
		x2o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y2o");
		y2o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z2o");
		z2o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x2i");
		x2i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y2i");
		y2i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z2i");
		z2i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		if((x2i == "0.000000")&&(y2i == "0.000000")&&(z2i == "0.000000"))
		{
			
		}
		else
		{
			m_str = m_str + "2" + "\n" + x2o + "\n" + y2o + "\n" + z2o + "\n" + x2i + "\n" + y2i + "\n" + z2i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "2、";			
		}

		//******************************************喷头3显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x3o");
		x3o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("y3o");
		y3o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z3o");
		z3o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x3i");
		x3i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y3i");
		y3i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z3i");
		z3i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		if((x3i == "0.000000")&&(y3i == "0.000000")&&(z3i == "0.000000"))
		{

		}
		else		
		{
			m_str = m_str + "3" + "\n" + x3o + "\n" + y3o + "\n" + z3o + "\n" + x3i + "\n" + y3i + "\n" + z3i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "3、";		
		}

		//******************************************喷头4显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x4o");
		x4o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y4o");
		y4o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z4o");
		z4o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x4i");
		x4i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("y4i");
		y4i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z4i");
		z4i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		if((x4i == "0.000000")&&(y4i == "0.000000")&&(z4i == "0.000000"))
		{
		}
		else
		{
			m_str = m_str + "4" + "\n" + x4o + "\n" + y4o + "\n" + z4o + "\n" + x4i + "\n" + y4i + "\n" + z4i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "4、";	
		}

		//******************************************喷头5显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x5o");
		x5o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y5o");
		y5o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z5o");
		z5o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x5i");
		x5i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y5i");
		y5i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z5i");
		z5i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		if((x5i == "0.000000")&&(y5i == "0.000000")&&(z5i == "0.000000"))
		{
		}
		else
		{
			m_str = m_str + "5" + "\n" + x5o + "\n" + y5o + "\n" + z5o + "\n" + x5i + "\n" + y5i + "\n" + z5i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "5、";		
		}

		//******************************************喷头6显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x6o");
		x6o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y6o");
		y6o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z6o");
		z6o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x6i");
		x6i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y6i");
		y6i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z6i");
		z6i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		if((x6i == "0.000000")&&(y6i == "0.000000")&&(z6i == "0.000000"))
		{
		}
		else
		{
			m_str = m_str + "6" + "\n" + x6o + "\n" + y6o + "\n" + z6o + "\n" + x6i + "\n" + y6i + "\n" + z6i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "6、";			
		}

		//******************************************喷头7显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x7o");
		x7o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y7o");
		y7o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z7o");
		z7o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x7i");
		x7i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y7i");
		y7i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z7i");
		z7i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		if((x7i == "0.000000")&&(y7i == "0.000000")&&(z7i == "0.000000"))
		{
		}
		else
		{
			m_str = m_str + "7" + "\n" + x7o + "\n" + y7o + "\n" + z7o + "\n" + x7i + "\n" + y7i + "\n" + z7i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "7、";			
		}

		//******************************************喷头8显示部分**********************************8
		vFieldValue = m_pRecordset->GetCollect("x8o");
		x8o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y8o");
		y8o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z8o");
		z8o = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		/////////////////////////////////////////////////////////////////////////////////////////

		vFieldValue = m_pRecordset->GetCollect("x8i");
		x8i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		vFieldValue = m_pRecordset->GetCollect("y8i");
		y8i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();

		vFieldValue = m_pRecordset->GetCollect("z8i");
		z8i = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		
		if((x8i == "0.000000")&&(y8i == "0.000000")&&(z8i == "0.000000"))
		{
		}
		else
		{
			m_str = m_str + "8" + "\n" + x8o + "\n" + y8o + "\n" + z8o + "\n" + x8i + "\n" + y8i + "\n" + z8i+ "\n" ;
			pDoc->PrintNumNow = pDoc->PrintNumNow + "8、";				
		}

		////////////////////////数据发送部分代码////////////////////
			int ncount=m_str.GetLength();
			CByteArray m_Array;//二进制数组
			m_Array.SetSize(ncount);
			for(int j=0;j<ncount;j++)//为数组赋值
			{
				m_Array.SetAt(j,m_str[j]);
			}
			m_ctrlComm.SetOutput(COleVariant(m_Array));//发送数据
	}
	return (1);

}



