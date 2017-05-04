#pragma once
class CDBEntity
{
public:
	// 初始化数据成员
	CDBEntity(void);
	// 利用 DatabaseBlock 结构来初始化数据成员
	CDBEntity(DatabaseBlock &db);
	// 初始化数据库名称
	CDBEntity(const CString strName);
	// 析构器
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
	CString m_strName;		// 数据库名称
	bool m_bType;			// 数据库类型
	CString m_strFilepath;	// 数据库文件路径
	SYSTEMTIME m_tCtTime;	// 创建时间
};