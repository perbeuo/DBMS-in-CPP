#include "StdAfx.h"
#include "TableLogic.h"
#include "FileHelper.h"
//´´½¨±í
bool CTableLogic::CreateTable(const CString strDBName, CTableEntity &te)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
		CString tdfPath;
		tdfPath = m_fileLogic.GetTbDefineFile(strDBName, te.GetName());
		te.SetTdfPath(tdfPath);
		if (m_daoTable.IsValidFile(strTableFile) == false)
		{
			if(m_daoTable.CreateFile(strTableFile) == false)
			{
				return false;
			}
		}

		// Create table and save table information
		if(m_daoTable.Create(strTableFile, te) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException* e)
	{
		throw e;
	}

	return false;
}
	// Query table
bool CTableLogic::GetTable(CTableEntity &tb, CString dbName){
	try
	{
		CString tableFilePath = _T("");
		tableFilePath = m_fileLogic.GetTableFile(dbName);
		return m_daoTable.GetTable(tableFilePath, tb);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to load table!"));
	}
	return false;
}

/**************************************************
[FunctionName]	AddField
[Function]	Add table field
[Argument]	const CString strDBName: Database name
CTableEntity &te: Table information entity
		CFieldEntity &fe: Field entity
[ReturnedValue]	bool: True if adds field successfully, otherwise false
**************************************************/
bool CTableLogic::AddField(const CString strDBName, CTableEntity &te, CFieldEntity &fe)
{	
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTdfPath = te.GetTdfPath();
		if (CFileHelper::IsValidFile(strTdfPath) == false)
		{
			if(CFileHelper::CreateFile(strTdfPath) == false)
			{
				return false;
			}
		}

		// Save field information
		if(m_daoTable.AddField(strTdfPath, fe) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException* e)
	{
		throw e;
	}

	return false;
}


