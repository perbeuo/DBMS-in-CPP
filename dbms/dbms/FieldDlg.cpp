// FieldDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "FieldDlg.h"
#include "afxdialogex.h"
#include "dbmsDlg.h"
#include "TableLogic.h"
// CFieldDlg �Ի���

IMPLEMENT_DYNAMIC(CFieldDlg, CDialogEx)

CFieldDlg::CFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFieldDlg::IDD, pParent)
{

	m_strName = _T("");
	m_strDefault = _T("");
	m_strType = _T("");
	m_bNull = FALSE;
	m_bPrimary = FALSE;

}

CFieldDlg::~CFieldDlg()
{
}

void CFieldDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_Text(pDX, IDC_EDIT_DEFAULT, m_strDefault);
	DDX_Check(pDX, IDC_CHECK_NULL, m_bNull);
	DDX_Check(pDX, IDC_CHECK_PRIMARY, m_bPrimary);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
}

/*****************************************************
[FunctionName]	OnInitDialog
[Function]	Dialog initialization function
[Argument]	void
[ReturnedValue]	BOOL:TRUE if the operation is successful, otherwise FALSE
*****************************************************/
BOOL CFieldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Initializes the combo box
	m_cbType.InsertString(0, _T("INT"));
	m_cbType.InsertString(1, _T("VARCHAR"));
	m_cbType.InsertString(2, _T("BOOL"));
	m_cbType.InsertString(3, _T("DOUBLE"));
	m_cbType.InsertString(4, _T("DATATIME"));
	m_cbType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CFieldDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CFieldDlg::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFieldDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IFieldDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {E9FEAB3F-4868-45E1-979E-AA38A5B82479}
static const IID IID_IFieldDlg =
{ 0xE9FEAB3F, 0x4868, 0x45E1, { 0x97, 0x9E, 0xAA, 0x38, 0xA5, 0xB8, 0x24, 0x79 } };

BEGIN_INTERFACE_MAP(CFieldDlg, CDialogEx)
	INTERFACE_PART(CFieldDlg, IID_IFieldDlg, Dispatch)
END_INTERFACE_MAP()


// CFieldDlg ��Ϣ�������


void CFieldDlg::OnBnClickedButton2()
{
	CFileLogic fileLogic;
	CString tdfPath;
	CString dbName;
	CString tbName;
	CString fieldName;
	CString defaultValue;
	int datatype;
	CTableEntity tableE;
	CFieldEntity fieldE;
	GetDlgItemText(IDC_EDIT_NAME,fieldName);
	if(!fieldName.CompareNoCase(_T(""))){
		MessageBox(_T("Field name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	HWND hWnd=::FindWindow(NULL,_T("dbms"));
	CdbmsDlg* pWnd= (CdbmsDlg*)CdbmsDlg::FromHandle(hWnd);
	dbName = pWnd->GetChosenDBName();

	//�ж��Ƿ�ѡ�����ݿ�
	if(dbName.GetLength()==0){
	    MessageBox(_T("Database name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	//�ж��Ƿ�ѡ���
	tbName =  pWnd->GetChosenTBName();
	if(tbName.GetLength()==0){
	    MessageBox(_T("Table name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	pWnd->SendMessage(WM_SAVE_VALUES,NULL,0);
	tableE = pWnd->GetTableEntity();
	tdfPath = fileLogic.GetTbDefineFile(dbName, tableE.GetName());
	tableE.SetTdfPath(tdfPath);
	datatype = m_cbType.GetCurSel() + 1;
	fieldE.SetName(fieldName);
	fieldE.SetDataType(datatype);
	fieldE.SetDefault(defaultValue);

	CTableLogic tbLogic;
	try
	{
		// Add a field
		if(tbLogic.AddField(dbName, tableE, fieldE) == false)
		{
			throw new CAppException(_T("Failed to save table field file"));
		}
		//CFieldEntity* pField = m_pEditTable->AddField(field);
		//return pField;
		//CWnd *pWnd=CWnd::FindWindow(NULL,_T("dbms"));
		pWnd->SendMessage(WM_UPDATE_FIELDS,NULL,0);
	}
	catch(CAppException* e)
	{
		m_strError = e->GetErrorMessage();
		delete e;
		MessageBox(m_strError, _T("ERROR"));
	}
	DestroyWindow( );
	stop:;
}


void CFieldDlg::OnPaint()
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
