#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "FileIO.h"

using namespace std;

int main()
{
	double str1 = 2.66;
	double res, res2;
	FileOut fout("llo.txt", f_out, f_new);
	fout << str1;
	fout.closeFile();

	FileIn fin("llo.txt", f_in, f_exist);
	fin >> res;
	cout << res << endl;
	fin.closeFile();

	return 0;
}
