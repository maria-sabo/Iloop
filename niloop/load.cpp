#include "stdafx.h"
#include "Iloop.h"

int Iloop::loadListProg(ifstream& F) {
	if (F.is_open()) {
		while (!F.eof())	{
			string buffer = ""; 
			string buffer1  = "";
			string buffer2  = "";
			getline(F, buffer,';');	
		    buffer.erase (remove(buffer.begin(), buffer.end(), ' '), buffer.end());
			buffer.erase (remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
			buffer.erase (remove(buffer.begin(), buffer.end(), '\t'), buffer.end());
			if (buffer != "") {
			    int ex = 1;
				while(ex) {
					size_t pos = buffer.find("DO");
					if (pos == string::npos){
						Command com(0, buffer, 0, 0, 0, 0, 0);
						prog_list.push_back(com);
						ex = 0;
					}
					else {
						buffer1 = buffer.substr(0,pos);
						Command com(0, buffer1, 0, 0, 0, 0, 0);
						prog_list.push_back(com);
						Command com1(0, "DO", 0, 0, 0, 0, 0);
						prog_list.push_back(com1);
						buffer2 = buffer.substr(pos+2); 
						buffer = buffer2;
					}
				}
			}
		}
	//printList(prog_list, F);
		return 1;
	}
	else
		return 0;
}
int Iloop::loadListVar(ifstream& F) {
	if (F.is_open()) {
		while (!F.eof())	{
			string buffer = ""; 
			getline(F, buffer,',');	
		    buffer.erase (remove(buffer.begin(), buffer.end(), ' '), buffer.end());
			buffer.erase (remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
			buffer.erase (remove(buffer.begin(), buffer.end(), '\t'), buffer.end());
				Command com(0, buffer, 0, 0, 0, 0, 0);
				var_list.push_back(com);
			
		}
//		printList(var_list, NULL);
		return 1;
	}
	else
		return 0;
}