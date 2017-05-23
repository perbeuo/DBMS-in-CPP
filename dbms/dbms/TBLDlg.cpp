// TBLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "TBLDlg.h"
#include "afxdialogex.h"
#include "TableEntity.h"
#include "TableLogic.h"
#include "dbmsDlg.h"
#include "DBLogic.h"
// CTBLDlg �Ի���

IMPLEMENT_DYNAMIC(CTBLDlg, CDialogEx)

CTBLDlg::CTBLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTBLDlg::IDD, pParent)
{

	EnableAutomation();

}

CTBLDlg::~CTBLDlg()
{
}

void CTBLDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CTBLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TBL_DBNAME, m_cbDBNameTB);
}


BEGIN_MESSAGE_MAP(CTBLDlg, CDialogEx)
	ON_EN_CHANGE(IDC_DBNAME, &CTBLDlg::OnEnChangeDbname)
	ON_BN_CLICKED(IDOK, &CTBLDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_TABLENAME, &CTBLDlg::OnEnChangeTablename)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTBLDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_ITBLDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {8446BA70-DA87-4775-93FE-E41F7D6934B6}
static const IID IID_ITBLDlg =
{ 0x8446BA70, 0xDA87, 0x4775, { 0x93, 0xFE, 0xE4, 0x1F, 0x7D, 0x69, 0x34, 0xB6 } };

BEGIN_INTERFACE_MAP(CTBLDlg, CDialogEx)
	INTERFACE_PART(CTBLDlg, IID_ITBLDlg, Dispatch)
END_INTERFACE_MAP()


// CTBLDlg ��Ϣ�������


void CTBLDlg::OnEnChangeDbname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}




void CTBLDlg::OnBnClickedOk()
{
	CEdit* pBoxOne;
	pBoxOne = (CEdit*) GetDlgItem(IDC_TABLENAME);
	CTableLogic tbLogic;
	pBoxOne->GetWindowText(TableName);
	CString DBName = _T("");
	//Tbl.SetFilepath(TableName);
	CTableEntity* pTable = new CTableEntity();
	pTable->SetName(TableName);
/*	tableList.AddString(TableName)*/;
      /*tableList.AddString(TableName);*/
	GetDlgItemText(IDC_COMBO_TBL_DBNAME,DBName);
	if(!DBName.CompareNoCase(_T(""))){
		MessageBox(_T("Database name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	if(!TableName.CompareNoCase(_T(""))){
		MessageBox(_T("Table name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	DBName.Trim();
	m_dbEntity.SetName(DBName);
	CDBLogic dbLogic;
	try{
		if (dbLogic.GetDatabase(m_dbEntity) == false){
			throw new CAppException(_T("Failed to load database��"));
		}
	}catch (CAppException* e){
		CString errMsg;
		errMsg = e->GetErrorMessage();
		MessageBox(errMsg, _T("ERROR"));
	}

	try
	{
		// Decide whether creates table successfully
		if (tbLogic.CreateTable(m_dbEntity.GetName(), *pTable) == true)
		{
			
			// If creates table successfully, the created table information would be saved to the array.
			m_arrTable.Add(pTable);
			/*Name();*/
		}
		else
		{
			// If creates failure, release the memory allocated by new
			delete pTable;
			pTable = NULL;
		}
	}
	catch(CAppException* e)	// Catch exception
	{
		// If there is exception, release the memory allocated by new
		if (pTable != NULL)
		{
			delete pTable;
			pTable = NULL;
		}
		// Get exception information
		m_strError = e->GetErrorMessage();
		// Delete exception
		delete e;
	}
	DestroyWindow( );
	stop:;
}


BOOL CTBLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	CStdioFile dbList;
	CString dbListPath;
	CString dbName;
	CFileLogic fileLgc;
	dbListPath = fileLgc.GetDBListFile();
	try{
		if (dbList.Open(dbListPath, CFile::modeRead) == FALSE)
			throw new CAppException();
		while(dbList.ReadString(dbName)){
			//ReadStringCharToUnicode(dbName);
			m_cbDBNameTB.AddString(dbName);
		}
	}catch(CAppException* e){
		MessageBox(_T("Failed to load databases"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTBLDlg::OnPaint()
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


void CTBLDlg::OnEnChangeTablename()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
