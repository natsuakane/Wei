#include <string>

std::string replaceAll(const std::string& input, const std::string& from, const std::string& to) {
    if (from.empty()) return input; // 置き換える文字列が空ならそのまま返す

    std::string result = input;
    size_t startPos = 0;

    // 部分文字列を検索しながら置き換える
    while ((startPos = result.find(from, startPos)) != std::string::npos) {
        result.replace(startPos, from.length(), to);
        startPos += to.length(); // 次の検索位置を更新
    }

    return result;
}
