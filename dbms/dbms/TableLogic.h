#pragma once
#include "TableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"


class CTableLogic
{
public:
	// ������
	bool CreateTable(const CString strDBName, CTableEntity &te);

private:
	CTableDao m_daoTable;	// �������
	CFileLogic m_fileLogic;	// �ļ��߼���
};