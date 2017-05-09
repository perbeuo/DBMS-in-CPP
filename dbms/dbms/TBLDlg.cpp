// TBLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dbms.h"
#include "TBLDlg.h"
#include "afxdialogex.h"
#include "TableEntity.h"
#include "TableLogic.h"
#include "dbmsDlg.h"
#include "DBLogic.h"
// CTBLDlg 对话框

IMPLEMENT_DYNAMIC(CTBLDlg, CDialogEx)

CTBLDlg::CTBLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTBLDlg::IDD, pParent)
{

	EnableAutomation();

}

CTBLDlg::~CTBLDlg()
{
}

void CTBLDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CTBLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TBL_DBNAME, m_cbDBNameTB);
}


BEGIN_MESSAGE_MAP(CTBLDlg, CDialogEx)
	ON_EN_CHANGE(IDC_DBNAME, &CTBLDlg::OnEnChangeDbname)
	ON_BN_CLICKED(IDOK, &CTBLDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTBLDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ITBLDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {8446BA70-DA87-4775-93FE-E41F7D6934B6}
static const IID IID_ITBLDlg =
{ 0x8446BA70, 0xDA87, 0x4775, { 0x93, 0xFE, 0xE4, 0x1F, 0x7D, 0x69, 0x34, 0xB6 } };

BEGIN_INTERFACE_MAP(CTBLDlg, CDialogEx)
	INTERFACE_PART(CTBLDlg, IID_ITBLDlg, Dispatch)
END_INTERFACE_MAP()


// CTBLDlg 消息处理程序


void CTBLDlg::OnEnChangeDbname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void CTBLDlg::OnBnClickedOk()
{
	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_TABLENAME);
	CTableLogic tbLogic;
	pBoxOne->GetWindowText(TableName);
	CString DBName = _T("");
	//Tbl.SetFilepath(TableName);
	CTableEntity* pTable = new CTableEntity();
	pTable->SetName(TableName);
/*	tableList.AddString(TableName)*/;
      /*tableList.AddString(TableName);*/
	GetDlgItemText(IDC_COMBO_TBL_DBNAME,DBName);
	if(!DBName.CompareNoCase(_T(""))){
		MessageBox(_T("Database name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	if(!TableName.CompareNoCase(_T(""))){
		MessageBox(_T("Table name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	DBName.Trim();
	m_dbEntity.SetName(DBName);
	CDBLogic dbLogic;
	try{
		if (dbLogic.GetDatabase(m_dbEntity) == false){
			throw new CAppException(_T("Failed to load database！"));
		}
	}catch (CAppException* e){
		CString errMsg;
		errMsg = e->GetErrorMessage();
		MessageBox(errMsg, _T("ERROR"));
	}

	try
	{
		// Decide whether creates table successfully
		if (tbLogic.CreateTable(m_dbEntity.GetName(), *pTable) == true)
		{
			
			// If creates table successfully, the created table information would be saved to the array.
			m_arrTable.Add(pTable);
			/*Name();*/
		}
		else
		{
			// If creates failure, release the memory allocated by new
			delete pTable;
			pTable = NULL;
		}
	}
	catch(CAppException* e)	// Catch exception
	{
		// If there is exception, release the memory allocated by new
		if (pTable != NULL)
		{
			delete pTable;
			pTable = NULL;
		}
		// Get exception information
		m_strError = e->GetErrorMessage();
		// Delete exception
		delete e;
	}
	DestroyWindow( );
	stop:;
}


BOOL CTBLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	CStdioFile dbList;
	CString dbListPath;
	CString dbName;
	CFileLogic fileLgc;
	dbListPath = fileLgc.GetDBListFile();
	try{
		if (dbList.Open(dbListPath, CFile::modeRead) == FALSE)
			throw new CAppException();
		while(dbList.ReadString(dbName)){
			//ReadStringCharToUnicode(dbName);
			m_cbDBNameTB.AddString(dbName);
		}
	}catch(CAppException* e){
		MessageBox(_T("Failed to load databases"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
