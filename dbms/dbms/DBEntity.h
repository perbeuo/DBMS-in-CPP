#pragma once
class CDBEntity
{
public:
	// ��ʼ�����ݳ�Ա
	CDBEntity(void);
	// ���� DatabaseBlock �ṹ����ʼ�����ݳ�Ա
	CDBEntity(DatabaseBlock &db);
	// ��ʼ�����ݿ�����
	CDBEntity(const CString strName);
	// ������
	~CDBEntity(void);

public:
	DatabaseBlock GetBlock(void);
	void SetBlock(DatabaseBlock db);
	void SetName(CString strName);
	void SetType(bool bType);
	void SetFilepath(CString strFilepath);
	void SetCtTime(SYSTEMTIME tTime);	
	CString GetName(void);
	bool GetType(void);
	CString GetFilepath(void);
	SYSTEMTIME GetCtTime(void);

private:
	CString m_strName;		// ���ݿ�����
	bool m_bType;			// ���ݿ�����
	CString m_strFilepath;	// ���ݿ��ļ�·��
	SYSTEMTIME m_tCtTime;	// ����ʱ��
};