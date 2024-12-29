#pragma once
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include <stdexcept>
#include"Value.cpp"
#include<iostream>
using namespace std;

class Array : public ExpressionTree {
public:
    Array(vector<ExpressionTree*> a, int c, int p) {
        array = a;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "配列"));
    }
    pair<Value*, string> getValue() {
        vector<pair<Value*, string> >* valuearray = new vector<pair<Value*, string> >();
        for(ExpressionTree* exp : array) {
            valuearray->push_back(exp->getValue());
        }
        return pair<Value*, string>(new Value(valuearray), "array");
    }
private:
    vector<ExpressionTree*> array;
};
