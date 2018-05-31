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

extern CMy3DPMaxApp theApp;       // 在此引用应用类中的theApp来获取库连接指针
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

//关闭对话框
void CModBusRTU::OnBClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::EndDialog(0);
	MODBUS_S_UnInit();  //关闭MODBUS
	KillTimer(1);
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

}


//关闭对话框时，关闭串口
void CModBusRTU::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	MODBUS_S_UnInit();  //关闭MODBUS
	KillTimer(1);
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

}

//销毁对话框，同时销毁计时器
void CModBusRTU::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(1);  
	MODBUS_S_UnInit();  //关闭MODBUS
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
	// TODO: Add your message handler code here
}
//ASCII to Hex对二进制的转换
//函数接口：输入asc码型的字符串，转换为十六进制的字符串
//2x%：表示输出两位十六进制，若只有一位则高位补零，若不止两位，则截取高两位
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
//将通讯信息交给richedit显示
//LPCTSTR 一种不可被其他函数改变的字符串，采用Unicode编码方式，类型为：wchar_t，十六位
void CModBusRTU::ShowCommFrame(LPCTSTR Msg)
{	
	//Append str To Rich;
	int nlength=m_r_text.GetTextLength();
	m_r_text.SetSel(nlength,  nlength);  
	m_r_text.ReplaceSel(Msg);
}

//读寄存器内容
void CModBusRTU::OnBRead() 
{
	// TODO: Add your control notification handler code here
		//发送读指令并接受返回
	short int ilist[200];  //整型数组
	bool	  blist[200];  //布尔数组
	CString rtu,regadd,regcount,strtmp;
	
	memset(ilist,0x00,200);   //初始化为0
	memset(blist,0x00,200);   //初始化为FALSE

	m_rtu.GetWindowText(rtu);  //获取从机地址    字符串类型
	m_regadd.GetWindowText(regadd);//获取寄存器地址
	m_regcount.GetWindowText(regcount);//获取读取寄存器的个数
	//判断控件内是否填有参数
	if(rtu.IsEmpty())
	{
		MessageBox("PLC地址不能为空","MODBUS测试",MB_OK);
		return;
	}
	else if(regadd.IsEmpty())
	{
		MessageBox("变量地址不能为空","MODBUS测试",MB_OK);
		return;
	}
	else if(regcount.IsEmpty())
	{
		MessageBox("变量数量不能为空","MODBUS测试",MB_OK);
		return;
	}

	//判断PLC地址是否为数字
	unsigned short int i_regadd, i_regcount;
	unsigned char i_rtu;

	for(int i=0; i<rtu.GetLength(); i++)
	{
		if(isdigit(rtu[i])==0)
		{
			MessageBox("PLC地址不能为字符","MODBUS测试",MB_OK);
			return;
		}
	}
	i_rtu= atoi(rtu);  //转换为数字，整型


	for(i=0; i<regadd.GetLength(); i++)
	{
		if(isdigit(regadd[i])==0)
		{
			MessageBox("变量地址不能为字符","MODBUS测试",MB_OK);
			return;
		}
	}
	i_regadd= atoi(regadd);
	if(i_regadd > 50000 || i_regadd <= 0)
	{
			MessageBox("变量地址范围不正确","MODBUS测试",MB_OK);
			return;
	}

	for(i=0; i<regcount.GetLength(); i++)
	{
		if(isdigit(regcount[i])==0)
		{
			MessageBox("变量数量不能为字符","MODBUS测试",MB_OK);
			return;
		}
	}
	i_regcount= atoi(regcount);

	if(i_regcount > 200)
	{
			MessageBox("变量数量不能大于200","MODBUS测试",MB_OK);
			return;
	}

	//生成并发送命令
	char state= 0;
	ShowCommFrame("发送读寄存器命令\r\n");	
		

	if(i_regadd >= 40001 && i_regadd <= 49999)
	{		
		state= MODBUS_S_ReadMultiRegD(i_rtu,i_regadd,i_regcount,ilist);   //读保持寄存器函数  返回short int 整型数值
	}																	  //short int在32位编译器里是占16位的 int占32位，而在16位编译器里没有区别
	else if(i_regadd >= 10001 && i_regadd <= 19999)
	{		
		state= MODBUS_S_ReadMultiRegM_1x(i_rtu,i_regadd,i_regcount,blist);
	}	
	else if(i_regadd >= 1 && i_regadd <= 9999)
	{
		state= MODBUS_S_ReadMultiRegM(i_rtu,i_regadd,i_regcount,blist);
	}
	//返回state -1 -2 以及 1 来判别是否发送命令成功
	if(state==-1)   
	{	
		ShowCommFrame("读取数据CRC检验失败\r\n");
	}
	else if(state==-2)
	{
		ShowCommFrame("读取数据失败,无应答\r\n");
	}
	else if(state == -3)
	{
		ShowCommFrame("串口连接失败.\r\n");		
	}
	else 
	{
		ShowCommFrame("读取数据成功.\r\n");
	}

	//寄存器地址：为十进制，与从机一致
	CString str;
	if(i_regadd >= 40001 && i_regadd <= 49999)
	{
		for(i=0; i<i_regcount; i++)
		{			
			strtmp.Format("寄存器地址%d--0x%04x\r\n", i_regadd+i,(unsigned short int)ilist[i]);	  //十六进制输出						
			str+= strtmp;

		}
	}

	else
	{
		for(i=0; i<i_regcount; i++)
		{			
			strtmp.Format("寄存器地址%d--0x%2x\r\n", i_regadd+i,blist[i]);	  						
			str+= strtmp;
		}
	}		
	//Append str To Rich;
	ShowCommFrame(str);	
}

//写寄存器内容
void CModBusRTU::OnBWrite() 
{
	// TODO: Add your control notification handler code here
		//发送写指令并接受返回
	CString rtu,regadd,regcount,regvalue;
	
	m_rtu.GetWindowText(rtu);
	m_regadd.GetWindowText(regadd);
	m_regcount.GetWindowText(regcount);
	m_value.GetWindowText(regvalue);

	if(rtu.IsEmpty())
	{
		MessageBox("PLC地址不能为空","MODBUS测试",MB_OK);
		return;
	}
	else if(regadd.IsEmpty())
	{
		MessageBox("变量地址不能为空","MODBUS测试",MB_OK);
		return;
	}
	else if(regvalue.IsEmpty())
	{
		MessageBox("变量值不能为空","MODBUS测试",MB_OK);
		return;
	}

	//判断是否为数字	
	unsigned short int i_regadd;
	unsigned char i_rtu;
	short int  i_regvalue;

	for(int i=0; i<rtu.GetLength(); i++)
	{
		if(isdigit(rtu[i])==0)
		{
			MessageBox("PLC地址不能为字符","MODBUS测试",MB_OK);
			return;
		}
	}
	i_rtu= atoi(rtu);

	//寄存器值写入问题
//	for(i=0; i<regvalue.GetLength(); i++)
//	{
//		if(isdigit(regvalue[i])==0)
//		{
//			MessageBox("变量值不能为字符","MODBUS测试",MB_OK);
//			return;
//		}
//	}
//	i_regvalue= atoi(regvalue);
	
	if((regvalue.GetLength() > 4)||(regvalue.GetLength() < 1))
	{
		MessageBox("数据长度不对，应为1-4之间的长度","MODBUS测试",MB_OK);
		return ;
	}
	//十六进制串改为十六进制
	sscanf(regvalue,"%x",&i_regvalue);

	for(i=0; i<regadd.GetLength(); i++)
	{
		if(isdigit(regadd[i])==0)
		{
			MessageBox("变量地址不能为字符","MODBUS测试",MB_OK);
			return;
		}
	}
	i_regadd= atoi(regadd);
	if(i_regadd > 50000 || i_regadd <= 0)
	{
			MessageBox("变量地址范围不正确","MODBUS测试",MB_OK);
			return;
	}

	//生成并发送命令

	char state= 0;
	ShowCommFrame("发送数据\r\n");		
	//写保持寄存器
	if(i_regadd >= 40001 && i_regadd <= 49999)
	{		
		state= MODBUS_S_WriteSingRegD(i_rtu,i_regadd,i_regvalue);  //写保持寄存器，写的寄存器值为16进制i_regvalue
	}
	//写线圈
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
		ShowCommFrame("发送数据成功.\r\n");
	}
	else
	{
		ShowCommFrame("发送数据失败\r\n");
	}
	
}


//////////////////////////坐标数据传输函数/////////////////////////////
void CModBusRTU::OnTimer(UINT nIDEvent)      
{
	// TODO: Add your message handler code here and/or call default
	short int ilist[200];  //整型数组
	ilist[0] = 0;
	char state_r= 0,state_w = 0;       //返回通讯状态

	state_r= MODBUS_S_ReadMultiRegD(01,45002,1,ilist);  //读保持寄存器的值，并返回状态

	//返回state -1 -2 以及 1 来判别是否发送命令成功
	if(state_r==-1)   
	{	
		ShowCommFrame("读取数据CRC检验失败\r\n");   //连接没有断开，但是可能受到干扰，数据校验失败
													//待加应急处理程序，添加日志文件
		Beep( 650, 500);
		//exit(0);

	}
	else if(state_r==-2)
	{

		ShowCommFrame("读取数据失败,无应答\r\n");   //从机端被外界物理断开连接，
													//
		Beep( 650, 500);
		//exit(0);
	}

	else if(state_r == -3)
	{
		ShowCommFrame("串口打开失败.\r\n");	        //主机端串口被人强制断开
		Beep( 650, 500);

	}
	else
	{
		if(printFlag == TRUE)
		{
			ShowCommFrame("设备已连接,正在打印...\r\n");    //一切正常
			printFlag = FALSE;
		}
		//m_r_text.SetWindowText("设备已连接...\r\n");
	}
	
	if(cengNum != ilist[0])
	{
		cengNum = ilist[0];
		updateFlag = TRUE;   //在数据发送函数里，发送数据完毕并且保证准确无误后，将此标志位归位FALSE
		m_cengNum = cengNum;
		UpdateData(FALSE);
	}
	//如果层数改变则发送坐标信息
	if(updateFlag)
	{
		GetstrOutOfDB();

		int num = coordinate.GetSize();
		for(int i = 0; i < num; i++)
		{
			state_w = MODBUS_S_WriteSingFloat(1, (45010 + i*2), coordinate[i]->floatNum);
			//返回state -1 -2 以及 1 来判别是否发送命令成功
			if(state_w > 0)
			{
				//ShowCommFrame("发送数据成功.\r\n");
			}
			else
			{
				ShowCommFrame("发送数据失败,\r\n");   //有个日志文件
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



//备注：本来是要监听变量，然后通过触发事件的，可惜尝试多次未果，//还是要寻求办法的
//获取要发送信息的字符串
char CModBusRTU::GetstrOutOfDB()
{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
		CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
		CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

		pDoc->CengNumNow = cengNum;
		pDoc->PrintNumNow = "";
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
			//AfxMessageBox("请求层数有误，请重新请求...");
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

		float floatNum[56];
		//存储1打印头信息
        floatNum[0] = 1.0f;                       
		floatNum[1] = (float)m_pRecordset->GetCollect("x1o");      
		floatNum[2] = (float)m_pRecordset->GetCollect("y1o"); 
		floatNum[3] = (float)m_pRecordset->GetCollect("z1o"); 

		floatNum[4] = (float)m_pRecordset->GetCollect("x1i");      
		floatNum[5] = (float)m_pRecordset->GetCollect("y1i"); 
		floatNum[6] = (float)m_pRecordset->GetCollect("z1i"); 
		if(floatNum[3] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "1、";				
		}

		//存储2打印头信息
        floatNum[7] = 2.0f;                       
		floatNum[8] = (float)m_pRecordset->GetCollect("x2o");      
		floatNum[9] = (float)m_pRecordset->GetCollect("y2o"); 
		floatNum[10] = (float)m_pRecordset->GetCollect("z2o"); 

		floatNum[11] = (float)m_pRecordset->GetCollect("x2i");      
		floatNum[12] = (float)m_pRecordset->GetCollect("y2i"); 
		floatNum[13] = (float)m_pRecordset->GetCollect("z2i");
		if(floatNum[10] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "2、";				
		}

		//存储3打印头信息
        floatNum[14] = 3.0f;                       
		floatNum[15] = (float)m_pRecordset->GetCollect("x3o");      
		floatNum[16] = (float)m_pRecordset->GetCollect("y3o"); 
		floatNum[17] = (float)m_pRecordset->GetCollect("z3o"); 

		floatNum[18] = (float)m_pRecordset->GetCollect("x3i");      
		floatNum[19] = (float)m_pRecordset->GetCollect("y3i"); 
		floatNum[20] = (float)m_pRecordset->GetCollect("z3i"); 
		if(floatNum[17] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "3、";				
		}

		//存储4打印头信息
        floatNum[21] = 4.0f;                       
		floatNum[22] = (float)m_pRecordset->GetCollect("x4o");      
		floatNum[23] = (float)m_pRecordset->GetCollect("y4o"); 
		floatNum[24] = (float)m_pRecordset->GetCollect("z4o"); 

		floatNum[25] = (float)m_pRecordset->GetCollect("x4i");      
		floatNum[26] = (float)m_pRecordset->GetCollect("y4i"); 
		floatNum[27] = (float)m_pRecordset->GetCollect("z4i");
		if(floatNum[24] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "4、";				
		}

		//存储5打印头信息
        floatNum[28] = 5.0f;                       
		floatNum[29] = (float)m_pRecordset->GetCollect("x5o");      
		floatNum[30] = (float)m_pRecordset->GetCollect("y5o"); 
		floatNum[31] = (float)m_pRecordset->GetCollect("z5o"); 

		floatNum[32] = (float)m_pRecordset->GetCollect("x5i");      
		floatNum[33] = (float)m_pRecordset->GetCollect("y5i"); 
		floatNum[34] = (float)m_pRecordset->GetCollect("z5i");
		if(floatNum[31] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "5、";				
		}

		//存储6打印头信息
        floatNum[35] = 6.0f;                       
		floatNum[36] = (float)m_pRecordset->GetCollect("x6o");      
		floatNum[37] = (float)m_pRecordset->GetCollect("y6o"); 
		floatNum[38] = (float)m_pRecordset->GetCollect("z6o"); 

		floatNum[39] = (float)m_pRecordset->GetCollect("x6i");      
		floatNum[40] = (float)m_pRecordset->GetCollect("y6i"); 
		floatNum[41] = (float)m_pRecordset->GetCollect("z6i"); 
		if(floatNum[38] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "6、";				
		}

		//存储7打印头信息
        floatNum[42] = 7.0f;                       
		floatNum[43] = (float)m_pRecordset->GetCollect("x7o");      
		floatNum[44] = (float)m_pRecordset->GetCollect("y7o"); 
		floatNum[45] = (float)m_pRecordset->GetCollect("z7o"); 

		floatNum[46] = (float)m_pRecordset->GetCollect("x7i");      
		floatNum[47] = (float)m_pRecordset->GetCollect("y7i"); 
		floatNum[48] = (float)m_pRecordset->GetCollect("z7i");
		if(floatNum[45] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "7、";				
		}		

		//存储8打印头信息
        floatNum[49] = 8.0f;                       
		floatNum[50] = (float)m_pRecordset->GetCollect("x8o");      
		floatNum[51] = (float)m_pRecordset->GetCollect("y8o"); 
		floatNum[52] = (float)m_pRecordset->GetCollect("z8o"); 

		floatNum[53] = (float)m_pRecordset->GetCollect("x8i");      
		floatNum[54] = (float)m_pRecordset->GetCollect("y8i"); 
		floatNum[55] = (float)m_pRecordset->GetCollect("z8i"); 
		if(floatNum[52] != 0.0f)
		{
			pDoc->PrintNumNow = pDoc->PrintNumNow + "8、";				
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
	ShowCommFrame("已开始打印...\r\n");
	GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(TRUE);
	printFlag = TRUE;
}

void CModBusRTU::OnButClosertu() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	ShowCommFrame("已关闭打印...\r\n");
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
		ShowCommFrame("串口成功打开...\r\n");
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(TRUE);
	}
	else
	{
		ShowCommFrame("串口打开失败请重新打开...\r\n");
	}
	
}

void CModBusRTU::OnButCloseMscom() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //关闭串口
	if(IsOpen())
	{
		ShowCommFrame("串口关闭失败，请重新关闭...\r\n");
	}
	else
	{
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);
		ShowCommFrame("串口已成功关闭...\r\n");
	}
}

void CModBusRTU::OnSelchangeCOMBOCommSelectRTU() 
{
	// TODO: Add your control notification handler code here	
	ClosePort();  //关闭串口	
	if(IsOpen())
	{
		ShowCommFrame("串口参数更换失败，请重启软件...\r\n");
	}
	else
	{
		ShowCommFrame("串口号已更改，串口被迫关闭...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}
}

void CModBusRTU::OnSelchangeCOMBOBaudRateSelectRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //关闭串口	
	if(IsOpen())
	{
		ShowCommFrame("串口参数更换失败，请重启软件...\r\n");
	}
	else
	{
		ShowCommFrame("波特率已更改，串口被迫关闭...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnSelchangeCOMBODataSelectRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //关闭串口
	if(IsOpen())
	{
		ShowCommFrame("串口参数更换失败，请重启软件...\r\n");
	}
	else
	{

		ShowCommFrame("数据位已更改，串口被迫关闭...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnSelchangeCOMBOParityCheckRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //关闭串口
	if(IsOpen())
	{
		ShowCommFrame("串口参数更换失败，请重启软件...\r\n");
	}
	else
	{
		ShowCommFrame("校验位已更改，串口被迫关闭...\r\n");
		GetDlgItem(IDC_BUT_CLOSE_MSCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPEN_MSCOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_CLOSERTU)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_OPENRTU)->EnableWindow(FALSE);	

	}	
}

void CModBusRTU::OnSelchangeCOMBOStopBitRTU() 
{
	// TODO: Add your control notification handler code here
	ClosePort();  //关闭串口
	if(IsOpen())
	{
		ShowCommFrame("串口参数更换失败，请重启软件...\r\n");
	}
	else
	{
		ShowCommFrame("停止位已更改，串口被迫关闭...\r\n");
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



