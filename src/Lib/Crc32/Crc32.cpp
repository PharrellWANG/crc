//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#include "Crc32.h"

Crc32::Crc32(uint8_t *arr, uint32_t theLen, uint32_t poly, uint32_t width) : m_len(theLen), m_truncPoly(poly),
                                                                             m_width(width) {
    m_inputBytes.reserve(m_len);
    m_inputBytes.reserve(m_len);
    for (int i = 0; i < m_len; i++)
        m_inputBytes.push_back(arr[i]);
    xInitTable();
}

Crc32::~Crc32() {

}

uint32_t Crc32::getCRCSlow() {
    uint32_t crc = 0;
    for (int idx = 0; idx < m_len; idx++) {
        crc ^= (uint32_t) (m_inputBytes.at(idx) << 24u);
        for (uint32_t i = 8; i > 0; i--) {
            if (crc & 0x80000000u) {
                crc <<= 1u;
                crc ^= m_truncPoly;
            } else {
                crc <<= 1u;
            }
        }
    }
    return crc;
}

uint32_t Crc32::getCRC() {
    uint32_t crc = 0u;
    uint8_t key;
    for (int idx = 0; idx < m_len; idx++) {
        key = static_cast<uint8_t>(crc >> 24u) ^ m_inputBytes.at(idx);
        crc = static_cast<uint32_t>(crc << 8u) ^ m_table[key];
    }
    return crc;
}

void Crc32::xInitTable() {
    for (uint32_t dividend = 0; dividend < 256; dividend++) {
        uint32_t crc = 0;
        crc ^= static_cast<uint32_t>(dividend << 24u);
        for (uint32_t i = 8; i > 0; i--) {
            if (crc & 0x80000000u) {
                crc <<= 1u;
                crc ^= m_truncPoly;
            } else {
                crc <<= 1u;
            }
        }
        m_table[dividend] = crc;
    }
}