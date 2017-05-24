#include "StdAfx.h"
#include "RecordLogic.h"

/**************************************************
[FunctionName]	Insert
[Function]	Create new rows in a table
[Argument]	CTableEntity &te: Table information entity
		CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CRecordLogic::Insert(const CString strDBName,CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString recordPath;
		recordPath = m_fileLogic.GetTbRecordFile(strDBName, te.GetName());
		te.SetTrdPath(recordPath);
		CString strTrdPath = te.GetTrdPath();
		if (CFileHelper::IsValidFile(strTrdPath) == false)
		{
			if(CFileHelper::CreateFile(strTrdPath) == false)
			{
				return false;
			}
		}

		// Insert a record
		if (m_daoRecord.Insert(te, re) == false)
		{
			return false;
		}

		// Modify record number
		int nRecordNum = te.GetRecordNum()+1;
		te.SetRecordNum(nRecordNum);

		// Alert table information
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
		if(m_daoTable.AlterTable(strTableFile, te) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}

bool CRecordLogic::SelectAll(CTableEntity &te, RECORDARR &data)
{
	try
	{
		// Read record
		if (m_daoRecord.SelectAll(te, data) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}

bool CRecordLogic::AfterInsertField(const CString strDBName,CTableEntity &te, RECORDARR &data, std::vector<CString> vals){
	try{
		CString recordPath;
		recordPath = m_fileLogic.GetTbRecordFile(strDBName, te.GetName());
		if (CFileHelper::IsValidFile(recordPath) == false)
		{
			if(CFileHelper::CreateFile(recordPath) == false)
			{
				return false;
			}
		}
		if (m_daoRecord.AfterInsertField(te, data, vals) == false)
		{
			return false;
		}
		return true;
	}catch(CAppException *e){
		throw e;
	}
	return false;
}
