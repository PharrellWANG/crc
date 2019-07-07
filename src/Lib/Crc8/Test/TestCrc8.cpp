//
// Created by WANG Zhenxiang Pharrell on 2019-07-07.
//

#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "Crc8.h"

static uint8_t tmpArr[] = {0b00000001, 0b00000010};

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
//    Crc8General c8g{tmpArr};
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(Crc8Test, yetAnotherCrc8Test) {
    auto width = c8.getWidth();  // checksum width in bits
    EXPECT_EQ(8, width);  // crc8 algorithm here can only be used on single-byte msg.
    auto res = c8.getCRC8();
    auto bRes = Crc8::decimal2binary(res, width);
    EXPECT_EQ("0b00001111", bRes);
}

TEST(Crc8GeneralTest, yetAnotherCrc8GenralTest){
    Crc8General c8g{tmpArr};
    auto widthG = c8g.getWidth();  // checksum width in bits
    auto resG = c8g.getCRC8();
    auto bResG = Crc8::decimal2binary(resG, widthG);
    EXPECT_EQ("0b01110110", bResG);
}

TEST(Crc8FastTest, initTable){
    Crc8Fast1 c8f1{tmpArr};
    Crc8Fast2 c8f2{tmpArr};
    for(int i=0;i<256;i++)
        EXPECT_EQ(c8f1.getTable()[i], c8f2.getTable()[i]);
    auto res1 = c8f1.getCRC8();
    auto res2 = c8f1.getCRC8();
    auto bRes1 = Crc8::decimal2binary(res1, c8f1.getWidth());
    auto bRes2 = Crc8::decimal2binary(res2, c8f2.getWidth());
    EXPECT_EQ("0b01110110", bRes1);
    EXPECT_EQ("0b01110110", bRes2);
}