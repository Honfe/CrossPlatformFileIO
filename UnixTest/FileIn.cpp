#include "FileIn.h"

FileIn::FileIn()
	: BaseFileIO()
{
	latestReadSize = 0;
	bin = false;		// 默认字符流
}

FileIn::FileIn(std::string fileName, _mode_code op, bool binary)
	: BaseFileIO(fileName, f_in, op)
{
	latestReadSize = 0;
	bin = binary;
}

FileIn::~FileIn()
{
}

int FileIn::getLatestReadSize()
{
	return latestReadSize;
}

bool FileIn::openFile(std::string filePath, _mode_code op, bool binary)
{
	latestReadSize = 0;
	bin = binary;
	return BaseFileIO::openFile(filePath, f_in, op);
}

bool FileIn::isBinaryVisit()
{
	return bin;
}

int FileIn::strToInt(std::string str)
{
	if (str == "")
		return 0;
	// 使用sstream将字符串转成整数
	std::istringstream is(str);
	int num;
	is >> num;
	return num;
}

double FileIn::strToDouble(std::string str)
{
	if (str == "")
		return 0.0;
	// 使用sstream将字符串转成浮点数
	std::istringstream is(str);
	double num;
	is >> num;
	return num;
}

FileIn & operator >> (FileIn & fop, int & number)
{
	// 根据文件访问方式进行不同的读取文件操作
	if (fop.isBinaryVisit()) {		
		fop.latestReadSize = fop.readFile(&number, sizeof(int));
		// 如果文件什么都没读进来，则默认number值为0
		if (fop.latestReadSize == 0)
			number = 0;
	}
	else {
		std::string numStr;
		fop >> numStr;
		number = fop.strToInt(numStr);
	}
	return fop;
}

FileIn & operator >> (FileIn & fop, double & number)
{
	// 根据文件访问方式进行不同的读取文件操作
	if (fop.isBinaryVisit()) {
		fop.latestReadSize = fop.readFile(&number, sizeof(double));
		// 如果文件什么都没读进来，则默认number值为0
		if (fop.latestReadSize == 0)
			number = 0.0;
	}
	else {
		std::string strNum;
		fop >> strNum;
		number = fop.strToDouble(strNum);
	}
	return fop;
}

FileIn & operator >> (FileIn & fop, char & ch)
{
	fop.latestReadSize = fop.readFile(&ch, sizeof(char));
	// 如果文件什么都没读进来，则默认number值为0
	if (fop.latestReadSize == 0)
		ch = 0;
	return fop;
}

FileIn & operator >> (FileIn & fop, std::string & str)
{
	str.clear();
	char tar;
	fop.latestReadSize = 0;
	do {
		fop >> tar;
		// 检查是否到达文件尾或者读完一个单词，是则结束字符串读取
		if (tar == ' ' || fop.isEof()) break;	
		str += tar;		// 一次只读1个字符，因此将其组装起来
		++fop.latestReadSize;	// 统计读入的字节总数
	} while (true);
	return fop;
}
