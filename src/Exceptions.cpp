#pragma once
#include<string>
#include<unordered_map>
#include"convert_num.cpp"
using namespace std;

unordered_map<string, string> types = {
    {"integer", "整数"},
    {"float", "小数"},
    {"number", "数"},
    {"string", "文字列"},
    {"array", "配列"},
    {"function", "関数"}
};

string invalid_kanji(int gyosu, int pos, string invalid, string t) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目不正漢字「"+invalid+"」正漢字「"+t+"」！";
}

string type_has_no_children(int gyosu, int pos, int n, string type) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目"+type+"不持其番号的子供「"+tokansuji(n)+"」！";
}

string invalid_type_assign(int gyosu, int pos) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目左項不是変数！";
}

string is_not_variable(int gyosu, int pos) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目此不変数！";
}

string unknown_variable(int gyosu, int pos, string var) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目変数「"+var+"」未定義！";
}

string not_match_argments(int gyosu, int pos) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目不正引数発生！";
}

string invalid_type(int gyosu, int pos, string c, string w) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目不正型「"+types[w]+"」正型「"+types[c]+"」！";
}

string index_out_of_range(int gyosu, int pos) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目此指定配列外！";
}
