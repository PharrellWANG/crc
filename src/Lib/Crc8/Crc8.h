//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#ifndef CRC_CRC8_H
#define CRC_CRC8_H

#include <iostream>
#include <string>
#include <vector>
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
 * The CRC8 algorithm capable of handling multiple-byte input data.
 * Still inefficient because it works bit by bit.
 *
 * */
class Crc8General {
private:
//    uint8_t *m_msg;
    std::vector<uint8_t> m_msg;
    uint32_t m_len; // msg len
    uint8_t m_poly;
public:

    explicit Crc8General(const uint8_t *arr, uint32_t len = 2, uint8_t poly = 0x1D) {
        m_len = len;
        m_poly = poly;
//        m_msg = new uint8_t[m_len];
        m_msg.reserve(m_len);
        for (int i = 0; i < m_len; i++)
            m_msg.push_back(arr[i]);
    }

    /*!get checksum width in bits*/
    uint32_t getWidth() { return 8 * sizeof(m_poly); }

    /*!
     * Get the CRC checksum
     * */
    uint8_t getCRC8();
};

class Crc8FastBase {
protected:
    uint32_t m_truncPoly;
    std::vector<uint8_t> m_msg;
    uint32_t m_len; // len of msg
    uint32_t m_bits;  // num of bits of the poly

    virtual void xInitTable() = 0;

public:
    explicit Crc8FastBase(const uint8_t *arr, uint32_t numBits, uint32_t poly, uint32_t theLen) {
        m_truncPoly = poly;
        m_len = theLen;
        m_bits = numBits;
        m_msg.reserve(m_len);
        for (int i = 0; i < m_len; i++)
            m_msg.push_back(arr[i]);
    };

};

class Crc8Fast1 : public Crc8FastBase {
private:
    uint32_t m_table[256];

    void xInitTable() override;

public:
    explicit Crc8Fast1(const uint8_t *arr, uint32_t numBits = 8, uint32_t poly = 0x1D, uint32_t theLen = 2)
            : Crc8FastBase(arr, numBits, poly, theLen) {
        xInitTable();
    }

    uint32_t *getTable() { return m_table; }

};

class Crc8Fast2 : public Crc8FastBase {
private:
    uint32_t m_table[256];

    void xInitTable() override;

public:
    explicit Crc8Fast2(const uint8_t *arr, uint32_t numBits = 8, uint32_t poly = 0x1D, uint32_t theLen = 2)
            : Crc8FastBase(arr, numBits, poly, theLen) {
        xInitTable();
    }

    uint32_t *getTable() { return m_table; }
};

#endif //CRC_CRC8_H
