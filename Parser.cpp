#include <exception>
#include<iostream>
#include<vector>
#include<string>
#include "Exceptions.cpp"
#include "ExpressionTree.cpp"
#include "Number.cpp"
#include "Identifier.cpp"
#include "UnaryOperator.cpp"
#include "BinaryOperator.cpp"
#include "convert_num.cpp"
using namespace std;

class Parser {
public:
    Parser(string c) {
        this->code = c;
        pos = 0;
        gyosu=1;
    }

    void test() {
        ExpressionTree* result2 = add();
        cout << result2->getpos().first << endl;
        cout << result2->getpos().second << endl;
        ExpressionTree* child1 = result2->getchild(0);
        cout << child1->getpos().first << endl;
        cout << child1->getpos().second << endl;
        ExpressionTree* child2 = result2->getchild(1);
        cout << child2->getpos().first << endl;
        cout << child2->getpos().second << endl;
    }
private:
    string code;
    int pos;
    int gyosu;
    void one_kanji(string kanji) {
        if(kanji.size() != 3 || code.size() - pos < 3 || (code[pos] != kanji[0] || code[pos+1] != kanji[1] || code[pos+2] != kanji[2])) {
            cout << invalid_kanji(gyosu, pos/3+3, code.substr(pos, 3), kanji) << endl;;
        }
        pos+=3;
    }
    bool is_kanji(string kanji) {
        if(kanji.size() != 3 || code.size() - pos < 3 || (code[pos] != kanji[0] || code[pos+1] != kanji[1] || code[pos+2] != kanji[2])) {
            return false;
        }
        return true;
    }

    bool isnumber(string s) {
        return containspos(numlist1, s) != -1 || containspos(numlist2, s) != -1 || containspos(numlist3, s) != -1;
    }

    ExpressionTree* factor() {
        string nextmoji = code.substr(pos, 3);
        int current_pos = pos;
        if(isnumber(nextmoji)) {
            int tmppos = pos;
            while(isnumber(code.substr(pos, 3))) {
                pos+=3;
            }
            return new Number(tosuji(code.substr(tmppos, pos-tmppos)), gyosu, current_pos);
        }
        else if(is_kanji("「")) {
            one_kanji("「");
            string varname = "";
            while(!is_kanji("」")) {
                varname += code.substr(pos, 3);
                pos += 3;
            }
            one_kanji("」");
            return new Identifier(varname, gyosu, current_pos);
        }
        return nullptr;
    }

    ExpressionTree* minus() {
        int current_pos = pos;
        if(is_kanji("負")) {
            one_kanji("負");
            ExpressionTree* exp = factor();
            return new UnaryOperator("負", exp, gyosu, current_pos);
        }
        return factor();
    }

    ExpressionTree* power() {
        ExpressionTree* left = minus();
        if(is_kanji("乗")) {
            int current_pos = pos;
            one_kanji("乗");
            ExpressionTree* right = power();
            return new BinaryOperator("乗", left, right, gyosu, current_pos);
        }
        return left;
    }

    ExpressionTree* multi() {
        ExpressionTree* left = power();
        ExpressionTree* right;
        while(is_kanji("掛") || is_kanji("割") || is_kanji("余")) {
            int current_pos = pos;

            if(is_kanji("掛")) {
                one_kanji("掛");
                right = power();
                left = new BinaryOperator("掛", left, right, gyosu, current_pos);
            }

            else if(is_kanji("割")) {
                one_kanji("割");
                right = power();
                left = new BinaryOperator("割", left, right, gyosu, current_pos);
            }

            else if(is_kanji("余")) {
                one_kanji("余");
                right = power();
                left = new BinaryOperator("余", left, right, gyosu, current_pos);
            }
        }

        return left;
    }

    ExpressionTree* add() {
        ExpressionTree* left = multi();
        ExpressionTree* right;
        while(is_kanji("足") || is_kanji("引")) {
            int current_pos = pos;

            if(is_kanji("足")) {
                one_kanji("足");
                right = multi();
                left = new BinaryOperator("足", left, right, gyosu, current_pos);
            }

            else if(is_kanji("引")) {
                one_kanji("引");
                right = multi();
                left = new BinaryOperator("引", left, right, gyosu, current_pos);
            }
        }

        return left;
    }
};
