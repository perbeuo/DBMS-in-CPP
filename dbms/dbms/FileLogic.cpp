#include "StdAfx.h"
#include "FileLogic.h"

	// �õ����ݿ������ļ���λ��
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

	// �õ����ݿ��ļ��е�λ��
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

	// �����·��ת��Ϊ����·��
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

//��ñ��ļ�
CString CFileLogic::GetTableFile(const CString strDBName)
{
	CString strPath = _T("");
	try
	{
		// ��ñ������ļ��ľ���·�� (*.tb)
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