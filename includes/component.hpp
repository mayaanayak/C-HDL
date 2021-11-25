#pragma once
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Component {
    
    public:
    Component() {
        state_ = false;
        evaluate_count_ = 0;
        max_inputs_ = 0;
    }
    void virtual Evaluate() = 0;
    bool GetState() { return state_; }
    void AttachInput(Component* device) {
        if (max_inputs_ == 0 || inputs_.size() < max_inputs_) {
            inputs_.push_back(device);
            device->outputs_.push_back(this);
        }
    }
    bool RemoveInput(Component* device){
        if (!inputs_.empty()){
            auto it = find(inputs_.begin(), inputs_.end(), device);
            if (it==inputs_.end()){
                return false;
            }
            inputs_.erase(it);
            auto reit = find(device->outputs_.begin(), device->outputs_.end(), this);
            device->outputs_.erase(reit);
            return true;
        }
        return false;
    }
    string& getGateName(){
        return gateType;
    }
    string& getName(){
        return name_;
    }
    protected:
    vector<Component*> inputs_;
    vector<Component*> outputs_;
    bool state_;
    size_t evaluate_count_;
    size_t max_inputs_;
    string name_;
    string gateType;
};

class AndGate : public Component {
    public:
    AndGate(string name) {
        max_inputs_ = 0;
        state_ = false;
        evaluate_count_ = 0;
        gateType = "and";
        name_=name;
    }
    void Evaluate() override {
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_ == inputs_.size()) {
            state_ = true;
            for (Component* input : inputs_) {
                if (!input->GetState()) {
                    state_ = false;
                    break;
                }
            }
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
            evaluate_count_ = 0;
        }
    }

};

class NandGate : public Component {
    public:
    NandGate(string name) {
        max_inputs_ = 0;
        state_ = false;
        evaluate_count_ = 0;
        gateType = "nand";
        name_=name;
    }
    void Evaluate() override {
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_ == inputs_.size()) {
            state_ = true;
            for (Component* input : inputs_) {
                if (!input->GetState()) {
                    state_ = false;
                    break;
                }
            }
            state_ = !state_;
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
            evaluate_count_ = 0;
        }

    }

};

class OrGate : public Component {
    public:
    OrGate(string name) {
        max_inputs_ = 0;
        state_ = false;
        evaluate_count_ = 0;
        gateType = "or";
        name_=name;
    }
    void Evaluate() override {
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_ == inputs_.size()) {
            state_ = false;
            for (Component* input : inputs_) {
                if (input->GetState()) {
                    state_ = true;
                    break;
                }
            }
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
            evaluate_count_ = 0;
        }
    }
};

class NorGate : public Component {
    public:
    NorGate(string name) {
        max_inputs_ = 0;
        state_ = false;
        evaluate_count_ = 0;
        gateType = "nor";
        name_=name;
    }
    void Evaluate() override {
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_ == inputs_.size()) {
            state_ = false;
            for (Component* input : inputs_) {
                if (input->GetState()) {
                    state_ = true;
                    break;
                }
            }
            state_ = !state_;
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
            evaluate_count_ = 0;
        }
    }
};

class XorGate : public Component {
    public:
    XorGate(string name) {
        max_inputs_ = 0;
        state_ = false;
        evaluate_count_ = 0;
        gateType = "xor";
        name_=name;
    }
    void Evaluate() override {
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_ == inputs_.size()) {
            state_ = false;
            for (Component* input : inputs_) {
                state_ ^= input->GetState();
            }
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
            evaluate_count_ = 0;
        }
    }
};

class NotGate : public Component {
    public:
    NotGate(string name) {
        max_inputs_ = 1;
        state_ = false;
        evaluate_count_ = 0;
        gateType = "not";
        name_=name;
    }
    void Evaluate() override {
        if (inputs_.empty()) return;
        evaluate_count_++;
        if (evaluate_count_ == inputs_.size()) {
            state_ = !(inputs_[0]->GetState());
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
            evaluate_count_ = 0;
        }
    }
};

class Register : public Component {
    public:
        Register(string name) {
            max_inputs_ = 0;
            state_ = false;
            evaluate_count_ = 0;
            name_=name;
        }
        void SetState(bool state) {
            state_ = state;
        }
        void AttachInput(Component * device) = delete;
        void Evaluate() override {
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i]->Evaluate();
            }
        }
};

class Monitor : public Component {
    public:
        Monitor(string name) {
            max_inputs_ = 1;
            state_ = false;
            evaluate_count_ = 0;
            name_=name;
        }
        void Evaluate() override {
            state_ = inputs_[0]->GetState();
        }
};
