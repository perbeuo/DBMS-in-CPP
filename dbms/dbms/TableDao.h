#pragma once
#include "TableEntity.h"
#include "FieldEntity.h"
//����������
class CTableDao
{
public:
	// �����������Ϣ
	bool Create(const CString strFilePath, CTableEntity &te);
	// �����ļ�
	bool CreateFile(const CString strFileName);
	//�ж��ļ���Ч��
	bool IsValidFile(const CString strPath);
	//get table
	bool GetTable(const CString strFilepath, CTableEntity &db);
	//���field
	bool AddField(const CString strFilePath, CFieldEntity &fe);
	bool AlterTable(const CString strFilePath, CTableEntity &te);
};