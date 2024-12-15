#pragma once
#include<string>
#include"convert_num.cpp"
using namespace std;

string invalid_kanji(int gyosu, char invalid, char t) {
    return "我発見誤部分！"+tokansuji(gyosu)+"行目不正漢字「"+invalid+"」正漢字「"+t+"」！";
}
