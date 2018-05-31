#include "FileOut.h"

FileOut::FileOut()
	: BaseFileIO()
{
	latestWrittenSize = 0;
	bin = false;
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
	this->bin = bin;
	return BaseFileIO::openFile(filePath, visitMode, op);
}

bool FileOut::isBinaryVisit()
{
	return bin;
}

std::string FileOut::numToStr(int number)
{
	//char strNum[100];
	//return itoa(number, strNum, 10);
	return std::string("");
}

std::string FileOut::numToStr(double number)
{
	//char strNum[100] = { 0 };
	//sprintf(strNum, "%g", number);
	return std::string("");
}

FileOut & operator<<(FileOut & fop, int & number)
{
	if (fop.isBinaryVisit()) {
		fop.writeFile(&number, sizeof(int));
	}
	else {
		fop << fop.numToStr(number);
	}
	return fop;
}

FileOut & operator<<(FileOut & fop, double & number)
{
	if (fop.isBinaryVisit()) {
		fop.writeFile(&number, sizeof(double));
	}
	else {
		fop << fop.numToStr(number);
	}
	return fop;
}

FileOut & operator<<(FileOut & fop, char & ch) 
 {
	fop.writeFile(&ch, sizeof(char));
	return fop;
}

FileOut & operator<<(FileOut & fop, std::string & str)
{
	const char * tar = str.data();
	char * pTemp = new char[str.size() + 1];
	strcpy(pTemp, tar);
	fop.writeFile(pTemp, sizeof(char) * str.size());
	delete pTemp;
	return fop;
}
