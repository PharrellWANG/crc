//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#include "CrcXVTM4.h"

CrcXVTM4::CrcXVTM4(uint32_t bits, uint32_t truncPoly) {
    m_remainder = 0;
    m_bits = bits;
    m_truncPoly = truncPoly;
    m_finalResultMask = (1 << bits) - 1;

    xInitTable();
}

CrcXVTM4::~CrcXVTM4() {

}

void CrcXVTM4::processData(unsigned char *curData, uint32_t dataLength) {
    for (uint32_t i = 0; i < dataLength; i++) {
        unsigned char index = (m_remainder >> (m_bits - 8)) ^curData[i];
        m_remainder <<= 8u;
        m_remainder ^= m_table[index];
    }
}

void CrcXVTM4::xInitTable() {
    const uint32_t highBit = 1 << (m_bits - 1);
    const uint32_t byteHighBit = 1 << (8 - 1);  // pha: 128, 10,000,000

    for (uint32_t value = 0; value < 256; value++) {
        uint32_t remainder = 0;
        for (unsigned char mask = byteHighBit; mask != 0; mask >>= 1) {
            if (value & mask) {
                remainder ^= highBit;
            }

            if (remainder & highBit) {
                remainder <<= 1;
                remainder ^= m_truncPoly;
            } else {
                remainder <<= 1;
            }
        }

        m_table[value] = remainder;
    }
}
