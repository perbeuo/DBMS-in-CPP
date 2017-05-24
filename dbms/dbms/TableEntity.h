#pragma once
#include <afx.h>
#include <afxdisp.h>        // MFC Automation classes
#include <vector>
#include "FieldEntity.h"
class CTableEntity
{
public:
	// ��ʵ�幹����
	CTableEntity(CString strName);
	CTableEntity(void);
	// ��������
	~CTableEntity(void);

	// Class and block conversion function
	TableBlock GetBlock();
	void SetBlock(TableBlock tb);

	// ���ù��ܺ���
	void SetName(CString strName);
	void SetRecordNum(int nNum);
	void SetTdfPath(const CString strTdfPath);
	void SetTrdPath(const CString strTrdPath);
	void SetCrTime(SYSTEMTIME tTime);
	void SetMTime(SYSTEMTIME tTime);
	void AddFieldNum();
	// ��������ֵ
	CString GetName();
	int GetRecordNum();
	int GetFieldNum();
	CString GetTdfPath();
	CString GetTrdPath();
	SYSTEMTIME GetCrTime();
	SYSTEMTIME GetMTime();
public:
	CFieldEntity* AddField(CFieldEntity &fe);
	CFieldEntity* GetFieldAt(int nIndex);
private:
	// �������Ϣ
	CString m_strName;		// ������
	int m_nRecordNum;		// ��¼���
	int m_nFieldNum;		// ������
	CString m_strTdfPath;	// �����ļ�·�� 
	CString m_strTrdPath;	// ��¼�ļ�·��
	SYSTEMTIME m_tCrTime;	// ����ʱ��
	SYSTEMTIME m_tMTime;	// ����޸�ʱ��
	FIELDARRAY m_arrFields;	// Field array
};

typedef std::vector<CTableEntity*> TABLEARR;