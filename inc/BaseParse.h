#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <vector>

namespace baidu {

using wordJudge = std::function<bool(const std::string&, int)>;

inline bool readLine(const std::string& line, char pattern, wordJudge func) {
    std::string strs = line;
    strs += pattern;

    int count = 0;
    auto pos = strs.find(pattern);
    while (pos != strs.npos) {
        std::string word = strs.substr(0, pos);
        if (!func(word, count++)) return false;

        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }
    return true;
}

template<typename T>
inline bool parse(const std::string& input, T& output) {
    std::cout << "未实现此类的parser函数" << std::endl;
    return false;
}

template<typename T>
inline bool parse(const std::string& input, std::vector<T>& output) {
    output.clear();
    auto parseWord = [&output](const std::string& word, int index) {
        T temp;
        if (parse(word, temp)) {
            output.push_back(temp);
            return true;
        }
        output.clear();
        return false;
    };
    return readLine(input, ',', parseWord);
}

// 加上template<>才是特化, 不加是函数重载
template<>
inline bool parse(const std::string& input, int& output) {
    try {
        output = std::stoi(input);
        return true;
    } catch (...) {
        output = 0;
        return false;
    }
}

template <>
inline bool parse(const std::string& input, float& output) {
    try {
        output = std::stof(input);
        return true;
    } catch (...) {
        output = 0;
        return false;
    }
}

template <>
inline bool parse(const std::string& input, std::string& output) {
    try {
        output = input;
        return true;
    } catch (...) {
        output = "";
        return false;
    }
}

class baseParser {
public:
    baseParser() = default;
    virtual ~baseParser() = default;
    virtual bool main(const std::string& word) = 0;
};

template<typename T>
class Parser : public baseParser {
public:
    virtual bool main(const std::string& word) override {
        return parse(word, data_);
    }

    const T& getData() {return data_;}
private:
    T data_;
};
}
