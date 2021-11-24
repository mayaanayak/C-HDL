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
static string helpStringB = "\n\nadd <module> <name> - adds a module with the given name\ndelete <module> <name> - removes a module with the given name\nwire <src> <dest> - connects source module to destination module\nunwire <src> <dest> - removes connection from source module to destination module, if one exists\nlist [registers/modules/monitors/all] - lists the created modules";

map<string, Component*> register_map;
map<string, Component*> schematic_map;
map<string, Component*> monitor_map;

int main(){
    cout << progTitle << endl << endl;
    cout << "Type 'help' for a list of commands. Type 'exit' to quit." << endl;

    // Register x1("x1");
    // Register x2("x2");
    // AndGate a1("a1");
    // x1.SetState(true);
    // x2.SetState(true);
    // a1.AttachInput(&x1);
    // a1.AttachInput(&x1);
    // cout << a1.GetState() << endl;
    // x1.Evaluate();
    // x2.Evaluate();
    // cout << a1.GetState() << endl;
    
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
            case ADD:
                Add(arguments[1], arguments[2]);
                break;
            case LIST:
            {
                string arg = (arguments.size()>1) ? arguments[1] : "";
                List(arg);
                break;
            }
            case UNKNOWN:
                cout << "Unknown Command." << endl;
                break;
            default:
                break;
        }


    }

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

void Delete(string& module, string& name) {
    if (!IsAModule(module)) {
        cout<<"Second argument should be a module"<<endl;
    }
    if (IsInMap(module, name)) {
        DeleteFromMap(module, name);
    }
}

void DeleteFromMap(string& module, string& name) {
    if (module == "register") {
        register_map.erase(name);
    } else if (module == "monitor") {
        monitor_map.erase(name);
    } else {
        schematic_map.erase(name);
    }
}

void Add(string& module, string& name) {
    if (!IsAModule(module)) {
       cout<<"Second argument should be a module"<<endl;
       return;
    }
    if (!IsInMap(module, name)) {
        AddToMap(module, name);
    }
}

void AddToMap(string& module, string& name) {
    if (module == "register") {
        auto* to_add = new Register(name);
        register_map[name] = to_add;
        return;
    }
    if (module == "monitor") {
        auto* to_add = new Monitor(name);
        monitor_map[name] = to_add;
        return;
    }
    Component* to_add;
    if (module == "and") {
        to_add = new AndGate(name);
    } else if (module == "or") {
        to_add = new OrGate(name);
    } else if (module == "not") {
        to_add = new NotGate(name);
    } else if (module == "nor") {
        to_add = new NorGate(name);
    } else if (module == "nand") {
        to_add = new NandGate(name);
    } else {
        to_add = new XorGate(name);
    }
    schematic_map[name] = to_add;
}

bool IsInMap(string& module, string& name) {
    if (module == "register") {
        return !(register_map.find(name) == register_map.end());
    }
    if (module == "monitor") {
        return !(monitor_map.find(name) == monitor_map.end());
    }
    return !(schematic_map.find(name) == schematic_map.end());
}

bool IsAModule(string& potential_module) {
    vector<string> extended_modules {"and", "or", "not", "nor", "nand", "xor", "register", "monitor"};
    return find(extended_modules.begin(), extended_modules.end(), potential_module) == extended_modules.end();
}

void List(string& module_type){
    bool reg=true,mod=true,mon=true;
    if (module_type=="registers"){
        mod=false; mon=false;
    } else if (module_type=="modules"){
        reg=false; mon=false;
    } else if (module_type=="monitors"){
        reg=false; mod=false;
    } else if (module_type!="" && module_type!="all"){
        cout<<"Unknown Component Group"<<endl;
        return;
    }
    if (reg){
        cout<<"-- Registers ---"<<endl;
        for (auto it = register_map.begin(); it!=register_map.end(); it++){
            cout<<it->first<<endl;
        }
    }
    if (mod){
        cout<<"-- Modules -----"<<endl;
        for (auto it = schematic_map.begin(); it!=schematic_map.end(); it++){
            cout<<it->first<< " - "<<it->second->getGateName()<<endl;
        }
    }
    if (mon){
        cout<<"-- Monitors ----"<<endl;
        for (auto it = monitor_map.begin(); it!=monitor_map.end(); it++){
            cout<<it->first<<endl;
        }
    }
}