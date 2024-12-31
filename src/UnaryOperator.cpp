#include"UnaryOperator.h"

pair<Value*, string> UnaryOperator::getValue() {
    if(op == "負") {
        pair<Value*, string> v = exp->getValue();
        if(v.second == "integer") {
            return pair<Value*, string>(new Value(-1 * v.first->i), "integer");
        }
        else if(v.second == "float") {
            return pair<Value*, string>(new Value(-1 * v.first->f), "float");
        }
    }
    if(op == "不") {
        pair<Value*, string> v = exp->getValue();
        if(v.second == "integer") {
            return pair<Value*, string>(new Value(v.first->i == 0 ? 1l : 0l), "integer");
        }
    }
    throw runtime_error(invalid_type(collum, pos, "number", exp->getValue().second));
}
