#pragma once
#include <stdexcept>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include"Value.cpp"
#include"Number.cpp"
#include"Variable.cpp"
#include"Environment.cpp"
using namespace std;

class CallFunc : public ExpressionTree {
public:
    CallFunc(ExpressionTree* f, vector<ExpressionTree*> a, int c, int p) {
        functree = f;
        args = a;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> f = functree->getValue();
        if(f.second != "function") throw runtime_error(invalid_type(collum, pos, "function", f.second));
        Func* func = f.first->fun;

        if(args.size() != func->args.size()) throw runtime_error(not_match_argments(collum, pos));
        Environments::pushEnvironment();
        for(int i = 0; i < args.size(); i++) {
            Environments::setvar(func->args[i], args[i]->getValue());
        }
        pair<Value*, string> result = func->code->getValue();
        Environments::popEnvironment();
        return result;
    }
private:
    ExpressionTree* functree;
    vector<ExpressionTree*> args;
};
