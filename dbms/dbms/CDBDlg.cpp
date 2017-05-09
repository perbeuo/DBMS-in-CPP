// CDBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "CDBDlg.h"
#include "afxdialogex.h"
#include "DBEntity.h"
#include "DBLogic.h"


// CCDBDlg �Ի���

IMPLEMENT_DYNAMIC(CCDBDlg, CDialogEx)

CCDBDlg::CCDBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCDBDlg::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CCDBDlg::~CCDBDlg()
{
}

void CCDBDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CCDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCDBDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DBINFO_OK, &CCDBDlg::OnBnClickedDbinfoOk)
	ON_BN_CLICKED(IDC_DB_CANCEL, &CCDBDlg::OnBnClickedDbCancel)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCDBDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_ICDBDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {30E666E0-086D-4784-8B80-EB71D7067CA2}
static const IID IID_ICDBDlg =
{ 0x30E666E0, 0x86D, 0x4784, { 0x8B, 0x80, 0xEB, 0x71, 0xD7, 0x6, 0x7C, 0xA2 } };

BEGIN_INTERFACE_MAP(CCDBDlg, CDialogEx)
	INTERFACE_PART(CCDBDlg, IID_ICDBDlg, Dispatch)
END_INTERFACE_MAP()


// CCDBDlg ��Ϣ�������


void CCDBDlg::OnBnClickedDbinfoOk()
{
	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_DBNAME);
	CString DBName;
	pBoxOne->GetWindowText(DBName);
	CDBEntity DBE;
	DBE.SetName(DBName);
	//DBE.SetFilepath(DBName);

	CDBLogic dbLogic;
	try{
		if (dbLogic.GetDatabase(DBE) == false)
		{
			//	Decide whether creates the database successfully
			if (dbLogic.CreateDatabase(DBE) == false)
			{
				//	If creates failure, throw an exception
				throw new CAppException(_T("Failed to create database��"));
			}

		}
		CWnd *pWnd=CWnd::FindWindow(NULL,_T("dbms"));
		pWnd->SendMessage(WM_UPDATE_DIALOG_DBN,NULL,0);
	//HWND hWnd = ::FindWindowEx( this->GetParent()->m_hWnd, NULL, NULL, _T(RECEIVE1_TITLE)) ;
	//FromHandle(hWnd)->SendMessage(WM_UPDATE_DIALOG_DBN,0,0);
		//::SendMessage(NULL, WM_UPDATE_DIALOG_DBN, 0, 0);
	}catch (CAppException* e){
		CString errMsg;
		errMsg = e->GetErrorMessage();
		MessageBox(errMsg, _T("ERROR"));
	}
	DestroyWindow( );
}


void CCDBDlg::OnBnClickedDbCancel()
{
	DestroyWindow( );
}
