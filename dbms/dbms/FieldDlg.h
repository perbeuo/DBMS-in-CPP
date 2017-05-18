#pragma once
#include "FieldEntity.h"

// CFieldDlg �Ի���

class CFieldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFieldDlg)

public:
	CFieldDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFieldDlg();

	virtual void OnFinalRelease();

public :
	CFieldEntity GetField();
// �Ի�������
	enum { IDD = IDD_FIELD_DIALOG };
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	CFieldEntity m_fieldEntity;	// Field information entity
public:
	CString m_strType;
	afx_msg void OnEnChangeEditName();
public:
	CString m_strName;		// Field name
	CComboBox m_cbType;		// Type
	CString m_strDefault;	// Defult value
	BOOL m_bNull;			// Whether is null
	BOOL m_bPrimary;		// Whether is primary key
	afx_msg void OnBnClickedButton2();
	CString m_strError;
};
