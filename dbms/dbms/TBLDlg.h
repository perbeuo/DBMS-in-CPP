#pragma once
#include "DBEntity.h"
#include "TableEntity.h"

// CTBLDlg �Ի���

class CTBLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTBLDlg)

private:
	CDBEntity m_dbEntity;	// Database entity object
	CString m_strError;		// Exception information
	TABLEARR m_arrTable;	// Table array
public:
	CTBLDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTBLDlg();
	
	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_CREATE_TABLE};

public:
	 CString TableName;
	 CComboBox m_cbDBNameTB;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeDbname();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEnChangeTablename();
};
