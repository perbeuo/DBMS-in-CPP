#pragma once
#include "DBEntity.h"
#include "DBDao.h"
#include "FileLogic.h"

class CDBLogic
{
public:
	// Create database
	bool CreateDatabase(CDBEntity &db);
	// Query database
	bool GetDatabase(CDBEntity &db);

private:
	CDBDao m_daoDB;			// 数据库操作类
	CFileLogic m_fileLogic;	// 文件处理类
};