#include "stdafx.h"
#include "LoopEl.h"

string LoopEl::toString() {
    return to_string(count) + " from " + to_string(index_command) + "; ";
}
