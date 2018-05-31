// 3DPMaxDoc.cpp : implementation of the CMy3DPMaxDoc class
//

#include "stdafx.h"
#include "3DPMax.h"

#include "3DPMaxDoc.h"
#include "3DPMaxView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxDoc

IMPLEMENT_DYNCREATE(CMy3DPMaxDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DPMaxDoc, CDocument)
	//{{AFX_MSG_MAP(CMy3DPMaxDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_STL_FILEIN, OnStlFilein)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxDoc construction/destruction

CMy3DPMaxDoc::CMy3DPMaxDoc()
{
	// TODO: add one-time construction code here

	m_stlRead = false;    //读取
	m_paint_flag = false; //切片 
	m_Nceng = 0;          //层数
	infoArray[0] = 0;     //模型基本信息，长
	infoArray[1] = 0;     //宽
	infoArray[2] = 0;     //高
	infoArray[3] = 0;     //面片数

	CengNumNow = 0;
	PrintNumNow = "";

}

CMy3DPMaxDoc::~CMy3DPMaxDoc()
{
}

BOOL CMy3DPMaxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxDoc serialization

void CMy3DPMaxDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		m_Part.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxDoc diagnostics

#ifdef _DEBUG
void CMy3DPMaxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3DPMaxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DPMaxDoc commands

/**************************打开文件*******************************/

void CMy3DPMaxDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CMy3DPMaxView *pView = (CMy3DPMaxView *)((CMainFrame *)AfxGetApp()->GetMainWnd())->GetActiveView();
	pView->clearAll();
	OnStlFilein();
	
}


void CMy3DPMaxDoc::OnStlFilein() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE,"stl",NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Stereo Lithograpic File(*.stl)|*.stl||", NULL );
	
	CMy3DPMaxView *pView = (CMy3DPMaxView *)((CMainFrame *)AfxGetApp()->GetMainWnd())->GetActiveView();
	pView->clearAll() ;
  

	if(dlg.DoModal() == IDOK)
	{
		pView->viewClear();     //待加入
		m_Part.RemoveAllEntity();//打开之前清空视图

		pSTLModel = new CSTLModel();

		CString strName = dlg.GetPathName();

		pSTLModel->LoadSTLFile(strName);//  存储模型的对象指针

		ModalName = GetSubStr(strName);  //得到文件名用于显示
		


		if(pSTLModel->IsEmpty())
		{
			delete pSTLModel;
		}
		else
		{
			m_Part.AddEntity(pSTLModel);   //具体看看CPart到底是个什么类

		}

		UpdateAllViews(NULL);

		m_stlRead=1;
		pView->m_bool=1;//	其实和m_stlRead有重复              //待加入


	}
	pSTLModel->UpdateBox();
	infoArray[0] = (int)((pSTLModel->m_pBox->x1)-(pSTLModel->m_pBox->x0));
	infoArray[1] = (int)((pSTLModel->m_pBox->y1)-(pSTLModel->m_pBox->y0));
	infoArray[2] = (int)((pSTLModel->m_pBox->z1)-(pSTLModel->m_pBox->z0));
	infoArray[3] = pSTLModel->m_TriList.GetSize();
	
}
		

//自己加的函数，用于从绝对路径获取文件名

CString CMy3DPMaxDoc::GetSubStr(CString str)
{
	int pos = 0,pos1 = 0;
	CString substr;
	while((pos >= 0)&&(pos < str.GetLength()))
	{
		pos = str.Find("\\",pos);
		if(pos > 0)
		{
			pos1 = pos;
			pos++;			
		}
	}
	substr = str.Right(str.GetLength()-pos1-1);
	return substr;
}

