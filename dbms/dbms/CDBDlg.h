#pragma once
#define WM_UPDATE_DIALOG_DBN WM_USER + 77

// CCDBDlg �Ի���

class CCDBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCDBDlg)

public:
	CCDBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCDBDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_CREATE_DATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDbinfoOk();
	afx_msg void OnBnClickedDbCancel();
	afx_msg void OnPaint();
};
