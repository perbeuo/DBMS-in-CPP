
// dbmsDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "FileLogic.h"
#include "TableEntity.h"
#include "RecordLogic.h"
#define WM_UPDATE_DIALOG_DBN WM_USER + 77 //新建数据库后刷新列表
#define WM_UPDATE_FIELDS WM_USER + 78 //新建field后刷新listcontrol
#define WM_NEW_RECORD WM_USER + 79 //新建record后刷新listcontrol
#define WM_SAVE_VALUES WM_USER + 80 //保存现有recordds到vector
#define WM_NEW_TABLE WM_USER + 81 //新建table后刷新列表
// CdbmsDlg 对话框
class CdbmsDlg : public CDialogEx
{
// 构造
public:
	CdbmsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DBMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFileLogic m_fileLogic;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdateDialogDB();
	DECLARE_MESSAGE_MAP()
	void ReadStringCharToUnicode(CString &str);
public:
	HACCEL hAccel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	CComboBox m_cbDBName;
	CComboBox m_cbTBLName;
protected:
	afx_msg LRESULT OnUpdateDialogDbn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateField(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewRecord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSaveValues(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewTable(WPARAM wParam, LPARAM lParam);
	CTableEntity m_tableEntity;
	CRecordLogic m_recordLogic;
	std::vector<CString> vals;
	CString error_msg;
	CTableDao m_tableDao;
public:
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ctllist;
	afx_msg void OnCbnSelchangeComboDbname();
	CString GetChosenDBName();
	CString GetChosenTBName();
	CTableEntity GetTableEntity();
	afx_msg void OnCbnSelchangeComboTablename();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedShowRecord();
	RECORDARR GetRecordArray();
};
