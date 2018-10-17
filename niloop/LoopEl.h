#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;
class LoopEl
{

private:
	int count;
	int index_command;

public:
	string toString();
	int get_count() { return count; }
	int get_index() { return index_command; }
	void put_count(int c) { count = c; }
	void put_index(int index) { index_command = index; }
};


