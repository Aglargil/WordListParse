#pragma once

#include "base_parser.h"

struct CustomerData {
    int a;
    float b;
};

struct EmbedData {
    CustomerData data;
    std::string str;
};

namespace baidu {

template<>
bool parse(const std::string& input, CustomerData& output);

template<>
bool parse(const std::string& input, EmbedData& output);

}; // namespace baidu