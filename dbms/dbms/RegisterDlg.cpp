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

	m_NewName = _T("");
	m_NewPassword = _T("");
	m_AgainPassword = _T("");
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
		MessageBox(_T("�û�������Ϊ�գ����������룡"));
		goto stop;
	}
	else if(this->m_NewPassword.IsEmpty()){
	    MessageBox(_T("���벻��Ϊ�գ����������룡"));
		goto stop;
	}
	else if(m_NewPassword.CompareNoCase(m_AgainPassword)){
	    MessageBox(_T("�����������벻һ�£����ٴ�����"));
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
                 throw new CAppException(_T("���û����Ѿ�����"));
			}		
		} 
		//MessageBox(_T("��������ȷ���û���"));
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
