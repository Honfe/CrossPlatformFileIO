#include "BaseFileIO.h"

BaseFileIO::BaseFileIO()
{
	id = OPEN_FAIL;
	eof = false;
	err = NO_ERR;
}

BaseFileIO::BaseFileIO(std::string fileName, _mode_code visitMode, _mode_code op)
{
	id = __OPEN_FILE(fileName.data(), visitMode, op);
	if (id == OPEN_FAIL) {
		err = OPEN_ERR;
	}
	else {
		err = NO_ERR;
	}
	eof = false;
}

BaseFileIO::~BaseFileIO()
{
	if (id != OPEN_FAIL) {
		__CLOSE_FILE(id);
	}
}

bool BaseFileIO::openFile(std::string filePath, _mode_code visitMode, _mode_code op)
{
	if ((id = __OPEN_FILE(filePath.data(), visitMode, op)) != OPEN_FAIL) {
		return true;
	}
	else {
		return false;
	}
}

int BaseFileIO::readFile(void * buffer, int type)
{
	int readSize = 0;
	eof = false;
	if ((readSize = __READ_FROM_FILE(id, buffer, type)) >= 0) {
		if (readSize == 0) {
			eof = true;
		}
		return readSize;
	}
	else {
		err = READ_ERR;
		return -1;
	}
}

int BaseFileIO::writeFile(void * buffer, int type)
{
	_file_int writtenSize = 0;
	if ((writtenSize = __WRITE_TO_FILE(id, buffer, type)) >= 0) {
		return writtenSize;
	}
	else {
		err = WRITE_ERR;
		return -1;
	}
}

bool BaseFileIO::setPositionFilePointor(int absPos, int offset)
{
	int pos = 0;
	if ((pos = __SET_POSITION_FILE(id, absPos, offset)) != SEEK_FAIL) {
		return pos;
	}
	else {
		err = SEEK_ERR;
		return -1;
	}
}

bool BaseFileIO::closeFile()
{
	if (__CLOSE_FILE(id) == CLOSE_SUC) {
		id = OPEN_FAIL;
		return true;
	}
	else {
		err = CLOSE_ERR;
		return false;
	}
}

bool BaseFileIO::isEof()
{
	return eof;
}

int BaseFileIO::getErrorCode()
{
	return err;
}

std::string BaseFileIO::getErrorMsg()
{
	std::string msg;
	switch (err) {
	case NO_ERR:
		msg = "no error";
		break;
	case OPEN_ERR:
		msg = "open file error";
		break;
	case READ_ERR:
		msg = "read file error";
		break;
	case WRITE_ERR:
		msg = "write file error";
		break;
	case SEEK_ERR:
		msg = "change file pointer error";
		break;
	case CLOSE_ERR:
		msg = "close file error";
		break;
	default:
		break;
	}
	return msg;
}

#ifdef _WIN32

inline int __inline_WriteToFile(_file_id id, void * buffer, int size)
{
	_file_int writtenSize = 0;
	if (::WriteFile(id, buffer, size, &writtenSize, NULL)) {
		return writtenSize;
	}
	else {
		return WRITE_ERR;
	}
}

inline int __inline_ReadFromFile(_file_id id, void * buffer, int size)
{
	_file_int readSize = 0;
	if (::ReadFile(id, buffer, size, &readSize, NULL)) {
		return readSize;
	}
	else {
		return READ_ERR;
	}
}

#endif
