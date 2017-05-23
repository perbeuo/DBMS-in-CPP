#pragma once
#include "FileLogic.h"

// CRecordDlg 对话框

class CRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordDlg)

public:
	CRecordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecordDlg();
	virtual void OnFinalRelease();
	CListCtrl m_ctllistRecord;
	CEdit m_edit;
	int m_Row;
	int m_Col;
// 对话框数据
	enum { IDD = IDD_INSERT_RECORD };
private:
    CRecordEntity m_recordEntity;	// Record the object of view
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CFileLogic m_fileLogic;
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusInputRecord();
	afx_msg void OnBnClickedOutputRecord();
	afx_msg void OnPaint();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
