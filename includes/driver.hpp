#pragma once
#include <string>
#include <vector>

using namespace std;

enum command{ HELP, SAVE, LOAD, ADD, WIRE, UNWIRE, DELETE, LIST, UNKNOWN };
//and, or, not, nor, nand, xor, register, monitor

command GetCommand(const string &argument);

void Add(string& second_arg, string& third_arg);
bool IsInMap(string& extended_module, string& name);
void AddToMap(string& extended_module, string& name);

void List(string& module_type);