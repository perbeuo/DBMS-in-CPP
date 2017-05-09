#pragma once
#include "DBEntity.h"

//进行数据库操作
class CDBDao
{
public:
	// 创建数据库
	bool Create(const CString DBListFilePath, const CString strFilepath, CDBEntity db, bool bAppend = true);
	// 读取数据库信息
	bool GetDatabase(const CString strFilepath, CDBEntity &db);

	// 创建文件
	bool CreateFile(const CString strFileName);
	// 判断文件是否有效
	bool IsValidFile(const CString strPath);
};