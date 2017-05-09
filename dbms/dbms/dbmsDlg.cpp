
// dbmsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "dbmsDlg.h"
#include "afxdialogex.h"
#include "DBEntity.h"
#include "DBLogic.h"
#include "TBLDlg.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CdbmsDlg �Ի���




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


// CdbmsDlg ��Ϣ�������

BOOL CdbmsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HMENU m_hMenu1;
	m_hMenu1=LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));
	::SetMenu(this->GetSafeHwnd(),m_hMenu1);
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU1));
	//��ȡ���ݿ����ֲ���ʾ
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
			throw new CAppException(_T("Failed to load database��"));
		}
		m_cbDBName.AddString(DBE.GetName());
	}catch (CAppException* e){
		CString errMsg;
		errMsg = e->GetErrorMessage();
		MessageBox(errMsg, _T("ERROR"));
	}*/

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CdbmsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
char *szBuf = new char[str.GetLength() + 1];//ע�⡰+1����char�ַ�Ҫ�����������CStringû��
memset(szBuf, '\0',str.GetLength());

int i;
for ( i = 0 ; i < str.GetLength(); i++)
{
szBuf[i] = (char)str.GetAt(i);
}
szBuf[i] = '\0';//���������������ĩβ�������롣

int nLen;
WCHAR *ptch;
CString strOut;
if(szBuf == NULL)
{
return ;
}
nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//�����Ҫ�Ŀ��ַ��ֽ���
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
	CString dbListPath;
	CString dbName;
	CFileLogic fileLgc;
	dbListPath = fileLgc.GetDBListFile();
	m_cbDBName.ResetContent();
	if (dbList.Open(dbListPath, CFile::modeRead) == FALSE)
		return false;
	while(dbList.ReadString(dbName)){
		ReadStringCharToUnicode(dbName);
		m_cbDBName.AddString(dbName);
	}
	return 0;
}
