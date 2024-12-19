#pragma once
#include<string>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
using namespace std;

class BinaryOperator : public ExpressionTree {
public:
    BinaryOperator(string o, ExpressionTree* e1, ExpressionTree* e2, int c, int p) {
        op = o;
        exp1 = e1;
        exp2 = e2;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        if(i == 0) return exp1;
        if(i == 1) return exp2;
        throw runtime_error(type_has_no_children(collum, pos, i, "二項演算子"));
    }
private:
    string op;
    ExpressionTree* exp1;
    ExpressionTree* exp2;
};
