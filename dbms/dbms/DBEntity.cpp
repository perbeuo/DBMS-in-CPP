#include "StdAfx.h"
#include "DBEntity.h"
//数据库实体类型
//全部初始化为空
CDBEntity::CDBEntity(void){
	m_strName = _T("");
	m_bType = false;
	m_strFilepath = _T("");
	::GetLocalTime(&m_tCtTime);
}
//设置数据库名称
CDBEntity::CDBEntity(const CString strName){
	m_strName = strName;
	m_bType = false;
	m_strFilepath = _T("");
	::GetLocalTime(&m_tCtTime);
}
//用已有的 DatabaseBlock 结构初始化数据库
CDBEntity::CDBEntity(DatabaseBlock &db){
	this->SetBlock(db);
}
//析构函数
CDBEntity::~CDBEntity(void){
}
//将数据库信息存到 DatabaseBlock 中
DatabaseBlock CDBEntity::GetBlock(void){
	DatabaseBlock db;
	memset(&db, 0, sizeof(DatabaseBlock));
	
	CCharHelper::ToChars(db.name, m_strName, sizeof(VARCHAR));
	db.type = m_bType;
	CCharHelper::ToChars(db.filepath, m_strFilepath, sizeof(VARCHAR));
	db.crtime = m_tCtTime;
	return db;
}
//将 DatabaseBlock 中的信息导入到这个数据库
void CDBEntity::SetBlock(DatabaseBlock db){
	m_strName = CCharHelper::ToString(db.name, sizeof(VARCHAR));
	m_bType = db.type;
	m_strFilepath = CCharHelper::ToString(db.filepath, sizeof(VARCHAR));
	m_tCtTime = db.crtime;
}
//设置数据库名称
void CDBEntity::SetName(CString strName){
	m_strName = strName;
}
//设置数据库类型
void CDBEntity::SetType(bool bType){
	m_bType = bType;
}
//设置数据库文件路径
void CDBEntity::SetFilepath(CString strFilepath){
	m_strFilepath = strFilepath;
}
//设置数据库创建时间
void CDBEntity::SetCtTime(SYSTEMTIME tTime){
	m_tCtTime = tTime;
}
//返回数据库名称
CString CDBEntity::GetName(void){
	return m_strName;
}
//返回数据库类型
bool CDBEntity::GetType(void){
	return m_bType;
}
//返回数据库文件路径
CString CDBEntity::GetFilepath(void){
	return m_strFilepath;
}
//返回数据库创建时间
SYSTEMTIME CDBEntity::GetCtTime(void){
	return m_tCtTime;
}