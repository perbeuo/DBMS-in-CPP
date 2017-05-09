#pragma once
#include "TableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"


class CTableLogic
{
public:
	// 创建表
	bool CreateTable(const CString strDBName, CTableEntity &te);

private:
	CTableDao m_daoTable;	// 表操作类
	CFileLogic m_fileLogic;	// 文件逻辑类
};