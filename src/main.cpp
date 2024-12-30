#include<iostream>
#include<fstream>
#include"convert_num.cpp"
#include"Parser.cpp"
#include"Environment.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    ifstream file("test.wei");
    string line, code;

    if(file.is_open()) {
        while(getline(file, line)) {
            code += line + "\n";
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }

    Parser parser(code);
    parser.Code()->getValue();

    return 0;
}
