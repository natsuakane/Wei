#include <exception>
#include<iostream>
#include <stdexcept>
#include<vector>
#include<string>
#include "Exceptions.cpp"
#include "ExpressionTree.cpp"
#include "Number.cpp"
#include "FloatNumber.cpp"
#include "Variable.cpp"
#include "UnaryOperator.cpp"
#include "BinaryOperator.cpp"
#include "Block.cpp"
#include "DecFunc.cpp"
#include "CallFunc.cpp"
#include "String.cpp"
#include "Array.cpp"
#include "Index.cpp"
#include "If.cpp"
#include "While.cpp"
#include "LibFuncCode.cpp"
#include "Environment.cpp"
#include "Value.cpp"
#include "convert_num.cpp"
using namespace std;

class Parser {
public:
    Parser(string c) {
        this->code = c;
        pos = 0;
        gyosu=1;

        //環境準備
        Environments::pushEnvironment();

        //標準ライブラリ関数
        vector<string> args; args.push_back("arg1");
        ExpressionTree* func = new GetLength(gyosu, pos);
        pair<Value*, string> getlength = make_pair(new Value(new Func(args, func)), "function");
        Environments::setvar("長取得", getlength);

        args.clear(); args.push_back("arg1");
        func = new MakeArray(gyosu, pos);
        pair<Value*, string> makearray = make_pair(new Value(new Func(args, func)), "function");
        Environments::setvar("配列生成", makearray);

        args.clear(); args.push_back("arg1");
        func = new MakeString(gyosu, pos);
        pair<Value*, string> makestring = make_pair(new Value(new Func(args, func)), "function");
        Environments::setvar("文字列生成", makestring);

        args.clear(); args.push_back("arg1"); args.push_back("arg2");
        func = new PushElm(gyosu, pos);
        pair<Value*, string> pushelm = make_pair(new Value(new Func(args, func)), "function");
        Environments::setvar("要素追加", pushelm);

        args.clear(); args.push_back("arg1");
        func = new Print(gyosu, pos);
        pair<Value*, string> print = make_pair(new Value(new Func(args, func)), "function");
        Environments::setvar("表示", print);

        args.clear(); args.push_back("arg1");
        func = new Copy(gyosu, pos);
        pair<Value*, string> copy = make_pair(new Value(new Func(args, func)), "function");
        Environments::setvar("複製", copy);
    }

    void test() {
        ExpressionTree* result = Code();
        pair<Value*, string> v = result->getValue();
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
            bool isfloat = false;
            int tmppos = pos;
            while(isnumber(code.substr(pos, 3)) || code.substr(pos, 3) == "点") {
                if(code.substr(pos, 3) == "点") isfloat = true;
                pos+=3;
            }
            if(isfloat) return new FloatNumber(toshosu(code.substr(tmppos, pos-tmppos)), gyosu, current_pos);
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

            return new Variable(varname, gyosu, current_pos);
        }
        else if(is_kanji("『")) {
            one_kanji("『");
            string value = "";
            while(!is_kanji("』")) {
                value += code.substr(pos, 3);
                pos+= 3;
            }
            one_kanji("』");

            return new String(value, gyosu, pos);
        }
        else if(is_kanji("《")) {
            one_kanji("《");
            vector<ExpressionTree*> array;
            while(!is_kanji("》")) {
                array.push_back(assign());
                skipspace();
            }
            one_kanji("》");

            return new Array(array, gyosu, pos);
        }
        return nullptr;
    }

    ExpressionTree* index() {
        int current_pos = pos;
        ExpressionTree* arrayn = factor();
        if(is_kanji("《")) {
            one_kanji("《");
            ExpressionTree* id = assign();
            one_kanji("》");
            return new Index(arrayn, id, gyosu, pos);
        }
        return arrayn;
    }

    ExpressionTree* funcall() {
        int current_pos = pos;
        ExpressionTree* fun = index();
        if(is_kanji("（")) {
            vector<ExpressionTree*> param = params();
            return new CallFunc(fun, param, gyosu, pos);
        }
        return fun;
    }

    ExpressionTree* unary() {
        int current_pos = pos;
        if(is_kanji("負")) {
            one_kanji("負");
            ExpressionTree* exp = funcall();
            return new UnaryOperator("負", exp, gyosu, current_pos);
        }
        else if(is_kanji("不")) {
            one_kanji("不");
            ExpressionTree* exp = funcall();
            return new UnaryOperator("不", exp, gyosu, current_pos);
        }
        return funcall();
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
            return new DecFunc(getname(name), string_args, code, gyosu, current_pos);
        }

        ExpressionTree* exp = assign();
        if(is_kanji("場")) {
            int current_pos = pos;
            one_kanji("場"); one_kanji("合");
            ExpressionTree* code;
            if(!is_kanji("行")) {
                skipspace();
                code = statement();
            }
            else code = block();
            skipspace();

            if(is_kanji("其")) {
                one_kanji("其"); one_kanji("他");
                ExpressionTree* fcode;
                if(!is_kanji("行")) {
                    skipspace();
                    fcode = statement();
                }
                else fcode = block();
                return new If(exp, code, fcode, gyosu, current_pos);
            }
            return new If(exp, code, nullptr, gyosu, pos);
        }

        if(is_kanji("間")) {
            int current_pos = pos;
            one_kanji("間"); one_kanji("繰"); one_kanji("返");
            ExpressionTree* code;
            if(!is_kanji("行")) {
                skipspace();
                code = statement();
            }
            else code = block();

            return new While(exp, code, gyosu, current_pos);
        }

        return exp;
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
