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
    pair<Value*, string> getValue() {
        if(op == "負") {
            pair<Value*, string> v = exp->getValue();
            if(v.second == "integer") {
                return pair<Value*, string>(new Value(-1 * v.first->i), "integer");
            }
        }
        if(op == "不") {
            pair<Value*, string> v = exp->getValue();
            if(v.second == "integer") {
                return pair<Value*, string>(new Value(v.first->i == 0 ? 1l : 0l), "integer");
            }
        }
        return pair<Value*, string>(nullptr, "");
    }
private:
    string op;
    ExpressionTree* exp;
};
