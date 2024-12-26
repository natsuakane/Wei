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

class Index : public ExpressionTree {
public:
    Index(ExpressionTree* a, ExpressionTree* i, int c, int p) {
        array = a;
        id = i;
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
        pair<Value*, string> a = array->getValue();
        if(a.second != "array" && a.second != "string") throw runtime_error(invalid_type(collum, pos, "array", a.second));
        pair<Value*, string> i = id->getValue();

        pair<Value*, string> result;
        if(a.second == "array") {
            if(a.first->a->size() <= i.first->i) throw runtime_error(index_out_of_range(collum, pos));
            result = pair<Value*, string>(new Value(*(a.first->a->at(i.first->i).first), a.first->a->at(i.first->i).second), a.first->a->at(i.first->i).second);
        }
        if(a.second == "string") {
            if(a.first->s->size() < i.first->i * 3 + 3) throw runtime_error(index_out_of_range(collum, pos));
            string* c = new string((a.first->s)->substr(i.first->i*3, 3));
            result = pair<Value*, string>(new Value(c), "string");
        }

        return result;
    }
private:
    ExpressionTree* array;
    ExpressionTree* id;
};
