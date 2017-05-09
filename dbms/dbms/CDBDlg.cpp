// CDBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dbms.h"
#include "CDBDlg.h"
#include "afxdialogex.h"
#include "DBEntity.h"
#include "DBLogic.h"


// CCDBDlg 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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

// 注意: 我们添加 IID_ICDBDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {30E666E0-086D-4784-8B80-EB71D7067CA2}
static const IID IID_ICDBDlg =
{ 0x30E666E0, 0x86D, 0x4784, { 0x8B, 0x80, 0xEB, 0x71, 0xD7, 0x6, 0x7C, 0xA2 } };

BEGIN_INTERFACE_MAP(CCDBDlg, CDialogEx)
	INTERFACE_PART(CCDBDlg, IID_ICDBDlg, Dispatch)
END_INTERFACE_MAP()


// CCDBDlg 消息处理程序


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
				throw new CAppException(_T("Failed to create database！"));
			}

		}
		CWnd *pWnd=CWnd::FindWindow(NULL,_T(RECEIVE1_TITLE));
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
