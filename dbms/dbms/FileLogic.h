#pragma once

class CFileLogic
{
public:
	// �õ����ݿ������ļ���λ��
	CString GetDBFile(void);
	// �õ����ݿ��ļ��е�λ��
	CString GetDBFolder(const CString strDBName);

private:
	// �����·��ת��Ϊ����·��
	CString GetAbsolutePath(const CString strRelativePath);
};