#pragma once
#include "TableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"
#include "FieldEntity.h"

class CTableLogic
{
public:
	// ������
	bool CreateTable(const CString strDBName, CTableEntity &te);
	bool GetTable(CTableEntity &tb, CString dbName);
	//���Field
	bool AddField(const CString strDBName, CTableEntity &te, CFieldEntity &fe);
private:
	CTableDao m_daoTable;	// �������
	CFileLogic m_fileLogic;	// �ļ��߼���
};