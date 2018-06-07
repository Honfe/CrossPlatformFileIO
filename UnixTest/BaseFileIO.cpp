#include "BaseFileIO.h"

BaseFileIO::BaseFileIO()
{
	id = OPEN_FAIL;	// 文件标识设置为无效
	eof = false;			// 文件标识无效的情况下eof默认false
	err = NO_ERR;
}

BaseFileIO::BaseFileIO(std::string fileName, _mode_code visitMode, _mode_code op)
{
	id = __OPEN_FILE(fileName.data(), visitMode, op);
	// 检查打开文件操作的结果，设置错误代码
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
	// 如果此时文件未关闭，则关闭文件
	if (id != OPEN_FAIL) {
		__CLOSE_FILE(id);
	}
}

bool BaseFileIO::openFile(std::string filePath, _mode_code visitMode, _mode_code op)
{
	// 检查文件打开操作的结果，并更新错误代码
	if ((id = __OPEN_FILE(filePath.data(), visitMode, op)) != OPEN_FAIL) {
		err = NO_ERR;
		eof = false;		// 刚打开的文件EOF默认false
		return true;
	}
	else {
		err = OPEN_ERR;
		return false;
	}
}

int BaseFileIO::readFile(void * buffer, int type)
{
	int readSize = 0;
	eof = false;	// 读取之前默认eof为false
	// 读取文件并检查读取情况
	if ((readSize = __READ_FROM_FILE(id, buffer, type)) >= 0) {
		if (readSize == 0)		// 如果读取0个字节则说明到达文件尾端
			eof = true;
		err = NO_ERR;
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
	// 写入文件并检查写入情况
	if ((writtenSize = __WRITE_TO_FILE(id, buffer, type)) >= 0) {
		err = NO_ERR;
		return writtenSize;
	}
	else {
		err = WRITE_ERR;
		return -1;
	}
}

int BaseFileIO::setPositionFilePointor(int absPos, int offset)
{
	int pos = 0;
	// 检查改变文件指针的情况
	if ((pos = __SET_POSITION_FILE(id, absPos, offset)) != SEEK_FAIL) {
		err = NO_ERR;
		return pos;
	}
	else {
		err = SEEK_ERR;
		return -1;
	}
}

bool BaseFileIO::closeFile()
{
	// 检查文件关闭情况
	if (__CLOSE_FILE(id) == CLOSE_SUC) {
		err = NO_ERR;
		id = OPEN_FAIL;	// 重置文件标识变量
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
	// 检查错误代码并返回相应的错误消息
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

// Windows环境下特有的函数，用于API形式转换
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
