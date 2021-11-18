#include "../includes/component.hpp"
#include "../includes/driver.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <algorithm>
using namespace std;

static string progTitle = "  _____  __    __    __ _____  __ \n / ___/_/ /___/ /_  / // / _ \\/ / \n/ /__/_  __/_  __/ / _  / // / /__\n\\___/ /_/   /_/   /_//_/____/____/";
static string helpStringA = "help - prints this\nexit - terminates program\nsave <filename> - saves schematic to local directory\nload <filename> - loads schematic from local directory (clears any unsaved work!)";
static string helpStringB = "\n\nadd <module> <name> - adds a module with the given name\ndelete <name> - removes a module with the given name\nwire <src> <dest> - connects source module to destination module\nunwire <src> <dest> - removes connection from source module to destination module, if one exists\nlist [registers/modules/monitors/all] - lists the created modules";

map<string, Component*> register_map;
map<string, Component*> schematic_map;
map<string, Component*> monitor_map;

int main(){
    cout << progTitle << endl << endl;
    cout << "Type 'help' for a list of commands. Type 'exit' to quit." << endl;

    //Handle autoload schematic

    while (true){
        string command;
        cout << "> ";
        getline(cin, command);

        stringstream sscom(command);
        string arg;
        vector<string> arguments;
        while (sscom >> arg) arguments.push_back(arg);

        auto com = GetCommand(arguments[0]);

        switch(com){
            case HELP:
                cout << helpStringA<<helpStringB << endl;
                break;
            case UNKNOWN:
                cout << "Unknown Command." << endl;
                break;
            default:
                break;
        }


    }
    // Register x1;
    // Register x2;
    // AndGate a1;
    // x1.SetState(true);
    // x2.SetState(true);
    // a1.AttachInput(&x1);
    // a1.AttachInput(&x1);
    // cout << a1.GetState() << endl;
    // x1.Evaluate();
    // x2.Evaluate();
    // cout << a1.GetState() << endl;
}


command GetCommand(const string &argument) {
    if (!argument.find("help")) { 
        return HELP;
    }
    if (!argument.find("exit")) {
        exit(0);
    }
    if (!argument.find("load")) {
        return LOAD;
    }
    if (!argument.find("save")) {
        return SAVE;
    }
    if (!argument.find("list")){
        return LIST;
    }
    if (!argument.find("add")) {
        return ADD;
    }
    if (!argument.find("wire")) {
        return WIRE;
    }
    if (!argument.find("unwire")) {
        return UNWIRE;
    }
    if (!argument.find("delete")) {
        return DELETE;
    }
    return UNKNOWN;
}

void Add(string& first_arg, string& second_arg, string& third_arg) {
    if (first_arg != "add") throw invalid_argument("First argument should be 'add'");
    vector<string> extended_modules {"and", "or", "not", "nor", "nand", "xor", "register", "monitor"};
    if (find(extended_modules.begin(), extended_modules.end(), second_arg) == extended_modules.end()) {
        throw invalid_argument("Second argument should be a module");
    }
    if (!IsInMap(second_arg, third_arg)) {
        AddToMap(second_arg, third_arg);
    }
}

bool IsInMap(string& extended_module, string& name) {
    if (extended_module == "register") {
        return !(register_map.find(name) == register_map.end());
    }
    if (extended_module == "monitor") {
        return !(monitor_map.find(name) == monitor_map.end());
    }
    return !(schematic_map.find(name) == schematic_map.end());
}

void AddToMap(string& extended_module, string& name) {
    if (extended_module == "register") {
        auto* to_add = new Register();
        register_map[name] = to_add;
        return;
    }
    if (extended_module == "monitor") {
        auto* to_add = new Monitor();
        monitor_map[name] = to_add;
        return;
    }
    Component* to_add;
    if (extended_module == "and") {
        to_add = new AndGate();
    } else if (extended_module == "or") {
        to_add = new OrGate();
    } else if (extended_module == "not") {
        to_add = new NotGate();
    } else if (extended_module == "nor") {
        to_add = new NorGate();
    } else if (extended_module == "nand") {
        to_add = new NandGate();
    } else {
        to_add = new XorGate();
    }
    schematic_map[name] = to_add;
}