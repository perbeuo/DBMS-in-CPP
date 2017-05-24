#pragma once
#include "TableEntity.h"
#include "RecordEntity.h"
#include "RecordDao.h"
#include "TableDao.h"
#include "FileLogic.h"
#include "FileHelper.h"
/**************************************************
[ClassName]	CRecordLogic
[Function]	Data record business logic class
**************************************************/
class CRecordLogic
{
public:
	// Create new rows in a table
	bool Insert(const CString strDBName, CTableEntity &te, CRecordEntity &re);
	bool SelectAll(CTableEntity &te, RECORDARR &data);
	bool CRecordLogic::AfterInsertField(const CString strDBName,CTableEntity &te, RECORDARR &data, std::vector<CString> vals);
private:
	CRecordDao m_daoRecord;	// Record data operation object
	CTableDao m_daoTable;	// Table data operation object
	CFileLogic m_fileLogic;	// File logic object
};