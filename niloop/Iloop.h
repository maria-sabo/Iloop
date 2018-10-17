#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "LoopEl.h"
#include "VarEl.h"
#include "Command.h"
#include <algorithm>
#include <sstream>
using namespace std;
class Iloop
{
public:
	int loadListProg(ifstream& F);
	int loadListVar(ifstream& F);

	int checkSyntax(ofstream& F);
	Command checkpline(string text, int ns);
	Command checkvline(string text, int ns);

	void doProg(ofstream& F, int comlimit);
	int  doCommand(int c, int p1, int p2, int p3, int * index);
	int findvar(int p1);
	int getloop(int *index);
	int putloop(int p1, int index);
	void putvar(int p1, int value);
	int getvar(int p1);
	int checkloop();

	void printList(vector<Command> list, ofstream& F);
	string varToString();
    string loopToString();

private:
	vector<LoopEl> loopEl_list;
	vector<VarEl> varEl_list;
	vector<Command> prog_list;
	vector<Command> var_list;
};

