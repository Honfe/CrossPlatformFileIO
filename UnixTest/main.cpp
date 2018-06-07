#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "FileIn.h"
#include "FileOut.h"

using namespace std;

int main()
{	
	string res1 = "Hello";
	FileOut fout("allo.txt", f_out, f_new);
	cout << fout.getErrorMsg() << endl;
	fout << res1;
	cout << fout.getErrorMsg() << endl;
	fout.closeFile();
	cout << fout.getErrorMsg() << endl;

	string res;
	FileIn fin("allo.txt", f_in, f_exist);
	cout << fin.getErrorMsg() << endl;
	fin >> res;
	cout << fin.getErrorMsg() << endl;
	cout << res << endl;
	cout << fin.getErrorMsg() << endl;
	fin >> res;
	cout << fin.getErrorMsg() << endl;
	cout << res << endl;
	cout << fin.getErrorMsg() << endl;
	fin.closeFile();
	cout << fin.getErrorMsg() << endl;

	return 0;
}
