#include "stdafx.h"
#include "Command.h"

Command::Command(int pns, string pcommandText, int pcommand, int perror, size_t pp1, size_t pp2, size_t pp3)
{
	ns = pns;
	commandText = pcommandText;
	command = pcommand;
	error = perror;
	p1 = pp1;
	p2 = pp2;
	p3 = pp3;
}
void Command::set_command(int pns, string pcommandText, int pcommand, int perror, size_t pp1, size_t pp2, size_t pp3) {
	ns = pns;
	commandText = pcommandText;
	command = pcommand;
	error = perror;
	p1 = pp1;
	p2 = pp2;
	p3 = pp3;
}
string Command::toString() {
	int ns = get_ns();
	string Ct = get_commandText();
	string te = get_textError(error);
    return to_string(ns)+ " " + Ct + " " + te + " ";
}
string Command::get_textError(int error) {
	string er = "";
	switch (error) {
	case 0:
		er = "\0";
		break;
	case 1:
		er = " er: 1 Garbage characters in the use of DO";
		break;
	case 2:
		er = "  er: 2 Garbage characters in the use of END";
		break;
	case 3:
		er = "  er: 3 Garbage characters in the use of LOOP-X";
		break;
	case 4:
		er = "  er: 4 Garbage characters in the index of LOOP x";
		break;
	case 5:
		er = "   er: 5 Garbage characters in the left part of +-";
		break;
	case 6:
		er = "   er: 5 Garbage characters in the left part of +-";
		break;
	case 7:
		er = "  er: 7 Garbage characters in the index of left part";
		break;
	case 8:
		er = "  er: 8 Plus or minus are not found";
		break;
	case 9:
		er = " er: 9 There is unrecognised command";
		break;
	case 10:
		er = " er: 10 Garbage characters in the use of х";
		break;
	case 11:
		er = " er: 11 Garbage characters in the index of x";
		break;
	case 12:
		er = "er: 12 Garbage characters in the right part of = ";
		break;
	case 13:
		er = "er: 13 There is unrecognised command";
		break;
	case 14:
		er = " er: 14 Count of DO greater than LOOP";
		break;
	case 15:
		er = " er: 15 Count of END greater than LOOP or DO";
		break;
	case 21:
		er = "er: 21 The x is not available";
		break;
	case 22:
		er = " er: 22 The x is not initialised";
		break;
	case 23:
		er = " er: 23 Garbage characters in the right part of +- \0";
		break;
	case 24:
		er = "  er: 24 Limit of index is exceeded \0";
		break;
	}
	return er;
}