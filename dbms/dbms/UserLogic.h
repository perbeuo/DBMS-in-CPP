#pragma once
#include "UserEntity.h"
#include "UserDao.h"
#include "FileLogic.h"
class CUserLogic
{
public:
	bool AddUser(CUserEntity &ue);
private:
	CUserDao m_daoUser;	// �������
	CFileLogic m_fileLogic;	// �ļ��߼���
};