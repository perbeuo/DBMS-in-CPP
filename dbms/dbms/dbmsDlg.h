
// dbmsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "FileLogic.h"
#include "TableEntity.h"
#include "RecordLogic.h"
#define WM_UPDATE_DIALOG_DBN WM_USER + 77 //�½����ݿ��ˢ���б�
#define WM_UPDATE_FIELDS WM_USER + 78 //�½�field��ˢ��listcontrol
#define WM_NEW_RECORD WM_USER + 79 //�½�record��ˢ��listcontrol
#define WM_SAVE_VALUES WM_USER + 80 //��������recordds��vector
#define WM_NEW_TABLE WM_USER + 81 //�½�table��ˢ���б�
// CdbmsDlg �Ի���
class CdbmsDlg : public CDialogEx
{
// ����
public:
	CdbmsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DBMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CFileLogic m_fileLogic;
	// ���ɵ���Ϣӳ�亯��
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
