#pragma once
#include "TableEntity.h"

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
};