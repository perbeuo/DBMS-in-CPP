#include "StdAfx.h"
#include "UserDao.h"

bool CUserDao::AddUser(const CString strFilePath, CUserEntity &ue)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}

		// Add user informaiton
		file.SeekToEnd();
		LoginBlock lb = ue.GetBlock();
		file.Write(&lb, sizeof(LoginBlock));

		// Close file
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to add field!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to add field!"));
	}
	return false;
}