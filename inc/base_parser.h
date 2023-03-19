#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <vector>

namespace baidu {

using WordJudge = std::function<bool(const std::string&, int)>;

bool read_line(const std::string& line, char pattern, WordJudge func);

template<typename T>
bool parse(const std::string& input, T& output) {
    std::cout << "未实现此类的parser函数" << std::endl;
    return false;
}

template<typename T>
bool parse(const std::string& input, std::vector<T>& output) {
    output.clear();
    auto word_parse = [&output](const std::string& word, int index) {
        T temp;
        if (parse<T>(word, temp)) {
            output.push_back(temp);
            return true;
        }
        output.clear();
        return false;
    };
    return read_line(input, ',', word_parse);
}

// 加上template<>才是特化, 不加是函数重载
template<>
bool parse(const std::string& input, int& output);

template <>
bool parse(const std::string& input, float& output);

template <>
bool parse(const std::string& input, std::string& output);

class BaseParser {
public:
    BaseParser() = default;
    virtual ~BaseParser() = default;
    virtual bool main(const std::string& word) = 0;
};

template<typename T>
class Parser : public BaseParser {
public:
    virtual bool main(const std::string& word) override {
        return parse(word, _data);
    }

    const T& get_data() {return _data;}
private:
    T _data;
};

} // namespace baidu
