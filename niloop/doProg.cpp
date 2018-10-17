#include "stdafx.h"
#include "Iloop.h"

void Iloop::doProg(ofstream& F, int comlimit) {

	int er;
	for (int i = 0; i < var_list.size(); i++) {
		er = doCommand(var_list[i].get_command(), var_list[i].get_p1(), var_list[i].get_p2(), var_list[i].get_p3(), &i);
		var_list[i].put_error(er);
		// печать команды
		cout << var_list[i].toString() << endl;
		cout << "                " << varToString() << "    " << loopToString() << endl;
		F << var_list[i].toString() << endl;
		F << "                " << varToString() << "    " << loopToString() << endl;
			
		if (er != 0)
			break;
	}
	if (er != 0) cout << "Variable initialisation error" << endl; 

	int cnt_temp = 0;
	int cnt_all = 0;
	int decision = 0; // решение продолжить ли работу программы
	for (int i = 0; i < prog_list.size(); i++) {
		er = doCommand(prog_list[i].get_command(), prog_list[i].get_p1(), prog_list[i].get_p2(), prog_list[i].get_p3(), &i);
		if (er != -1) {
			prog_list[i].put_error(er);
			// печать команды
			cout << prog_list[i].toString() << endl;
			cout << "                " << varToString() << "    " << loopToString() << endl;
			F << prog_list[i].toString() << endl;
			F << "                " << varToString() << "    " << loopToString() << endl;
		}
		if (er != -1 && er != 0)
			break;
		cnt_temp++;
		if (cnt_temp == comlimit) {
			cnt_all = cnt_all + cnt_temp;
			cnt_temp = 0;
			cout << endl << cnt_all << "commands completed \n0 - continue \n1 - exit" << endl;
			
			scanf("%d", &decision);
			if (decision == 1) {
				cout << "The program is interrupted by user" << endl;
				break;
			}
		}
	}
	if (er != -1 && er != 0) cout << "The program is interrupted" << endl; 
	if (findvar(0)) {
		cout << "x0 = " << getvar(0) << endl;
	}
	else {
		cout << "x0 is not initialised" << endl;
	}
	system("pause");
}
	

int  Iloop::doCommand(int c, int p1, int p2, int p3, int * index) {

	if (!checkloop() && c != 2) // выход, если последний loop нулевой и не END
		return -1;
	int ok = 0;
	int val;
	switch (c) {
	case 1: // LOOPx
		if (!findvar(p1)) 
			ok = 22;
		else
			if (!putloop(p1, *index)) 	
				ok = 21;	
		break;
	case 2: // DO 
		break;
	case 3: // END
		*index = getloop(index);
		break;
	case 4: // :=+
		if (!findvar(p2)) 
			ok = 22;
		else {
			val = getvar(p2);
			putvar(p1, val + p3);
		}
		break;
	case 5: // :=-
		if (!findvar(p2)) 		
			ok = 22;
		else {
			val = getvar(p2);
			putvar(p1, val - p3);
		}
		break;
	case 6: // = 
		putvar(p1, p2);
		break;
	}
	return ok;
}
int Iloop::getloop(int *index) {
	if (loopEl_list.size() != 0) {
		LoopEl le = loopEl_list[loopEl_list.size() - 1];
		loopEl_list.pop_back();
		int count = le.get_count();
		count--;
		if (count < 1)
			return *index;
		else {
			int ind = le.get_index();
			le.put_count(count);
			loopEl_list.push_back(le);
			return ind;  
		}
	}
	else
		return *index; // указатель на текущий узел
}

int Iloop::checkloop() {
	if (loopEl_list.size() == 0)
		return 1;
	if (loopEl_list[loopEl_list.size() -1 ].get_count() < 1)
		return 0;
	else
		return 1;
}

int Iloop::putloop(int p1, int index) {
	if (findvar(p1)) {
		int val = getvar(p1);
		LoopEl le;
		le.put_count(val);
		le.put_index(index);
		loopEl_list.push_back(le);
		return 1;
	}
	else
		return 0;
}

void Iloop::putvar(int p1, int value) {
	int ok = 0;
	for (int i = 0; i < varEl_list.size(); i++) {
		if (varEl_list[i].get_index() == p1) {
			varEl_list[i].put_value(value);
			ok = 1;
			break;
		}
	
	}
	if (!ok) {
		VarEl ve;
		ve.put_index(p1);
		ve.put_value(value);
		varEl_list.push_back(ve);
	}
}

int Iloop::getvar(int p1) {
	int value = 0;
	for (int i = 0; i < varEl_list.size(); i++) {
		if (varEl_list[i].get_index() == p1) {
			value = varEl_list[i].get_value();
			break;
		}

	}
	return value;
}

int Iloop::findvar(int p1) {
	int value = 0;
	for (int i = 0; i < varEl_list.size(); i++) {
		if (varEl_list[i].get_index() == p1) {
			value = 1;
			break;
		}
	}
	return value;
}