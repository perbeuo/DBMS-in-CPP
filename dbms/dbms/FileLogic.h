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

private:
	// �����·��ת��Ϊ����·��
	CString GetAbsolutePath(const CString strRelativePath);
};