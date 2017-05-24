#include "StdAfx.h"
#include "UserLogic.h"
#include "FileHelper.h"
#include "UserDao.h"
bool CUserLogic::AddUser(CUserEntity &ue)
{	
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		const CString Path = ue.GetPath();
		if (CFileHelper::IsValidFile(Path) == false)
		{
			if(CFileHelper::CreateFile(Path) == false)
			{
				return false;
			}
		}
		// Save user information
		if(m_daoUser.AddUser(Path, ue) == false)
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
