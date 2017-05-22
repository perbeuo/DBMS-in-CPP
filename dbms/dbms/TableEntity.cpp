#include "StdAfx.h"
#include "TableEntity.h"

//表实体初始化为空
CTableEntity::CTableEntity(void)
{
	m_strName = _T("");			
	m_nRecordNum = 0;
	m_nFieldNum = 0;
	m_strTdfPath = _T("");		
	m_strTrdPath = _T("");		
	::GetLocalTime(&m_tCrTime);	
	m_tMTime = m_tCrTime;		
}

//设置表信息
CTableEntity::CTableEntity(CString strName)
{
	m_strName = strName;		// Table name
	m_nRecordNum = 0;			// Record number
	m_nFieldNum = 0;
	m_strTdfPath = _T("");		// Path of table definition file 
	m_strTrdPath = _T("");		// Path of record file
	::GetLocalTime(&m_tCrTime);	// Table creation time
	m_tMTime = m_tCrTime;		// Last modification time
}

//析构函数
CTableEntity::~CTableEntity(void)
{

}


//表信息存储到TableBlock中
TableBlock CTableEntity::GetBlock()
{
	TableBlock tb;
	CCharHelper::ToChars(tb.name, m_strName, sizeof(VARCHAR));
	tb.field_num = m_nFieldNum;
	tb.record_num = m_nRecordNum;

	CCharHelper::ToChars(tb.tdf, m_strTdfPath, sizeof(VARCHAR));
	CCharHelper::ToChars(tb.trd, m_strTrdPath, sizeof(VARCHAR));
	tb.crtime = m_tCrTime;
	tb.mtime = m_tMTime;

	return tb;
}


//将结构体信息放入表信息结构
void CTableEntity::SetBlock(TableBlock tb)
{
	m_strName = CCharHelper::ToString(tb.name, sizeof(VARCHAR));
	m_nRecordNum = tb.record_num;
	m_strTdfPath = CCharHelper::ToString(tb.tdf, sizeof(VARCHAR));
	m_strTrdPath = CCharHelper::ToString(tb.trd, sizeof(VARCHAR));
	m_tCrTime = tb.crtime;
	m_tMTime = tb.mtime;
}


//Set函数
void CTableEntity::SetName(CString strName)
{
	m_strName = strName;
}

void CTableEntity::SetRecordNum(int nNum)
{
	m_nRecordNum = nNum;
}

void CTableEntity::SetTdfPath( const CString strTdfPath )
{
	m_strTdfPath = strTdfPath;
}

void CTableEntity::SetTrdPath( const CString strTrdPath )
{
	m_strTrdPath = strTrdPath;
}

void CTableEntity::SetCrTime(SYSTEMTIME tTime)
{
	m_tCrTime = tTime;
}

void CTableEntity::SetMTime(SYSTEMTIME tTime)
{
	m_tMTime = tTime;
}



//Get 函数
CString CTableEntity::GetName()
{
	return m_strName;
}

int CTableEntity::GetRecordNum()
{
	return m_nRecordNum;
}

int CTableEntity::GetFieldNum()
{
	return m_nFieldNum;
}

CString CTableEntity::GetTdfPath()
{
	return m_strTdfPath;
}

CString CTableEntity::GetTrdPath()
{
	return m_strTrdPath;
}

SYSTEMTIME CTableEntity::GetCrTime()
{
	return m_tCrTime;
}

SYSTEMTIME CTableEntity::GetMTime()
{
	return m_tMTime;
}


