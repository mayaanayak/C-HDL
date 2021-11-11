#include "../includes/component.hpp"
#include <iostream>
using namespace std;
int main(){
    Register x1;
    Register x2;
    AndGate a1;
    x1.SetState(true);
    x2.SetState(true);
    a1.AttachInput(&x1);
    a1.AttachInput(&x1);
    cout<<a1.GetState()<<endl;
    x1.Evaluate();
    x2.Evaluate();
    cout<<a1.GetState()<<endl;
}
