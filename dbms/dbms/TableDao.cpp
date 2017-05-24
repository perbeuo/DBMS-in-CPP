#include "StdAfx.h"
#include "TableDao.h"


//������
bool CTableDao::Create(const CString strFilePath, CTableEntity &te)
{
	try
	{
		CFile file;
		// ���ļ�
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}
		// ����Ϣд���ļ�
		file.SeekToEnd();
		file.Write(&te.GetBlock(), sizeof(TableBlock));
		// �ļ��ر�
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


//�������ļ�·�����ļ��е��ļ�������ʱ�����ļ���
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



//�ж��ļ��Ƿ���Ч����
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

bool CTableDao::GetTable(const CString strFilepath, CTableEntity &tb){
	CString tableName;
	CFile file;
	try{
		tableName = tb.GetName();
		if(tableName.GetLength() == 0)
			return false;
		//ֻ����ʽ���ļ�
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
			return false;
		//��ȡ��Ϣ
		bool ifexist = false;
		TableBlock tempTBL;
		file.SeekToBegin();
		while(file.Read(&tempTBL, sizeof(TableBlock)) > 0){
			CString name = CCharHelper::ToString(tempTBL.name, sizeof(VARCHAR));
			//�ж��Ƿ�ΪҪ�������ݿ�
			if(name.CompareNoCase(tableName) == 0){
				tb.SetBlock(tempTBL);
				ifexist = true;
				break;
			}
		}
		file.Close();
		return ifexist;
	}catch(CException* e){
	e->Delete();
	throw new CAppException(_T("Failed to read the table file!"));
	}catch(...){
	throw new CAppException(_T("Failed to read the table file!"));
	}
	return false;
}

/**************************************************
[FunctionName]	AddField
[Function]	Add table field
[Argument]	const CString strFilePath: Path of the table definition file
		CFieldEntity &te: Field information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CTableDao::AddField(const CString strFilePath, CFieldEntity &fe)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}

		// Add field informaiton
		file.SeekToEnd();
		FieldBlock fb = fe.GetBlock();
		file.Write(&fb, sizeof(FieldBlock));

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


/**************************************************
[FunctionName]	AlterTable
[Function]	Alter the table information
[Argument]	const CString strFilePath: Path of the table definition file
		CTableEntity &te: Table information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false
**************************************************/
bool CTableDao::AlterTable(const CString strFilePath, CTableEntity &te)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(strFilePath, CFile::modeReadWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}

		file.SeekToBegin();
		long lOffset = file.GetPosition();

		// Query table information according to the table name, then alter the it
		bool flag = false;
		TableBlock tb;
		CString strName;// Table name
		while(file.Read(&tb, sizeof(TableBlock)) > 0)
		{
			strName = CCharHelper::ToString(tb.name, sizeof(VARCHAR));
			// Compare the table name
			if (te.GetName().Compare(strName) == 0)
			{
				file.Seek(lOffset, CFile::begin);// The file pointer points to the position of the previous record
				file.Write(&te.GetBlock(), sizeof(TableBlock));// Alter the table information
				flag = true;
				break;
			}
			lOffset = file.GetPosition();
		}

		// Close file
		file.Close();
		return flag;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to alert table!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to alert table!"));
	}
	return false;
}