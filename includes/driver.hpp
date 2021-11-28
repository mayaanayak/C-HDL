#pragma once
#include "component.hpp"
#include <map>
#include <string>
#include <vector>

using namespace std;

enum command{ HELP, SAVE, LOAD, ADD, WIRE, UNWIRE, DELETE, LIST, RUN, UNKNOWN };
//and, or, not, nor, nand, xor, register, monitor

command GetCommand(const string &argument);

void ToNewFile(const string& file_name);
string KeysToString(const map<string, Component*>& kMap);
string SchematicKeysToString();
string PrintVector(const vector<string>& vector);

bool IsInMap(string& module, string& name);
bool IsAModule(string& potential_module);

void Add(string& module, string& name);
void AddToMap(string& module, string& name);

void Delete(string& module, string& name);
void DeleteFromMap(string& module, string& name);

void Wire(string& from, string& to);
void Unwire(string& from, string& to);

void List(string& module_type);

void Simulate(vector<string>& args);