#include "StdAfx.h"
#include "RecordDao.h"

/**************************************************
[FunctionName]	Insert
[Function]	Create new rows in a table
[Argument]	CTableEntity &te: Table structure information
		CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful; otherwise false.
**************************************************/
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
		// Save each field of the record to the file one by one
		int nFieldNum = te.GetFieldNum();
		for(int i = 0; i < nFieldNum; i++)
		{
			// Get field information.
			CFieldEntity* pField ;
				/*= te.GetFieldAt(i);*/

			// Get the value of the field, the data type is CString. Before you save the need for type conversion
			CString strFieldName = pField->GetName();
			CString strVal = re.Get(strFieldName);

			// Get the data type of the field.
			// Convert the value of the field to the actual data types, and write in the file.
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
					int nSize = sizeof(char) * pField->GetParam();
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
					throw new CAppException(_T("Data type of the field is unusual, failed to save record!"));
				}
			}// end switch

		}// end for

		// Close file
		file.Close();
		return true;
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to save record!"));
	}

	return false;	
}