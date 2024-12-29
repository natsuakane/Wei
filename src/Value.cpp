#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<unordered_map>
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
    vector<pair<Value*, string> >* a;
    Func* fun;
    unordered_map<string, pair<Value*, string> >* obj;

    Value(long v) {
        i = v;
    }
    Value(double v) {
        f = v;
    }
    Value(string* v) {
        s = v;
    }
    Value(vector<pair<Value*, string> >* v) {
        a = v;
    }
    Value(Func* f) {
        fun = f;
    }
    Value(unordered_map<string, pair<Value*, string> >* o) {
        obj = o;
    }
    Value(const Value& other, string type) {
        // コピー元の型に応じた処理を行う
        if (type == "string") {
            s = new string(*other.s);  // ポインタ型の場合は深いコピー
        } else if (type == "array") {
            a = new vector<pair<Value*, string> >(*other.a);
        } else if (type == "function") {
            fun = new Func(*other.fun);
        } else if (type == "integer") {
            i = other.i;
        } else if (type == "float") {
            f = other.f;
        } else if (type == "object") {
            obj = new unordered_map<string, pair<Value*, string> >(*other.obj);
        }
    }
};
