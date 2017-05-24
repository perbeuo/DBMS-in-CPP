#include "StdAfx.h"
#include "UserEntity.h"

// Constructor
CUserEntity::CUserEntity(void)
{
	m_strName = _T("");			// Field name
	m_strPassword = _T("");    // default value
}

// Constructor
CUserEntity::CUserEntity(CString strName,CString strPassword)
{
	m_strName = strName;
	m_strPassword= strPassword;
}

// Copy constructor
CUserEntity::CUserEntity(CUserEntity& ue)
{
	m_strName = ue.m_strName;
	m_strPassword = ue.m_strPassword;
}


// Destructor
CUserEntity::~CUserEntity(void)
{
}

void CUserEntity::SetBlock(LoginBlock lb)
{
	m_strName = CCharHelper::ToString(lb.user, sizeof(VARCHAR));
	m_strPassword = CCharHelper::ToString(lb.password, sizeof(VARCHAR));
}

LoginBlock CUserEntity::GetBlock()
{
	LoginBlock lb;
	memset(&lb, 0, sizeof(LoginBlock));

	CCharHelper::ToChars(lb.user, m_strName, sizeof(VARCHAR));
    CCharHelper::ToChars(lb.password, m_strPassword, sizeof(VARCHAR));
	return lb;
}

// Set function
void CUserEntity::SetName(CString strName)
{
	m_strName = strName;
}

void CUserEntity::SetPassword(CString strPassword)
{
	m_strPassword = strPassword;
}

void CUserEntity::SetPath( const CString strPath )
{
	m_strPath = strPath;
}

// Get function
CString CUserEntity::GetName()
{
	return m_strName;
}

CString CUserEntity::GetPassword()
{
	return m_strPassword;
}
CString CUserEntity::GetPath()
{
	return m_strPath;
}


