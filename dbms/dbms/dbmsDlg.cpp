
// dbmsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dbms.h"
#include "dbmsDlg.h"
#include "afxdialogex.h"
#include "DBEntity.h"
#include "DBLogic.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnAltX();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
//	afx_msg LRESULT OnUpdateDialogDb(WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_SYSTEM_EXIT, &CAboutDlg::OnAltX)
//	ON_MESSAGE(WM_UPDATE_DIALOG_DB, &CAboutDlg::OnUpdateDialogDb)
END_MESSAGE_MAP()


// CdbmsDlg 对话框




CdbmsDlg::CdbmsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdbmsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdbmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DBNAME, m_cbDBName);
}

BEGIN_MESSAGE_MAP(CdbmsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CdbmsDlg::OnBnClickedOk)
	//ON_MESSAGE(WM_UPDATA_DIALOG, &CdbmsDlg::OnUpdateDialogDB)
	ON_MESSAGE(WM_UPDATE_DIALOG_DBN, &CdbmsDlg::OnUpdateDialogDbn)
END_MESSAGE_MAP()


// CdbmsDlg 消息处理程序

BOOL CdbmsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HMENU m_hMenu1;
	m_hMenu1=LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));
	::SetMenu(this->GetSafeHwnd(),m_hMenu1);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU1));
	//读取数据库名字并显示
	CStdioFile dbList;
	//std::ifstream out;
	CString dbListPath;
	CString dbName;
	//char temp[100];
	CFileLogic fileLgc;
	dbListPath = fileLgc.GetDBListFile();
	//out.open(dbListPath, std::ios::in);
	//while(!out.eof()){
	//	out.getline(temp, sizeof(VARCHAR));
   // }
	if (dbList.Open(dbListPath, CFile::modeRead) == FALSE)
		return false;
	while(dbList.ReadString(dbName)){
		int strLen;
		strLen = dbName.GetLength();
		ReadStringCharToUnicode(dbName);
		m_cbDBName.AddString(dbName);
	}
/*	CDBLogic dbLogic;
	CDBEntity DBE;
	DBE.SetName(_T("321"));
	try{
		if (dbLogic.GetDatabase(DBE) == false){
			throw new CAppException(_T("Failed to load database！"));
		}
		m_cbDBName.AddString(DBE.GetName());
	}catch (CAppException* e){
		CString errMsg;
		errMsg = e->GetErrorMessage();
		MessageBox(errMsg, _T("ERROR"));
	}*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdbmsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdbmsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdbmsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CdbmsDlg::PreTranslateMessage(MSG* pMsg)
{
	if(::TranslateAccelerator(GetSafeHwnd(),hAccel,pMsg))
		return   true;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CdbmsDlg::OnBnClickedOk()
{
}

void CdbmsDlg::OnUpdateDialogDB(){

}

void CdbmsDlg::ReadStringCharToUnicode(CString &str)
{
char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
memset(szBuf, '\0',str.GetLength());

int i;
for ( i = 0 ; i < str.GetLength(); i++)
{
szBuf[i] = (char)str.GetAt(i);
}
szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

int nLen;
WCHAR *ptch;
CString strOut;
if(szBuf == NULL)
{
return ;
}
nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
ptch = new WCHAR[nLen];
memset(ptch, '\0', nLen);
MultiByteToWideChar(CP_ACP, 0, szBuf, -1, ptch, nLen);
str.Format(_T("%s"), ptch);

if(NULL != ptch)
delete [] ptch;
ptch = NULL;

if(NULL != szBuf)
delete []szBuf;
szBuf = NULL;
return ;
}

//afx_msg LRESULT CAboutDlg::OnUpdateDialogDb(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}


afx_msg LRESULT CdbmsDlg::OnUpdateDialogDbn(WPARAM wParam, LPARAM lParam)
{
	CStdioFile dbList;
	//std::ifstream out;
	CString dbListPath;
	CString dbName;
	//char temp[100];
	CFileLogic fileLgc;
	dbListPath = fileLgc.GetDBListFile();
	//out.open(dbListPath, std::ios::in);
	//while(!out.eof()){
	//	out.getline(temp, sizeof(VARCHAR));
   // }
	m_cbDBName.ResetContent();
	if (dbList.Open(dbListPath, CFile::modeRead) == FALSE)
		return false;
	while(dbList.ReadString(dbName)){
		int strLen;
		strLen = dbName.GetLength();
		ReadStringCharToUnicode(dbName);
		m_cbDBName.AddString(dbName);
	}
	return 0;
}
