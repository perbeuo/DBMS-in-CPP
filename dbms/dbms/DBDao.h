#pragma once
#include "DBEntity.h"

//�������ݿ����
class CDBDao
{
public:
	// �������ݿ�
	bool Create(const CString DBListFilePath, const CString strFilepath, CDBEntity db, bool bAppend = true);
	// ��ȡ���ݿ���Ϣ
	bool GetDatabase(const CString strFilepath, CDBEntity &db);

	// �����ļ�
	bool CreateFile(const CString strFileName);
	// �ж��ļ��Ƿ���Ч
	bool IsValidFile(const CString strPath);
};