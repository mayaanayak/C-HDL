#pragma once
#include <string>
#include <vector>

using namespace std;

enum command{ HELP, SAVE, LOAD, ADD, WIRE, UNWIRE, DELETE, LIST, UNKNOWN };
//and, or, not, nor, nand, xor, register, monitor

command GetCommand(const string &argument);

bool IsInMap(string& module, string& name);
bool IsAModule(string& potential_module);

void Add(string& module, string& name);
void AddToMap(string& module, string& name);

void Delete(string& module, string& name);
void DeleteFromMap(string& module, string& name);

void List(string& module_type);