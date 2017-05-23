// RecordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dbms.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include "dbmsDlg.h"

// CRecordDlg 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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



// 注意: 我们添加 IID_IRecordDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

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
		//获得所需要的数据库与表名
	    dbName = pWnd->GetChosenDBName();
	    tbName = pWnd->GetChosenTBName();
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
			//显示到表格
			m_ctllistRecord.InsertItem(row, FE.GetName());
			row=row+1;
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
    m_Row = pNMListView->iItem;//获得选中的行  
    m_Col = pNMListView->iSubItem;//获得选中列  
  
  
    if   (pNMListView->iSubItem != 0) //如果选择的是子项;  
    {  
        m_ctllistRecord.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；  
        m_edit.SetParent(&m_ctllistRecord);//转换坐标为列表框中的坐标  
        m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
        m_edit.SetWindowText(m_ctllistRecord.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；  
        m_edit.ShowWindow(SW_SHOW);//显示Edit控件；  
        m_edit.SetFocus();//设置Edit焦点  
        m_edit.ShowCaret();//显示光标  
        m_edit.SetSel(-1);//将光标移动到最后  
    }  
  
  
    *pResult = 0;  
	}


	void CRecordDlg::OnEnKillfocusInputRecord()
	{
		CString tem;  
	m_edit.GetWindowText(tem);    //得到用户输入的新的内容  
	m_ctllistRecord.SetItemText(m_Row,m_Col,tem);   //设置编辑框的新内容  
	m_edit.ShowWindow(SW_HIDE);                //应藏编辑框  
	}


	void CRecordDlg::OnBnClickedOutputRecord()
	{
		CString FieldValue;
		CString Field;
		int row = m_ctllistRecord.GetItemCount();
		//获得第二列的值
		for(int i = 0; i < row; i++){
			Field=m_ctllistRecord.GetItemText(i,0);
			FieldValue = m_ctllistRecord.GetItemText(i,1);
		    m_recordEntity.Put(Field,FieldValue);
		}

	}


	void CRecordDlg::OnPaint()
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


	void CRecordDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码

		NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;  
	  CRect rc;  
	  m_Row = pNMListView->iItem;//获得选中的行  
	 m_Col = pNMListView->iSubItem;//获得选中列  
  
  
    if   (pNMListView->iSubItem != 0) //如果选择的是子项;  
    {  
        m_ctllistRecord.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；  
        m_edit.SetParent(&m_ctllistRecord);//转换坐标为列表框中的坐标  
        m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
        m_edit.SetWindowText(m_ctllistRecord.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；  
        m_edit.ShowWindow(SW_SHOW);//显示Edit控件；  
        m_edit.SetFocus();//设置Edit焦点  
        m_edit.ShowCaret();//显示光标  
        m_edit.SetSel(-1);//将光标移动到最后  
    }  
  
  
		*pResult = 0;
	}
