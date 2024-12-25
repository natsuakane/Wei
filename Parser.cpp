#include <exception>
#include<iostream>
#include <stdexcept>
#include<vector>
#include<string>
#include "Exceptions.cpp"
#include "ExpressionTree.cpp"
#include "Number.cpp"
#include "Variable.cpp"
#include "UnaryOperator.cpp"
#include "BinaryOperator.cpp"
#include "Block.cpp"
#include "DecFunc.cpp"
#include "CallFunc.cpp"
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
        ExpressionTree* result = Code();
        cout << result->getValue().first->i << endl;
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

    bool isend() {
        return pos == code.size();
    }

    void skipspace() {
        while(is_kanji("　") || code[pos] == ' ' || code[pos] == '\t' || code[pos] == '\n' || code[pos] == '\r') {
            if(is_kanji("　")) {
                one_kanji("　");
            }
            if(code[pos] == ' ' || code[pos] == '\t' || code[pos] == '\r') pos++;
            if(code[pos] == '\n') {
                pos++;
                gyosu++;
            }
        }
    }

    string getname(ExpressionTree* v) {
        try {
            return ((Variable*)v)->getname();
        } catch(exception a) {
            throw runtime_error(is_not_variable(gyosu, pos));
        }
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

            if(!is_kanji("（")) return new Variable(varname, gyosu, current_pos);

            vector<ExpressionTree*> parameters = params();
            return new CallFunc(varname, parameters, gyosu, pos);
        }
        return nullptr;
    }

    ExpressionTree* unary() {
        int current_pos = pos;
        if(is_kanji("負")) {
            one_kanji("負");
            ExpressionTree* exp = factor();
            return new UnaryOperator("負", exp, gyosu, current_pos);
        }
        else if(is_kanji("不")) {
            one_kanji("不");
            ExpressionTree* exp = factor();
            return new UnaryOperator("不", exp, gyosu, current_pos);
        }
        return factor();
    }

    ExpressionTree* power() {
        ExpressionTree* left = unary();
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

    ExpressionTree* comp() {
        ExpressionTree* left = add();
        ExpressionTree* right;
        while(is_kanji("等") || is_kanji("大") || is_kanji("小") || is_kanji("違")) {
            int current_pos = pos;

            if(is_kanji("等")) {
                one_kanji("等");
                right = add();
                left = new BinaryOperator("等", left, right, gyosu, current_pos);
            }

            else if(is_kanji("大")) {
                one_kanji("大");
                right = add();
                left = new BinaryOperator("大", left, right, gyosu, current_pos);
            }

            else if(is_kanji("小")) {
                one_kanji("小");
                right = add();
                left = new BinaryOperator("小", left, right, gyosu, current_pos);
            }

            else if(is_kanji("違")) {
                one_kanji("違");
                right = add();
                left = new BinaryOperator("違", left, right, gyosu, current_pos);
            }
        }

        return left;
    }

    ExpressionTree* logicmulti() {
        ExpressionTree* left = comp();
        ExpressionTree* right;
        while(is_kanji("且")) {
            int current_pos = pos;
            one_kanji("且");
            right = comp();
            left = new BinaryOperator("且", left, right, gyosu, current_pos);
        }

        return left;
    }

    ExpressionTree* logicadd() {
        ExpressionTree* left = logicmulti();
        ExpressionTree* right;
        while(is_kanji("或")) {
            int current_pos = pos;
            one_kanji("或");
            right = logicmulti();
            left = new BinaryOperator("或", left, right, gyosu, current_pos);
        }

        return left;
    }

    ExpressionTree* assign() {
        ExpressionTree* left = logicadd();
        if(is_kanji("是")) {
            int current_pos = pos;
            one_kanji("是");
            ExpressionTree* right = assign();
            return new BinaryOperator("是", left, right, gyosu, current_pos);
        }
        return left;
    }

    ExpressionTree* statement() {
        if(is_kanji("関")) {
            int current_pos = pos;
            one_kanji("関"); one_kanji("数");
            ExpressionTree* name = factor();
            one_kanji("引"); one_kanji("数");
            vector<ExpressionTree*> args;
            while(!is_kanji("行")) {
                args.push_back(factor());
            }
            ExpressionTree* code = block();
            vector<string> string_args;
            for(ExpressionTree* arg : args) string_args.push_back(getname(arg));
            return new DecFunc(getname(name), string_args, code, gyosu, pos);
        }

        return assign();
    }

    ExpressionTree* block() {
        one_kanji("行");
        skipspace();
        vector<ExpressionTree*> programs;
        int current_pos = pos;
        while(!is_kanji("終")) {
            programs.push_back(statement());
            skipspace();
        }
        one_kanji("終");
        return new Block(programs, gyosu, current_pos);
    }

    vector<ExpressionTree*> params() {
        vector<ExpressionTree*> parameters;
        one_kanji("（");
        while(!is_kanji("）")) {
            parameters.push_back(assign());
            skipspace();
        }
        one_kanji("）");
        return parameters;
    }

    ExpressionTree* Code() {
        vector<ExpressionTree*> programs;
        int current_pos = pos;
        while(!isend()) {
            programs.push_back(statement());
            skipspace();
        }
        return new Block(programs, gyosu, current_pos);
    }
};
