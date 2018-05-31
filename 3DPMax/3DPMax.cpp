// 3DPMax.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "3DPMax.h"

#include "MainFrm.h"
#include "3DPMaxDoc.h"
#include "3DPMaxView.h"
#include "Splash.h"
#include "ModBusTcp.h"
#include "Mysocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxApp

BEGIN_MESSAGE_MAP(CMy3DPMaxApp, CWinApp)
	//{{AFX_MSG_MAP(CMy3DPMaxApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxApp construction

CMy3DPMaxApp::CMy3DPMaxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy3DPMaxApp object

CMy3DPMaxApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxApp initialization

BOOL CMy3DPMaxApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	AfxEnableControlContainer();
	AfxInitRichEdit();   //初始化RichEdit控件

	WSADATA wsd;
	AfxSocketInit(&wsd);   //初始化套接字
	
	//数据库连接代码
	if(!AfxOleInit())
	{
		AfxMessageBox("初始化OLE DLL失败！");
		return FALSE;
	}
	::CoInitialize(NULL);

	HRESULT hr;   //连接数据库
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if(SUCCEEDED(hr))
		{
			//注意在发行新版本时，该数据库路径需要更改，为相对于exe的相对路径，才能正常运行；
			//m_pConnection->Open("Provider=Microsoft.Ace.Oledb.12.0;Data Source=C:\\Users\\Administrator\\Desktop\\3DPMax\\3DPMax\\MDB\\test.mdb","","",adModeUnknown); 
			m_pConnection->Open("Provider=Microsoft.Ace.Oledb.12.0;Data Source=test.mdb","","",adModeUnknown); 
			//上面一句中连接字串中的Provider是针对ACCESS2000环境的，
			//对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;
		}
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return FALSE;
	}
/*
	AfxOleInit();
	m_pConnection.CreateInstance(__uuidof(Connection));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息,因为它有时会经常出现一些想不到的错误。

	try                 
	{	
		// 打开本地Access库student.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.12.0;Data Source=test.mdb","","",adModeUnknown);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("数据库连接失败，确认数据库test.mdb是否在当前路径下!");
		return FALSE;
	} 
*/
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMy3DPMaxDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMy3DPMaxView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);   //运行最大化
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMy3DPMaxApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxApp message handlers


BOOL CMy3DPMaxApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

int CMy3DPMaxApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	//关闭ADO连接状态
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
	return CWinApp::ExitInstance();
}
