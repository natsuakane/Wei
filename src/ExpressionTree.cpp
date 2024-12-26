#pragma once
#include<algorithm>
#include"Value.cpp"
using namespace std;

class ExpressionTree {
public:
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    virtual ExpressionTree *getchild(int i) = 0;
    virtual ~ExpressionTree() = default;
    virtual pair<Value*, string> getValue() = 0;

protected:
    int collum, pos;
};
