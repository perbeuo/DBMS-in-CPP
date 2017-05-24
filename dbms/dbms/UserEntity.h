#pragma once
#include <afxdisp.h>        // MFC Automation classes
#include <afx.h>

class CUserEntity : public CObject
{
public:
	// Constructor
	CUserEntity(CString strName, CString strPassword);
	CUserEntity(CUserEntity& ue);
	CUserEntity(void);
	~CUserEntity(void);
	// Class and block conversion function
	LoginBlock GetBlock();
	void SetBlock(LoginBlock lb);

	// Set function
	void SetName(CString strName);
	void SetPassword(CString strPassword);
	void SetPath( const CString strPath );
	// Get function
	CString GetName();
	CString GetPassword();
	CString GetPath();

private:
	CString m_strName;  //用户名和密码
	CString m_strPassword;
	CString m_strPath;
};
