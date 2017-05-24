#pragma once
#include "TableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"
#include "FieldEntity.h"
class CTableLogic
{
public:
	// 创建表
	bool CreateTable(const CString strDBName, CTableEntity &te);
	bool GetTable(CTableEntity &tb, CString dbName);
	//添加Field
	bool AddField(const CString strDBName, CTableEntity &te, CFieldEntity &fe);
private:
	CTableDao m_daoTable;	// 表操作类
	CFileLogic m_fileLogic;	// 文件逻辑类
};