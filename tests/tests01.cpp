#include <gtest/gtest.h>
#include "../include/include.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE();
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}