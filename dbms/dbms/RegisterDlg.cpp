// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dbms.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterDlg::IDD, pParent)
{

	EnableAutomation();

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRegisterDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IRegisterDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {0A921BFE-4450-43BB-B784-9BDE809E66C1}
static const IID IID_IRegisterDlg =
{ 0xA921BFE, 0x4450, 0x43BB, { 0xB7, 0x84, 0x9B, 0xDE, 0x80, 0x9E, 0x66, 0xC1 } };

BEGIN_INTERFACE_MAP(CRegisterDlg, CDialogEx)
	INTERFACE_PART(CRegisterDlg, IID_IRegisterDlg, Dispatch)
END_INTERFACE_MAP()


// CRegisterDlg 消息处理程序
