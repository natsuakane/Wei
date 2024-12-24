#pragma once
#include <stdexcept>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include"Value.cpp"
#include"Number.cpp"
#include"Variable.cpp"
#include"Environment.cpp"
using namespace std;

class DecFunc : public ExpressionTree {
public:
    DecFunc(string n, vector<string> a, ExpressionTree* co, int c, int p) {
        name = n;
        args = a;
        code = co;
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
        Environments::setfunc(name, new Func(args, code));
        return pair<Value*, string>(new Value(new Func(args, code)), "function");
    }
private:
    string name;
    vector<string> args;
    ExpressionTree* code;
};
