#include <exception>
#include<iostream>
#include<vector>
#include<string>
#include"Exceptions.cpp"
using namespace std;

class Parser {
public:
    Parser(string c) {
        this->code = c;
        pos = 0;
        gyosu=1;
    }
private:
    string code;
    int pos;
    int gyosu;
    void one_kanji(char kanji) {
        if(code[pos] != kanji) {
            cout << invalid_kanji(gyosu, code[pos], kanji);
        }
    }
};
