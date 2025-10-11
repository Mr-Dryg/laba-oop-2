#include <gtest/gtest.h>
#include <string>
#include "../include/buffer.h"

TEST(BufferTest, DefaultConstructor) {
    Buffer buf;
    EXPECT_EQ(buf.get_size(), 0);
    EXPECT_EQ(buf.get_buffer(), "");
}

TEST(BufferTest, StringConstructor) {
    Buffer buf1("12345");
    EXPECT_EQ(buf1.get_size(), 5);
    EXPECT_EQ(buf1.get_buffer(), "12345");

    Buffer buf2("");
    EXPECT_EQ(buf2.get_size(), 0);
    EXPECT_EQ(buf2.get_buffer(), "");

    Buffer buf3("1234567");
    EXPECT_EQ(buf3.get_size(), 7);
    EXPECT_EQ(buf3.get_buffer(), "1234567");
}

TEST(BufferTest, CopyConstructor) {
    Buffer original("test");
    Buffer copy(original);
    
    EXPECT_EQ(copy.get_size(), 4);
    EXPECT_EQ(copy.get_buffer(), "test");
    EXPECT_EQ(original.get_buffer(), copy.get_buffer());
}

TEST(BufferTest, AssignmentOperator) {
    Buffer original("assignment");
    Buffer assigned;
    assigned = original;
    
    EXPECT_EQ(assigned.get_size(), 10);
    EXPECT_EQ(assigned.get_buffer(), "assignment");
    
    assigned = assigned;
    EXPECT_EQ(assigned.get_buffer(), "assignment");
}

TEST(BufferTest, GetSize) {
    Buffer empty;
    EXPECT_EQ(empty.get_size(), 0);
    
    Buffer single("a");
    EXPECT_EQ(single.get_size(), 1);
    
    Buffer multiple("abcde");
    EXPECT_EQ(multiple.get_size(), 5);
}

TEST(BufferTest, SetElem) {
    Buffer buf("hello");
    
    buf.set_elem(0, 'H');
    EXPECT_EQ(buf.get_buffer(), "Hello");
    
    EXPECT_NO_THROW(buf.set_elem(4, 'O'));
    EXPECT_EQ(buf.get_buffer(), "HellO");
    
    EXPECT_THROW(buf.set_elem(-1, 'x'), std::out_of_range);
    EXPECT_THROW(buf.set_elem(10, 'x'), std::out_of_range);
    EXPECT_THROW(buf.set_elem(100, 'x'), std::out_of_range);
}

TEST(BufferTest, Push_back) {
    Buffer buf;
    
    buf.push_back('a');
    EXPECT_EQ(buf.get_size(), 1);
    EXPECT_EQ(buf.get_buffer(), "a");
    
    buf.push_back('b');
    buf.push_back('c');
    buf.push_back('d');
    buf.push_back('e');
    buf.push_back('f');
    
    EXPECT_EQ(buf.get_size(), 6);
    EXPECT_EQ(buf.get_buffer(), "abcdef");
    
    for (char c = 'g'; c <= 'z'; c++) {
        buf.push_back(c);
    }
    EXPECT_EQ(buf.get_size(), 26);
    EXPECT_EQ(buf.get_buffer(), "abcdefghijklmnopqrstuvwxyz");
}

TEST(BufferTest, GetElem) {
    Buffer buf("test");
    
    EXPECT_EQ(buf.get_elem(0), 't');
    EXPECT_EQ(buf.get_elem(1), 'e');
    EXPECT_EQ(buf.get_elem(2), 's');
    EXPECT_EQ(buf.get_elem(3), 't');
    EXPECT_EQ(buf.get_elem(4), '\0');
    
    EXPECT_THROW(buf.get_elem(-1), std::out_of_range);
    EXPECT_THROW(buf.get_elem(10), std::out_of_range);
    
    Buffer empty;
    EXPECT_EQ(empty.get_elem(0), '\0');
}

TEST(BufferTest, GetBuffer) {
    Buffer empty;
    EXPECT_EQ(empty.get_buffer(), "");
    
    Buffer single("a");
    EXPECT_EQ(single.get_buffer(), "a");
    
    Buffer longStr("hello world");
    EXPECT_EQ(longStr.get_buffer(), "hello world");
    
    Buffer specialChars("test\n\t\x01");
    EXPECT_EQ(specialChars.get_buffer(), "test\n\t\x01");
}

TEST(BufferTest, EdgeCases) {

    Buffer empty("");
    EXPECT_EQ(empty.get_size(), 0);
    EXPECT_EQ(empty.get_buffer(), "");
    

    Buffer single("x");
    EXPECT_EQ(single.get_size(), 1);
    EXPECT_EQ(single.get_buffer(), "x");
    
    Buffer exact("12345");
    EXPECT_EQ(exact.get_size(), 5);
    EXPECT_EQ(exact.get_buffer(), "12345");
}

TEST(BufferTest, OperationChain) {
    Buffer buf;
    
    std::string expected;
    for (int i = 0; i < 20; i++) {
        char c = 'a' + (i % 26);
        buf.push_back(c);
        expected += c;
    }
    
    EXPECT_EQ(buf.get_buffer(), expected);
    EXPECT_EQ(buf.get_size(), expected.length());
    
    buf.set_elem(0, 'A');
    buf.set_elem(5, 'Z');
    
    expected[0] = 'A';
    expected[5] = 'Z';
    EXPECT_EQ(buf.get_buffer(), expected);
}

TEST(BufferTest, CopyAndAssignmentVariants) {
    Buffer empty1;
    Buffer empty2(empty1);
    EXPECT_EQ(empty2.get_size(), 0);
    
    Buffer nonEmpty("hello");
    nonEmpty = empty1;
    EXPECT_EQ(nonEmpty.get_size(), 0);
    
    Buffer empty3;
    empty3 = Buffer("world");
    EXPECT_EQ(empty3.get_buffer(), "world");
}

TEST(BufferTest, DataIntegrity) {
    std::string originalData = "This is a test string for data integrity";
    Buffer buf(originalData);
    
    Buffer copy(buf);
    EXPECT_EQ(copy.get_buffer(), originalData);
    
    Buffer assigned;
    assigned = buf;
    EXPECT_EQ(assigned.get_buffer(), originalData);

    copy.set_elem(0, 'X');
    EXPECT_EQ(buf.get_buffer(), originalData);
    EXPECT_NE(copy.get_buffer(), originalData);
}
