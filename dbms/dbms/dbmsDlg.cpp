
// dbmsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "dbmsDlg.h"
#include "afxdialogex.h"
#include "DBEntity.h"
#include "DBLogic.h"
#include "TableLogic.h"
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
	DDX_Control(pDX, IDC_LIST2, m_ctllist);
	DDX_Control(pDX, IDC_COMBO_TABLENAME, m_cbTBLName);
}

BEGIN_MESSAGE_MAP(CdbmsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CdbmsDlg::OnBnClickedOk)
	//ON_MESSAGE(WM_UPDATA_DIALOG, &CdbmsDlg::OnUpdateDialogDB)
	ON_MESSAGE(WM_UPDATE_DIALOG_DBN, &CdbmsDlg::OnUpdateDialogDbn)
	ON_MESSAGE(WM_UPDATE_FIELDS, &CdbmsDlg::OnUpdateField)
	ON_MESSAGE(WM_NEW_RECORD, &CdbmsDlg::OnNewRecord)
	ON_MESSAGE(WM_SAVE_VALUES, &CdbmsDlg::OnSaveValues)
	ON_MESSAGE(WM_NEW_TABLE, &CdbmsDlg::OnNewTable)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CdbmsDlg::OnLvnItemchangedList2)
	ON_CBN_SELCHANGE(IDC_COMBO_DBNAME, &CdbmsDlg::OnCbnSelchangeComboDbname)
	ON_CBN_SELCHANGE(IDC_COMBO_TABLENAME, &CdbmsDlg::OnCbnSelchangeComboTablename)
	//ON_BN_CLICKED(IDC_BUTTON1, &CdbmsDlg::OnBnClickedButton1)
	/*ON_BN_CLICKED(IDCANCEL, &CdbmsDlg::OnBnClickedCancel)*/
	ON_BN_CLICKED(IDC_SHOW_RECORD, &CdbmsDlg::OnBnClickedShowRecord)
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
	m_ctllist.ShowWindow(FALSE); //���ظÿؼ�
	DWORD dwStyle = m_ctllist.GetExtendedStyle();                    //����б��������ߣ�����
	//m_ctllist.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ   
    //m_ctllist.SetExtendedStyle(m_ctllist.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    dwStyle |= LVS_EX_FULLROWSELECT;            
    dwStyle |= LVS_EX_GRIDLINES;                
    m_ctllist.SetExtendedStyle(dwStyle);
    m_ctllist.InsertColumn(0,_T("Field "),LVCFMT_LEFT,60);              //����б��⣡������  �����80,40,90���������еĿ�ȡ�������LVCFMT_LEFT�������ö��뷽ʽ������
    m_ctllist.InsertColumn(1,_T("Data Type"),LVCFMT_LEFT,90);
    m_ctllist.InsertColumn(2,_T("Not Null"),LVCFMT_LEFT,80);
    m_ctllist.InsertColumn(3,_T("Primary key"),LVCFMT_LEFT,80);
    m_ctllist.InsertColumn(4,_T("Default Value"),LVCFMT_LEFT,100);

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
	    CPaintDC dc(this);
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


void CdbmsDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//CListCtrl m_List;
	////LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	////// TODO: �ڴ���ӿؼ�֪ͨ����������
 ////   pResult = 0;
 //   m_List.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ   
 //   m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
 //   m_List.InsertColumn(0,_T("Field"));  
 //   m_List.InsertColumn(1,_T("Data Type"));  
	//m_List.InsertColumn(2,_T("Not Null")); 
	//m_List.InsertColumn(3,_T("Primary Key"));
	//m_List.InsertColumn(4,_T("Default Value"));  
}


void CdbmsDlg::OnCbnSelchangeComboDbname()
{
	m_cbTBLName.ResetContent();
	CString dbName = _T("");
	CString tableFilePath = _T("");
	CFile file;
	GetDlgItemText(IDC_COMBO_DBNAME,dbName);
	dbName.TrimLeft();
	dbName.TrimRight();
	tableFilePath = m_fileLogic.GetTableFile(dbName);
	try{
		if(m_tableDao.IsValidFile(tableFilePath) == false){
			throw new CAppException(_T("No table in this database!"));
		}
		if (file.Open(tableFilePath, CFile::modeRead | CFile::shareDenyNone) == FALSE){
			throw new CAppException(_T("Failed to read the table file!"));
		}			
		TableBlock tempTBL;
		file.SeekToBegin();
		CTableEntity tableE;
		while(file.Read(&tempTBL, sizeof(TableBlock)) > 0){
			tableE.SetBlock(tempTBL);
			m_cbTBLName.AddString(tableE.GetName());
		}
	}catch(CAppException* e){
		error_msg = e->GetErrorMessage();
		delete e;
		MessageBox(error_msg);
	}
}

CString CdbmsDlg::GetChosenDBName(){
	CString dbName;
	GetDlgItemText(IDC_COMBO_DBNAME,dbName);
	dbName.TrimLeft();
	dbName.TrimRight();
	return dbName;
}

CString CdbmsDlg::GetChosenTBName(){
	CString tbName;
	GetDlgItemText(IDC_COMBO_TABLENAME,tbName);
	tbName.TrimLeft();
	tbName.TrimRight();
	return tbName;
}

CTableEntity CdbmsDlg::GetTableEntity(){
	CTableEntity tableE;
	CTableLogic tbLogic;
	CString dbName;
	CString tableName;
	GetDlgItemText(IDC_COMBO_DBNAME,dbName);
	GetDlgItemText(IDC_COMBO_TABLENAME,tableName);
	tableName.TrimLeft();
	tableName.TrimRight();
	dbName.TrimLeft();
	dbName.TrimRight();
	tableE.SetName(tableName);
	tbLogic.GetTable(tableE,dbName);
	return tableE;
}


void CdbmsDlg::OnCbnSelchangeComboTablename()
{
/****************************************************************************
	*
	*
	*m_cbTBLName.ResetContent();  ��Ŀ����已�ɾ��һ�У��������һ�����20����˼������Ϊʲô��õ�ֵ�ǿգ����������Ҿ����ˣ�����
	*
	*
	****************************************************************************/
	CString dbName = _T("");
	CString tbName = _T("");
	CString tableTdfPath = _T("");
	CString typeName;
	int type;
	m_tableEntity = GetTableEntity();
	CFile file;
	dbName = GetChosenDBName();
	tbName = GetChosenTBName();
	dbName.TrimLeft();
	dbName.TrimRight();
	tbName.TrimLeft();
	tbName.TrimRight();
	if(dbName.GetLength() == 0)
		goto stop;
	if(tbName.GetLength() == 0)
		goto stop;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 int nCols = m_ctllist.GetHeaderCtrl()->GetItemCount();
	 for (int j = 0;j < nCols;j++)
	{
		m_ctllist.DeleteColumn(0);
	}
	m_ctllist.InsertColumn(0,_T("Field "),LVCFMT_LEFT,60);              
	m_ctllist.InsertColumn(1,_T("Data Type"),LVCFMT_LEFT,90);
	m_ctllist.InsertColumn(2,_T("Not Null"),LVCFMT_LEFT,80);
	m_ctllist.InsertColumn(3,_T("Primary key"),LVCFMT_LEFT,80);
	m_ctllist.InsertColumn(4,_T("Default Value"),LVCFMT_LEFT,100);
	tableTdfPath = m_fileLogic.GetTbDefineFile(dbName,tbName);
	m_ctllist.DeleteAllItems(); // ȫ�����
	 m_ctllist.ShowWindow(TRUE);//��ʾ�ÿؼ�
	try{
		if(m_tableDao.IsValidFile(tableTdfPath) == false){
			throw new CAppException(_T(""));
		}
		if (file.Open(tableTdfPath, CFile::modeRead | CFile::shareDenyNone) == FALSE){
			throw new CAppException(_T("Failed to read the table file!"));
		}
		FieldBlock tempFB;
		file.SeekToBegin();
		CFieldEntity FE;
		int row = m_ctllist.GetItemCount();
		while(file.Read(&tempFB, sizeof(tempFB)) > 0){
			FE.SetBlock(tempFB);
			m_tableEntity.AddField(FE);
			//��ʾ�����
			type = FE.GetDataType();
			typeName = FE.GetTypeName(type);
			m_ctllist.InsertItem(row, FE.GetName());
			m_ctllist.SetItemText(row,1, typeName);
			m_ctllist.SetItemText(row,2, _T(""));
			m_ctllist.SetItemText(row,3, _T(""));
			m_ctllist.SetItemText(row,4, FE.GetDefault());
			row=row+1;
		}
	}catch(CAppException* e){
		error_msg = e->GetErrorMessage();
		delete e;
		if (error_msg != _T("")){
			MessageBox(error_msg);
		}		
	}
	stop:;
}

//
//void CdbmsDlg::OnBnClickedButton1()
//{
//}

afx_msg LRESULT CdbmsDlg::OnUpdateField(WPARAM wParam, LPARAM lParam){		
	CString dbName = _T("");
	int fieldNum = 0;	
	RECORDARR records;
	CRecordLogic recordLogic;
	dbName = GetChosenDBName();
	dbName.TrimLeft();
	dbName.TrimRight();

	OnCbnSelchangeComboTablename();

	fieldNum = m_tableEntity.GetFieldNum();
	records = GetRecordArray();
	if(fieldNum != 0 && records.size() != 0){
		recordLogic.AfterInsertField(dbName, m_tableEntity, records, vals);
	}
	vals.clear();
	return 0;
}

void CdbmsDlg::OnBnClickedShowRecord()
{
	CString dbName = GetChosenDBName();
	CString tbName = GetChosenTBName();
	CString savedData;
	int recordnum = 0;
	int fieldnum = 0;
	RECORDARR records;
		//�ж��Ƿ�ѡ�����ݿ�
	if(dbName.GetLength()==0){
	    MessageBox(_T("Database name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	//�ж��Ƿ�ѡ���
	if(tbName.GetLength()==0){
	    MessageBox(_T("Table name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	recordnum = m_tableEntity.GetRecordNum();
	m_recordLogic.SelectAll(m_tableEntity, records);
	fieldnum = m_tableEntity.GetFieldNum();
	int nCols = m_ctllist.GetHeaderCtrl()->GetItemCount();
	m_ctllist.DeleteAllItems();
	for (int j = 0;j < nCols;j++)
		{
			m_ctllist.DeleteColumn(0);
		}
	
	for (int i = 0; i < fieldnum; i++){
			CFieldEntity* pField = m_tableEntity.GetFieldAt(i);
			CString strFieldName = pField->GetName();
			m_ctllist.InsertColumn(i, strFieldName, LVCFMT_LEFT,60);  
	}
	
	for (int i = 0; i < recordnum; i++){
		for (int j = 0; j < fieldnum; j++){
			CFieldEntity* pField = m_tableEntity.GetFieldAt(j);
			CString strFieldName = pField->GetName();
			savedData = records[i]->Get(strFieldName);
			if(j == 0){
				m_ctllist.InsertItem(i, savedData);
			}else{
				m_ctllist.SetItemText(i ,j, savedData);
			}
		}
	}

	stop:;
}

RECORDARR CdbmsDlg::GetRecordArray(){
	CString dbName = GetChosenDBName();
	CString tbName = GetChosenTBName();
	RECORDARR records;
		//�ж��Ƿ�ѡ�����ݿ�
	if(dbName.GetLength()==0){
	    MessageBox(_T("Database name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	//�ж��Ƿ�ѡ���
	if(tbName.GetLength()==0){
	    MessageBox(_T("Table name cannot be empty"), _T("ERROR"));
		goto stop;
	}
	m_recordLogic.SelectAll(m_tableEntity, records);

stop:;
	return records;
}

afx_msg LRESULT CdbmsDlg::OnNewRecord(WPARAM wParam, LPARAM lParam){
	int recordNum = 0;
	recordNum = m_tableEntity.GetRecordNum() + 1;
	m_tableEntity.SetRecordNum(recordNum);
	return 0;
}
afx_msg LRESULT CdbmsDlg::OnSaveValues(WPARAM wParam, LPARAM lParam){
	CString dbName = _T("");
	int recordNum = 0;
	int fieldNum = 0;	
	RECORDARR records;
	CRecordLogic recordLogic;
	CRecordEntity* recordEntity;
	CFieldEntity* fieldEntity;

	dbName = GetChosenDBName();
	dbName.Trim();
	recordNum = m_tableEntity.GetRecordNum();
	fieldNum = m_tableEntity.GetFieldNum();
	if(fieldNum != 0 && recordNum != 0){
		records = GetRecordArray();
		for(int i = 0; i < recordNum; i++){
			recordEntity = records[i];
			for(int j = 0; j < fieldNum; j++){
				fieldEntity = m_tableEntity.GetFieldAt(j);
				CString strFieldName = fieldEntity->GetName();
				CString strVal = recordEntity->Get(strFieldName);
				vals.push_back(strVal);
			}
		}
	}
	return 0;
}

afx_msg LRESULT CdbmsDlg::OnNewTable(WPARAM wParam, LPARAM lParam){
	OnCbnSelchangeComboDbname();
	return 0;
}