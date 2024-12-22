#pragma once
#include<vector>
#include<string>
using namespace std;

union Value {
public:
    long i;
    double f;
    string s();
    vector<Value> a();

    Value(long v) {
        i = v;
    }
    Value(double v) {
        f = v;
    }
    Value(string v) {
        s() = v;
    }
    Value(vector<Value> v) {
        a() = v;
    }
};
