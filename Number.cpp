#pragma once
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include <stdexcept>
using namespace std;

class Number : public ExpressionTree {
public:
    Number(int num, int c, int p) {
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
private:
    int number;
};
