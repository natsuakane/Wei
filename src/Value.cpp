#include "Value.h"

// Value のコピーコンストラクタの実装
Value::Value(const Value& other, const string& type) {
    if (type == "string") {
        s = new string(*other.s);  // 深いコピー
    } else if (type == "array") {
        a = new vector<pair<Value*, string>>(*other.a);
    } else if (type == "function") {
        fun = new Func(*other.fun);
    } else if (type == "integer") {
        i = other.i;
    } else if (type == "float") {
        f = other.f;
    } else if (type == "object") {
        obj = new unordered_map<string, pair<Value*, string>>(*other.obj);
    }
}
