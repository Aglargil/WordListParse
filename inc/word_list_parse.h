#pragma once

#include <fstream>
#include "base_parser.h"

namespace baidu {

class WordListParse {
public:
    WordListParse() {;}
    ~WordListParse() {
        if (_fin.is_open()) {
            _fin.close();
        }
    }

    bool open(const char* file_path) {
        if (_fin.is_open()) {
            _fin.close();
        }
        _fin.open(file_path);
        return _fin.is_open();
    }

    bool parse_line() {
        if (!_fin.is_open()) {
            return false;
        }
        char buf[1024] = {0};
        if (_fin.getline(buf, sizeof(buf))) {
            return parse(buf);
        }
        
        return false;
    }

    bool parse(const std::string& line) {
        auto word_parse = [this](const std::string& word, int index) {
            if (index < _parser_vector.size()) {
                _parser_vector.at(index)->main(word);
            }
            return true;
        };
        return read_line(line, '\t', word_parse);
    }

    void add_parser(BaseParser* bp) {
        _parser_vector.push_back(bp);
    }

private:
    std::ifstream _fin;
    std::vector<BaseParser*> _parser_vector;
};

} // namespace baidu