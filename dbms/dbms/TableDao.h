#pragma once
#include "TableEntity.h"
#include "FieldEntity.h"
//创建表功能类
class CTableDao
{
public:
	// 创建保存表信息
	bool Create(const CString strFilePath, CTableEntity &te);

	// 创建文件
	bool CreateFile(const CString strFileName);
	//判断文件有效性
	bool IsValidFile(const CString strPath);
	//get table
	bool GetTable(const CString strFilepath, CTableEntity &db);
	//添加field
	bool AddField(const CString strFilePath, CFieldEntity &fe);
};