#include<iostream>
#include"convert_num.cpp"
#include"Parser.cpp"
#include"Environment.cpp"

int main() {
    Environments::pushEnvironment();
    // "五足二乗四乗二等六万五千五百四十一且一違二 三十"
    Parser parser("「亜」是三十　「伊」是「亜」足三十五 「伊」掛「亜」");
    parser.test();

    return 0;
}
