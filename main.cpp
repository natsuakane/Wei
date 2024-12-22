#include<iostream>
#include"convert_num.cpp"
#include"Parser.cpp"
#include"Environment.cpp"

int main() {
    Environments::pushEnvironment();
    Parser parser("五足二乗四乗二等六万五千五百四十一且一違二");
    parser.test();

    return 0;
}
