#include "../includes/command.hpp"

map<string, Component*> register_map;
map<string, Component*> schematic_map;
map<string, Component*> monitor_map;
string mstr = "monitor";
string rstr = "register";

command GetCommand(const string &argument) {
    if (!argument.find("help")) { 
        return HELP;
    }
    if (!argument.find("exit")) {
        clearMaps();
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
    if (!argument.find("clear")){
        return CLEAR;
    }
    return UNKNOWN;
}

void clearMaps(){
    for (auto it = register_map.begin(); it!=register_map.end();){
        Component* c = it->second;
        it = register_map.erase(it);
        delete c;
    }
    for (auto it = schematic_map.begin(); it!=schematic_map.end();){
        Component* c = it->second;
        it = schematic_map.erase(it);
        delete c;
    }
    for (auto it = monitor_map.begin(); it!=monitor_map.end();){
        Component* c = it->second;
        it = monitor_map.erase(it);
        delete c;
    }
}

vector<string> SeparateByDel(const string& line) {
    vector<string> sep_by_del;
    ifstream fd;
    fd.open(line);
    if (fd.is_open()){
        string temp;
        while(std::getline(fd, temp)) {
            sep_by_del.push_back(temp);
        }
        
    } else{
        cout << "File does not exist." << endl;
    }
    return sep_by_del;
} 


vector<string> GetFullVectorFromLine(const string& line) {
    string names=line;
    stringstream ssname(names);
    string t;
    vector<string> names_vector;
    while (ssname>>t){
        names_vector.push_back(t);
    }
    return names_vector;
}

void AttachListInput(const string& line){
    vector<string> list = GetFullVectorFromLine(line);
    for (size_t i=1;i<list.size();i++){
        auto smap = schematic_map.find(list[0]);
        if (smap==schematic_map.end()){
            smap = monitor_map.find(list[0]);
        }
        auto tmap = schematic_map.find(list[i]);
        if (tmap==schematic_map.end()){
            tmap = register_map.find(list[i]);
        }
        Component* c1 = smap->second;
        Component* c2 = tmap->second;
        c1->AttachInput(c2);
    }
}

void Deserialize(const string& file) {
    vector<string> lines = SeparateByDel(file);
    if (lines.empty()) return;
    vector<string> corresponding_module = {"register", "and", "nand", "or", "nor", "xor", "not", "monitor"};
    for (size_t i = 0; i < 8; i++) {
        LineToMap(corresponding_module.at(i), lines.at(i));
    }
    for (size_t i = 8; i<lines.size();i++){
        AttachListInput(lines.at(i));
    }
}

void LineToMap(const string& module, const string& line) {
     vector<string> names = GetNamesVectorFromLine(line);
     for (size_t i = 0; i < names.size(); i++) {
         AddToMap(module, names.at(i));
     }
}

vector<string> GetNamesVectorFromLine(const string& line) {
    string names = line.substr(line.find(' ') + 1);
    stringstream ssname(names);
    string t;
    vector<string> names_vector;
    while (ssname>>t){
        names_vector.push_back(t);
    }
    return names_vector;
}

void Serialize(const string& file_name) {
    ofstream ofs{file_name};
    ofs << "Registers " << KeysToString(register_map) << "\n";
    ofs << SchematicKeysToString();
    ofs << "Monitors " << KeysToString(monitor_map) << "\n";
    ofs << ConnectionsToString();
}

string ConnectionsToString() {
    string connection_string;
    for (auto const& component : schematic_map) {
        connection_string += component.second->GetName() + " ";
        vector<Component*> inputs = component.second->GetInputs();
        for (auto const& component : inputs) {
            connection_string += component->GetName() + " ";
        }
        connection_string += "\n";
    }
    for (auto const& component : monitor_map) {
        connection_string += component.second->GetName() + " ";
        vector<Component*> inputs = component.second->GetInputs();
        for (auto const& component : inputs) {
            connection_string += component->GetName() + " ";
        }
        connection_string += "\n";
    }
    return connection_string;
}

string KeysToString(const map<string, Component*>& kMap) {
    string keys;
    for (auto const& key_and_value : kMap) {
        string key = key_and_value.first;
        keys += key + " ";
    }
    return keys;
}

string SchematicKeysToString() {
    string schematic_string;
    vector<string> and_names, nand_names, or_names, nor_names, xor_names, not_names;
    for (auto const& component : schematic_map) {
        string gate_type = component.second->GetGateName();
        if (gate_type == "and") {
            and_names.push_back(component.first);
        } else if (gate_type == "nand") {
            nand_names.push_back(component.first);
        } else if (gate_type == "or") {
            or_names.push_back(component.first);
        } else if (gate_type == "nor") {
            nor_names.push_back(component.first);
        } else if (gate_type == "xor") {
            xor_names.push_back(component.first);
        } else {
            not_names.push_back(component.first);
        }
    }
    schematic_string += "And " + PrintVector(and_names) + "\n";
    schematic_string += "Nand " + PrintVector(nand_names) + "\n";
    schematic_string += "Or " + PrintVector(or_names) + "\n";
    schematic_string += "Nor " + PrintVector(nor_names) + "\n";
    schematic_string += "Xor " + PrintVector(xor_names) + "\n";
    schematic_string += "Not " + PrintVector(not_names) + "\n";
    return schematic_string;
}

string PrintVector(const vector<string>& vector) {
    string vector_string;
    for (string str : vector) vector_string += str + " ";
    return vector_string;
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

void Add(string& module, string& name) {
    if (!IsAModule(module)) {
       cout << "Second argument should be a module" << endl;
       return;
    }
    string a;
    if (!(IsInMap(mstr, name) || IsInMap(rstr, name) || IsInMap(a, name))) {
        AddToMap(module, name);
    } else{
        cout << "Module \"" << name << "\" already exists" << endl;
    }
}

void AddToMap(const string& module, const string& name) {
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

void Delete(string& name) {
    string a;
    if (IsInMap(mstr, name)) {
        DeleteFromMap(mstr, name);
        cout << "Deleted \"" << name << "\"" << endl;
    } else if(IsInMap(rstr, name)){
        DeleteFromMap(rstr, name);
        cout << "Deleted \"" << name << "\"" << endl;
    } else if (IsInMap(a, name)){
        DeleteFromMap(a, name);
        cout << "Deleted \"" << name << "\"" << endl;
    } else{
        cout << "Module \"" << name << "\" does not exist" << endl;
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

void Wire(string& from, string& to) {
    Component* fromptr = nullptr;
    Component* toptr = nullptr;
    if (IsInMap(mstr, from)) {
        cout << "Can't connect monitors to other modules" << endl;
        return;
    } 
    if (IsInMap(rstr,from)) {
        fromptr = register_map.find(from)->second;
    } else {
        auto it = schematic_map.find(from);
        if (it == schematic_map.end()) {
            cout << "Module does not exist" << endl;
            return;
        }
        fromptr = it->second;
    }
    if (IsInMap(rstr, to)) {
        cout << "Can't connect other modules to registers" << endl;
        return;
    }
    if (IsInMap(mstr, to)) {
        toptr = monitor_map.find(to)->second;
    } else {
        auto it = schematic_map.find(to);
        if (it == schematic_map.end()){
            cout << "Module does not exist" << endl;
            return;
        }
        toptr = it->second;
    }
    auto inputVec = toptr->GetInputs();
    if (find(inputVec.begin(), inputVec.end(), fromptr)!=inputVec.end()){
        cout << "Wire already exists" << endl;
        return;
    }
    toptr->AttachInput(fromptr);
}

void Unwire(string& from, string& to) {
    Component* fromptr = nullptr;
    Component* toptr = nullptr;
    if (IsInMap(mstr, from)){
        cout << "Wire shouldn't exist" << endl;
        return;
    } 
    if (IsInMap(rstr,from)) {
        fromptr = register_map.find(from)->second;
    } else {
        auto it = schematic_map.find(from);
        if (it == schematic_map.end()){
            cout << "Module does not exist" << endl;
            return;
        }
        fromptr = it->second;
    }
    if (IsInMap(rstr, to)) {
        cout << "Wire shouldn't exist" << endl;
        return;
    }
    if (IsInMap(mstr, to)) {
        toptr = monitor_map.find(to)->second;
    } else {
        auto it = schematic_map.find(to);
        if (it == schematic_map.end()){
            cout << "Module does not exist" << endl;
            return;
        }
        toptr = it->second;
    }
    if(!(toptr->RemoveInput(fromptr))) {
        cout << "No wire existed" << endl;
    }
}

void List(string& module_type) {
    bool reg=true,mod=true,mon=true;
    if (module_type == "registers") {
        mod=false; mon=false;
    } else if (module_type == "modules") {
        reg=false; mon=false;
    } else if (module_type == "monitors") {
        reg=false; mod=false;
    } else if (module_type != "" && module_type != "all") {
        cout << "Unknown Component Group" << endl;
        return;
    }
    if (reg) {
        cout << "-- Registers ---" << endl;
        for (auto it = register_map.begin(); it != register_map.end(); it++){
            cout << it->first << endl;
        }
    }
    if (mod) {
        cout << "-- Modules -----" << endl;
        for (auto it = schematic_map.begin(); it != schematic_map.end(); it++) {
            cout << it->first << " - " << it->second->GetGateName() << endl;
        }
    }
    if (mon) {
        cout << "-- Monitors ----" << endl;
        for (auto it = monitor_map.begin(); it != monitor_map.end(); it++){
            cout << it->first << endl;
        }
    }
}

void Simulate(vector<string>& args) {
    if (args.size() < 1+2*register_map.size()){
        cout << "Missing states or register inputs" << endl;
        return;
    }
    if (args.size() > 1+2*register_map.size()){
        cout << "Too many states or register inputs" << endl;
    }
    for (auto reg : register_map) {
        ((Register*)reg.second)->SetState(false);
    }
    for (size_t i = 1; i < args.size(); i += 2) {
        auto reg = register_map.find(args[i]);
        bool x = false;
        try{
            x = stoi(args[i + 1]);
        } catch(...){
            cout << "Invalid state input" << endl;
            return;
        }
        ((Register*)reg->second)->SetState(x);
    }
    for (auto reg : register_map) {
        ((Register*)reg.second)->Evaluate();
    }
    for (auto mon : monitor_map) {
        cout << mon.second->GetName() << " " << mon.second->GetState() << endl;
    }
}