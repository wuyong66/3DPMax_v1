// ModBusTcp.cpp : implementation file
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#include "3dpmax.h"
#include "ModBusTcp.h"
#include "3DPMaxDoc.h"
#include "3DPMaxView.h"
#include "MainFrm.h"
#include "ModBusRTU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CMy3DPMaxApp theApp;       // 在此引用应用类中的theApp来获取库连接指针
/////////////////////////////////////////////////////////////////////////////
unsigned char tcp_buff[256];
/////////////////////////////////////////////////////////////////////////////
// CModBusTcp dialog


CModBusTcp::CModBusTcp(CWnd* pParent /*=NULL*/)
	: CDialog(CModBusTcp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModBusTcp)
	m_port = _T("3000");
	m_cengNum = -1;
	m_dataAddr = 5002;
	m_percent = 0.00;
	m_serverAddr = _T("192.168.1.88");
	m_wirteFloat = 0.0f;
	//}}AFX_DATA_INIT
	flag = 0;
	cengNum = -1;
	updateFlag = FALSE;
}


void CModBusTcp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModBusTcp)
	DDX_Control(pDX, IDC_RICHEDIT_R, m_r_text);
	DDX_Control(pDX, IDC_EDIT_DATA_WRITE, m_dataWrite);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_CENG_NUM, m_cengNum);
	DDX_Text(pDX, IDC_EDIT_DATA_ADDR, m_dataAddr);
	DDX_Text(pDX, IDC_EDIT_PRIT_PERCENT, m_percent);
	DDX_Text(pDX, IDC_EDIT_SERVER_ADDR, m_serverAddr);
	DDX_Text(pDX, IDC_EDIT_DATA_FLOAT, m_wirteFloat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModBusTcp, CDialog)
	//{{AFX_MSG_MAP(CModBusTcp)
	ON_BN_CLICKED(IDC_BUTTON_CREAT_LINK, OnButtonCreatLink)
	ON_BN_CLICKED(IDC_BUTTON_BREAK_LINK, OnButtonBreakLink)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_TEXT, OnButtonCleanText)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_START_DOWNLOAD, OnButtonStartDownload)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP_DOWNLOAD, OnButtonStopDownload)
	ON_EN_CHANGE(IDC_EDIT_SERVER_ADDR, OnChangeEditServerAddr)
	ON_EN_CHANGE(IDC_EDIT_PORT, OnChangeEditPort)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_WRITE_FLOAT, OnButtonWriteFloat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CModBusTcp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here IDC_BUTTON_CREAT_LINK
	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModBusTcp::OnChangeEditServerAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	pMysocket->Close();
	if(pMysocket != NULL)
	{
		delete pMysocket;
		pMysocket = NULL;
	}
	if(pMysocket == NULL)
	{
		ShowCommFrame("网络被强制断开...\n");
	}

	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(FALSE);
	
	// TODO: Add your control notification handler code here
	
}

void CModBusTcp::OnChangeEditPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	pMysocket->Close();
	if(pMysocket != NULL)
	{
		delete pMysocket;
		pMysocket = NULL;
	}
	if(pMysocket == NULL)
	{
		ShowCommFrame("网络被强制断开...\n");
	}

	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(FALSE);	
	// TODO: Add your control notification handler code here
	
}

//将通讯信息交给richedit显示
//LPCTSTR 一种不可被其他函数改变的字符串，采用Unicode编码方式，类型为：wchar_t，十六位
void CModBusTcp::ShowCommFrame(LPCTSTR Msg)
{	
	//Append str To Rich;
	int nlength = m_r_text.GetTextLength();
	m_r_text.SetSel(nlength,  nlength);  
	m_r_text.ReplaceSel(Msg);
}

/////////////////////////////////////////////////////////////////////////////
// CModBusTcp message handlers

void CModBusTcp::OnButtonCreatLink() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString serverName = m_serverAddr;  //获取服务器地址
	int port = atoi(m_port); //获取端口

	if(pMysocket != NULL)
	{
		//delete pMysocket;
		pMysocket = NULL;
	}
	pMysocket = new CMysocket(this); //创建套接字对象
	if (!pMysocket->Create()) //创建套接字
	{
		delete pMysocket;
		pMysocket = NULL;
		ShowCommFrame("套接字创建失败...\n");
		return;
	}
	if (!pMysocket->Connect(serverName,port)) //连接服务器
	{
		ShowCommFrame("连接服务器失败...\n");
		return;
	}
	flag = 1;
	//成功连接则在RichEdit显示出来
	CString str;
	str.Format("ModBus TCP/IP 设备：%s 端口号：%s 已连接！\n", m_serverAddr, m_port);
	ShowCommFrame(str);

	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(FALSE);
	
}

//断开网络连接
void CModBusTcp::OnButtonBreakLink() 
{
	// TODO: Add your control notification handler code here
	pMysocket->Close();
	if(pMysocket != NULL)
	{
		delete pMysocket;
		pMysocket = NULL;
	}
	if(pMysocket == NULL)
	{
		ShowCommFrame("网络已处于断开状态...\n");
	}

	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(FALSE);	
}
//开始打印
void CModBusTcp::OnButtonStartDownload() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,500,NULL);
	ShowCommFrame("已开始打印...\r\n");
	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(TRUE);	
	
}
//关闭打印
void CModBusTcp::OnButtonStopDownload() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	ShowCommFrame("已关闭打印...\r\n");
	GetDlgItem(IDC_BUTTON_CREAT_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BREAK_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START_DOWNLOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_DOWNLOAD)->EnableWindow(FALSE);
	
}
void CModBusTcp::OnButtonCleanText() 
{
	// TODO: Add your control notification handler code here
	m_r_text.SetWindowText("");
	
}

void CModBusTcp::OnDestroy() 
{
	CDialog::OnDestroy();
	if(pMysocket != NULL)
	{
		delete pMysocket;
		pMysocket = NULL;
	}
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
	KillTimer(1);
	
	// TODO: Add your message handler code here
	
}

//没有用的一个函数
char CModBusTcp::ReceieveData()
{
	unsigned char receieveBuff[200];
	int receieve_data_num = pMysocket->Receive(receieveBuff,200);
	int i = 0, j = 0;

	CString str, str1, temp;
	while(i < receieve_data_num)
	{
		temp.Format("%02X", receieveBuff[i]);
		if(receieveBuff[i] == 0xff)
			j = i;
		str = str + temp + " ";
		i++;
	}
	
	j = j + 3;

	int temp_num = (int)(receieveBuff[j] << 8);
	temp_num = temp_num + (int)receieveBuff[j + 1];
	temp.Format("%d", temp_num);
	str = str + temp + "\n";
	ShowCommFrame(str);

	return 0;
}

// 读寄存器的值，地址regAdd ,
char CModBusTcp::ModBus_readSingleRegData(long regAdd, long *list)
{
	
	memset(tcp_buff, 0x00, 255);   //buff 无符号字符型unsigned char变量 理解为8位寄存器
	long tmp = 0;    //
	if(pMysocket == NULL || flag == 0)
	{
		return -1;
	}

	//处理数据
	unsigned char regAdd_low, regAdd_high;
	regAdd = regAdd & 0xffff;
	regAdd_low = (unsigned char)(regAdd & 0x00ff);
	regAdd_high = (unsigned char)((regAdd >> 8) & 0x00ff);
	
	//////////////////////生成ModBusTcp报文格式
	//MBAP报文头
	tcp_buff[0] = 0;  //事物元标识符，高字节在前，低字节在后
	tcp_buff[1] = 0;

	tcp_buff[2] = 0;  //协议标识符，高字节在前，低字节在后
	tcp_buff[3] = 0;  //00 表示modBus

	tcp_buff[4] = 0x00; //后续字节长度
	tcp_buff[5] = 0x06; //后续有6个字节

	tcp_buff[6] = 0xff;

	tcp_buff[7] = 0x03; //功能码，表读单个寄存器

	tcp_buff[8] = regAdd_high;   //待写入寄存器地址
	tcp_buff[9] = regAdd_low;

	tcp_buff[10] = 0x00;   //数据长度，共一个字节
	tcp_buff[11] = 0x01;
	int num = pMysocket->Send(tcp_buff, 12);
	if(num == 12)
	{
		memset(tcp_buff, 0x00, 255);
		Sleep(50);
		num = pMysocket->Receive(tcp_buff,256);
		if(num == 0)
		{
			return -3; //服务器无响应
		}
		else
		{
			if((num == 11) && (tcp_buff[5] == 0x05) && (tcp_buff[6] == 0xff) && (tcp_buff[7] == 0x03))
			{
				tmp= tcp_buff[9];
				tmp= tmp << 8;
				tmp= tmp | tcp_buff[10];
				
				*list= tmp;    //解析数据

			}
			else 
			{
				return -4;//返回格式错误
			}
		}
	}
	else
	{
		return -2;   //发送出现错误
	}

	return 0;
	
}

////写寄存器值
char CModBusTcp::ModBus_WriteSingleRegData(long regAdd, long sendData)  
{
	memset(tcp_buff, 0x00, 255);   //buff 无符号字符型unsigned char变量 理解为8位寄存器

	if(pMysocket == NULL || flag == 0)
	{
		return -1;    //请先建立连接
	}

	//处理数据
	unsigned char regAdd_low, regAdd_high;
	unsigned char sendData_low,sendData_high;

	regAdd = regAdd & 0xffff;
	regAdd_low = (unsigned char)(regAdd & 0x00ff);
	regAdd_high = (unsigned char)((regAdd >> 8) & 0x00ff);

	sendData = sendData & 0xffff;
	sendData_low = (unsigned char)(sendData & 0x00ff);
	sendData_high = (unsigned char)((sendData >> 8) & 0x00ff);	
	//////////////////////生成ModBusTcp报文格式
	//MBAP报文头
	tcp_buff[0] = 0;  //事物元标识符，高字节在前，低字节在后
	tcp_buff[1] = 0;

	tcp_buff[2] = 0;  //协议标识符，高字节在前，低字节在后
	tcp_buff[3] = 0;  //00 表示modBus

	tcp_buff[4] = 0x00; //后续字节长度
	tcp_buff[5] = 0x06; //后续有6个字节

	tcp_buff[6] = 0xff;

	tcp_buff[7] = 0x06; //功能码，表写单个寄存器

	tcp_buff[8] = regAdd_high;   //待写入寄存器地址
	tcp_buff[9] = regAdd_low;

	tcp_buff[10] = sendData_high;   //待写入数据值
	tcp_buff[11] = sendData_low;

	int num = pMysocket->Send(tcp_buff, 12);

	if(num == 12)
	{
		Sleep(50);
		memset(tcp_buff, 0x00, 255);
		num = pMysocket->Receive(tcp_buff,256);
		if(num == 0)
		{
			return -3;  //服务器无响应
		}
		else
		{
			if((tcp_buff[6] == 0xff) && (tcp_buff[7] == 0x06))  //待加入其他的判断条件
			{
				return 0;  //正确发送
			}
			else 
			{
				return -4; //服务器响应错误
			}
		}

	}
	else
	{
		return -2;   //发送命令失败
	}
	

	return 0;
}

//数据转换float to byte
char CModBusTcp::FloatToByte(float floatNum,unsigned char *byteArry)
{
	char* pchar = (char*)&floatNum;
	for(int i = 0; i < sizeof(float); i++)
	{
		*byteArry = *pchar;
		pchar++;
		byteArry++;
	}
	return 1;
}
/////写一个浮点数
//写一个单精度浮点数 地址只能为偶数，与visual modbus slave一致
char CModBusTcp::ModBus_WriteSingFloat(long regAdd, float floatNum)
{
	if(pMysocket == NULL || flag == 0)
	{
		return -1;    //请先建立连接
	}

	unsigned char float2Hex[4];  //存放转换后的hex
	FloatToByte(floatNum,float2Hex);

	memset(tcp_buff, 0x00, 255);   //buff 无符号字符型unsigned char变量 理解为8位寄存器
	//////////////////////生成ModBusTcp报文格式
	//MBAP报文头
	tcp_buff[0] = 0;  //事物元标识符，高字节在前，低字节在后
	tcp_buff[1] = 0;

	tcp_buff[2] = 0;  //协议标识符，高字节在前，低字节在后
	tcp_buff[3] = 0;  //00 表示modBus

	tcp_buff[4] = 0x00; //后续字节长度
	tcp_buff[5] = 0x06; //后续有6个字节

	tcp_buff[6] = 0xff;

	tcp_buff[7] = 0x06; //功能码，表写单个寄存器

	tcp_buff[8] = (unsigned char)((regAdd >> 8) & 0x00ff);
	tcp_buff[9] = (unsigned char)(regAdd & 0x00ff);

	tcp_buff[10] = float2Hex[1];   //待写入数据值
	tcp_buff[11] = float2Hex[0];

	int num = pMysocket->Send(tcp_buff, 12);

	if(num == 12)
	{
		//Sleep(10);//tcp延时不需要，太快了
		memset(tcp_buff, 0x00, 255);
		num = pMysocket->Receive(tcp_buff,256);
		if(num == 0)
		{
			return -3;  //服务器无响应
		}
		else
		{
			if((tcp_buff[6] == 0xff) && (tcp_buff[7] == 0x06))  //带加入其他的判断条件
			{
				//return 0;  //正确发送,我的妈，，，，，，，，，这种错误
			}
			else 
			{
				return -4; //服务器响应错误
			}
		}

	}
	else
	{
		return -2;   //发送命令失败
	}
	memset(tcp_buff, 0x00, 255);   //buff 无符号字符型unsigned char变量 理解为8位寄存器


	//////////////////////生成ModBusTcp报文格式
	//MBAP报文头
	tcp_buff[0] = 0;  //事物元标识符，高字节在前，低字节在后
	tcp_buff[1] = 0;

	tcp_buff[2] = 0;  //协议标识符，高字节在前，低字节在后
	tcp_buff[3] = 0;  //00 表示modBus

	tcp_buff[4] = 0x00; //后续字节长度
	tcp_buff[5] = 0x06; //后续有6个字节

	tcp_buff[6] = 0xff;

	tcp_buff[7] = 0x06; //功能码，表写单个寄存器

	tcp_buff[8] = (unsigned char)(((regAdd + 1) >> 8) & 0x00ff);
	tcp_buff[9] = (unsigned char)((regAdd + 1) & 0x00ff);

	tcp_buff[10] = float2Hex[3];   //待写入数据值
	tcp_buff[11] = float2Hex[2];

	num = pMysocket->Send(tcp_buff, 12);

	if(num == 12)
	{
		//Sleep(10);
		memset(tcp_buff, 0x00, 255);
		num = pMysocket->Receive(tcp_buff,256);
		if(num == 0)
		{
			return -33;  //服务器无响应
		}
		else
		{
			if((tcp_buff[6] == 0xff) && (tcp_buff[7] == 0x06))  //带加入其他的判断条件
			{
				return 0;  //正确发送
			}
			else 
			{
				return -44; //服务器响应错误
			}
		}
	}
	else
	{
		return -22; //发送命令失败
	}
	return 0;		
}

//测试读命令
void CModBusTcp::OnButtonRead() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	long regAdd = m_dataAddr;
	long reg_value[10] ;
	memset(reg_value, 0x00, 10);
	char read_flag;
	read_flag = ModBus_readSingleRegData(regAdd, reg_value);

	if(read_flag == -1)
	{
		ShowCommFrame("请先建立连接...\n");		
	}
	else if(read_flag == -2)
	{
		ShowCommFrame("发送出现错误...\n");
	}
	else if(read_flag == -3)
	{
		ShowCommFrame("服务器无响应...\n");
	}
	else if(read_flag == -4)
	{
		ShowCommFrame("服务器响应数据有误...\n");
	}
	else
	{
		CString regadd_str, regvalue_str, play_str;
		regadd_str.Format("%d", regAdd);
		regvalue_str.Format("%04X", *reg_value);
		play_str = play_str + "读寄存器地址：" + regadd_str + "，值为0x" + regvalue_str + "\n";
		ShowCommFrame(play_str);
	}

	//AfxMessageBox(str);
	
}
//测试写命令
void CModBusTcp::OnButtonWrite() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	long regAdd = m_dataAddr;
	//long sendData = m_data_value;  改为写入十六进制
	CString regValue;
	long i_regValue;
	char write_flag;

	m_dataWrite.GetWindowText(regValue);
	sscanf(regValue,"%x",&i_regValue);
	
	write_flag = ModBus_WriteSingleRegData(regAdd, i_regValue);
	if(write_flag == -1)
	{
		ShowCommFrame("请先建立连接...\n");		
	}
	else if(write_flag == -2)
	{
		ShowCommFrame("发送出现错误...\n");
	}
	else if(write_flag == -3)
	{
		ShowCommFrame("服务器无响应...\n");
	}
	else if(write_flag == -4)
	{
		ShowCommFrame("服务器响应数据有误...\n");
	}
	else
	{
		CString regadd_str, regvalue_str, play_str;
		regadd_str.Format("%d", regAdd);
		regvalue_str.Format("%04X", i_regValue);
		play_str = play_str + "写寄存器地址：" + regadd_str + "，值为0x" + regvalue_str + "\n";
		ShowCommFrame(play_str);		
	}

}

void CModBusTcp::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	long ilist[10] ;

	memset(ilist, 0x00, 10);

	char state_r= 0,state_w = 0;       //返回通讯状态
	
	state_r = ModBus_readSingleRegData(5002, ilist);
	//返回state -1 -2 以及 1 来判别是否发送命令成功
	if(state_r==-1)   
	{	
		ShowCommFrame("未连接服务器...\r\n");   
													
		Beep( 650, 500);
		//exit(0);

	}
	else if(state_r==-2)
	{

		ShowCommFrame("读命令发送错误...\r\n");   
												
		Beep( 650, 500);
		//exit(0);
	}

	else if(state_r == -3)
	{
		ShowCommFrame("服务器无响应...\r\n");	        
		Beep( 650, 500);

	}
	else if(state_r == -4)
	{
		ShowCommFrame("服务器响应错误...\r\n");	       
		Beep( 650, 500);		
	}
	else
	{
		//m_r_text.SetWindowText("正在下载...\r\n");
	}

	if(cengNum != *ilist)
	{
		cengNum = *ilist;
		updateFlag = TRUE;   //在数据发送函数里，发送数据完毕并且保证准确无误后，将此标志位归位FALSE
		m_cengNum = cengNum;  //进度的设置
		UpdateData(FALSE);
	}
	//如果层数改变则发送坐标信息
	if(updateFlag)
	{
		GetstrOutOfDB();

		int num = coordinate.GetSize();
		for(int i = 0; i < num; i++)
		{
			state_w = ModBus_WriteSingFloat((5010 + i*2), coordinate[i]->floatNum);
			//返回state -1 -2 以及 1 来判别是否发送命令成功
			if(state_w == 0)
			{
				//ShowCommFrame("数据发送成功\r\n");   
			}
			else if(state_w == -1)
			{
				ShowCommFrame("未连接服务器\r\n");

			}
			else if(state_w == -2)
			{
				ShowCommFrame("数据一，发送命令失败\r\n");		
			}
			else if(state_w == -3)
			{
				ShowCommFrame("数据一，服务器无响应\r\n");		
			}
			else if(state_w == -4)
			{
				ShowCommFrame("数据一，服务器响应错误\r\n");
			}
			else if(state_w == -22)
			{
				ShowCommFrame("数据二，发送命令失败\r\n");		
			}
			else if(state_w == -33)
			{
				ShowCommFrame("数据二，服务器无响应\r\n");		
			}
			else if(state_w == -44)
			{
				ShowCommFrame("数据二，服务器响应错误\r\n");
			}
			else
			{
				ShowCommFrame("其他错误\r\n");				
			}

		}
		for(i = 0; i < num; i++)
			delete coordinate[i];
		coordinate.RemoveAll();

		updateFlag = FALSE;
	}

	
	CDialog::OnTimer(nIDEvent);
}


char CModBusTcp::GetstrOutOfDB()
{
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	CMy3DPMaxView* pView = (CMy3DPMaxView*)(pFrame->GetActiveView());
	CMy3DPMaxDoc* pDoc = (CMy3DPMaxDoc*)(pView->GetDocument());

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


		//存储2打印头信息
        floatNum[7] = 2.0f;                       
		floatNum[8] = (float)m_pRecordset->GetCollect("x2o");      
		floatNum[9] = (float)m_pRecordset->GetCollect("y2o"); 
		floatNum[10] = (float)m_pRecordset->GetCollect("z2o"); 

		floatNum[11] = (float)m_pRecordset->GetCollect("x2i");      
		floatNum[12] = (float)m_pRecordset->GetCollect("y2i"); 
		floatNum[13] = (float)m_pRecordset->GetCollect("z2i");

		//存储3打印头信息
        floatNum[14] = 3.0f;                       
		floatNum[15] = (float)m_pRecordset->GetCollect("x3o");      
		floatNum[16] = (float)m_pRecordset->GetCollect("y3o"); 
		floatNum[17] = (float)m_pRecordset->GetCollect("z3o"); 

		floatNum[18] = (float)m_pRecordset->GetCollect("x3i");      
		floatNum[19] = (float)m_pRecordset->GetCollect("y3i"); 
		floatNum[20] = (float)m_pRecordset->GetCollect("z3i"); 

		//存储4打印头信息
        floatNum[21] = 4.0f;                       
		floatNum[22] = (float)m_pRecordset->GetCollect("x4o");      
		floatNum[23] = (float)m_pRecordset->GetCollect("y4o"); 
		floatNum[24] = (float)m_pRecordset->GetCollect("z4o"); 

		floatNum[25] = (float)m_pRecordset->GetCollect("x4i");      
		floatNum[26] = (float)m_pRecordset->GetCollect("y4i"); 
		floatNum[27] = (float)m_pRecordset->GetCollect("z4i");

		//存储5打印头信息
        floatNum[28] = 5.0f;                       
		floatNum[29] = (float)m_pRecordset->GetCollect("x5o");      
		floatNum[30] = (float)m_pRecordset->GetCollect("y5o"); 
		floatNum[31] = (float)m_pRecordset->GetCollect("z5o"); 

		floatNum[32] = (float)m_pRecordset->GetCollect("x5i");      
		floatNum[33] = (float)m_pRecordset->GetCollect("y5i"); 
		floatNum[34] = (float)m_pRecordset->GetCollect("z5i");

		//存储6打印头信息
        floatNum[35] = 6.0f;                       
		floatNum[36] = (float)m_pRecordset->GetCollect("x6o");      
		floatNum[37] = (float)m_pRecordset->GetCollect("y6o"); 
		floatNum[38] = (float)m_pRecordset->GetCollect("z6o"); 

		floatNum[39] = (float)m_pRecordset->GetCollect("x6i");      
		floatNum[40] = (float)m_pRecordset->GetCollect("y6i"); 
		floatNum[41] = (float)m_pRecordset->GetCollect("z6i"); 

		//存储7打印头信息
        floatNum[42] = 7.0f;                       
		floatNum[43] = (float)m_pRecordset->GetCollect("x7o");      
		floatNum[44] = (float)m_pRecordset->GetCollect("y7o"); 
		floatNum[45] = (float)m_pRecordset->GetCollect("z7o"); 

		floatNum[46] = (float)m_pRecordset->GetCollect("x7i");      
		floatNum[47] = (float)m_pRecordset->GetCollect("y7i"); 
		floatNum[48] = (float)m_pRecordset->GetCollect("z7i");

		//存储8打印头信息
        floatNum[49] = 8.0f;                       
		floatNum[50] = (float)m_pRecordset->GetCollect("x8o");      
		floatNum[51] = (float)m_pRecordset->GetCollect("y8o"); 
		floatNum[52] = (float)m_pRecordset->GetCollect("z8o"); 

		floatNum[53] = (float)m_pRecordset->GetCollect("x8i");      
		floatNum[54] = (float)m_pRecordset->GetCollect("y8i"); 
		floatNum[55] = (float)m_pRecordset->GetCollect("z8i"); 

		for(int m = 0; m < 56; m++)
		{
			CCoordinate* pCoordinate = new CCoordinate;
			pCoordinate->floatNum = floatNum[m];
			coordinate.Add(pCoordinate);			
		}
		//AfxMessageBox(m_str);	
	return 0;
}


void CModBusTcp::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CModBusTcp::OnButtonWriteFloat() 
{
	// TODO: Add your control notification handler code here
	char state_w;
	
	UpdateData(TRUE);
	state_w = ModBus_WriteSingFloat(m_dataAddr , m_wirteFloat);
	if(state_w == 0)
	{
		ShowCommFrame("数据发送成功\r\n");   
	}
	else if(state_w == -1)
	{
		ShowCommFrame("未连接服务器\r\n");

	}
	else if(state_w == -2)
	{
		ShowCommFrame("数据一，发送命令失败\r\n");		
	}
	else if(state_w == -3)
	{
		ShowCommFrame("数据一，服务器无响应\r\n");		
	}
	else if(state_w == -4)
	{
		ShowCommFrame("数据一，服务器响应错误\r\n");
	}
	else if(state_w == -22)
	{
		ShowCommFrame("数据二，发送命令失败\r\n");		
	}
	else if(state_w == -33)
	{
		ShowCommFrame("数据二，服务器无响应\r\n");		
	}
	else if(state_w == -44)
	{
		ShowCommFrame("数据二，服务器响应错误\r\n");
	}
	else
	{
	}	



}
