#include "FileOut.h"

FileOut::FileOut()
	: BaseFileIO()
{
	latestWrittenSize = 0;
	bin = false;		// 默认字符流
}

FileOut::FileOut(std::string fileName, _mode_code visitMode, _mode_code op, bool bin)
	: BaseFileIO(fileName, visitMode, op)
{
	latestWrittenSize = 0;
	this->bin = bin;
}

FileOut::~FileOut()
{
}

int FileOut::getLatestWrittenSize()
{
	return latestWrittenSize;
}

bool FileOut::openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool bin)
{
	latestWrittenSize = 0;
	this->bin = bin;
	return BaseFileIO::openFile(filePath, visitMode, op);
}

bool FileOut::isBinaryVisit()
{
	return bin;
}

std::string FileOut::numToStr(const int number)
{
	// 使用sstream将整数转成字符串
	std::ostringstream os;
	os << number;
	return os.str();
}

std::string FileOut::numToStr(const double number)
{
	// 使用sstream将浮点数转成字符串
	std::ostringstream os;
	os << number;
	return os.str();
}

FileOut & operator<<(FileOut & fop, int & number)
{
	// 根据文件访问方式进行不同的写入文件操作
	if (fop.isBinaryVisit()) {
		fop.latestWrittenSize = fop.writeFile(&number, sizeof(int));
	}
	else {
		fop << fop.numToStr(number);
	}
	return fop;
}

FileOut & operator<<(FileOut & fop, double & number)
{
	// 根据文件访问方式进行不同的写入文件操作
	if (fop.isBinaryVisit()) {
		fop.latestWrittenSize = fop.writeFile(&number, sizeof(double));
	}
	else {
		fop << fop.numToStr(number);
	}
	return fop;
}

FileOut & operator<<(FileOut & fop, char & ch) 
 {
	fop.latestWrittenSize = fop.writeFile(&ch, sizeof(char));
	return fop;
}

FileOut & operator<<(FileOut & fop, const std::string & str)
{
	// 由于系统API参数不接受const char*类型参数，因此改成char*类型传入
	char * pTemp = new char[str.size() + 1];
	strcpy(pTemp, str.data());
	fop.latestWrittenSize = fop.writeFile(pTemp, sizeof(char) * str.size());
	delete pTemp;
	return fop;
}
