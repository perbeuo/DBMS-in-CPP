#pragma once

class CFileLogic
{
public:
	// �õ����ݿ������ļ���λ��
	CString GetDBFile(const CString strDBName);
	// �õ����ݿ��ļ��е�λ��
	CString GetDBFolder(const CString strDBName);
	//�õ����ݿ��б��ļ���λ��
	CString GetDBListFile(void);
	// ������ݿ�������ļ�·��
	CString GetTableFile(const CString strDBName);

	CString GetTbDefineFile(const CString strDBName, const CString strTableName);

	CString GetTbRecordFile(const CString strDBName, const CString strTableName);
private:
	// �����·��ת��Ϊ����·��
	CString GetAbsolutePath(const CString strRelativePath);
};