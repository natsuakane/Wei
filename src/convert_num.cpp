#pragma once
#include<string>
#include<cmath>
using namespace std;

vector<string> numlist1 = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
vector<string> numlist2 = {"", "十", "百", "千"};
vector<string> numlist3 = {"", "万", "億", "兆", "京", "垓", "秭", "負"};

std::string tokansuji(long n) {
    std::string ans = "";
    bool less0 = false;
    if(n < 0) {
        n = -n;
        less0 = true;
    }

    int keta=0;
    while(std::pow(10, keta) <= n) {
        if((n / (long)std::pow(10, keta)) % 10 != 0){
            std::string kansuji = "";
            if((n / (long)std::pow(10, keta)) % 10 != 1 || keta%4 == 0) kansuji = numlist1[(n / (long)std::pow(10, keta)) % 10];
            kansuji += numlist2[keta%4];
            if(keta % 4 == 0) kansuji += numlist3[keta/4];
            ans = kansuji + ans;
        }
        keta++;
    }

    if(less0) ans = "負" + ans;

    return ans;
}

int containspos(vector<string> kansuji, string moji) {
    for(int i = 0; i < kansuji.size(); i++) {
        if(kansuji[i][0] == moji[0] && kansuji[i][1] == moji[1] && kansuji[i][2] == moji[2]) return i;
    }
    return -1;
}

long tosuji(string s) {
    bool isminus = false;
    if(s[0] == '\350' && s[1] == '\262' && s[2] == '\240') {
        s = s.substr(3, s.size()-3);
        isminus = true;
    }
    long result = 0;
    int n = 0;
    for(int i = 0; i < s.size(); i+=3) {
        string moji = s.substr(i, 3);
        if(containspos(numlist1, moji) != -1) {
            int num = containspos(numlist1, moji);
            string moji2 = s.substr(i+3, 3);
            if(containspos(numlist2, moji2) != -1) {
                int keta1 = containspos(numlist2, moji2);
                n += num * (int)std::pow(10, keta1);
            }
            else n += num;
        }
        if(containspos(numlist3, moji) != -1) {
            int keta4 = containspos(numlist3, moji);
            result += n * (int)std::pow(10000, keta4);
            n = 0;
        }
    }
    result += n;

    if(isminus) result *= -1;

    return result;
}

double toshosu(string s) {
    bool isminus = false;
    if(s[0] == '\350' && s[1] == '\262' && s[2] == '\240') {
        s = s.substr(3, s.size()-3);
        isminus = true;
    }
    double result = 0;
    int n = 0;
    int ketabelow0 = 0;
    for(int i = 0; i < s.size(); i+=3) {
        string moji = s.substr(i, 3);

        if(ketabelow0) {
            int num = containspos(numlist1, moji);
            result += num/pow(10, ketabelow0);
            ketabelow0++;
            continue;
        }
        if(moji == "点") ketabelow0 = 1;

        if(containspos(numlist1, moji) != -1) {
            int num = containspos(numlist1, moji);
            string moji2 = s.substr(i+3, 3);
            if(containspos(numlist2, moji2) != -1) {
                int keta1 = containspos(numlist2, moji2);
                n += num * (int)std::pow(10, keta1);
            }
            else n += num;
        }
        if(containspos(numlist3, moji) != -1) {
            int keta4 = containspos(numlist3, moji);
            result += n * (int)std::pow(10000, keta4);
            n = 0;
        }
    }
    result += n;

    if(isminus) result *= -1;

    return result;
}
