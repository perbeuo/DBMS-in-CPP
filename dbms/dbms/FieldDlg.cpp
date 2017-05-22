// FieldDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dbms.h"
#include "FieldDlg.h"
#include "afxdialogex.h"
#include "dbmsDlg.h"
#include "TableLogic.h"
// CFieldDlg 对话框

IMPLEMENT_DYNAMIC(CFieldDlg, CDialogEx)

CFieldDlg::CFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFieldDlg::IDD, pParent)
{

	m_strName = _T("");
	m_strDefault = _T("");
	m_strType = _T("");
	m_bNull = FALSE;
	m_bPrimary = FALSE;

}

CFieldDlg::~CFieldDlg()
{
}

void CFieldDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_Text(pDX, IDC_EDIT_DEFAULT, m_strDefault);
	DDX_Check(pDX, IDC_CHECK_NULL, m_bNull);
	DDX_Check(pDX, IDC_CHECK_PRIMARY, m_bPrimary);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
}

/*****************************************************
[FunctionName]	OnInitDialog
[Function]	Dialog initialization function
[Argument]	void
[ReturnedValue]	BOOL:TRUE if the operation is successful, otherwise FALSE
*****************************************************/
BOOL CFieldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Initializes the combo box
	m_cbType.InsertString(0, _T("INT"));
	m_cbType.InsertString(1, _T("VARCHAR"));
	m_cbType.InsertString(2, _T("BOOL"));
	m_cbType.InsertString(3, _T("DOUBLE"));
	m_cbType.InsertString(4, _T("DATATIME"));
	m_cbType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CFieldDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CFieldDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFieldDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFieldDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {E9FEAB3F-4868-45E1-979E-AA38A5B82479}
static const IID IID_IFieldDlg =
{ 0xE9FEAB3F, 0x4868, 0x45E1, { 0x97, 0x9E, 0xAA, 0x38, 0xA5, 0xB8, 0x24, 0x79 } };

BEGIN_INTERFACE_MAP(CFieldDlg, CDialogEx)
	INTERFACE_PART(CFieldDlg, IID_IFieldDlg, Dispatch)
END_INTERFACE_MAP()


// CFieldDlg 消息处理程序


void CFieldDlg::OnBnClickedButton2()
{
	CFileLogic fileLogic;
	CString tdfPath;
	CString dbName;
	CString tbName;
	CString fieldName;
	CString defaultValue;
	int datatype;
	CTableEntity tableE;
	CFieldEntity fieldE;
	GetDlgItemText(IDC_EDIT_NAME,fieldName);
	if(!fieldName.CompareNoCase(_T(""))){
		MessageBox(_T("Field name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	HWND hWnd=::FindWindow(NULL,_T("dbms"));
	CdbmsDlg* pWnd= (CdbmsDlg*)CdbmsDlg::FromHandle(hWnd);
	dbName = pWnd->GetChosenDBName();

	//判断是否选择数据库
	if(dbName.GetLength()==0){
	    MessageBox(_T("Database name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	//判断是否选择表
	tbName =  pWnd->GetChosenTBName();
	if(tbName.GetLength()==0){
	    MessageBox(_T("Table name cannot be empty"), _T("ERROR"));
		goto stop;
	}

	tableE = pWnd->GetTableEntity();
	tdfPath = fileLogic.GetTbDefineFile(dbName, tableE.GetName());
	tableE.SetTdfPath(tdfPath);
	datatype = m_cbType.GetCurSel() + 1;
	fieldE.SetName(fieldName);
	fieldE.SetDataType(datatype);
	fieldE.SetDefault(defaultValue);

	CTableLogic tbLogic;
	try
	{
		// Add a field
		if(tbLogic.AddField(dbName, tableE, fieldE) == false)
		{
			throw new CAppException(_T("Failed to save table field file"));
		}
		//CFieldEntity* pField = m_pEditTable->AddField(field);
		//return pField;
	}
	catch(CAppException* e)
	{
		m_strError = e->GetErrorMessage();
		delete e;
		MessageBox(m_strError, _T("ERROR"));
	}
	DestroyWindow( );
	stop:;
}
