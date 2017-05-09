#include "StdAfx.h"
#include "TableLogic.h"

//´´½¨±í
bool CTableLogic::CreateTable(const CString strDBName, CTableEntity &te)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
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