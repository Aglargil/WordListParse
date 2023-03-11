#include <iostream>
#include "WordListParse.h"
#include "CustomData.h"

int main() {

    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<int>;
    auto parser2 = new baidu::Parser<float>;
    auto parser3 = new baidu::Parser<embedData>;
    parser.addParser(parser1);
    parser.addParser(parser2);
    parser.addParser(parser3);
    if (!parser.open("../resource/demo.txt")) return 0;
    while (parser.parseLine()) {
        std::cout << parser1->getData() << " ";
        std::cout << parser2->getData() << " ";
        std::cout << parser3->getData().data.a << " ";
        std::cout << parser3->getData().data.b << " ";
        std::cout << parser3->getData().str << std::endl;
    }
    return 0;
}