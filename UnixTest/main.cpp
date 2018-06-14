#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "FileIn.h"
#include "FileOut.h"

using namespace std;

int main()
{	
	// 读写测试
	int a = 3, b = 2, c = 1;
	double fa = 3.2, fb = 0.0, fc = 9.0;
	string str1 = "I_like_UNIX!", str2 = "", str3 = "";
	cout << "Before write" << endl;
	cout << "Interger: a = " << a  << " b = " << b << " c = " << c << endl;
	cout << "Float : fa = " << fa << " fb = " << fb << " fc = " << fc << endl;
	cout << "String: str1 = " << str1 << " str2 = " << str2 << " str3 = " << str3 << endl;

	cout << endl << "Now write the data to Test1.txt and Test2.txt~" << endl;
	// 准备写入文件，以字符流的形式
	FileOut fout1("Test1.txt", f_new);
	cout << fout1.getErrorMsg() << endl;	// 创建文件后输出错误信息，测试getErrorMsg方法
	fout1 << a << " " << fa << " " << str1;
	cout << fout1.getErrorCode() << endl;	// 写入数据后输出错误代码，测试getErrorCode方法
	fout1.closeFile();
	
	// 准备写入文件，以字节流的形式
	FileOut fout2("Test2.txt", f_new, f_bin);
	fout2 << a << fa << str1;
	fout2.closeFile();

	// 准备读取文件，以字符流的形式
	cout << endl << "Now read data from Test1.txt" << endl;
	FileIn fin1("Test1.txt", f_exist);
	fin1 >> b >> fb >> str2;
	cout << "b = " << b << " fb = " << fb << " str2 = " << str2 << endl;

	// 准备读取文件，以字节流的形式
	cout << endl << "Now read data from Test2.txt" << endl;
	FileIn fin2("Test2.txt", f_exist, f_bin);
	fin2 >> c >> fc >> str3;
	cout << "c = " << c << " fc = " << fc << " str3 = " << str3 << endl;
	fin2.closeFile();

	a = 0; // a值设置为0，测试移动文件指针方法
	cout << endl << "Now the file pointer is at eof. I change the file pointer position to file begin by setPositionFilePointor." << endl;
	fin1 >> a;
	cout << "Before change pointer and read from Test1.txt: a = " << a << endl;
	// 将文件指针移动到文件头
	fin1.setPositionFilePointor(f_set, 0);
	fin1 >> a;
	cout << "After change pointer and read from Test1.txt: a = " << a << endl;
	fin1.closeFile();

	return 0;
}
