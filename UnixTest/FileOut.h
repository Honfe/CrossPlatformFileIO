#ifndef FILEOUT_H_
#define FILEOUT_H_

#include <cstring>
#include <string>
#include "BaseFileIO.h"

#define f_bin	true

class FileOut : public BaseFileIO {
private:
	int latestWrittenSize;
	bool bin;

public:
	FileOut();
	FileOut(std::string fileName, _mode_code visitMode, _mode_code op, bool bin = false);
	virtual ~FileOut();

	int getLatestWrittenSize();

	bool openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool bin = false);

	friend FileOut & operator << (FileOut & fop, int & number);

	friend FileOut & operator << (FileOut & fop, double & number);

	friend FileOut & operator << (FileOut & fop, char & ch);

	friend FileOut & operator << (FileOut & fop, std::string & str);

	bool isBinaryVisit();

public:
	std::string numToStr(int number);

	std::string numToStr(double number);

};

#endif
