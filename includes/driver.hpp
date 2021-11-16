#pragma once
#include <string>
#include <vector>

using namespace std;

enum command{ HELP, SAVE, LOAD, ADD, WIRE, UNWIRE, DELETE, LIST, UNKNOWN };
//and, or, not, nor, nand, xor, register, monitor

command GetCommand(const string &argument);

void Add(std::string& first_arg, std::string& second_arg, std::string& third_arg);
bool IsInMap(std::string& extended_module, std::string& name);
void AddToMap(std::string& extended_module, std::string& name);