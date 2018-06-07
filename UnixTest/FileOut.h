/**
* FileName：FileOut.h
* Description：文件写入类（重载运算符<<）
* Author：ZiQin
* DateTime：2018-6-1
* Version：v1.0.0
*/

#ifndef FILEOUT_H_
#define FILEOUT_H_

#include <cstring>
#include <string>
#include <sstream>
#include "BaseFileIO.h"

/**
* 符号常量说明：
* f_bin	文件读写以字节流的形式
*/
#define f_bin	true

class FileOut : public BaseFileIO {
private:
	int latestWrittenSize;	// 最近一次写入文件的字节大小
	bool bin;						// 文件读是否以字节流的形式

public:
	// 构造函数
	FileOut();
	/* 参数：
		fileName：文件路径
		visitMode：访问模式（f_in/f_out）
		op：打开方式（f_exist/f_new）
		binary：是否以字节流的形式读取文件（默认字符流）
	*/
	FileOut(std::string fileName, _mode_code visitMode, _mode_code op, bool bin = false);
	virtual ~FileOut();

	/**
	* 函数名：getLatestWrittenSize
	* 功能：获取最近一次写入文件的字节大小
	* 参数：无
	* 返回值：最近一次写入文件的字节大小
	*/
	int getLatestWrittenSize();

	/**
	* 函数名：openFile
	* 功能：打开文件
	* 参数：
	fileName：文件路径
	visitMode：访问模式（f_in/f_out）
	op：打开方式（f_exist/f_new）
	binary：是否以字节流的形式读入（默认字符流）
	* 返回值：打开成功或失败
	*/
	bool openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool bin = false);

	/**
	* 友元函数：<<运算符重载
	* 功能：将第二个参数的内容写入到文件中
	*/
	friend FileOut & operator << (FileOut & fop, int & number);

	friend FileOut & operator << (FileOut & fop, double & number);

	friend FileOut & operator << (FileOut & fop, char & ch);

	friend FileOut & operator << (FileOut & fop, const std::string & str);

	/**
	* 函数名：isBinaryVisit
	* 功能：检查当前文件访问是否以字节流的形式
	* 参数：无
	* 返回值：是否以字节流的形式访问
	*/
	bool isBinaryVisit();

private:
	/**
	* 函数名：numToStr
	* 功能：整数转字符串
	* 参数：将要转换的整数
	* 返回值：转换结果
	*/
	std::string numToStr(const int number);

	/**
	* 函数名：numToStr
	* 功能：浮点数转字符串
	* 参数：将要转换的浮点数
	* 返回值：转换结果
	*/
	std::string numToStr(const double number);

};

#endif
