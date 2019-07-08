//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "Crc16.h"

static uint8_t tmpArr[] = {0b00000001, 0b00000010};

std::string decimal2binary(uint16_t deci, uint32_t width, bool bGroupDigits=true) {
    std::string ob;
    while (deci) {
        ob += std::to_string(deci % 2);
        deci /= 2;
    }
    std::reverse(ob.begin(), ob.end());  // note: dont forget to reverse!
    if (ob.size() < width) {
        std::string prefix(width - ob.size(), '0');  // fill constructor, fill a string with 4 zeros, it becomes "0000"
        ob = prefix + ob;
    }
    ob = "0b" + ob;
    if (bGroupDigits) {
        auto obLen = ob.size();
        int tmpLen = 2;
        while (tmpLen < obLen) {
            ob.insert(tmpLen, " ");
            tmpLen += 5;
            obLen = ob.size();
        }
    }
    return ob;
}

TEST(Crc16Test, Crc16GetCRCSlow){
    Crc16 c16{tmpArr};
    auto crc = c16.getCRCSlow();
    auto crcBinaryStr = decimal2binary(crc, 16);
    EXPECT_EQ("0b 0001 0011 0111 0011", crcBinaryStr);
}

TEST(Crc16Test, Crc16GetCRC){
    Crc16 c16{tmpArr};
    auto crc = c16.getCRC();
    auto crcBinaryStr = decimal2binary(crc, 16);
    EXPECT_EQ("0b 0001 0011 0111 0011", crcBinaryStr);
}