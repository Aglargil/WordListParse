#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "base_parser.h"
#include "word_list_parse.h"
#include "custom_data.h"

TEST(WordListParse, readFile) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<int>;
    auto parser2 = new baidu::Parser<float>;
    auto parser3 = new baidu::Parser<std::string>;
    parser.add_parser(parser1);
    parser.add_parser(parser2);
    parser.add_parser(parser3);
    EXPECT_EQ(parser.open("../resource/unit_test.txt"), true);
    EXPECT_EQ(parser.parse_line(), true);
    EXPECT_EQ(parser1->get_data(), 1);
    EXPECT_EQ(parser2->get_data(), 1.3f);
    EXPECT_EQ(parser3->get_data(), "wz");
}

TEST(WordListParse, parseInt) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<int>;
    parser.add_parser(parser1);

    parser.parse("1234");
    EXPECT_EQ(parser1->get_data(), 1234);

    parser.parse("65765456456536");
    EXPECT_EQ(parser1->get_data(), 0);

    parser.parse("1\t2\t");
    EXPECT_EQ(parser1->get_data(), 1);
}

TEST(WordListParse, parseFloat) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<float>;
    parser.add_parser(parser1);

    parser.parse("12.34");
    EXPECT_EQ(parser1->get_data(), 12.34f);

    parser.parse("1234");
    EXPECT_EQ(parser1->get_data(), 1234);

    parser.parse("abc");
    EXPECT_EQ(parser1->get_data(), 0);
}

TEST(WordListParse, parseString) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<std::string>;
    parser.add_parser(parser1);

    parser.parse("12.34");
    EXPECT_EQ(parser1->get_data(), "12.34");

    parser.parse("1234");
    EXPECT_EQ(parser1->get_data(), "1234");

    parser.parse("a\r\t");
    EXPECT_EQ(parser1->get_data(), "a\r");
}

TEST(WordListParse, parseIntVector) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<std::vector<int>>;
    parser.add_parser(parser1);

    parser.parse("12.34");
    EXPECT_EQ(parser1->get_data().size(), 1);

    parser.parse("1,2,3,4");
    EXPECT_EQ(parser1->get_data().size(), 4);

    parser.parse("1,2,a,b");
    EXPECT_EQ(parser1->get_data().size(), 0);
}



TEST(WordListParse, parseCustomerData) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<CustomerData>;
    parser.add_parser(parser1);

    parser.parse("1|2");
    EXPECT_EQ(parser1->get_data().a, 1);
    EXPECT_EQ(parser1->get_data().b, 2);

    parser.parse("1|a");
    EXPECT_EQ(parser1->get_data().a, 1);
    EXPECT_EQ(parser1->get_data().b, 0);
}

TEST(WordListParse, parseCustomerDataVector) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<std::vector<CustomerData>>;
    parser.add_parser(parser1);

    parser.parse("1|2,3|4");
    EXPECT_EQ(parser1->get_data()[0].a, 1);
    EXPECT_EQ(parser1->get_data()[0].b, 2);
    EXPECT_EQ(parser1->get_data()[1].a, 3);
    EXPECT_EQ(parser1->get_data()[1].b, 4);
}

TEST(WordListParse, parseEmbedData) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<EmbedData>;
    parser.add_parser(parser1);

    parser.parse("1|2~wz");
    EXPECT_EQ(parser1->get_data().data.a, 1);
    EXPECT_EQ(parser1->get_data().data.b, 2);
    EXPECT_EQ(parser1->get_data().str, "wz");
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();   
}
