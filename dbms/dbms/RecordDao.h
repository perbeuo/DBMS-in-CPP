#pragma once
#include "TableEntity.h"
#include "RecordEntity.h"
#include "TimeHelper.h"
/**************************************************
[ClassName]	CRecordDao
[Function]	Record data operation class
**************************************************/
class CRecordDao
{
public:
	// Create new rows in a table
	bool Insert(CTableEntity &te, CRecordEntity &re);
	// Retrieve all records from a specified table
	int SelectAll(CTableEntity &te, RECORDARR &data);

	bool AfterInsertField(CTableEntity &te, RECORDARR records, std::vector<CString> vals);
private:
	// Save record
	bool Write(CFile &file, CTableEntity &te, CRecordEntity &re);
	// Get record
	bool Read(CFile &file, CTableEntity &te, CRecordEntity &re);

	bool Write(CFile &file, CTableEntity &te, std::vector<CString> vals, long offset);
};