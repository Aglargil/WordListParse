#pragma once

#include <fstream>
#include "BaseParse.h"

namespace baidu {

class WordListParse {
public:
    WordListParse() {;}
    ~WordListParse() {
        if (fin_.is_open()) fin_.close();
    }

    bool open(const char* file_path) {
        if (fin_.is_open()) fin_.close();
        fin_.open(file_path);
        return fin_.is_open();
    }

    bool parseLine() {
        if (!fin_.is_open()) return false;
        char buf[1024] = {0};
        if (fin_.getline(buf, sizeof(buf))) {
            return parse(buf);
        }
        
        return false;
    }

    bool parse(const std::string& line) {
        auto parseWord = [this](const std::string& word, int index) {
            if (index < parserVector_.size()) {
                parserVector_.at(index)->main(word);
            }
            return true;
        };
        return readLine(line, '\t', parseWord);
    }

    void addParser(baseParser* bp) {
        parserVector_.push_back(bp);
    }

private:
    std::ifstream fin_;
    std::vector<baseParser*> parserVector_;
};
};