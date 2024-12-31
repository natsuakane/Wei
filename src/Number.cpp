#pragma once
#include"ExpressionTree.h"
#include"Exceptions.h"
#include <stdexcept>
#include"Value.h"
using namespace std;

class Number : public ExpressionTree {
public:
    Number(long num, int c, int p) {
        number = num;
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
        return pair<Value*, string>(new Value(number), "integer");
    }
private:
    long number;
};
