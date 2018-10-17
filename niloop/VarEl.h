#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class VarEl
{
private:
	int index;
	int value;
public:
	int get_value() { return value; }
	int get_index() { return index; }
	void put_value(int c) { value = c; }
	void put_index(int ind) { index = ind; }
	string toString();
};

