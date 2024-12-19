#pragma once
#include<string>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
using namespace std;

class UnaryOperator : public ExpressionTree {
public:
    UnaryOperator(string o, ExpressionTree* e, int c, int p) {
        op = o;
        exp = e;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        if(i == 0) return exp;
        throw runtime_error(type_has_no_children(collum, pos, i, "二項演算子"));
    }
private:
    string op;
    ExpressionTree* exp;
};
