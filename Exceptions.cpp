#pragma once
#include<string>
#include"convert_num.cpp"
using namespace std;

string invalid_kanji(int gyosu, int pos, string invalid, string t) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目不正漢字「"+invalid+"」正漢字「"+t+"」！";
}

string type_has_no_children(int gyosu, int pos, int n, string type) {
    return "誤！"+tokansuji(gyosu)+"行目"+tokansuji(pos)+"文字目"+type+"不持其番号的子供「"+tokansuji(n)+"」！";
}
