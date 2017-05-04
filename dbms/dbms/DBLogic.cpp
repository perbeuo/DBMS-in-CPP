#include "StdAfx.h"
#include "DBLogic.h"

//创建数据库
bool CDBLogic::CreateDatabase(CDBEntity &db){
	try{
		//判断该数据库是否存在，若不存在则创建
		CString DBFile = m_fileLogic.GetDBFile();
		if(m_daoDB.IsValidFile(DBFile) == false){
			if(m_daoDB.CreateFile(DBFile) == false){
				return false;
			}
		}
		if (m_daoDB.GetDatabase(DBFile, db) == true)
		{
			return false;
		}
		CString DBFolder = m_fileLogic.GetDBFolder(db.GetName());
		db.SetFilepath(DBFolder);
		if(m_daoDB.Create(DBFile, db) == false)
		{
			return false;
		}
	}catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create database!"));
	}

	return true;
}

	// Query database
bool CDBLogic::GetDatabase(CDBEntity &db){
	try
	{
		return m_daoDB.GetDatabase(m_fileLogic.GetDBFile(), db);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create database!"));
	}
	return false;
}