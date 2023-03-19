#include "custom_data.h"

namespace baidu {

template<>
bool parse(const std::string& input, CustomerData& output) {
    auto word_parse = [&output](const std::string& word, int index) {
        if (index == 0) {
            parse(word, output.a);
        } else if (index == 1) {
            parse(word, output.b);
        }

        return true;
    };
    return read_line(input, '|', word_parse);
}

template<>
bool parse(const std::string& input, EmbedData& output) {
    auto word_parse = [&output](const std::string& word, int index) {
        if (index == 0) {
            parse(word, output.data);
        } else if (index == 1) {
            parse(word, output.str);
        }

        return true;
    };
    return read_line(input, '~', word_parse);
}

} // namespace baidu