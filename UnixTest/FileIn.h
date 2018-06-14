/**
* FileName：FileIn.h
* Description：文件读入类（重载运算符>>）
* Author：ZiQin
* DateTime：2018-6-1
* Version：v1.0.0
*/

#ifndef FILEIN_H_
#define FILEIN_H_

#include <iostream>
#include <sstream>
#include <string>
#include "BaseFileIO.h"

/**
* 符号常量说明：
* f_bin	文件读写以字节流的形式
*/
#define f_bin	true	

class FileIn : public BaseFileIO {
private:
	int latestReadSize;	// 最近一次从文件读入的字节大小
	bool bin;					// 文件读是否以字节流的形式

public:
	// 构造函数
	FileIn();
	/* 参数：
		fileName：文件路径
		visitMode：访问模式（f_in/f_out）
		op：打开方式（f_exist/f_new）
		binary：是否以字节流的形式读取文件（默认字符流）
	*/
	FileIn(std::string fileName, _mode_code op, bool binary = false);
	virtual ~FileIn();

	/**
	* 函数名：getLatestReadSize
	* 功能：获取最近一次读取文件的字节大小
	* 参数：无
	* 返回值：最近一次读取文件的字节大小
	*/
	int getLatestReadSize();

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
	bool openFile(std::string filePath, _mode_code op, bool binary = false);

	/**
	* 友元函数：>>运算符重载
	* 功能：从文件中读取对应的内容放到第二个参数
	*/
	friend FileIn & operator >> (FileIn & fop, int & number);

	friend FileIn & operator >> (FileIn & fop, double & number);

	friend FileIn & operator >> (FileIn & fop, char & ch);

	friend FileIn & operator >> (FileIn & fop, std::string & str);

	/**
	* 函数名：isBinaryVisit
	* 功能：检查当前文件访问是否以字节流的形式
	* 参数：无
	* 返回值：是否以字节流的形式访问
	*/
	bool isBinaryVisit();

private:
	/**
	* 函数名：strToInt（类内部使用）
	* 功能：字符串转整型
	* 参数：要转换的字符串
	* 返回值：转换结果
	*/
	int strToInt(std::string str);

	/**
	* 函数名：strToDouble（类内部使用）
	* 功能：字符串转浮点数
	* 参数：要转换的字符串
	* 返回值：转换结果
	*/
	double strToDouble(std::string str);

};

#endif
