#include "../includes/component.hpp"
#include "../includes/driver.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <ostream>
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
                if (arguments.size()<3){
                    cout<<"Missing Module type or Name"<<endl;
                    break;
                }
                Add(arguments[1], arguments[2]);
                break;
            case LIST:
            {
                string arg = (arguments.size()>1) ? arguments[1] : "";
                List(arg);
                break;
            }
            case DELETE:
                if (arguments.size()<3){
                    cout<<"Missing Module type or Name"<<endl;
                    break;
                }
                Delete(arguments[1],arguments[2]);
                break;
            case WIRE:
                if (arguments.size()<3){
                    cout<<"Missing module names"<<endl;
                    break;
                }
                Wire(arguments[1], arguments[2]);
                break;
            case UNWIRE:
                if (arguments.size()<3){
                    cout<<"missing module names"<<endl;
                    break;
                }
                Unwire(arguments[1], arguments[2]);
                break;
            case RUN:
                Simulate(arguments);
                break;
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
    if (!argument.find("run")){
        return RUN;
    }
    return UNKNOWN;
}

void ToNewFile(const string& file_name) {
    ofstream ofs{file_name};
    ofs << "Registers: " << KeysToString(register_map) << "\n";
    ofs << SchematicKeysToString();
    ofs << "Monitors: " << KeysToString(monitor_map) << "\n";
}

string SchematicKeysToString() {
    string schematic_string;
    vector<string> and_names, nand_names, or_names, nor_names, xor_names, not_names;
    for (auto const& component : schematic_map) {
        if (dynamic_cast<AndGate*>(component.second) != nullptr) {
            and_names.push_back(component.first);
        } else if (dynamic_cast<NandGate*>(component.second) != nullptr) {
            nand_names.push_back(component.first);
        } else if (dynamic_cast<OrGate*>(component.second) != nullptr) {
            or_names.push_back(component.first);
        } else if (dynamic_cast<NorGate*>(component.second) != nullptr) {
            nor_names.push_back(component.first);
        } else if (dynamic_cast<XorGate*>(component.second) != nullptr) {
            xor_names.push_back(component.first);
        } else {
            not_names.push_back(component.first);
        }
    }
    schematic_string += "And: " + PrintVector(and_names) + "\n";
    schematic_string += "Nand: " + PrintVector(nand_names) + "\n";
    schematic_string += "Or: " + PrintVector(or_names) + "\n";
    schematic_string += "Nor: " + PrintVector(nor_names) + "\n";
    schematic_string += "Xor: " + PrintVector(xor_names) + "\n";
    schematic_string += "Not: " + PrintVector(not_names) + "\n";
    return schematic_string;
}

string PrintVector(const vector<string>& vector) {
    string vector_string;
    for (string str : vector) vector_string += str + " ";
    return vector_string;
}

string KeysToString(const map<string, Component*>& kMap) {
    string keys;
    for (auto const& key_and_value : kMap) {
        string key = key_and_value.first;
        keys += key + " ";
    }
    return keys;
}

void Delete(string& module, string& name) {
    if (!IsAModule(module)) {
        cout<<"Second argument should be a module"<<endl;
    }
    if (IsInMap(module, name)) {
        DeleteFromMap(module, name);
        cout<<"Deleted \""<<name<<"\""<<endl;
    } else{
        cout<<"Module \""<<name<<"\" does not exist"<<endl;
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
    } else{
        cout<<"Module \""<<name<<"\" already exists"<<endl;
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
    return find(extended_modules.begin(), extended_modules.end(), potential_module) != extended_modules.end();
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

void Wire(string& from, string& to){
    string m = "monitor";
    string r = "register";
    Component* fromptr = nullptr;
    Component* toptr = nullptr;
    if (IsInMap(m, from)){
        cout<<"Can't connect monitors to other modules"<<endl;
        return;
    } 
    if (IsInMap(r,from)){
        fromptr = register_map.find(from)->second;
    } else{
        auto it = schematic_map.find(from);
        if (it==schematic_map.end()){
            cout<<"Module does not exist"<<endl;
            return;
        }
        fromptr = it->second;
    }
    if (IsInMap(r, to)){
        cout<<"Can't connect other modules to registers"<<endl;
        return;
    }
    if (IsInMap(m, to)){
        toptr = monitor_map.find(to)->second;
    } else{
        auto it = schematic_map.find(to);
        if (it==schematic_map.end()){
            cout<<"Module does not exist"<<endl;
            return;
        }
        toptr = it->second;
    }
    toptr->AttachInput(fromptr);
}

void Unwire(string& from, string& to){
    string m = "monitor";
    string r = "register";
    Component* fromptr = nullptr;
    Component* toptr = nullptr;
    if (IsInMap(m, from)){
        cout<<"Wire shouldn't exist"<<endl;
        return;
    } 
    if (IsInMap(r,from)){
        fromptr = register_map.find(from)->second;
    } else{
        auto it = schematic_map.find(from);
        if (it==schematic_map.end()){
            cout<<"Module does not exist"<<endl;
            return;
        }
        fromptr = it->second;
    }
    if (IsInMap(r, to)){
        cout<<"Wire shouldn't exist"<<endl;
        return;
    }
    if (IsInMap(m, to)){
        toptr = monitor_map.find(to)->second;
    } else{
        auto it = schematic_map.find(to);
        if (it==schematic_map.end()){
            cout<<"Module does not exist"<<endl;
            return;
        }
        toptr = it->second;
    }
    if(!(toptr->RemoveInput(fromptr))){
        cout<<"No wire existed"<<endl;
    }
}

void Simulate(vector<string>& args){
    if (args.size()%2==0){
        cout<<"Missing states"<<endl;
        return;
    }
    for (auto reg : register_map){
        ((Register*)reg.second)->SetState(false);
    }
    for (size_t i=1; i<args.size(); i+=2){
        auto reg = register_map.find(args[i]);
        bool x = stoi(args[i+1]);
        ((Register*)reg->second)->SetState(x);
    }
    for (auto reg : register_map){
        ((Register*)reg.second)->Evaluate();
    }
    for (auto mon : monitor_map){
        cout<<mon.second->getName()<<" "<<mon.second->GetState()<<endl;
    }
    return;
}