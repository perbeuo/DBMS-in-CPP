#pragma once
#define WM_UPDATE_DIALOG_DBN WM_USER + 77

// CCDBDlg 对话框

class CCDBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCDBDlg)

public:
	CCDBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCDBDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_CREATE_DATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDbinfoOk();
	afx_msg void OnBnClickedDbCancel();
	afx_msg void OnPaint();
};
