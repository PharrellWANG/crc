//
// Created by WANG Zhenxiang Pharrell on 2019-07-07.
//

#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "Crc8.h"

// The fixture for testing class Sort. From google test primer.
class Crc8Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    Crc8Test() {
        // You can do set-up work for each test here.
    }

    virtual ~Crc8Test() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Decimal2Any.
    Crc8 c8;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(Crc8Test, yetAnotherCrc8Test) {
    auto width = c8.getWidth();  // checksum width in bits

    auto res = c8.getCRC8();
    auto bRes = Crc8::decimal2binary(res, width);
    EXPECT_EQ("0b00001111", bRes);
}