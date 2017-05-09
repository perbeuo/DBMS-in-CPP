#pragma once

class CFileLogic
{
public:
	// 得到数据库描述文件的位置
	CString GetDBFile(const CString strDBName);
	// 得到数据库文件夹的位置
	CString GetDBFolder(const CString strDBName);
	//得到数据库列表文件的位置
	CString GetDBListFile(void);

private:
	// 将相对路径转化为绝对路径
	CString GetAbsolutePath(const CString strRelativePath);
};