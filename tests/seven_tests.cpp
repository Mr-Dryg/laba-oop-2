#include <string>
#include <gtest/gtest.h>
#include "../include/seven.h"

TEST(test_01, basic_test_set)
{
    Seven num {"1"};
    ASSERT_TRUE(num == "0");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}