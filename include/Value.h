#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 前方宣言
class ExpressionTree;

struct Func {
    Func(vector<string> a, ExpressionTree* c) : args(a), code(c) {}

    vector<string> args;
    ExpressionTree* code;
};

union Value {
    long i;
    double f;
    string* s;
    vector<pair<Value*, string>>* a;
    Func* fun;
    unordered_map<string, pair<Value*, string>>* obj;

    Value(long v) : i(v) {}
    Value(double v) : f(v) {}
    Value(string* v) : s(v) {}
    Value(vector<pair<Value*, string>>* v) : a(v) {}
    Value(Func* f) : fun(f) {}
    Value(unordered_map<string, pair<Value*, string>>* o) : obj(o) {}
    Value(const Value& other, const string& type);
};
