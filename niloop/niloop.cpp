// iloop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Iloop.h"

#define COMLIMIT 100

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	ifstream file_prog;
	ifstream file_var;
	ofstream ofile;

	// вывод справки
	if (argc == 2 && strcmp(argv[1], "help") == 0) {
		cout  <<
			"\tFor access the commands used, run the program with the key. 'help' \n"
			"\tFor running the program you need to write paths to files. \n"
			"\tUnnecessary COMLIMIT –  positive integer. Default COMLIMIT = 100.  \n"
			"\tExample: iloop.exe program.txt var.txt out.txt [COMLIMIT] (not necessary)\n\n"
			"You can use commands such as this: \n\txN := xM +- C;\n\tLOOP xi\n\tDO\n\tsomething...\n\tEND;\n"
			"You can input parametres such as this: x0 = C1, ... xN = CN \n"
			"You can use only non-negative integer \n" << endl;
		system("pause");
		return 0;
	}
	if (argc < 4) {
		cout << "Author: Sabo Maria \n"
			"\tThis program interpret programs written in the LOOP language.\n"
			"\tFor access the commands used, run the program with the key. 'help' \n"
			"\tFor running the program you need to write paths to files. \n"
			"\tUnnecessary COMLIMIT –  positive integer. Default COMLIMIT = 100.  \n"
			"\tExample: iloop.exe program.txt var.txt out.txt [COMLIMIT](not necessary) \n" << endl;
		system("pause");
		return 0;
	}
	if (strcmp(argv[1], argv[3]) == 0 || strcmp(argv[2], argv[3]) == 0) {
		cout << "Input file name and output file name couldn't equal" << endl;
		return 0;
	}
	// необязательный пятый аргумент
	int comlimit;
	if (argc == 5) {
		comlimit = atoi(argv[4]);
		if (comlimit <= 0) {
			cout << "Wrong COMLIMIT parameter \n" << endl;
			return 0;
		}
	}
	else
		comlimit = COMLIMIT;

	
	ofile.open(argv[3]);
	if (!ofile.is_open()) {
		cout << "Output file " << argv[3] << " can not be create" << endl;
		system("pause");
		return 0;
	}
	file_prog.open(argv[1]);
	if (!file_prog.is_open()) {
		cout << "File " << argv[1] << " is not found" << endl;
		system("pause");
		return 0;
	}
	else {
		file_var.open(argv[2]);
		if (!file_var.is_open()) {
			cout << "File " << argv[2] << " is not found" << endl;
			system("pause");
			return 0;
		}
		else {
			// выполнение программы, если файлы загружены и синтаксический разбор не имеет ошибок
			Iloop iloop;
			if (iloop.loadListProg(file_prog) && iloop.loadListVar(file_var)) {
				if (iloop.checkSyntax(ofile))
					iloop.doProg(ofile, comlimit);
			}
			else
				cout << "Load program error" << endl;
			file_var.close();
		}
		file_prog.close();
	}
	if (ofile.is_open()) ofile.close();
	cout << "The programm is completed" << endl;
	system("pause");
	return 0;

}


