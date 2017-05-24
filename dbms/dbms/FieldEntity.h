#pragma once
#include <afxdisp.h>        // MFC Automation classes
#include <afx.h>
#include <vector>
/************************************************
[ClassName]	CFieldEntity
[Function]	Field entity class
************************************************/
class CFieldEntity : public CObject
{
public:
	// Field type definitions
	enum DataType
	{
		DT_NONE = 0,
		DT_INTEGER = 1,// Integer: 4byte  corresponding: int
		DT_BOOL = 3,// Boolean: 1byte, corresponding£ºbool
		DT_DOUBLE = 4,// Floating-point number: 2byte,  corresponding: double
		DT_VARCHAR = 2,// String: 256byte, corresponding: char[256]
		DT_DATETIME = 5// Data time: 16byte, corresponding: SYSTEMTIME type
	};

public:
	// Constructor
	CFieldEntity(CString strName, CString defaValue,int nType = DT_INTEGER, int nParam = NULL, int nIntegrities = 0);
	CFieldEntity(CFieldEntity& fe);
	CFieldEntity(void);
	~CFieldEntity(void);

	// Get the name of the data type
	CString GetTypeName(int nType);

	// Class and block conversion function
	FieldBlock GetBlock();
	void SetBlock(FieldBlock fb);

	// Set function
	void SetName(CString strName);
	void SetDefault(CString strDefault);
	void SetDataType(int nType);
	void SetParam(int nParam);
	void SetMTime(SYSTEMTIME t);

	// Get function
	CString GetName();
	CString GetDefault();
	int GetDataType();
	int GetParam();
	SYSTEMTIME GetMTime();

private:
	CString m_strName;  // Field name
	CString m_defaultValue;
	int m_nType; // Field type
	int m_nParam;  // Field type parameter
	SYSTEMTIME m_tMTime; // Last modification time
	int m_nIntegrities; // Type of integrity constraints
};

typedef std::vector<CFieldEntity*> FIELDARRAY;
