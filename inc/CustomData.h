#pragma once

#include "BaseParse.h"

struct customerData {
    int a;
    float b;
};

struct embedData {
    customerData data;
    std::string str;
};

namespace baidu {

template<>
inline bool parse(const std::string& input, customerData& output) {
    auto wordParse = [&output](const std::string& word, int index) {
        if (index == 0) {
            parse(word, output.a);
        } else if (index == 1) {
            parse(word, output.b);
        }

        return true;
    };
    return readLine(input, '|', wordParse);
}

template<>
inline bool parse(const std::string& input, embedData& output) {
    auto wordParse = [&output](const std::string& word, int index) {
        if (index == 0) {
            parse(word, output.data);
        } else if (index == 1) {
            parse(word, output.str);
        }

        return true;
    };
    return readLine(input, '~', wordParse);
}

};