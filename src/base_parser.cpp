#include "base_parser.h"

namespace baidu {

using WordJudge = std::function<bool(const std::string&, int)>;

bool read_line(const std::string& line, char pattern, WordJudge func) {
    std::string strs = line;
    strs += pattern;

    int count = 0;
    auto pos = strs.find(pattern);
    while (pos != strs.npos) {
        std::string word = strs.substr(0, pos);
        if (!func(word, count++)) {
            return false;
        }

        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }
    return true;
}

template<>
bool parse(const std::string& input, int& output) {
    try {
        output = std::stoi(input);
        return true;
    } catch (...) {
        output = 0;
        return false;
    }
}

template <>
bool parse(const std::string& input, float& output) {
    try {
        output = std::stof(input);
        return true;
    } catch (...) {
        output = 0;
        return false;
    }
}

template <>
bool parse(const std::string& input, std::string& output) {
    try {
        output = input;
        return true;
    } catch (...) {
        output = "";
        return false;
    }
}

} // namespace baidu