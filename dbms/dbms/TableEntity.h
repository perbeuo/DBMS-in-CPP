#pragma once
#include <afxdisp.h>        // MFC Automation classes
#include <afx.h>
#include "FieldEntity.h"
class CTableEntity
{
public:
	// 表实体构造器
	CTableEntity(CString strName);
	CTableEntity(void);
	// 析构函数
	~CTableEntity(void);

	// Class and block conversion function
	TableBlock GetBlock();
	void SetBlock(TableBlock tb);

	// 设置功能函数
	void SetName(CString strName);
	void SetRecordNum(int nNum);
	void SetTdfPath(const CString strTdfPath);
	void SetTrdPath(const CString strTrdPath);
	void SetCrTime(SYSTEMTIME tTime);
	void SetMTime(SYSTEMTIME tTime);

	// 返回所需值
	CString GetName();
	int GetRecordNum();
	int GetFieldNum();
	CString GetTdfPath();
	CString GetTrdPath();
	SYSTEMTIME GetCrTime();
	SYSTEMTIME GetMTime();

private:
	// 表基本信息
	CString m_strName;		// 表名称
	int m_nRecordNum;		// 记录编号
	int m_nFieldNum;		// 区域编号
	CString m_strTdfPath;	// 表定义文件路径 
	CString m_strTrdPath;	// 记录文件路径
	SYSTEMTIME m_tCrTime;	// 表创建时间
	SYSTEMTIME m_tMTime;	// 最后修改时间
};

typedef CTypedPtrArray<CPtrArray, CTableEntity*> TABLEARR;