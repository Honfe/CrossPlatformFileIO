#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "FileIO.h"

using namespace std;

int main()
{
	string str1 = "ni zou!";
	string res, res2;
	FileOut fout("llo.txt", f_out, f_exist);
	fout << str1;
	fout.closeFile();

	FileIn fin("llo.txt", f_in, f_exist);
	fin >> res;
	cout << res << endl;
	fin.closeFile();

	return 0;
}
