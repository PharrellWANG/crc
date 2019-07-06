//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#include <iostream>
#include "Crc8/Crc8.h"

int main(){
    Crc8 c8;

    auto width = c8.getWidth();  // checksum width in bits

    auto res = c8.getCRC8();
    auto bRes = Crc8::decimal2binary(res,width);

    std::cout << bRes << std::endl;

    return 0;
}