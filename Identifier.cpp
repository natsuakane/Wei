#pragma once
#include<string>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
using namespace std;

class Identifier : public ExpressionTree {
public:
    Identifier(string n, int c, int p) {
        name = n;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "識別子"));
    }
private:
    string name;
};
