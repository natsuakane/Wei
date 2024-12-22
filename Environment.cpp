#pragma once
#include<unordered_map>
#include<vector>
#include"Value.cpp"
using namespace std;

class Environment {
private:
    unordered_map<string, pair<Value*, string> > vars;
public:
    bool hasvalue(string name) {
        return vars.count(name) != 0;
    }
    pair<Value*, string> getvalue(string name) {
        return vars[name];
    }
    void setvalue(string name, pair<Value*, string> value) {
        vars[name] = value;
    }
};

class Environments {
private:
    static vector<Environment*> environments;
public:
    static void popEnvironment() { environments.pop_back(); }
    static void pushEnvironment() { environments.push_back(new Environment()); }

    static pair<Value*, string> getvalue(string name) {
        for(int i = environments.size() - 1; i >= 0; i--) {
            if(environments[i]->hasvalue(name)) return environments[i]->getvalue(name);
        }
        return pair<Value*, string>(nullptr, "");
    }

    static void setvar(string name, pair<Value*, string> value) {
        environments[environments.size() - 1]->setvalue(name, value);
    }

    Environments() = delete;
}
