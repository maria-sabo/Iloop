#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class Command
{
public:
	int get_ns() { return ns; }
	string get_commandText() { return commandText; }
	int get_error() { return error; }
	int get_command() { return command; }
	int get_p1() { return p1; }
	int get_p2() { return p2; }
	int get_p3() { return p3; }
	void put_error(int e) { error = e; }
	void put_ns(int e) { ns = e; }
	void put_command(int e) { command = e; }
	void put_p1(int e) { p1 = e; }
	void put_p2(int e) { p2 = e; }
	void put_p3(int e) { p3 = e; }
	
	void set_command(int pns, string pcommandText, int pcommand, int perror, size_t pp1, size_t pp2, size_t pp3);
	Command(int pns, string pcommandText, int pcommand, int perror, size_t pp1, size_t pp2, size_t pp3);

	string toString();
	string get_textError(int error);

private:
	int ns;             // номер строки 
	string commandText; // строка с командой
	int command;        // номер команды
	int error;          // номер ошибки
	size_t p1;          // индекс переменной слева или переменной в LOOP
	size_t p2;          // индекс переменной справа или константа 
	size_t p3;          // константа
	
};


