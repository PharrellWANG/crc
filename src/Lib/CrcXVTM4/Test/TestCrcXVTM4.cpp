//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "CrcXVTM4.h"

static uint8_t tmpArr[] = {0b01100001, 0b01100010, 0b01100011};

std::string decimal2binary(uint32_t deci, uint32_t width, bool bGroupDigits = true) {
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


TEST(CrcXVTM4Test, CrcXVTM4Test32bits) {
    CrcXVTM4 c32{32, 0x04C11DB7};
    c32.processData(tmpArr, 3);
    auto res = c32.getCRCNoMask();
    auto crcBinaryStr = decimal2binary(res, 32);
    EXPECT_EQ("0b 0010 1100 0001 0111 0011 1001 1000 1100", crcBinaryStr);
}