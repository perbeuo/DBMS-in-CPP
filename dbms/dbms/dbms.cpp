
// dbms.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "dbms.h"
#include "dbmsDlg.h"
#include "CDBDLG.h"
#include "TBLDlg.h"
#include "FieldDlg.h"
#include "RecordDlg.h"
#include "LoginDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdbmsApp

BEGIN_MESSAGE_MAP(CdbmsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_COMMAND(ID_SYSTEM_EXIT, &CdbmsApp::OnSystemExit)
	ON_COMMAND(ID_HELP_ABOUTDBMS, &CdbmsApp::OnHelpAboutdbms)
	ON_COMMAND(ID_DATABASE_CREATEDATABASE, &CdbmsApp::OnDatabaseCreatedatabase)
	ON_COMMAND(ID_TABLE_CREATETABLE, &CdbmsApp::OnTableCreatetable)
	ON_COMMAND(ID_FIELD_ADDFIELD, &CdbmsApp::OnFieldAddfield)
	ON_COMMAND(ID_RECORD_INSERTRECORD, &CdbmsApp::OnRecordInsertrecord)
END_MESSAGE_MAP()


// CdbmsApp 构造

CdbmsApp::CdbmsApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CdbmsApp 对象

CdbmsApp theApp;


// CdbmsApp 初始化

BOOL CdbmsApp::InitInstance()
{
	AfxOleInit();
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
  
    CLoginDlg loginDlg; 
	
    if(loginDlg.DoModal() == IDOK)  
    {  
       CdbmsDlg dlg;  
    m_pMainWnd = &dlg;   
	   
        INT_PTR nResponse = dlg.DoModal();  
        if (nResponse == IDOK)  
        {  
            // TODO: 在此放置处理何时用  
            //  “确定”来关闭对话框的代码  
        }  
        else if (nResponse == IDCANCEL)  
        {  
            // TODO: 在此放置处理何时用  
            //  “取消”来关闭对话框的代码  
        }  
    }  
    else  
    {  
        return FALSE;  
    }
	//CdbmsDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “确定”来关闭对话框的代码
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “取消”来关闭对话框的代码
	//}

	//// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



void CdbmsApp::OnSystemExit()
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CdbmsApp::OnHelpAboutdbms()
{
	CDialog* dlg = new CDialog;
	dlg->Create(MAKEINTRESOURCE(IDD_ABOUTBOX));
	dlg->ShowWindow(1);
}

void CdbmsApp::OnDatabaseCreatedatabase()
{
	CCDBDlg* dlg = new CCDBDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_CREATE_DATABASE));
	dlg->ShowWindow(1);
}



void CdbmsApp::OnTableCreatetable()
{
	CTBLDlg* dlg = new CTBLDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_CREATE_TABLE));
	dlg->ShowWindow(1);
}


void CdbmsApp::OnFieldAddfield()
{
	// TODO: 在此添加命令处理程序代码
	CFieldDlg* dlg = new CFieldDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_FIELD_DIALOG));
	dlg->ShowWindow(1);
}


void CdbmsApp::OnRecordInsertrecord()
{
	CRecordDlg* dlg = new CRecordDlg;
	CString dbName;
	CString tbName;
    HWND hWnd=::FindWindow(NULL,_T("dbms"));
	CdbmsDlg* pWnd= (CdbmsDlg*)CdbmsDlg::FromHandle(hWnd);
	dbName = pWnd->GetChosenDBName();
	tbName = pWnd->GetChosenTBName();
		if(dbName.GetLength()>0 && tbName.GetLength()>0){
			dlg->Create(MAKEINTRESOURCE(IDD_INSERT_RECORD));
		    dlg->ShowWindow(1);
		}
		
		else{
		    AfxMessageBox(_T("Please choose the database and table"));
		}
	
}
