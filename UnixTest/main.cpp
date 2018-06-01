#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "FileIn.h"
#include "FileOut.h"

using namespace std;

int main()
{	
	string res1 = "Hello World";
	FileOut fout("allo.txt", f_out, f_exist);
	cout << fout.getErrorMsg() << endl;
	fout << res1;
	cout << fout.getErrorMsg() << endl;
	fout.closeFile();
	cout << fout.getErrorMsg() << endl;

	string res;
	FileIn fin("allo.txt", f_in, f_exist);
	cout << fout.getErrorMsg() << endl;
	fin >> res;
	cout << fout.getErrorMsg() << endl;
	cout << res << endl;
	cout << fout.getErrorMsg() << endl;
	fin.closeFile();
	cout << fout.getErrorMsg() << endl;

	return 0;
}
