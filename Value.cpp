#pragma once
#include<vector>
#include<string>
#include"ExpressionTree.cpp"
using namespace std;

class ExpressionTree;

struct Func {
public:
    Func(vector<string> a, ExpressionTree* c) {
        args = a;
        code = c;
    }
    vector<string> args;
    ExpressionTree* code;
};

union Value {
public:
    long i;
    double f;
    string* s;
    vector<pair<Value, string> > a();
    Func* fun;

    Value(long v) {
        i = v;
    }
    Value(double v) {
        f = v;
    }
    Value(string* v) {
        s = v;
    }
    Value(vector<pair<Value, string> > v) {
        a() = v;
    }
    Value(Func* f) {
        fun = f;
    }
};
