#include "StdAfx.h"
#include "RecordDao.h"
#include "vector"
int CRecordDao::SelectAll(CTableEntity &te, RECORDARR &data)
{
	try
	{		
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeRead | CFile::shareDenyNone) == FALSE)
		{
			return 0;
		}
		// The cursor to the end of the file
		file.SeekToBegin();

		int nCount = 0;
		while (true)
		{
			// Get the value to write
			CRecordEntity* pRecordEntity = new CRecordEntity();
			if (Read(file, te, *pRecordEntity) == true)
			{
				data.push_back(pRecordEntity);
				nCount++;
			}
			else
			{
				delete pRecordEntity;
				pRecordEntity = NULL;
				break;// Exit the while loop
			}
		}
		// Close file
		file.Close();

		return nCount;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to query record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to query record!"));
	}

	return 0;	
}

bool CRecordDao::Insert(CTableEntity &te, CRecordEntity &re)
{
	try
	{
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}
		// The cursor to the end of the file
		file.SeekToEnd();

		// Save record
		Write(file, te, re);

		// Close file
		file.Close();
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to save record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}

	return false;	
}

bool CRecordDao::Write(CFile &file, CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Get field number and save the value of each field  one by one.
		int nFieldNum = te.GetFieldNum();
		for(int i = 0; i < nFieldNum; i++)
		{
			// Get field information.
			CFieldEntity* pField = te.GetFieldAt(i);

			// Get the value of the field, the data type is CString. Before you save the need for type conversion
			CString strFieldName = pField->GetName();
			CString strVal = re.Get(strFieldName);

			// Get to the data type of the field.
			// To convert the value of the field to the actual data types, and write in the file.
			switch (pField->GetDataType())
			{
			case CFieldEntity::DT_INTEGER : // Integer
				{
					int nVal = _wtoi(strVal);
					file.Write(&nVal, sizeof(int));
					break;
				}
			case CFieldEntity::DT_BOOL : // Boolean type
				{
					int nVal = _wtoi(strVal);
					file.Write(&nVal, sizeof(bool));
					break;
				}
			case CFieldEntity::DT_DOUBLE : // Floating-point number
				{
					double dbVal = _wtof(strVal);
					file.Write(&dbVal, sizeof(double));
					break;
				}
			case CFieldEntity::DT_DATETIME : // Time type
				{
					SYSTEMTIME st = CTimeHelper::ToSystemTime(strVal);
					file.Write(&st, sizeof(SYSTEMTIME));
					break;
				}
			case CFieldEntity::DT_VARCHAR : // String type
				{
					// The length of the string
					int nSize = 256;
						/*sizeof(char) * pField->GetParam();*/
					// Create a cache to save the string
					char* pBuf = new char[nSize];
					CCharHelper::ToChars(pBuf, strVal, nSize);
					// Write in file
					file.Write(pBuf, nSize);
					// Release the cache
					delete[] pBuf;
					break;
				}
			default: // Other data types
				{
					throw new CAppException(_T("Field data type is unusual, save record failed!"));
				}
			}// end switch

		}// end for
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to save record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}

	return false;
}

bool CRecordDao::Read(CFile &file, CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Get field number and read the value of each field  one by one.
		int nFieldNum = te.GetFieldNum();
		for(int i = 0; i < nFieldNum; i++)
		{
			// Get field information.
			CFieldEntity* pField = te.GetFieldAt(i);
			CString strFieldName = pField->GetName();// Field name

			switch (pField->GetDataType())
			{
			case CFieldEntity::DT_INTEGER: // Integer
				{
					int nVal;
					if(file.Read(&nVal, sizeof(int)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, nVal);
					break;
				}
			case CFieldEntity::DT_BOOL : // Boolean
				{
					bool bVal;
					if(file.Read(&bVal, sizeof(bool)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, bVal);
					break;
				}
			case CFieldEntity::DT_DOUBLE : // Floating-point number
				{
					double dbVal;
					if(file.Read(&dbVal, sizeof(double)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, dbVal);
					break;
				}
			case CFieldEntity::DT_DATETIME : // Time type
				{
					SYSTEMTIME st;
					if(file.Read(&st, sizeof(SYSTEMTIME)) == 0)
					{
						return false;
					}
					re.Put(strFieldName, st);
					break;					
				}
			case CFieldEntity::DT_VARCHAR : // String type
				{
					int nSize = 256;
						/*sizeof(char) * pField->GetParam();*/
					char* pBuf = new char[nSize];
					if(file.Read(pBuf, nSize) == 0)
					{
						return false;
					}
					re.Put(strFieldName, CCharHelper::ToString(pBuf, nSize));					
					// Release cache
					delete[] pBuf;
					break;
				}
			default : // Other data types
				{
					throw new CAppException(_T("Field data type is unusual, read record failed!"));
				}
			}// end switch
		}// end for
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to read record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to read record!"));
	}

	return false;
}

bool CRecordDao::AfterInsertField(CTableEntity &te, RECORDARR records, std::vector<CString> vals){
	int recordNum = 0;
	int fieldNum = 0;
	long offset = 0;
	CRecordEntity* recordEntity;
	CFieldEntity* fieldEntity;
	recordNum = te.GetRecordNum();
	fieldNum = te.GetFieldNum();
	fieldEntity = te.GetFieldAt(fieldNum - 1);

	try{
		CFile file;
		// Open file
		if (file.Open(te.GetTrdPath(), CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
		{
			return false;
		}
		// The cursor to the end of the file
		file.SeekToBegin();
		for (int i = 0; i < recordNum; i++){
			offset = i * (fieldNum - 1);
			Write(file, te, vals, offset);
		}

		return true;
	}catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to save record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}
	return false;
}

bool CRecordDao::Write(CFile &file, CTableEntity &te, std::vector<CString> vals, long offset){
	try
	{
		// Get field number and save the value of each field  one by one.
		int nFieldNum = te.GetFieldNum();
		for(int i = 0; i < nFieldNum; i++)
		{
			// Get field information.
			CFieldEntity* pField = te.GetFieldAt(i);

			// Get the value of the field, the data type is CString. Before you save the need for type conversion
			CString strFieldName = pField->GetName();
			CString strVal = _T("");
			if(i == nFieldNum - 1){
				strVal = _T("");
			}else{
				strVal = vals[offset + i];
			}
			

			// Get to the data type of the field.
			// To convert the value of the field to the actual data types, and write in the file.
			switch (pField->GetDataType())
			{
			case CFieldEntity::DT_INTEGER : // Integer
				{
					int nVal = _wtoi(strVal);
					file.Write(&nVal, sizeof(int));
					break;
				}
			case CFieldEntity::DT_BOOL : // Boolean type
				{
					int nVal = _wtoi(strVal);
					file.Write(&nVal, sizeof(bool));
					break;
				}
			case CFieldEntity::DT_DOUBLE : // Floating-point number
				{
					double dbVal = _wtof(strVal);
					file.Write(&dbVal, sizeof(double));
					break;
				}
			case CFieldEntity::DT_DATETIME : // Time type
				{
					SYSTEMTIME st = CTimeHelper::ToSystemTime(strVal);
					file.Write(&st, sizeof(SYSTEMTIME));
					break;
				}
			case CFieldEntity::DT_VARCHAR : // String type
				{
					// The length of the string
					int nSize = 256;
						/*sizeof(char) * pField->GetParam();*/
					// Create a cache to save the string
					char* pBuf = new char[nSize];
					CCharHelper::ToChars(pBuf, strVal, nSize);
					// Write in file
					file.Write(pBuf, nSize);
					// Release the cache
					delete[] pBuf;
					break;
				}
			default: // Other data types
				{
					throw new CAppException(_T("Field data type is unusual, save record failed!"));
				}
			}// end switch

		}// end for
		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to save record!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}

	return false;
}