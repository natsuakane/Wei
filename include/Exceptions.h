#pragma once
#include <string>
#include <unordered_map>
#include "convert_num.h"
using namespace std;

// グローバル変数の宣言
extern unordered_map<string, string> types;

// 関数宣言
string invalid_kanji(int gyosu, int pos, string invalid, string t);
string type_has_no_children(int gyosu, int pos, int n, string type);
string invalid_type_assign(int gyosu, int pos);
string is_not_variable(int gyosu, int pos);
string unknown_variable(int gyosu, int pos, string var);
string not_match_argments(int gyosu, int pos);
string invalid_type(int gyosu, int pos, string c, string w);
string index_out_of_range(int gyosu, int pos);
