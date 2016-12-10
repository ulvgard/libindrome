#include <gtest/gtest.h>
#include <indrome/io.h>

#include <string>
#include <sstream>

TEST(IO, csv_readline_single_i) {
    std::string s("1");

    auto v = indrome::io::csv::readline<int>(s);
    ASSERT_EQ(v.size(), 1u);

    s = "1\n";
    v = indrome::io::csv::readline<int>(s);
    ASSERT_EQ(v.size(), 1u);
}

TEST(IO, csv_readline_multiline_i) {
    std::string s = "1\n2\n";
    auto v = indrome::io::csv::readline<int>(s);
    ASSERT_EQ(v.size(), 1u);
}

TEST(IO, csv_readline_single_f) {
    std::string s = "1.23\n";
    auto v = indrome::io::csv::readline<float>(s);

    ASSERT_TRUE(v.size() == 1);
    ASSERT_FLOAT_EQ(v[0], 1.23f);
}

TEST(IO, csv_readline_single_d) {
    std::string s("1.23\n");
    auto v = indrome::io::csv::readline<double>(s);

    ASSERT_TRUE(v.size() == 1);
    ASSERT_DOUBLE_EQ(v[0], 1.23);
}

TEST(IO, csv_readline_no_spaces) {
    std::string s("1,2,3,4,5\n");
    auto v = indrome::io::csv::readline<int>(s);

    ASSERT_EQ(v.size(), 5u);
    int i = 1;
    for(auto val: v)
        ASSERT_EQ(val, i++);
}

TEST(IO, csv_readline_with_spaces) {
    std::string s("1, 2,3 , 4 ,   5    \n");
    auto v = indrome::io::csv::readline<int>(s);

    ASSERT_EQ(v.size(), 5u);
}

TEST(IO, csv_readlines)
{
    std::stringstream ss("1,2,3,4,5\n6,7,8,9,0\n");    
    auto v = indrome::io::csv::readlines<int>(ss);
    ASSERT_EQ(v.size(), 2u);
}

TEST(IO, csv_readlines_single_i) {
    std::string s = "1\n2\n";
    auto v = indrome::io::csv::readline<int>(s);
    ASSERT_EQ(v.size(), 1u);
}
