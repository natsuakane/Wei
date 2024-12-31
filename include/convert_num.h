#pragma once
#include<string>
#include<cmath>
#include<vector>
using namespace std;

extern vector<string> numlist1;
extern vector<string> numlist2;
extern vector<string> numlist3;

std::string tokansuji(long n);
int containspos(vector<string> kansuji, string moji);
long tosuji(string s);
double toshosu(string s);
