
// dbms.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


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

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSystemExit();
	afx_msg void OnHelpAboutdbms();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CdbmsApp theApp;