#include "../includes/component.hpp"
#include "../includes/command.hpp"
#include <sstream>
#include <stdexcept>
#include <ostream>
using namespace std;

static string progTitle = "  _____  __    __    __ _____  __ \n / ___/_/ /___/ /_  / // / _ \\/ / \n/ /__/_  __/_  __/ / _  / // / /__\n\\___/ /_/   /_/   /_//_/____/____/";
static string helpStringA = "help - prints this\nexit - terminates program\nsave <filename> - saves schematic to local directory\nload <filename> - loads schematic from local directory (clears any unsaved work!)";
static string helpStringB = "\n\nadd <module> <name> - adds a module with the given name\ndelete <module> <name> - removes a module with the given name\nwire <src> <dest> - connects source module to destination module\nunwire <src> <dest> - removes connection from source module to destination module, if one exists\nlist [registers/modules/monitors/all] - lists the created modules";

int main() {
    cout << progTitle << endl << endl;
    cout << "Type 'help' for a list of commands. Type 'exit' to quit." << endl;
    
    //Handle autoload schematic

    while (true) {
        
        string command;
        cout << "> ";
        getline(cin, command);

        stringstream sscom(command);
        string arg;
        vector<string> arguments;
        while (sscom >> arg) arguments.push_back(arg);

        auto com = GetCommand(arguments[0]);

        switch(com) {
            case HELP:
                cout << helpStringA << helpStringB << endl;
                break;
            case ADD:
                if (arguments.size()<3) {
                    cout << "Missing Module type or Name" << endl;
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
                if (arguments.size()<3) {
                    cout << "Missing Module type or Name" << endl;
                    break;
                }
                Delete(arguments[1],arguments[2]);
                break;
            case WIRE:
                if (arguments.size()<3) {
                    cout << "Missing module names" << endl;
                    break;
                }
                Wire(arguments[1], arguments[2]);
                break;
            case UNWIRE:
                if (arguments.size()<3) {
                    cout << "missing module names" << endl;
                    break;
                }
                Unwire(arguments[1], arguments[2]);
                break;
            case RUN:
                Simulate(arguments);
                break;
            case SAVE:
                Serialize(arguments[1]);
                break;
            case LOAD:
                Deserialize(arguments[1]);
                break;
            case UNKNOWN:
                cout << "Unknown Command." << endl;
                break;
            default:
                break;
        }


    }

}
