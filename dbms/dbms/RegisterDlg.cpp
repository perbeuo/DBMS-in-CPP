// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// CRegisterDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IRegisterDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {0A921BFE-4450-43BB-B784-9BDE809E66C1}
static const IID IID_IRegisterDlg =
{ 0xA921BFE, 0x4450, 0x43BB, { 0xB7, 0x84, 0x9B, 0xDE, 0x80, 0x9E, 0x66, 0xC1 } };

BEGIN_INTERFACE_MAP(CRegisterDlg, CDialogEx)
	INTERFACE_PART(CRegisterDlg, IID_IRegisterDlg, Dispatch)
END_INTERFACE_MAP()


// CRegisterDlg ��Ϣ�������
