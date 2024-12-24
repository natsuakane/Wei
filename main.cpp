#include<iostream>
#include"convert_num.cpp"
#include"Parser.cpp"
#include"Environment.cpp"

int main() {
    Environments::pushEnvironment();
    // "五足二乗四乗二等六万五千五百四十一且一違二 三十"
    Parser parser("関数「亜」引数「伊」「宇」行 「伊」足「宇」　終");
    parser.test();
    cout << Environments::getvalue("江", 0, 0).second << endl;

    return 0;
}
