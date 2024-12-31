#pragma once
#include <string>
#include <utility>
#include "Value.h"

using namespace std;

// 前方宣言
union Value;

class ExpressionTree {
public:
    pair<int, int> getpos() {
        return make_pair(collum, pos);
    }

    virtual ExpressionTree* getchild(int i) = 0;
    virtual ~ExpressionTree() = default;
    virtual pair<Value*, string> getValue() = 0;

protected:
    int collum;
    int pos;
};
