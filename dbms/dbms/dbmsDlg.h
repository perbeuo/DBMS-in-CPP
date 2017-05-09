
// dbmsDlg.h : 头文件
//

#pragma once
#define WM_UPDATE_DIALOG_DBN WM_USER + 77

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
protected:
	afx_msg LRESULT OnUpdateDialogDbn(WPARAM wParam, LPARAM lParam);
};
