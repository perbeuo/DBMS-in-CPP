#pragma once
#include "UserEntity.h"
class CUserDao
{
public : 
	bool AddUser(const CString strFilePath, CUserEntity &ue);

};