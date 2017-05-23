
// dbms.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "RecordEntity.h"
#include "LoginDlg.h"
// CdbmsApp:
// �йش����ʵ�֣������ dbms.cpp
//

class CdbmsApp : public CWinApp
{
public:
	CdbmsApp();

// ��д
public:
	virtual BOOL InitInstance();
public:  
    CLoginDlg m_loginDlg;
// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSystemExit();
	afx_msg void OnHelpAboutdbms();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDatabaseCreatedatabase();
	afx_msg void OnTableCreatetable();
	afx_msg void OnFieldAddfield();
	afx_msg void OnRecordInsertrecord();
};

extern CdbmsApp theApp;