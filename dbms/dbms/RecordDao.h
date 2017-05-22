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
	// Insert record
	bool Insert(CTableEntity &te, CRecordEntity &re);
};