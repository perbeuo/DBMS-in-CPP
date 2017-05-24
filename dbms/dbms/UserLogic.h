#pragma once
#include "UserEntity.h"
#include "UserDao.h"
#include "FileLogic.h"
class CUserLogic
{
public:
	bool AddUser(CUserEntity &ue);
private:
	CUserDao m_daoUser;	// 表操作类
	CFileLogic m_fileLogic;	// 文件逻辑类
};