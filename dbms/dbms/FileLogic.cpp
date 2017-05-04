#include "StdAfx.h"
#include "FileLogic.h"

	// �õ����ݿ������ļ���λ��
CString CFileLogic::GetDBFile(void){
	CString filePath = _T("");
	try{
		filePath = GetAbsolutePath(_T("test.db"));
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