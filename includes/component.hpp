#pragma once
#include <vector>
#include <string>

using namespace std;

class Component{
    
    public:
    Component(){
        state_=false;
        evaluate_count_=0;
        max_inputs_=0;
    }
    void virtual Evaluate() = 0;
    bool GetState(){return state_;}
    void AttachInput(Component* device){
        if (max_inputs_==0 || inputs_.size()<max_inputs_){
            inputs_.push_back(device);
            device->outputs_.push_back(this);
        }
    }
    protected:
    vector<Component*> inputs_;
    vector<Component*> outputs_;
    bool state_;
    size_t evaluate_count_;
    size_t max_inputs_;
    string name;
};

class AndGate : public Component{
    public:
    AndGate(){
        max_inputs_=0;
        state_=false;
        evaluate_count_=0;
    }
    void Evaluate() override{
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_==inputs_.size()){
            bool temp = true;
            for (size_t i=0; i<inputs_.size(); i++){
                temp = temp && inputs_[i]->GetState();
            }
            state_=temp;
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
            evaluate_count_=0;
        }

    }

};

class NandGate : public Component{
    public:
    NandGate(){
        max_inputs_=0;
        state_=false;
        evaluate_count_=0;
    }
    void Evaluate() override{
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_==inputs_.size()){
            bool temp = true;
            for (size_t i=0; i<inputs_.size(); i++){
                temp = temp && inputs_[i]->GetState();
            }
            if (inputs_.empty()) temp=false;
            state_=!temp;
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
            evaluate_count_=0;
        }

    }

};

class OrGate : public Component{
    public:
    OrGate(){
        max_inputs_=0;
        state_=false;
        evaluate_count_=0;
    }
    void Evaluate() override{
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_==inputs_.size()){
            bool temp = false;
            for (size_t i=0; i<inputs_.size(); i++){
                temp = temp || inputs_[i]->GetState();
            }
            state_=temp;
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
            evaluate_count_=0;
        }
    }
};

class NorGate : public Component{
    public:
    NorGate(){
        max_inputs_=0;
        state_=false;
        evaluate_count_=0;
    }
    void Evaluate() override{
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_==inputs_.size()){
            bool temp = false;
            for (size_t i=0; i<inputs_.size(); i++){
                temp = temp || inputs_[i]->GetState();
            }
            state_=!temp;
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
            evaluate_count_=0;
        }
    }
};

class XorGate : public Component{
    public:
    XorGate(){
        max_inputs_=0;
        state_=false;
        evaluate_count_=0;
    }
    void Evaluate() override{
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_==inputs_.size()){
            bool temp = false;
            for (size_t i=0; i<inputs_.size(); i++){
                bool st = inputs_[i]->GetState();
                if (temp && st) temp=false;
                else temp = temp || st;
            }
            state_=temp;
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
            evaluate_count_=0;
        }
    }
};

class NotGate : public Component{
    public:
    NotGate(){
        max_inputs_=1;
        state_=false;
        evaluate_count_=0;
    }
    void Evaluate() override{
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_==inputs_.size()){
            state_ = !(inputs_[0]->GetState());
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
            evaluate_count_=0;
        }
    }
};

class Register : public Component{
    public:
        Register(){
            max_inputs_=0;
            state_=false;
            evaluate_count_=0;
        }
        void SetState(bool state){
            state_=state;
        }
        void AttachInputs(Component * device) = delete;
        void Evaluate() override{
            for (size_t i=0; i<outputs_.size(); i++){
                outputs_[i]->Evaluate();
            }
        }
};

class Monitor : public Component{
    public:
        Monitor(){
            max_inputs_=1;
            state_=false;
            evaluate_count_=0;
        }
        void Evaluate() override{
            state_=inputs_[0]->GetState();
        }
};