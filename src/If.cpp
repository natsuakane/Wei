#pragma once
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include <stdexcept>
#include"Value.cpp"
using namespace std;

class If : public ExpressionTree {
public:
    If(ExpressionTree* e, ExpressionTree* codet, ExpressionTree* codef, int c, int p) {
        exp = e;
        codetrue = codet;
        codefalse = codef;
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
        if(exp->getValue().first->i) codetrue->getValue();
        else if(codefalse != nullptr) codefalse->getValue();
        return pair<Value*, string>(nullptr, "null");
    }
private:
    ExpressionTree* exp, * codetrue, * codefalse;
};
