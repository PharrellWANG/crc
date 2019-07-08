//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#ifndef CRC_CRC16_H
#define CRC_CRC16_H

#include <iostream>
#include <vector>

/*!
 * The CRC16 algorithm
 * */
class Crc16 {
private:
    std::vector<uint8_t> m_inputBytes;

    uint32_t m_len; // len of inputBytes in bytes
    uint16_t m_truncPoly; // the generator
    uint32_t m_width; // len of m_truncPoly in bits
    uint16_t m_table[256]; // the lookup table

    void xInitTable();

public:
    explicit Crc16(uint8_t *arr, uint32_t theLen = 2, uint16_t poly = 0x1021, uint32_t width = 16);

    ~Crc16();

    /*!
     * Get CRC bitwise, it is very slow thus not suitable fo real world application
     * */
    uint16_t getCRCSlow();

    /*!
     * Get CRC using lookup table, handles the input stream bytewise
     * */
    uint16_t getCRC();
};


#endif //CRC_CRC16_H
