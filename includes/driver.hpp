#pragma once
#include <string>
#include <vector>

using namespace std;

enum command{HELP, SAVE, LOAD, ADD, WIRE, UNWIRE, DELETE, LIST, UNKNOWN};

command GetCommand(const string &argument);