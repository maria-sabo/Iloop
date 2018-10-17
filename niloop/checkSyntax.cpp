#include "stdafx.h"
#include <iostream>
#include "Iloop.h"

int Iloop::checkSyntax(ofstream& F) {
	int k_end = 0;
	int k_do = 0;
	int k_loop = 0; // количество end, do, loop в программе	int er = 0;
	int er = 0;
	int nc = 0;
	int errvar_count = 0;
	int errprog_count = 0;

	for (int i = 0; i < var_list.size(); i++) {
		var_list[i] = checkvline(var_list[i].get_commandText(), i);
		if (var_list[i].get_error() != 0)
			errvar_count++;
	}
	printList(var_list, F);
	cout << "Programm: " << errvar_count << " syntax error found\n";
	system("pause");
	
	er = 0;
	nc = 0;
	for (int i = 0; i < prog_list.size(); i++) {
		prog_list[i] = checkpline(prog_list[i].get_commandText(), i);
		if (prog_list[i].get_error() != 0)
			errvar_count++;
		switch (prog_list[i].get_command()) {
		case 1:
			k_loop++;
			break;
		case 2:
			k_do++;
			if (k_do > k_loop)
				prog_list[i].put_error(14);
			break;
		case 3:
			k_end++;
			if (k_end > k_loop || k_end > k_do)
				prog_list[i].put_error(15);
			break;
		}
	}
	printList(prog_list, F);
	if (k_end != k_loop || k_do != k_loop || k_end != k_do) {
		cout <<"Programm: " << k_loop << " LOOP - " << k_do << " DO - " << k_end << " END error found\n";
		errprog_count++; 
	}
	cout << "Programm: " << errprog_count << " syntax error found\n";
	system("pause");
	if (errvar_count + errprog_count != 0) 
		return 0;
	else
		return 1;

}

Command Iloop::checkpline(string text, int ns) {
	int of, p1, p2, p3;
	Command com(ns, text, 0, 0, 0, 0, 0);

	size_t pos = text.find("DO");
	if (pos != string::npos) {
		// DO входит в строку
		if (text.length() == 2) {
			// 2 - длина DO
			com.set_command(ns, text, 2, 0, 0, 0, 0);
		}
		else 
			com.set_command(ns, text, 2, 1, 0, 0, 0);
	}
	else {
		size_t pos = text.find("END");
		if (pos != string::npos) {
			// END входит в строку
			if (text.length() == 3) {
				// 2 - длина END			
					com.set_command(ns, text, 3, 0, 0, 0, 0);
			}
			else
				com.set_command(ns, text, 3, 2, 0, 0, 0);
		}
		else {
			size_t pos = text.find("LOOPx");
			if (pos != string::npos) {
				// LOOPx входит в строку
				if (text.length() == 5 || pos != 0) {
					// 5 - длина LOOPx
					com.set_command(ns, text, 1, 3, 0, 0, 0);
				}
				else {
						of = 1;
						for (size_t i = 5; i < text.length(); i++) {
							if (text[i] < 48 || text[i] > 57)  // после х стоит число, состоящее не из цифр (проверка по ASCII)
								of = 0;
						}
						if (!of)
							com.set_command(ns, text, 1, 4, 0, 0, 0); // ошибка в индексе х после LOOP
						else {
							p1 = atoi(text.substr(5).c_str()); // в p1 будет храниться индекс х
							if (p1 <= INT_MAX && p1 >= 0) {
								com.set_command(ns, text, 1, 0, p1, 0, 0);
							}
							else
								com.set_command(ns, text, 1, 24, 0, 0, 0);
						}
				}		
			}
			else {
				// присваивание
				size_t pos = text.find(":=");
				if (pos != string::npos) {
					string left = text.substr(0, pos);
					string right = text.substr(pos+2);
					size_t pos = left.find("x");
					if (pos != string::npos) {
						if (pos != 0 || left.length() == 1) {
							com.set_command(ns, text, 4, 6, 0, 0, 0); // мусорв левой части
						}
						else {
							of = 1;
							for (size_t i = 1; i < left.length(); i++) {
								if ((int)left[i] < 48 || (int)left[i] > 57) { // после х не стоит число, состоящее из цифр (проверка по ASCII)
									of = 0;
								}
							}
							if (!of) {
								com.set_command(ns, text, 4, 7, 0, 0, 0);
							}
							else {
								p1 = atoi(left.substr(1).c_str()); // в p1 будет храниться индекc х
								if (p1 > INT_MAX || p1 < 0) {
									com.set_command(ns, text, 4, 24, 0, 0, 0);
								}
								else {
									size_t pos = right.find("+");
									if (pos != string::npos) {
										//+
										string rleft = right.substr(0, pos);
										string rright = right.substr(pos + 1);
										size_t pos = rleft.find("x");
										if (pos != string::npos) {
											//
											if (pos != 0 || rleft.length() == 1) {
												com.set_command(ns, text, 5, 5, 0, 0, 0);
											}
											else {
												of = 1;
												for (size_t i = 1; i < rleft.length(); i++)
													if (rleft[i] < 48 || rleft[i] > 57) // после х не стоит число, состоящее из цифр (проверка по ASCII)
														of = 0;
												if (!of) {
													com.set_command(ns, text, 4, 5, 0, 0, 0);
												}
												else {
													p2 = atoi(rleft.substr(1).c_str()); // в p2 будет храниться индекс хM  
													if (p2 > INT_MAX || p2 < 0) {
														com.set_command(ns, text, 4, 24, 0, 0, 0);
													}
													else {
														of = 1;
														for (int i = 0; i < rright.length(); i++) {
															if ((int)rright[i] < 48 || (int)rright[i] > 57)
																of = 0;
														}
														if (!of) {
															com.set_command(ns, text, 4, 23, 0, 0, 0);
														}
														else {
															p3 = atoi(rright.c_str()); // в p3 будет храниться C
															com.set_command(ns, text, 4, 0, p1, p2, p3);
														}
													}
												}
											}
										}
										else {
											com.set_command(ns, text, 4, 5, 0, 0, 0);
										}								
									}
									else {
										size_t pos = right.find("-");
										if (pos != string::npos) {
											//-
											string rleft = right.substr(0, pos);
											string rright = right.substr(pos + 1);
											size_t pos = rleft.find("x");
											if (pos != string::npos) {
												//
												if (pos != 0 || rleft.length() == 1) {
													com.set_command(ns, text, 5, 5, 0, 0, 0);
												}
												else {
													of = 1;
													for (size_t i = 1; i < rleft.length(); i++)
														if (rleft[i] < 48 || rleft[i] > 57) // после х не стоит число, состоящее из цифр (проверка по ASCII)
															of = 0;
													if (!of) {
														com.set_command(ns, text, 5, 5, 0, 0, 0);
													}
													else {
														p2 = atoi(rleft.substr(1).c_str()); // в p2 будет храниться индекс хM  
														if (p2 > INT_MAX || p2 < 0) {
															com.set_command(ns, text, 5, 24, 0, 0, 0);
														}
														else {
															of = 1;
															for (int i = 0; i < rright.length(); i++) {
																if ((int)rright[i] < 48 || (int)rright[i] > 57)
																	of = 0;
															}
															if (!of) {
																com.set_command(ns, text, 5, 23, 0, 0, 0);
															}
															else {
																p3 = atoi(rright.c_str()); // в p3 будет храниться C
																com.set_command(ns, text, 5, 0, p1, p2, p3);
															}
														}
													}
												}
											}
											else {
												com.set_command(ns, text, 5, 5, 0, 0, 0);
											}
										}
										else {
											com.set_command(ns, text, 4, 8, 0, 0, 0); // no +-
										}
									
									}
								
								}
							}
						}
					}
					else {
						com.set_command(ns, text, 4, 6, 0, 0, 0); // мусор в левой части
					}
				}
				else {
					com.set_command(ns, text, 7, 13, 0, 0, 0); // неизвестная команда
				}
			}
		}
	}
	return com;
}
Command Iloop::checkvline(string text, int ns) {
	int of, p1, p2;
	Command com(ns, text, 0, 0, 0, 0, 0);
	size_t pos = text.find("=");
	if (pos == string::npos) {
		com.set_command(ns, text, 7, 13, 0, 0, 0);
	}
	else {
		string left = text.substr(0, pos);
		string right = text.substr(pos+1);
		pos = left.find("x");
		if (pos == string::npos) 
			com.set_command(ns, text, 6, 10, 0, 0, 0);
		else {
			if (pos !=0 || left.length() == 1)
				com.set_command(ns, text, 6, 10, 0, 0, 0);
			else {
				of = 1;
				for (int i = 1; i < left.length(); i++) {
					if (left[i] < 48 || left[i] > 57)  // после х не стоит число, состоящее из цифр (проверка по ASCII)
						of = 0;
				}
				if (!of) 
					com.set_command(ns, text, 6, 11, 0, 0, 0); // после х не цифровые символы 
				else {
					p1 = atoi(left.substr(1).c_str());
					if (p1 > INT_MAX || p1 < 0) 
						com.set_command(ns, text, 6, 24, p1, 0, 0); // индекс превышен
					else {
						of = 1;
						for (int i = 1; i < right.length(); i++) {
							if (right[i] < 48 || right[i] > 57) { // после х не стоит число, состоящее из цифр (проверка по ASCII)
								of = 0;
							}
						}
						if (!of) {
							com.set_command(ns, text, 6, 12, p1, 0, 0); // некорректная записать в правой части 
						}
						else {
							p2 = atoi(right.c_str());
							com.set_command(ns, text, 6, 0, p1, p2, p2);
						}
					}
				}			
			}
		}
	}
	return com;
}


