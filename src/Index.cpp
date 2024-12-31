#pragma once
#include <stdexcept>
#include"ExpressionTree.h"
#include"Exceptions.h"
#include"Value.h"
#include"Number.cpp"
#include"Variable.cpp"
#include"Environment.h"
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
    void assign(pair<Value*, string> value) {
        pair<Value*, string> a = array->getValue();
        if(a.second != "array" && a.second != "string") throw runtime_error(invalid_type(collum, pos, "array", a.second));
        pair<Value*, string> i = id->getValue();

        if(a.second == "array") {
            (*(a.first->a))[i.first->i] = value;
        }
        else if(a.second == "string") {
            (*(a.first->s))[i.first->i*3] = (*value.first->s)[0];
            (*(a.first->s))[i.first->i*3+1] = (*value.first->s)[1];
            (*(a.first->s))[i.first->i*3+2] = (*value.first->s)[2];
        }
    }
private:
    ExpressionTree* array;
    ExpressionTree* id;
};
