#include "StdAfx.h"
#include "DBEntity.h"
//���ݿ�ʵ������
//ȫ����ʼ��Ϊ��
CDBEntity::CDBEntity(void){
	m_strName = _T("");
	m_bType = false;
	m_strFilepath = _T("");
	::GetLocalTime(&m_tCtTime);
}
//�������ݿ�����
CDBEntity::CDBEntity(const CString strName){
	m_strName = strName;
	m_bType = false;
	m_strFilepath = _T("");
	::GetLocalTime(&m_tCtTime);
}
//�����е� DatabaseBlock �ṹ��ʼ�����ݿ�
CDBEntity::CDBEntity(DatabaseBlock &db){
	this->SetBlock(db);
}
//��������
CDBEntity::~CDBEntity(void){
}
//�����ݿ���Ϣ�浽 DatabaseBlock ��
DatabaseBlock CDBEntity::GetBlock(void){
	DatabaseBlock db;
	memset(&db, 0, sizeof(DatabaseBlock));
	
	CCharHelper::ToChars(db.name, m_strName, sizeof(VARCHAR));
	db.type = m_bType;
	CCharHelper::ToChars(db.filepath, m_strFilepath, sizeof(VARCHAR));
	db.crtime = m_tCtTime;
	return db;
}
//�� DatabaseBlock �е���Ϣ���뵽������ݿ�
void CDBEntity::SetBlock(DatabaseBlock db){
	m_strName = CCharHelper::ToString(db.name, sizeof(VARCHAR));
	m_bType = db.type;
	m_strFilepath = CCharHelper::ToString(db.filepath, sizeof(VARCHAR));
	m_tCtTime = db.crtime;
}
//�������ݿ�����
void CDBEntity::SetName(CString strName){
	m_strName = strName;
}
//�������ݿ�����
void CDBEntity::SetType(bool bType){
	m_bType = bType;
}
//�������ݿ��ļ�·��
void CDBEntity::SetFilepath(CString strFilepath){
	m_strFilepath = strFilepath;
}
//�������ݿⴴ��ʱ��
void CDBEntity::SetCtTime(SYSTEMTIME tTime){
	m_tCtTime = tTime;
}
//�������ݿ�����
CString CDBEntity::GetName(void){
	return m_strName;
}
//�������ݿ�����
bool CDBEntity::GetType(void){
	return m_bType;
}
//�������ݿ��ļ�·��
CString CDBEntity::GetFilepath(void){
	return m_strFilepath;
}
//�������ݿⴴ��ʱ��
SYSTEMTIME CDBEntity::GetCtTime(void){
	return m_tCtTime;
}