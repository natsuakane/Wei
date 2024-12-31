#include"Block.h"

pair<Value*, string> Block::getValue() {
    pair<Value*, string> result;
    for(ExpressionTree* e : exp) {
        pair<Value*, string> value = e->getValue();
        if(value.second != "null") result = value;
    }
    return result;
}
