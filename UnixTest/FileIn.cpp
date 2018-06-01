#include "FileIn.h"

FileIn::FileIn()
	: BaseFileIO()
{
	latestReadSize = 0;
	bin = false;
}

FileIn::FileIn(std::string fileName, _mode_code visitMode, _mode_code op, bool binary)
	: BaseFileIO(fileName, visitMode, op)
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

bool FileIn::openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool binary)
{
	bin = binary;
	return BaseFileIO::openFile(filePath, visitMode, op);
}

bool FileIn::isBinaryVisit()
{
	return bin;
}

int FileIn::strToInt(std::string str)
{
	std::istringstream is(str);
	int num;
	is >> num;
	return num;
}

double FileIn::strToDouble(std::string str)
{
	std::istringstream is(str);
	double num;
	is >> num;
	return num;
}

FileIn & operator >> (FileIn & fop, int & number)
{
	if (fop.isBinaryVisit()) {
		fop.readFile(&number, sizeof(int));
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
	if (fop.isBinaryVisit()) {
		fop.readFile(&number, sizeof(double));
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
	fop.readFile(&ch, sizeof(char));
	if (fop.isEof()) {
		ch = -1;
	}
	return fop;
}

FileIn & operator >> (FileIn & fop, std::string & str)
{
	str.clear();
	char tar;
	do {
		fop >> tar;
		if (tar == ' ' || tar == -1) break;
		str += tar;
	} while (true);
	return fop;
}
