
// dbmsDlg.h : ͷ�ļ�
//

#pragma once
#define WM_UPDATE_DIALOG_DBN WM_USER + 77

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
protected:
	afx_msg LRESULT OnUpdateDialogDbn(WPARAM wParam, LPARAM lParam);
};
