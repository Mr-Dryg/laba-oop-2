#include <string>
#include <gtest/gtest.h>
#include "../include/seven.h"

TEST(SevenTest, DefaultConstructor) {
    Seven num;
    EXPECT_EQ(num.get_string(), "0");
}

TEST(SevenTest, StringConstructorValid) {
    Seven num1("0123");
    EXPECT_EQ(num1.get_string(), "123");
    
    Seven num2("000");
    EXPECT_EQ(num2.get_string(), "0");
    
    Seven num3("00000000006");
    EXPECT_EQ(num3.get_string(), "6");
}

TEST(SevenTest, StringConstructorInvalid) {
    EXPECT_THROW(Seven("7"), std::invalid_argument);
    EXPECT_THROW(Seven("8"), std::invalid_argument);
    EXPECT_THROW(Seven("9"), std::invalid_argument);
    EXPECT_THROW(Seven("17"), std::invalid_argument);
    EXPECT_THROW(Seven("1a2"), std::invalid_argument);
}

TEST(SevenTest, CopyConstructor) {
    Seven original("123");
    Seven copy(original);
    EXPECT_EQ(copy.get_string(), "123");
    EXPECT_EQ(original.get_string(), "123");
}

TEST(SevenTest, AssignmentOperator) {
    Seven original("123");
    Seven assigned;
    assigned = original;
    EXPECT_EQ(assigned.get_string(), "123");
    
    assigned = assigned;
    EXPECT_EQ(assigned.get_string(), "123");
}

TEST(SevenTest, AdditionOperator) {
    Seven a("12");
    Seven b("13");
    Seven result1 = a + b;
    EXPECT_EQ(result1.get_string(), "25");
    
    Seven c("16");
    Seven d("12");
    Seven result2 = c + d;
    EXPECT_EQ(result2.get_string(), "31");
    
    Seven e("123");
    Seven zero("0");
    Seven result3 = e + zero;
    EXPECT_EQ(result3.get_string(), "123");
    
    Seven f("666666");
    Seven g("111111");
    Seven result4 = f + g;
    EXPECT_EQ(result4.get_string(), "1111110");
}

TEST(SevenTest, SubtractionOperator) {
    Seven a("25");
    Seven b("13");
    Seven result1 = a - b;
    EXPECT_EQ(result1.get_string(), "12");
    
    Seven c("101");
    Seven d("16"); 
    Seven result2 = c - d;
    EXPECT_EQ(result2.get_string(), "52");
    
    Seven e("123");
    Seven result3 = e - e;
    EXPECT_EQ(result3.get_string(), "0");
    
    Seven f("123");
    Seven zero("0");
    Seven result4 = f - zero;
    EXPECT_EQ(result4.get_string(), "123");
}

TEST(SevenTest, SubtractionThrowsWhenNegative) {
    Seven a("12");
    Seven b("13");
    EXPECT_THROW(a - b, std::invalid_argument);
    
    Seven small("10");
    Seven large("100");
    EXPECT_THROW(small - large, std::invalid_argument);
}

TEST(SevenTest, EqualityOperator) {
    Seven a("123");
    Seven b("123");
    Seven c("124");
    Seven d("12");
    
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
    EXPECT_TRUE(a == a);
}

TEST(SevenTest, InequalityOperator) {
    Seven a("123");
    Seven b("124");
    Seven c("123");
    
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != c);
}

TEST(SevenTest, GreaterThanOperator) {
    Seven a("100");
    Seven b("50");
    Seven c("100");
    Seven d("66");
    
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
    EXPECT_FALSE(a > c);
    EXPECT_TRUE(a > d);
}

TEST(SevenTest, LessThanOperator) {
    Seven a("50");
    Seven b("100");
    Seven c("50");
    Seven d("51");
    
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a < c);
    EXPECT_TRUE(a < d);
}

TEST(SevenTest, GreaterThanOrEqualOperator) {
    Seven a("100");
    Seven b("50");
    Seven c("100");
    
    EXPECT_TRUE(a >= b);
    EXPECT_FALSE(b >= a);
    EXPECT_TRUE(a >= c);
}

TEST(SevenTest, LessThanOrEqualOperator) {
    Seven a("50");
    Seven b("100");
    Seven c("50");
    
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(b <= a);
    EXPECT_TRUE(a <= c);
}

TEST(SevenTest, EdgeCases) {
    Seven zero1("0");
    Seven zero2("0");
    EXPECT_EQ(zero1.get_string(), "0");
    EXPECT_TRUE(zero1 == zero2);
    
    Seven a("123");
    Seven zero("0");
    Seven add_result = a + zero;
    Seven sub_result = a - zero;
    EXPECT_EQ(add_result.get_string(), "123");
    EXPECT_EQ(sub_result.get_string(), "123");
}

TEST(SevenTest, ComparisonDifferentLengths) {
    Seven short_num("10");
    Seven long_num("1000");
    
    EXPECT_TRUE(long_num > short_num);
    EXPECT_TRUE(short_num < long_num);
    EXPECT_FALSE(short_num > long_num);
    EXPECT_FALSE(long_num < short_num);
}

TEST(SevenTest, OperationChains) {
    Seven a("12");
    Seven b("13");
    Seven c("14");
    
    Seven result1 = (a + b) - c;
    EXPECT_EQ(result1.get_string(), "11");
    
    Seven d = a;
    Seven e = d;
    EXPECT_EQ(e.get_string(), "12");
}

TEST(SevenTest, ImmutabilityOfOperands) {
    Seven a("12");
    Seven b("13");
    std::string original_a = a.get_string();
    std::string original_b = b.get_string();
    
    Seven result = a + b;
    
    EXPECT_EQ(a.get_string(), original_a);
    EXPECT_EQ(b.get_string(), original_b);
}
