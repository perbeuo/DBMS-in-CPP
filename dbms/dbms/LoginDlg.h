#pragma once
#include "afxwin.h"
// CLoginDlg �Ի���

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
//	CString m_UserName;
//	CString m_UserPassword;
//	CEdit m_UserPassword1;
	CString m_UserPassword;
	CString m_UserName;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedRegister();
};
