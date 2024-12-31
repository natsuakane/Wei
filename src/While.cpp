#pragma once
#include"ExpressionTree.h"
#include"Exceptions.h"
#include <stdexcept>
#include"Value.h"
using namespace std;

class While : public ExpressionTree {
public:
    While(ExpressionTree* e, ExpressionTree* co, int c, int p) {
        exp = e;
        code = co;
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
        while(exp->getValue().first->i) {
            code->getValue();
        }
        return pair<Value*, string>(nullptr, "null");
    }
private:
    ExpressionTree* exp, * code;
};
