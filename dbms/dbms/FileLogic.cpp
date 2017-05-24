#include "StdAfx.h"
#include "FileLogic.h"

	// 得到数据库描述文件的位置
CString CFileLogic::GetDBFile(const CString strDBName){
	CString filePath = _T("");
	CString DBNameLogicPath = strDBName + _T(".db");
	try{
		filePath = GetAbsolutePath(DBNameLogicPath);
	}catch (CAppException* e)
	{
		throw e;
	}
	return filePath;
}

	// 得到数据库文件夹的位置
CString CFileLogic::GetDBFolder(const CString strDBName){
	CString fileFolder = _T("");
	try{
		fileFolder.Format(_T("data\\%s"), strDBName);
		fileFolder = GetAbsolutePath(fileFolder);
	}catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the database folder!"));
	}
	return fileFolder;
}

	// 将相对路径转化为绝对路径
CString CFileLogic::GetAbsolutePath(const CString strRelativePath){
	CString strFolder = _T("");
	try
	{
		// Get the absolute path of the executable file
		wchar_t acExeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, acExeFullPath, MAX_PATH);
		CString strFolder = acExeFullPath;
		// Get the folder path of the executable file
		int pos = strFolder.ReverseFind('\\');
		strFolder = strFolder.Left(pos+1);
		// Return absolute path
		return strFolder + strRelativePath;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to get the path of file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of file!"));
	}

	return strFolder;
}

CString CFileLogic::GetDBListFile(void){
	CString filePath = _T("");
	filePath = _T("DBList.dbl");
	try{
		filePath = GetAbsolutePath(filePath);
	}catch (CAppException* e)
	{
		throw e;
	}
	return filePath;
}

//获得表文件
CString CFileLogic::GetTableFile(const CString strDBName)
{
	CString strPath = _T("");
	try
	{
		// 获得表描述文件的绝对路径 (*.tb)
		strPath.Format(_T("data\\%s\\%s.tb"), strDBName, strDBName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get tb file path!"));
	}
	return strPath;
}

/**************************************************
[FunctionName]	GetTbDefineFile
[Function]	Get the path of the table definition file
[Argument]	const CString strDBName: Database name
		const CString strTableName: Table name
[ReturnedValue]	CString: Absolute path of the table definition file
**************************************************/
CString CFileLogic::GetTbDefineFile(const CString strDBName, const CString strTableName)
{
	CString strPath = _T("");
	try
	{
		strPath.Format(_T("data\\%s\\%s.tdf"), strDBName, strTableName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the table definition file"));
	}

	return strPath;
}

CString CFileLogic::GetTbRecordFile(const CString strDBName, const CString strTableName)
{
	CString strPath = _T("");
	try
	{
		strPath.Format(_T("data\\%s\\%s.trd"), strDBName, strTableName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the table record file!"));
	}

	return strPath;
}