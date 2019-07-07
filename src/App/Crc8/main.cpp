//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#include <iostream>
#include "Crc8/Crc8.h"

int main(){
//    Crc8 c8;
//
//    auto width = c8.getWidth();  // checksum width in bits
//
//    auto res = c8.getCRC8();
//    auto bRes = Crc8::decimal2binary(res,width);
//
//    std::cout << bRes << std::endl;
    uint8_t tmpArr[2] =  {0b00000001, 0b00000010};
    Crc8Fast1 c8f1{tmpArr};
    for(int i=0;i<256;i++)
        std::cout << i << ": " << c8f1.getTable()[i] << std::endl;

    Crc8Fast2 c8f2{tmpArr};
    for(int i=0;i<256;i++)
        std::cout << i << ": " << c8f2.getTable()[i] << std::endl;

    return 0;
}

//0: 0
//1: 29
//2: 58
//3: 39
//4: 116
//5: 105
//6: 78
//7: 83
//8: 232
//9: 245
//10: 210
//11: 207
//12: 156
//13: 129