#include "stdafx.h"
#include "VarEl.h"

string VarEl::toString() {
	return "x" + to_string(index) + " = " + to_string(value) + "; ";
}