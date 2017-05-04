#include "StdAfx.h"
#include "DBDao.h"

//�������ݿ�
bool CDBDao::Create(const CString strFilepath, CDBEntity db, bool bAppend){
	try{
	CFile file;
	if (bAppend == true){
	if (file.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			{
				return false;
			}
	}else{
	if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			{
				return false;
			}
	}
	file.SeekToBegin();
	file.Write(&db.GetBlock(), sizeof(DatabaseBlock));
	file.Close();
	return true;
	}catch(CException* e){
	e->Delete();
	throw new CAppException(_T("Failed to create the database file!"));
	}catch(...){
	throw new CAppException(_T("Failed to create the database file!"));
	}
	return false;
}
//��ȡ���ݿ���Ϣ
bool CDBDao::GetDatabase(const CString strFilepath, CDBEntity &db){
	CString dbName;
	CFile file;
	try{
		dbName = db.GetName();
		if(dbName.GetLength() == 0)
			return false;
		//ֻ����ʽ���ļ�
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
			return false;
		//��ȡ��Ϣ
		bool ifexist = false;
		DatabaseBlock tempDB;
		file.SeekToBegin();
		while(file.Read(&tempDB, sizeof(DatabaseBlock)) > 0){
			CString name = CCharHelper::ToString(tempDB.name, sizeof(VARCHAR));
			//�ж��Ƿ�ΪҪ�������ݿ�
			if(name.CompareNoCase(dbName) == 0){
				db.SetBlock(tempDB);
				ifexist = true;
				break;
			}
		}
		file.Close();
		return ifexist;
	}catch(CException* e){
	e->Delete();
	throw new CAppException(_T("Failed to create the database file!"));
	}catch(...){
	throw new CAppException(_T("Failed to create the database file!"));
	}
	return false;
}
//�����ļ�
bool CDBDao::CreateFile(const CString strFileName){
	try{
		//���ļ�·�������ļ�
		for(int i = 0; i < strFileName.GetLength(); i++){
			if((_T('\\') == strFileName.GetAt(i) || _T('/') == strFileName.GetAt(i)) && i != 2){
				CString fileDirectory;
				fileDirectory = strFileName.Left(i);
				if(!CreateDirectory(fileDirectory, NULL) && 183 != GetLastError())
				{
					return false;
				}
			}
		}
		//�����ļ�
		CFile file;
		if(!file.Open(strFileName,CFile::modeCreate))
			return false;
		file.Close();
		return true;
	}catch(CException* e){
	e->Delete();
	throw new CAppException(_T("Failed to create file!"));
	}catch(...){
	throw new CAppException(_T("Failed to create file!"));
	}
	return false;
}
//�ж��ļ��Ƿ���Ч
bool CDBDao::IsValidFile(const CString strPath){
	CFile file;
	try{
		if(file.Open(strPath, CFile::modeRead | CFile::shareDenyNone) == TRUE){
			file.Close();
			return true;
		}
	}catch(CException* e){
	e->Delete();
	throw new CAppException(_T("Failed to create file!"));
	}catch(...){
	throw new CAppException(_T("Failed to create file!"));
	}
	return false;
}