#include "stdafx.h"
#include "Iloop.h"


void Iloop::printList(vector<Command> list, ofstream& F) {
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].toString() << endl;
		F << list[i].toString() << endl;
	}
}

string Iloop::varToString() {
	string s = "";
	for (int i = 0; i < varEl_list.size(); i++) {
		s =  s + varEl_list[i].toString() + " ";
	}
	return s;
	
}

string Iloop::loopToString() {
	string s = "";
	for (int i = 0; i < loopEl_list.size(); i++){
		s = s + loopEl_list[i].toString() + " ";
	}
	return s;
}