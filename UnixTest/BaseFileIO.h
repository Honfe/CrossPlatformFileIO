/**
* FileName：BaseFileIO.h
* Description：基本文件IO操作
* Author：ZiQin
* DateTime：2018-6-1
* Version：v1.0.0
*/

#ifndef BASEFILEIO_H_
#define BASEFILEIO_H_

#include <iostream>
#include <string>

// 根据环境的不同选择包含不同的头文件
#ifdef _WIN32	
// 取消UNICODE宏定义，不让Windwos.h使用宽字符类型
#undef UNICODE	
#include <Windows.h>
#elif __linux__ || __unix__	
#include <fcntl.h>
#include <unistd.h>
#endif

// 统一Windows32和Unix/Linux各平台的字符常量
/**
* 符号常量使用说明：
* f_new		重写文件
* f_exist	仅打开文件，若文件不存在则新建文件
* f_in		读入文件
* f_out		写入文件
* f_cur		文件指针当前位置
* f_set		文件指针指向文件开头
* f_end		文件指针指向文件结尾
*/
#ifdef _WIN32
#define f_new		CREATE_ALWAYS
#define f_exist		OPEN_ALWAYS
#define f_in			GENERIC_READ
#define f_out		GENERIC_WRITE
#define f_cur		FILE_CURRENT
#define f_set		FILE_BEGIN
#define f_end		FILE_END
#elif __linux__ || __unix__	
#define f_new		(O_CREAT | O_TRUNC)
#define f_exist		O_CREAT
#define f_in			O_RDONLY
#define f_out		O_WRONLY
#define f_cur		SEEK_CUR
#define f_set		SEEK_SET
#define f_end		SEEK_END
#endif

// 统一Windows和Unix/Linux平台的字符常量
/**
* 符号常量功能说明：
* OPEN_FAIL	打开文件失败，或者文件标识变量无效
* CLOSE_SUC	关闭文件失败标识
* SEEK_FAIL		文件指针移动失败
*/
#ifdef _WIN32
#define OPEN_FAIL			INVALID_HANDLE_VALUE
#define CLOSE_SUC		TRUE
#define SEEK_FAIL			INVALID_SET_FILE_POINTER
#elif __linux__ || __unix__
#define OPEN_FAIL			-1
#define CLOSE_SUC		 0
#define SEEK_FAIL			-1
#endif

// 统一Windows和Unix/Linux各平台的变量类型名
#ifdef _WIN32
typedef	HANDLE			_file_id;
typedef	DWORD			_mode_code;
typedef	LPCTSTR			_file_string;
typedef	DWORD			_file_int;
#elif __linux__ || __unix__
typedef	int					_file_id;
typedef	int					_mode_code;
typedef	const char *		_file_string;
typedef	int					_file_int;
#endif

// 统一Windows和Linux/Unix各平台的文件IO函数接口
#ifdef _WIN32				// Windows环境
// 打开文件宏定义
#define __OPEN_FILE(NAME, VISITMODE, OP)	 \
	::CreateFile((NAME), (VISITMODE),					\
		0, NULL, (OP), FILE_ATTRIBUTE_NORMAL,	\
		NULL)
// 使用内联函数对函数API进行转换，使之适应宏定义的API
inline int __inline_WriteToFile(_file_id id, void * buffer, int size);
inline int __inline_ReadFromFile(_file_id id, void * buffer, int size);
// 写数据入文件宏定义
#define __WRITE_TO_FILE(ID, BUFFER, SIZE)		\
	::__inline_WriteToFile((ID), (BUFFER), (SIZE))
// 从文件读数据宏定义
#define __READ_FROM_FILE(ID, BUFFER, SIZE)	\
	::__inline_ReadFromFile((ID), (BUFFER), (SIZE))
// 更改文件指针宏定义
#define __SET_POSITION_FILE(ID, ABSPOS, OFFSET) \
	::SetFilePointer((ID), (OFFSET), NULL, (ABSPOS))
// 关闭文件宏定义
#define __CLOSE_FILE(ID)									\
	::CloseHandle((ID))
#elif __linux__ || __unix__	// Unix/Linux环境
// 打开文件宏定义
#define __OPEN_FILE(NAME, VISITMODE, OP)	\
	::open((NAME), (VISITMODE) | (OP), S_IRUSR | S_IWUSR | S_IXUSR)
// 写数据入文件宏定义
#define __WRITE_TO_FILE(ID, BUFFER, SIZE)		\
	::write((ID), (BUFFER), (SIZE))
// 从文件读数据宏定义
#define __READ_FROM_FILE(ID, BUFFER, SIZE)	\
	::read((ID), (BUFFER), (SIZE))
// 更改文件指针宏定义
#define __SET_POSITION_FILE(ID, ABSPOS, OFFSET) \
	::lseek((ID), (OFFSET), (ABSPOS))
// 关闭文件宏定义
#define __CLOSE_FILE(ID)									\
	::close((ID))
#endif

// 文件操作错误码
#define NO_ERR			 0		// 无错误
#define OPEN_ERR		-1		// 打开文件错误
#define CLOSE_ERR		-2		// 关闭文件错误
#define READ_ERR		-3		// 读取文件错误
#define WRITE_ERR		-4		// 写入文件错误
#define SEEK_ERR		-5		// 更改文件指针错误

class BaseFileIO {
protected:
	_file_id	id;			// 文件标识
	bool		eof;		// 文件指针到达文件尾标志
	int		err;		// 错误码

public:
	// 构造函数
	BaseFileIO();
	/* 参数：
		fileName：文件路径
		visitMode：访问模式（f_in/f_out）
		op：打开方式（f_exist/f_new）
	*/
	BaseFileIO(std::string fileName, _mode_code visitMode, _mode_code op);
	virtual ~BaseFileIO();

	/**
	* 函数名：openFile
	* 功能：打开文件或者创建文件
	* 参数：
		fileName：文件路径
		visitMode：访问模式（f_in/f_out）
		op：打开方式（f_exist/f_new）
	* 返回值：打开成功或失败
	*/
	bool openFile(std::string filePath, _mode_code visitMode, _mode_code op);

	/**
	* 函数名：readFile
	* 功能：从文件中读取数据
	* 参数：
		buffer：数据写入缓冲区
		type：读出类型的字节大小
	* 返回值：读取文件的字节大小，失败返回-1
	*/
	int readFile(void * buffer, int type);

	/**
	* 函数名：writeFile
	* 功能：将数据写入文件
	* 参数：
		buffer：将要写入文件的数据
		type：写入类型的字节大小
	* 返回值：写入文件的字节大小，失败返回-1
	*/
	int writeFile(void * buffer, int type);

	/**
	* 函数名：setPositionPointor
	* 功能：更改文件指针的位置
	* 参数：
		absPos：绝对位置
		offset：基于绝对位置的偏移量
	* 返回值：移动文件指针的成功与否
	*/
	int setPositionFilePointor(int absPos, int offset);

	/**
	* 函数名：closeFile
	* 功能：关闭文件
	* 参数：无
	* 返回值：关闭成功与否
	*/
	bool closeFile();

	/**
	* 函数名：isEof
	* 功能：判断是否到达文件尾
	* 参数：无
	* 返回值：文件指针是否已经到达文件尾
	*/
	bool isEof();

	/**
	* 函数名：getErrorCode
	* 功能：获取错误码
	* 参数：无
	* 返回值：最近一次操作产生的错误码
	*/
	int getErrorCode();

	/**
	* 函数名：getErrorMsg
	* 功能：获取错误信息
	* 参数：无
	* 返回值：最近一次操作产生的错误信息
	*/
	std::string getErrorMsg();

};

#endif
