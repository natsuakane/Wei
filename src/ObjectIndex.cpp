#pragma once
#include <stdexcept>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include"Value.cpp"
#include"Number.cpp"
#include"Variable.cpp"
#include"Environment.cpp"
#include<iostream>
using namespace std;

class ObjectIndex : public ExpressionTree {
public:
    ObjectIndex(ExpressionTree* o, ExpressionTree* i, int c, int p) {
        object = o;
        id = i;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "物体"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> obj = object->getValue();
        if(obj.second != "object") throw runtime_error(invalid_type(collum, pos, "object", obj.second));
        Variable* var = dynamic_cast<Variable*>(id);
        if(var) {
            pair<Value*, string> result;
            result = pair<Value*, string>(new Value(*(obj.first->obj->find(var->getname())->second.first), obj.first->obj->find(var->getname())->second.second), obj.first->obj->find(var->getname())->second.second);

            return result;
        }

        throw runtime_error(unknown_variable(collum, pos, "???"));
    }

    void assign(pair<Value*, string> value) {
        pair<Value*, string> obj = object->getValue();
        if(obj.second != "object") throw runtime_error(invalid_type(collum, pos, "object", obj.second));
        Variable* var = dynamic_cast<Variable*>(id);
        if(var) {
            (*(obj.first->obj))[var->getname()] = value;
        }
        else throw runtime_error(unknown_variable(collum, pos, "???"));
    }
private:
    ExpressionTree* object;
    ExpressionTree* id;
};
