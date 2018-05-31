// ChkPlace.cpp : implementation file
//

#include "stdafx.h"
#include "3dpmax.h"
#include "ChkPlace.h"

#include "atlbase.h" //ATL,,,//STL


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChkPlace dialog

extern CMy3DPMaxApp theApp;       // 在此引用应用类中的theApp来获取库连接指针

CChkPlace::CChkPlace(CWnd* pParent /*=NULL*/)
	: CDialog(CChkPlace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChkPlace)
	m_cengNum = 0;
	m_roundNum = _T("");
	m_1o = _T("");
	m_2o = _T("");
	m_3o = _T("");
	m_4o = _T("");
	m_5o = _T("");
	m_6o = _T("");
	m_7o = _T("");
	m_8o = _T("");
	m_1i = _T("");
	m_2i = _T("");
	m_3i = _T("");
	m_4i = _T("");
	m_5i = _T("");
	m_6i = _T("");
	m_7i = _T("");
	m_8i = _T("");
	//}}AFX_DATA_INIT
}


void CChkPlace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChkPlace)
	DDX_Text(pDX, IDC_EDIT1, m_cengNum);
	DDX_Text(pDX, IDC_EDIT10, m_roundNum);
	DDX_Text(pDX, IDC_EDIT2, m_1o);
	DDX_Text(pDX, IDC_EDIT3, m_2o);
	DDX_Text(pDX, IDC_EDIT4, m_3o);
	DDX_Text(pDX, IDC_EDIT5, m_4o);
	DDX_Text(pDX, IDC_EDIT6, m_5o);
	DDX_Text(pDX, IDC_EDIT7, m_6o);
	DDX_Text(pDX, IDC_EDIT8, m_7o);
	DDX_Text(pDX, IDC_EDIT9, m_8o);
	DDX_Text(pDX, IDC_EDIT11, m_1i);
	DDX_Text(pDX, IDC_EDIT12, m_2i);
	DDX_Text(pDX, IDC_EDIT13, m_3i);
	DDX_Text(pDX, IDC_EDIT14, m_4i);
	DDX_Text(pDX, IDC_EDIT15, m_5i);
	DDX_Text(pDX, IDC_EDIT16, m_6i);
	DDX_Text(pDX, IDC_EDIT17, m_7i);
	DDX_Text(pDX, IDC_EDIT18, m_8i);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChkPlace, CDialog)
	//{{AFX_MSG_MAP(CChkPlace)
	ON_BN_CLICKED(IDC_BUT_CHECKPLA, OnButCheckpla)
	ON_BN_CLICKED(IDC_BUT_CANCELPLA, OnButCancelpla)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CChkPlace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// CChkPlace message handlers


void CChkPlace::OnDestroy() 
{
	// TODO: Add your message handler code here

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

void CChkPlace::OnButCancelpla() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


//查看层轮廓信息
char CChkPlace::OnButCheckpla() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

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
	if((m_cengNum >= nCount)||(m_cengNum < 0))
	{
		AfxMessageBox("输入越界,请重新输入");
		return (-1);
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString strSql;
	strSql.Format("select * from coordinate where cengNum = %d ",m_cengNum);    //为什么在例程里面%d 加了单引号，
//	AfxMessageBox(strSql);                                                      //测试是不行的，所以在此就把引号给去掉了
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
		//将查询结果在列表框中显示出来
		_variant_t vFieldValue;
		CString roundNum;

		CString x1o, y1o, z1o, x1i, y1i, z1i;
		CString x2o, y2o, z2o, x2i, y2i, z2i;
		CString x3o, y3o, z3o, x3i, y3i, z3i;
		CString x4o, y4o, z4o, x4i, y4i, z4i;
		CString x5o, y5o, z5o, x5i, y5i, z5i;
		CString x6o, y6o, z6o, x6i, y6i, z6i;
		CString x7o, y7o, z7o, x7i, y7i, z7i;
		CString x8o, y8o, z8o, x8i, y8i, z8i;
		
		CString _1o,_1i;
		CString _2o,_2i;
		CString _3o,_3i;
		CString _4o,_4i;
		CString _5o,_5i;
		CString _6o,_6i;
		CString _7o,_7i;
		CString _8o,_8i;

		vFieldValue = m_pRecordset->GetCollect("roundNum");
		roundNum = (char*)_bstr_t(vFieldValue);
		vFieldValue.Clear();
		m_roundNum = roundNum;

//////////////////////////////////////////////////////////
//		float aa = 0.0f;                                //
//		aa =(float)m_pRecordset->GetCollect("z1o");     //
//		CString str111;                                 //
//		str111.Format("%f",aa);                         //
//		AfxMessageBox(str111);                          //
//////////////////////////////////////////////////////////

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
		
		if((x1o == "0.000000")&&(y1o == "0.000000")&&(z1o == "0.000000"))

			m_1o = "此枪头不工作";
		else
			m_1o = "(" + x1o + "," + y1o + "," + z1o + ")";
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

			m_1i = "此枪头不工作";
		else
			m_1i = "(" + x1i + "," + y1i + "," + z1i + ")";

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

		if((x2o == "0.000000")&&(y2o == "0.000000")&&(z2o == "0.000000"))

			m_2o = "此枪头不工作";
		else
			m_2o = "(" + x2o + "," + y2o + "," + z2o +")";
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

			m_2i = "此枪头不工作";
		else
			m_2i = "(" + x2i + "," + y2i + "," + z2i + ")";

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
		
		if((x3o == "0.000000")&&(y3o == "0.000000")&&(z3o == "0.000000"))

			m_3o = "此枪头不工作";
		else
			m_3o = "(" + x3o + "," + y3o + "," + z3o + ")";
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

			m_3i = "此枪头不工作";
		else
			m_3i = "(" + x3i + "," + y3i + "," + z3i + ")";

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

		if((x4o == "0.000000")&&(y4o == "0.000000")&&(z4o == "0.000000"))

			m_4o = "此枪头不工作";
		else
			m_4o = "(" + x4o + "," + y4o + "," + z4o + ")";
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

			m_4i = "此枪头不工作";
		else
			m_4i = "(" + x4i + "," + y4i + "," + z4i + ")";

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
		
		if((x5o == "0.000000")&&(y5o == "0.000000")&&(z5o == "0.000000"))

			m_5o = "此枪头不工作";
		else
			m_5o = "(" + x5o + "," + y5o + "," + z5o +")";
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

			m_5i = "此枪头不工作";
		else
			m_5i = "(" + x5i + "," + y5i + "," + z5i + ")";

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
		
		if((x6o == "0.000000")&&(y6o == "0.000000")&&(z6o == "0.000000"))

			m_6o = "此枪头不工作";
		else
			m_6o = "(" + x6o + "," + y6o + "," + z6o +")";

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

			m_6i = "此枪头不工作";
		else
			m_6i = "(" + x6i + "," + y6i + "," + z6i +")";

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

		if((x7o == "0.000000")&&(y7o == "0.000000")&&(z7o == "0.000000"))

			m_7o = "此枪头不工作";
		else
			m_7o = "(" + x7o + "," + y7o + "," + z7o +")";

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

			m_7i = "此枪头不工作";
		else
			m_7i = "(" + x7i + "," + y7i + "," + z7i +")";

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
		
		if((x8o == "0.000000")&&(y8o == "0.000000")&&(z8o == "0.000000"))

			m_8o = "此枪头不工作";
		else
			m_8o = "(" + x8o + "," + y8o + "," + z8o +")";

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

			m_8i = "此枪头不工作";
		else
			m_8i = "(" + x8i + "," + y8i + "," + z8i +")";

		UpdateData(FALSE);

		return (1);
	
}

