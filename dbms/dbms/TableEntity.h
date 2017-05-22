#pragma once
#include <afxdisp.h>        // MFC Automation classes
#include <afx.h>
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
private:
	// �������Ϣ
	CString m_strName;		// ������
	int m_nRecordNum;		// ��¼���
	int m_nFieldNum;		// ������
	CString m_strTdfPath;	// �����ļ�·�� 
	CString m_strTrdPath;	// ��¼�ļ�·��
	SYSTEMTIME m_tCrTime;	// ����ʱ��
	SYSTEMTIME m_tMTime;	// ����޸�ʱ��

};

typedef CTypedPtrArray<CPtrArray, CTableEntity*> TABLEARR;