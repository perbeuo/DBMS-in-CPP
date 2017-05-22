
// dbms.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "dbms.h"
#include "dbmsDlg.h"
#include "CDBDLG.h"
#include "TBLDlg.h"
#include "FieldDlg.h"
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


// CdbmsApp ����

CdbmsApp::CdbmsApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CdbmsApp ����

CdbmsApp theApp;


// CdbmsApp ��ʼ��

BOOL CdbmsApp::InitInstance()
{
	AfxOleInit();
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CdbmsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
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
	// TODO: �ڴ���������������
	CFieldDlg* dlg = new CFieldDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_FIELD_DIALOG));
	dlg->ShowWindow(1);
}


void CdbmsApp::OnRecordInsertrecord()
{
	
}
