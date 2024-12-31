#pragma once
#include"ExpressionTree.h"
#include"Exceptions.h"
#include <stdexcept>
#include"Value.h"
using namespace std;

class String : public ExpressionTree {
public:
    String(string s, int c, int p) {
        str = s;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "数"));
    }
    pair<Value*, string> getValue() {
        return pair<Value*, string>(new Value(&str), "string");
    }
private:
    string str;
};
