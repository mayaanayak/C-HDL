#include "../includes/component.hpp"
#include "../includes/driver.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;

static string progTitle = "  _____  __    __    __ _____  __ \n / ___/_/ /___/ /_  / // / _ \\/ / \n/ /__/_  __/_  __/ / _  / // / /__\n\\___/ /_/   /_/   /_//_/____/____/";
static string helpStringA = "help - prints this\nexit - terminates program\nsave <filename> - saves schematic to local directory\nload <filename> - loads schematic from local directory (clears any unsaved work!)";
static string helpStringB = "\n\nadd <module> <name> - adds a module with the given name\ndelete <name> - removes a module with the given name\nwire <src> <dest> - connects source module to destination module\nunwire <src> <dest> - removes connection from source module to destination module, if one exists\nlist [registers/modules/monitors/all] - lists the created modules";
int main(){
    cout << progTitle << endl << endl;
    cout << "Type 'help' for a list of commands. Type 'exit' to quit." << endl;

    //Handle autoload schematic

    map<string, Component*> registerMap;
    map<string, Component*> schematicMap;
    map<string, Component*> monitorMap;

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