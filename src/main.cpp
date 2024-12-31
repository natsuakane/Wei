#include<iostream>
#include<fstream>
#include"convert_num.h"
#include"Parser.cpp"
#include"Environment.h"
using namespace std;

int main(int argc, char *argv[]) {
    if(argc == 1) {
        std::cout << "Unable to open file\n";
    }
    ifstream file(argv[1]);
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
    try{
        parser.Code()->getValue();
    }
    catch(const std::exception& e) {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}
