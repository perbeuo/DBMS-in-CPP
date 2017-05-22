#pragma  once
//������������
typedef int INTEGER;			// Integer
typedef bool BOOLE;				// Boolean type
typedef double DOUBLE;			// Floating-point number
typedef char VARCHAR[256];		// String type
typedef SYSTEMTIME DATETIME;	// Date time type

//DatabaseBlock �ṹ
struct DatabaseBlock{
	BOOLE type;			// Database type��true is system database��false is custom database.
	VARCHAR name;		// Database name
	VARCHAR filepath;	// Database file path
	DATETIME crtime;	// Creation time
};

// ����Ϣ�ṹ
struct TableBlock
{
	VARCHAR name;		// Name
	INTEGER record_num;	// Record number
	INTEGER field_num;	// Field number
	VARCHAR tdf;		// Path of the table definition file
	VARCHAR trd;		// Path of the record file
	DATETIME crtime;	// Table creation time
	DATETIME mtime;		// Last modification time
};


// The definition of field block
struct FieldBlock
{
	VARCHAR name;		// Name
	VARCHAR defaultValue; //Ĭ��ֵ
	INTEGER type;		// Type
	INTEGER param;		// Parameter
	DATETIME mtime;		// Last modification time
	INTEGER integrities;// Integrity constraints information
};