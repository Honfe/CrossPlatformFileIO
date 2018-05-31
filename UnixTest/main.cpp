#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "FileIO.h"

using namespace std;

int main()
{
	double str1 = 2.7;
	double res, res2;
	FileOut fout("Hello.txt", f_out, f_new | f_trunc, f_bin);
	fout << str1;
	fout.closeFile();

	FileIn fin("Hello.txt", f_in, f_exist, f_bin);
	fin >> res;
	cout << res << endl;
	fin.closeFile();

	return 0;
}
