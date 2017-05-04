#pragma  once
//基础数据类型
typedef int INTEGER;			// Integer
typedef bool BOOLE;				// Boolean type
typedef double DOUBLE;			// Floating-point number
typedef char VARCHAR[256];		// String type
typedef SYSTEMTIME DATETIME;	// Date time type

//DatabaseBlock 结构
struct DatabaseBlock{
	BOOLE type;			// Database type：true is system database，false is custom database.
	VARCHAR name;		// Database name
	VARCHAR filepath;	// Database file path
	DATETIME crtime;	// Creation time
};