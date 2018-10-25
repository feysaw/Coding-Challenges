#include <gtest/gtest.h>

extern "C" {
    #include "isbn.h"
}

using namespace ::testing;

TEST(ISBN, Should_Handle_Dashes_And_Spaces) {
    const char* test1 = "0 471 60695 2";
    ASSERT_EQ(1, isValidISBN(test1));
    const char* test2 = "978-0596809485";
    ASSERT_EQ(1, isValidISBN(test2));
}

TEST(ISBN, Should_Handle_Valid_ISBN_10) {
    const char* test1 = "0471606952";
    ASSERT_EQ(1, isValidISBN(test1));
}

TEST(ISBN, Should_Handle_Valid_ISBN_13) {
    const char* test1 = "9780596809485";
    ASSERT_EQ(1, isValidISBN(test1));
}

TEST(ISBN, Should_Throw_Exception_To_Invalid_ISBN_10) {
    const char* test1 = "0471606953";
    ASSERT_EQ(0, isValidISBN(test1));
}

TEST(ISBN, Should_Throw_Exception_To_Invalid_ISBN_13) {
    const char* test1 = "9780596809483";
    ASSERT_EQ(0, isValidISBN(test1));
}

TEST(ISBN, Should_Throw_Exception_If_ISBN_Too_Long) {
    const char* test1 = "0 471 6069521";
    ASSERT_EQ(0, isValidISBN(test1));
}

TEST(ISBN, Should_Throw_Exception_Is_ISBN_Too_Short) {
    const char* test1 = "0 471 60697";
    ASSERT_EQ(0, isValidISBN(test1));
}
    