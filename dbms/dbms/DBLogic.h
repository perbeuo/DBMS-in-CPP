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
	CDBDao m_daoDB;			// ���ݿ������
	CFileLogic m_fileLogic;	// �ļ�������
};