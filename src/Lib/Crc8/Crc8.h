//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#ifndef CRC_CRC8_H
#define CRC_CRC8_H

#include <iostream>
#include <string>
#include <algorithm>

/**
 * An implementation of a CRC-8 algorithm for solely one byte input data
 *
 * @param msg, the one byte message to be transmitted
 * @return the CRC value (i.e., the ``checksum``)
 * */
class Crc8 {
private:
    uint8_t m_msg;
    uint8_t m_poly;
public:
    explicit Crc8(uint8_t msg = 0b11000010, uint8_t poly = 0b00011101) : m_msg(msg), m_poly(poly) {}

    ~Crc8() = default;

    /*!get checksum width in bits*/
    uint32_t getWidth() { return 8 * sizeof(m_poly); }

    /*!
     * Get the CRC checksum
     * */
    uint8_t getCRC8();

    /**
     * @param deci, the decimal num to be converted to binary
     * @param width, the num of bits in the output binary
     * @return the str formatted binary val in the form of "0bxxxxxxxx" where x represents 0 or 1
     */
    static std::string decimal2binary(uint8_t deci, uint32_t width = 0);
};

/*!
 * The CRC8 algorithm capable of handling multiple-byte input data
 *
 * */
class Crc8General {
private:
    uint8_t* m_msg;
    uint32_t m_len; // msg len
    uint8_t m_poly;
public:
    //uint32_t msg = 0b0000000100000010,

    explicit Crc8General(const uint8_t *arr, uint32_t len = 2, uint8_t poly = 0x1D){
        m_len = len;
        m_poly = poly;
        m_msg = new uint8_t[m_len];
        for (int i = 0; i < m_len; i++)
            m_msg[i] = arr[i];
    }

    ~Crc8General() = default;

    /*!get checksum width in bits*/
    uint32_t getWidth() { return 8 * sizeof(m_poly); }

    /*!
     * Get the CRC checksum
     * */
    uint8_t getCRC8();
};

#endif //CRC_CRC8_H
