#pragma once
#include<string>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
using namespace std;

class Block : public ExpressionTree {
public:
    Block(vector<ExpressionTree*> e, int c, int p) {
        exp = e;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        if(i < exp.size()) return exp[i];
        throw runtime_error(type_has_no_children(collum, pos, i, "塊"));
    }
    pair<Value*, string> getValue();
private:
    vector<ExpressionTree*> exp;
};

pair<Value*, string> Block::getValue() {
    pair<Value*, string> result;
    for(ExpressionTree* e : exp) {
        result = e->getValue();
    }
    return result;
}
