#pragma once
#include"ExpressionTree.h"
#include"Exceptions.h"
#include <stdexcept>
#include"Value.h"
#include"Variable.cpp"
using namespace std;

class Object : public ExpressionTree {
public:
    Object(vector<pair<ExpressionTree*, ExpressionTree*> > vars, int c, int p) {
        variables = vars;
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
        unordered_map<string, pair<Value*, string> >* res = new unordered_map<string, pair<Value*, string> >();

        for(auto variable : variables) {
            Variable* var = dynamic_cast<Variable*>(variable.first);
            if(var) {
                pair<Value*, string> value = make_pair(nullptr, "null");
                if(variable.second != nullptr) {
                    value = variable.second->getValue();
                }
                (*res)[var->getname()] = value;
            }
            else throw runtime_error(invalid_type_assign(collum, pos));
        }

        return make_pair(new Value(res), "object");
    }
private:
    vector<pair<ExpressionTree*, ExpressionTree*> > variables;
};
