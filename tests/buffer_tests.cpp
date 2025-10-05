#include <string>
#include <gtest/gtest.h>
#include "../include/buffer.h"

TEST(test_01, basic_test_set)
{
    Buffer buf{};
    ASSERT_TRUE(buf.get_buffer() == "0");
}

TEST(test_02, basic_test_set)
{
    std::string str {"1"};
    Buffer buf{str};
    ASSERT_TRUE(buf.get_buffer() == str);
}

TEST(test_03, basic_test_set)
{
    std::string str {"123"};
    Buffer buf{str};
    ASSERT_TRUE(buf.get_buffer() == str);
}

TEST(test_04, basic_test_set)
{
    std::string str {"12345"};
    Buffer buf{str};
    ASSERT_TRUE(buf.get_buffer() == str);
}

TEST(test_05, basic_test_set)
{
    std::string str {"1234567"};
    Buffer buf{str};
    ASSERT_TRUE(buf.get_buffer() == str);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}