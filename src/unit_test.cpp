#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "BaseParse.h"
#include "WordListParse.h"
#include "CustomData.h"

TEST(WordListParse, readFile) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<int>;
    auto parser2 = new baidu::Parser<float>;
    auto parser3 = new baidu::Parser<std::string>;
    parser.addParser(parser1);
    parser.addParser(parser2);
    parser.addParser(parser3);
    EXPECT_EQ(parser.open("../resource/unit_test.txt"), true);
    EXPECT_EQ(parser.parseLine(), true);
    EXPECT_EQ(parser1->getData(), 1);
    EXPECT_EQ(parser2->getData(), 1.3f);
    EXPECT_EQ(parser3->getData(), "wz");
}

TEST(WordListParse, parseInt) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<int>;
    parser.addParser(parser1);

    parser.parse("1234");
    EXPECT_EQ(parser1->getData(), 1234);

    parser.parse("65765456456536");
    EXPECT_EQ(parser1->getData(), 0);

    parser.parse("1\t2\t");
    EXPECT_EQ(parser1->getData(), 1);
}

TEST(WordListParse, parseFloat) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<float>;
    parser.addParser(parser1);

    parser.parse("12.34");
    EXPECT_EQ(parser1->getData(), 12.34f);

    parser.parse("1234");
    EXPECT_EQ(parser1->getData(), 1234);

    parser.parse("abc");
    EXPECT_EQ(parser1->getData(), 0);
}

TEST(WordListParse, parseString) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<std::string>;
    parser.addParser(parser1);

    parser.parse("12.34");
    EXPECT_EQ(parser1->getData(), "12.34");

    parser.parse("1234");
    EXPECT_EQ(parser1->getData(), "1234");

    parser.parse("a\r\t");
    EXPECT_EQ(parser1->getData(), "a\r");
}

TEST(WordListParse, parseIntVector) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<std::vector<int>>;
    parser.addParser(parser1);

    parser.parse("12.34");
    EXPECT_EQ(parser1->getData().size(), 1);

    parser.parse("1,2,3,4");
    EXPECT_EQ(parser1->getData().size(), 4);

    parser.parse("1,2,a,b");
    EXPECT_EQ(parser1->getData().size(), 0);
}



TEST(WordListParse, parseCustomerData) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<customerData>;
    parser.addParser(parser1);

    parser.parse("1|2");
    EXPECT_EQ(parser1->getData().a, 1);
    EXPECT_EQ(parser1->getData().b, 2);

    parser.parse("1|a");
    EXPECT_EQ(parser1->getData().a, 1);
    EXPECT_EQ(parser1->getData().b, 0);
}

TEST(WordListParse, parseCustomerDataVector) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<std::vector<customerData>>;
    parser.addParser(parser1);

    parser.parse("1|2,3|4");
    EXPECT_EQ(parser1->getData()[0].a, 1);
    EXPECT_EQ(parser1->getData()[0].b, 2);
    EXPECT_EQ(parser1->getData()[1].a, 3);
    EXPECT_EQ(parser1->getData()[1].b, 4);
}

TEST(WordListParse, parseEmbedData) {
    baidu::WordListParse parser;
    auto parser1 = new baidu::Parser<embedData>;
    parser.addParser(parser1);

    parser.parse("1|2~wz");
    EXPECT_EQ(parser1->getData().data.a, 1);
    EXPECT_EQ(parser1->getData().data.b, 2);
    EXPECT_EQ(parser1->getData().str, "wz");
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();   
}
