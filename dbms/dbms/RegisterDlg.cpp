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

	m_NewName = _T("");
	m_NewPassword = _T("");
	m_AgainPassword = _T("");
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
	DDX_Text(pDX, IDC_EDIT1, m_NewName);
	DDV_MaxChars(pDX, m_NewName, 30);
	DDX_Text(pDX, IDC_EDIT2, m_NewPassword);
	DDV_MaxChars(pDX, m_NewPassword, 30);
	DDX_Text(pDX, IDC_EDIT3, m_AgainPassword);
	DDV_MaxChars(pDX, m_AgainPassword, 30);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegisterDlg::OnBnClickedOk)
	ON_WM_PAINT()
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


void CRegisterDlg::OnBnClickedOk()
{
    CFileLogic fileLogic;
	CUserEntity UserE;
	CString path;
    CUserLogic usLogic;
	CUserEntity ue;
	CFile file;
	this->UpdateData(true);  
	if(this->m_NewName.IsEmpty()){
		MessageBox(_T("用户名不能为空，请重新输入！"));
		goto stop;
	}
	else if(this->m_NewPassword.IsEmpty()){
	    MessageBox(_T("密码不能为空，请重新输入！"));
		goto stop;
	}
	else if(m_NewPassword.CompareNoCase(m_AgainPassword)){
	    MessageBox(_T("两次输入密码不一致，请再次输入"));
		goto stop;
	}
	path = fileLogic.GetUserFile();
	UserE.SetPath(path);
	UserE.SetName(m_NewName);
	UserE.SetPassword(m_NewPassword);
	path = fileLogic.GetUserFile();
			try{
		if (file.Open(path, CFile::modeRead | CFile::shareDenyNone) == FALSE)
			throw new CAppException(_T("Failed to read the table file!"));
		LoginBlock tempLB;
		file.SeekToBegin();
		while(file.Read(&tempLB, sizeof(tempLB)) > 0){
			ue.SetBlock(tempLB);
			if(m_NewName==ue.GetName()){
                 throw new CAppException(_T("此用户名已经存在"));
			}		
		} 
		//MessageBox(_T("请输入正确的用户名"));
	}catch(CAppException* e){
		CString m_strError = e->GetErrorMessage();
		delete e;
		MessageBox(m_strError, _T("ERROR"));
		goto stop;
	}
	try
	{
		//Add a user
		if(usLogic.AddUser(UserE) == false)
		{
			throw new CAppException(_T("Failed to save  file"));
		}
		DestroyWindow();
	}
	catch(CAppException* e)
	{
		m_strError = e->GetErrorMessage();
		delete e;
		MessageBox(m_strError, _T("ERROR"));
	}
	stop:;
}


void CRegisterDlg::OnPaint()
{
CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rc;
        GetClientRect(&rc);
        CDC dcMem;
        dcMem.CreateCompatibleDC(&dc);
        CBitmap bmpBackground;
        bmpBackground.LoadBitmap(IDB_BITMAP2);

        BITMAP bitmap;
        bmpBackground.GetBitmap(&bitmap);
        CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
        dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}
