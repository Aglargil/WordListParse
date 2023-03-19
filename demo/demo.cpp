#include <iostream>
#include "word_list_parse.h"
#include "custom_data.h"

int main() {

    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<int>;
    auto parser2 = new baidu::Parser<float>;
    auto parser3 = new baidu::Parser<EmbedData>;
    parser.add_parser(parser1);
    parser.add_parser(parser2);
    parser.add_parser(parser3);

    if (!parser.open("../resource/demo.txt")) {
        return 0;
    }

    while (parser.parse_line()) {
        std::cout << parser1->get_data() << " ";
        std::cout << parser2->get_data() << " ";
        std::cout << parser3->get_data().data.a << " ";
        std::cout << parser3->get_data().data.b << " ";
        std::cout << parser3->get_data().str << std::endl;
    }
    return 0;
}