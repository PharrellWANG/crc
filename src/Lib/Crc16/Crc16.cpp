//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#include "Crc16.h"

Crc16::Crc16(uint8_t *arr, uint32_t theLen, uint16_t poly, uint32_t width) : m_len(theLen), m_truncPoly(poly),
                                                                             m_width(width) {
    m_inputBytes.reserve(m_len);
    for (int i = 0; i < m_len; i++)
        m_inputBytes.push_back(arr[i]);
    xInitTable();
}

Crc16::~Crc16() {

}

/*!
 * get CRC using lookup table, its so tricky!
 * */
uint16_t Crc16::getCRC() {
    uint16_t crc = 0u;
    uint8_t key;
    for (int idx = 0; idx < m_len; idx++) {
        /*
         * IDE Warning: Use of a signed integer operand with a binary bitwise operator
         *
         * The ``integer promotion`` causes the warning above. Operands smaller than an int
         * are widened to integer for the arithmetic expression, which is signed.
         *
         * So ``crc>>8u^x`` is actually ``(int)(crc>>8u)^x``.
         * To fix it, just cast it back to unsigned type ``(uint16_t)(crc>>8u)^x``.
         * -------------------------------------------------------------------------------
         *
         * Comparing static_cast<> and C style cast:
         *
         * 1. static_cast<>() gives you a compile time checking ability, C-Style cast doesn't.
         * 2. static_cast<>() is more readable and can be spotted easily anywhere inside a C++ source code, C-Style cast is'nt.
         * 3. Intentions are conveyed much better using C++ casts.
         *
         * So when writing C++, use static_cast instead of C style cast.
         * -------------------------------------------------------------------------------
         *
         * */
        key = static_cast<uint16_t>(crc >> 8u) ^ m_inputBytes.at(idx);
        crc = static_cast<uint16_t>(crc << 8u) ^ m_table[key];
    }
    return crc;
}


uint16_t Crc16::getCRCSlow() {
    uint16_t crc = 0;
    for (int idx = 0; idx < m_len; idx++) {
        crc ^= (uint16_t) (m_inputBytes.at(idx) << 8u);
        for (uint32_t i = 8; i > 0; i--) {
            if (crc & 0x8000u) {
                crc <<= 1u;
                crc ^= m_truncPoly;
            } else {
                crc <<= 1u;
            }
        }
    }
    return crc;
}

void Crc16::xInitTable() {
    /*
     * Note:
     *
     * one common error could happen here is using ``uint8_t`` as the type of dividend,
     * in which case when dividend == 255, adding 1 will make dividend go to 0. Thus the
     * condition ``dividend < 256`` is always true, you cannot jump out of that for loop.
     *
     * */
    for (uint32_t dividend = 0; dividend < 256; dividend++) {
        uint16_t crc = 0;
        crc ^= static_cast<uint16_t>(dividend << 8u);
        for (uint32_t i = 8; i > 0; i--) {
            if (crc & 0x8000u) {
                crc <<= 1u;
                crc ^= m_truncPoly;
            } else {
                crc <<= 1u;
            }
        }
        m_table[dividend] = crc;
    }
}
