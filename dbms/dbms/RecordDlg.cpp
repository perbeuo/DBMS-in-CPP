// RecordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dbms.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include "dbmsDlg.h"

// CRecordDlg �Ի���

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecordDlg::IDD, pParent)
{

	EnableAutomation();

}

CRecordDlg::~CRecordDlg()
{
}

void CRecordDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctllistRecord);
	DDX_Control(pDX, IDC_INPUT_RECORD, m_edit);
}

BEGIN_MESSAGE_MAP(CRecordDlg, CDialogEx)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST1, &CRecordDlg::OnNMRDblclkList1)
	ON_EN_KILLFOCUS(IDC_INPUT_RECORD, &CRecordDlg::OnEnKillfocusInputRecord)
	ON_BN_CLICKED(IDC_OUTPUT_RECORD, &CRecordDlg::OnBnClickedOutputRecord)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CRecordDlg::OnNMDblclkList1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRecordDlg, CDialogEx)
END_DISPATCH_MAP()



// ע��: ������� IID_IRecordDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {4E394C38-73EC-43E4-9E39-BB070DB9D934}
static const IID IID_IRecordDlg =
{ 0x4E394C38, 0x73EC, 0x43E4, { 0x9E, 0x39, 0xBB, 0x7, 0xD, 0xB9, 0xD9, 0x34 } };

BEGIN_INTERFACE_MAP(CRecordDlg, CDialogEx)
	INTERFACE_PART(CRecordDlg, IID_IRecordDlg, Dispatch)
END_INTERFACE_MAP()
	BOOL CRecordDlg::OnInitDialog()
	{
		CDialogEx::OnInitDialog();
		m_edit.ShowWindow(SW_HIDE);
		CFile file;
		CString dbName;
	    CString tbName;
		CString tableTdfPath = _T("");
        HWND hWnd=::FindWindow(NULL,_T("dbms"));
	    CdbmsDlg* pWnd= (CdbmsDlg*)CdbmsDlg::FromHandle(hWnd);
		//�������Ҫ�����ݿ������
	    dbName = pWnd->GetChosenDBName();
	    tbName = pWnd->GetChosenTBName();

		m_tableEntity.SetName(tbName);
		m_tableLogic.GetTable(m_tableEntity, dbName);
		m_ctllistRecord.SetExtendedStyle(m_ctllistRecord.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
		tableTdfPath = m_fileLogic.GetTbDefineFile(dbName,tbName);
	try{
		if (file.Open(tableTdfPath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
			throw new CAppException(_T("Failed to read the table file!"));
		FieldBlock tempFB;
		file.SeekToBegin();
		CFieldEntity FE;
		m_ctllistRecord.InsertColumn(0,_T("Field "),LVCFMT_LEFT,60);
		m_ctllistRecord.InsertColumn(1,_T("Value"),LVCFMT_LEFT,100);
		int row = m_ctllistRecord.GetItemCount();
		while(file.Read(&tempFB, sizeof(tempFB)) > 0){
			FE.SetBlock(tempFB);
			//��ʾ�����
			m_ctllistRecord.InsertItem(row, FE.GetName());
			row=row+1;
			m_tableEntity.AddField(FE);
			//m_tableEntity.AddFieldNum();
		}
	}catch(CAppException e){
		MessageBox(_T("Failed to load table"));
	}

		
		//m_ctllistRecord.SetItemText(0,1, typeName);
		return TRUE;  // return TRUE unless you set the focus to a control

	}

	void CRecordDlg::OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
	{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;  
    CRect rc;  
    m_Row = pNMListView->iItem;//���ѡ�е���  
    m_Col = pNMListView->iSubItem;//���ѡ����  
  
  
    if   (pNMListView->iSubItem != 0) //���ѡ���������;  
    {  
        m_ctllistRecord.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//��������RECT��  
        m_edit.SetParent(&m_ctllistRecord);//ת������Ϊ�б���е�����  
        m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
        m_edit.SetWindowText(m_ctllistRecord.GetItemText(m_Row,m_Col));//���������е�ֵ����Edit�ؼ��У�  
        m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
        m_edit.SetFocus();//����Edit����  
        m_edit.ShowCaret();//��ʾ���  
        m_edit.SetSel(-1);//������ƶ������  
    }  
  
  
    *pResult = 0;  
	}


	void CRecordDlg::OnEnKillfocusInputRecord()
	{
		CString tem;  
	m_edit.GetWindowText(tem);    //�õ��û�������µ�����  
	m_ctllistRecord.SetItemText(m_Row,m_Col,tem);   //���ñ༭���������  
	m_edit.ShowWindow(SW_HIDE);                //Ӧ�ر༭��  
	}


	void CRecordDlg::OnBnClickedOutputRecord()
	{
		CString FieldValue;
		CString Field;
		CString dbName;
		CString tbName;

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
		int row = m_ctllistRecord.GetItemCount();
		//��õڶ��е�ֵ
		for(int i = 0; i < row; i++){
			Field=m_ctllistRecord.GetItemText(i,0);
			FieldValue = m_ctllistRecord.GetItemText(i,1);
		    m_recordEntity.Put(Field,FieldValue);
		}
		m_recordLogic.Insert(dbName, m_tableEntity, m_recordEntity);
		pWnd->SendMessage(WM_NEW_RECORD,NULL,0);
		DestroyWindow( );
		stop:;
	}


	void CRecordDlg::OnPaint()
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


	void CRecordDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: �ڴ���ӿؼ�֪ͨ����������

		NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;  
	  CRect rc;  
	  m_Row = pNMListView->iItem;//���ѡ�е���  
	 m_Col = pNMListView->iSubItem;//���ѡ����  
  
  
    if   (pNMListView->iSubItem != 0) //���ѡ���������;  
    {  
        m_ctllistRecord.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//��������RECT��  
        m_edit.SetParent(&m_ctllistRecord);//ת������Ϊ�б���е�����  
        m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
        m_edit.SetWindowText(m_ctllistRecord.GetItemText(m_Row,m_Col));//���������е�ֵ����Edit�ؼ��У�  
        m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
        m_edit.SetFocus();//����Edit����  
        m_edit.ShowCaret();//��ʾ���  
        m_edit.SetSel(-1);//������ƶ������  
    }  
  
  
		*pResult = 0;
	}
