#include "StdAfx.h"
#include "TableDao.h"


//创建表
bool CTableDao::Create(const CString strFilePath, CTableEntity &te)
{
	try
	{
		CFile file;
		// 打开文件
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}
		// 表信息写入文件
		file.SeekToEnd();
		file.Write(&te.GetBlock(), sizeof(TableBlock));
		// 文件关闭
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to add table information!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to add table information!"));
	}

	return false;
}


//创建表文件路径，文件夹的文件不存在时创建文件夹
bool CTableDao::CreateFile(const CString strFileName)
{
	try
	{
		// Create all the folder of the fiel path
		for (int i = 0; i < strFileName.GetLength(); i++)
		{
			if ( (_T('\\') == strFileName.GetAt(i)
				|| _T('/') == strFileName.GetAt(i))
				&& 2 != i
				)
			{
				CString strDirectory;
				strDirectory = strFileName.Left(i);
				if(!CreateDirectory(strDirectory, NULL) && 183 != GetLastError())
				{
					return false;
				}
			}
		}

		// Create file
		CFile file;
		if (!file.Open(strFileName, CFile::modeCreate))
		{
			return false;
		}
		file.Close();

		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to create file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create file!"));
	}

	return false;
}



//判断文件是否有效创建
bool CTableDao::IsValidFile(const CString strPath)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strPath, CFile::modeRead | CFile::shareDenyNone) == TRUE)
		{
			// Close file
			file.Close();
			return true;
		}
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to open file"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to open file"));
	}
	return false;
}