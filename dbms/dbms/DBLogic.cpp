#include "StdAfx.h"
#include "DBLogic.h"

//�������ݿ�
bool CDBLogic::CreateDatabase(CDBEntity &db){
	try{
		//�жϸ����ݿ��Ƿ���ڣ����������򴴽�
		CString DBFile = m_fileLogic.GetDBFile(_T("test"));
		CString DBListFile = m_fileLogic.GetDBListFile();
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
		if(m_daoDB.Create(DBListFile, DBFile, db) == false)
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
		return m_daoDB.GetDatabase(m_fileLogic.GetDBFile(_T("test")), db);
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