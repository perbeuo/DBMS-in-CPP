// LoginDlg.cpp : 实现文件
#include "stdafx.h"
#include "dbms.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "RegisterDlg.h"
#include "FileLogic.h"
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{

	EnableAutomation();

	//  m_UserName = _T("");
	//  m_UserPassword = _T("");
	m_UserPassword = _T("");
	m_UserName = _T("");

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_PASSWORD, m_UserName);
	//  DDV_MaxChars(pDX, m_UserName, 20);
	//  DDX_Text(pDX, IDC_EDIT_USER, m_UserPassword);
	//  DDV_MaxChars(pDX, m_UserPassword, 30);
	//  DDX_Control(pDX, IDC_EDIT_PASSWORD, m_UserPassword1);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_UserPassword);
	DDV_MaxChars(pDX, m_UserPassword, 30);
	DDX_Text(pDX, IDC_EDIT_USER, m_UserName);
	DDV_MaxChars(pDX, m_UserName, 20);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LOGIN, &CLoginDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_REGISTER, &CLoginDlg::OnBnClickedRegister)
END_MESSAGE_MAP()
BEGIN_DISPATCH_MAP(CLoginDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ILoginDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {9D5F1BB5-8B82-4CB3-A673-85572C61A3EA}
static const IID IID_ILoginDlg =
{ 0x9D5F1BB5, 0x8B82, 0x4CB3, { 0xA6, 0x73, 0x85, 0x57, 0x2C, 0x61, 0xA3, 0xEA } };

BEGIN_INTERFACE_MAP(CLoginDlg, CDialogEx)
	INTERFACE_PART(CLoginDlg, IID_ILoginDlg, Dispatch)
END_INTERFACE_MAP()



void CLoginDlg::OnPaint()
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

void CLoginDlg::OnBnClickedLogin()
{
	 this->UpdateData(true);  
	 CString Path = _T("");
	 CFileLogic  fileLogic;
	 CUserEntity ue;
	 CFile file;
    if(this->m_UserName.IsEmpty() || this->m_UserPassword.IsEmpty())  
    {  
        MessageBox(_T("The user name and password cannot be vacant!"),_T("User login info"),MB_ICONINFORMATION);  
        return;  

    }   

    else  
    {  
		Path = fileLogic.GetUserFile();
			try{
		if (file.Open(Path, CFile::modeRead | CFile::shareDenyNone) == FALSE)
			throw new CAppException(_T("Failed to read the table file!"));
		LoginBlock tempLB;
		file.SeekToBegin();
		while(file.Read(&tempLB, sizeof(tempLB)) > 0){
			ue.SetBlock(tempLB);
			if(m_UserName==ue.GetName()){
				if(m_UserPassword==ue.GetPassword()){
					OnOK();    // 假如用户名和密码正确，就关闭对话框
					goto stop;
				}else{
					throw new CAppException(_T("Wrong password"));
			   // MessageBox(_T("密码不正确"));
				goto stop;
				}

			}
			
		} 
		throw new CAppException(_T("Please input a valid username"));
		//MessageBox(_T("请输入正确的用户名"));
		stop:;
	}catch(CAppException* e){
		CString m_strError = e->GetErrorMessage();
		delete e;
		MessageBox(m_strError, _T("ERROR"));
	}
       
    }  
}



void CLoginDlg::OnBnClickedRegister()
{
	CRegisterDlg* dlg = new CRegisterDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_DIALOG_REGISTER));
	dlg->ShowWindow(1);
}
