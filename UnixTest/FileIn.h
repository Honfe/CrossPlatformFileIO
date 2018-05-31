#ifndef FILEIN_H_
#define FILEIN_H_

#include <iostream>
#include <string>
#include "BaseFileIO.h"

#define f_bin	true

class FileIn : public BaseFileIO {
private:
	int latestReadSize;
	bool bin;

public:
	FileIn();
	FileIn(std::string fileName, _mode_code visitMode, _mode_code op, bool binary = false);
	virtual ~FileIn();

	int getLatestReadSize();

	bool openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool binary = false);

	friend FileIn & operator >> (FileIn & fop, int & number);

	friend FileIn & operator >> (FileIn & fop, double & number);

	friend FileIn & operator >> (FileIn & fop, char & ch);

	friend FileIn & operator >> (FileIn & fop, std::string & str);

	bool isBinaryVisit();

public:
	int strToInt(std::string str);

	double strToDouble(std::string str);

};

#endif
