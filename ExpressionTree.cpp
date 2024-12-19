#pragma once
#include<algorithm>
using namespace std;

class ExpressionTree {
public:
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    virtual ExpressionTree *getchild(int i) = 0;
    virtual ~ExpressionTree() = default;
protected:
    int collum, pos;
};
