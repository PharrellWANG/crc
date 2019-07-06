//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#include "Crc8.h"

uint8_t Crc8::getCRC8(){
    // statically define the generator polynomial as ``0x1D``, which is equiv to the binary ``0001 1101``
    // note: the generator polynomial should be of width n (where the n came from the name of ``crc-n``),
    //       in this example, it should be of width 9. But actually the MSB of the poly doesnt matter at all,
    //       hence the MSB of the poly is discarded.
    //
    const uint8_t genPoly = m_poly;

    // shift msg into the register
    auto crc = m_msg;
    auto w = getWidth(); // here w must be 8, we ensure this in ``TestCrc8.cpp``.
    for(uint32_t i = w;i>0;i--){
        // check if the MSB is 1
        if(crc&0x80u){  // append ``u`` to the end to get rid of the warning of ``Use of a signed integer operand with a binary bitwise operator``
            crc<<=1u;
            crc^=genPoly;
        }else{
            crc<<=1u;
        }
    }
    return crc;
}

std::string Crc8::decimal2binary(uint8_t deci, uint32_t width){
    std::string ob;
    while(deci){
        ob += std::to_string(deci%2);
        deci/=2;
    }
    if(ob.size()<width){
        std::string prefix(width-ob.size(), '0');  // fill constructor, fill a string with 4 zeros, it becomes "0000"
        ob = prefix+ob;
    }
    ob = "0b"+ob;
    return ob;
}