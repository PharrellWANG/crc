//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#include "Crc8.h"

uint8_t Crc8::getCRC8() {
    // statically define the generator polynomial as ``0x1D``, which is equiv to the binary ``0001 1101``
    // note: the generator polynomial should be of width n (where the n came from the name of ``crc-n``),
    //       in this example, it should be of width 9. But actually the MSB of the poly doesnt matter at all,
    //       hence the MSB of the poly is discarded.
    //
    const uint8_t genPoly = m_poly;

    // shift msg into the register
    auto crc = m_msg;
    auto w = getWidth(); // here w must be 8, we ensure this in ``TestCrc8.cpp``.
    for (uint32_t i = w; i > 0; i--) {
        // check if the MSB is 1
        if (crc &
            0x80u) {  // append ``u`` to the end to get rid of the warning of ``Use of a signed integer operand with a binary bitwise operator``
            crc <<= 1u;
            crc ^= genPoly;
        } else {
            crc <<= 1u;
        }
    }
    return crc;
}

std::string Crc8::decimal2binary(uint8_t deci, uint32_t width) {
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
    return ob;
}

uint8_t Crc8General::getCRC8() {

    // shift msg into the register
    uint8_t crc = 0;
    for (uint32_t j = 0; j < m_len; j++) {
//        crc ^= m_msg.at(j);
        crc ^= m_msg.at(j);
//        std::cout << (int)m_msg[j] << std::endl;
        for (uint32_t i = 8; i > 0; i--) {
            // check if the MSB is 1
            if (crc &
                0x80u) {  // append ``u`` to the end to get rid of the warning of ``Use of a signed integer operand with a binary bitwise operator``
                crc <<= 1u;
                crc ^= m_poly;
            } else {
                crc <<= 1u;
            }
        }
    }
    return crc;
}

void Crc8Fast1::xInitTable() {
    for (int i = 0; i < 256; i++) {
        uint8_t crc = i;
        for (uint32_t j = 8; j > 0; j--) {
            // check if the MSB is 1
            if (crc & 0x80u) {
                crc <<= 1u;
                crc ^= m_truncPoly;
            } else {
                crc <<= 1u;
            }
        }
        m_table[i] = crc;
    }
}

Crc8Fast1::Crc8Fast1(const uint8_t *arr, uint32_t numBits, uint32_t poly, uint32_t theLen)
        : Crc8FastBase(arr, numBits, poly, theLen) {
    xInitTable();
}

uint32_t* Crc8Fast1::getTable() { return m_table; }

uint8_t Crc8Fast1::getCRC8() {
    uint8_t crc = 0;
    for (uint32_t j = 0; j < m_len; j++) {
        /* XOR-in next input byte */
        crc ^= m_msg.at(j);
        /* get current CRC value = remainder */
        crc = m_table[crc];
    }
    return crc;
}

/*!
 * This is the init table method in VTM4.0.
 * Except that the ``remainder`` has been changed from uint32_t to uint8_t.
 * */
void Crc8Fast2::xInitTable() {
    // todo: compare it with the init table method above.
    const uint32_t highBit = 1u << (m_bits - 1);
    const uint32_t byteHighBit = 1u << (8u - 1u);  // pha: 128, 10,000,000

    for (uint32_t value = 0; value < 256; value++) {
        uint8_t remainder = 0;
        for (unsigned char mask = byteHighBit; mask != 0; mask >>= 1u) {
            if (value & mask) {
                remainder ^= highBit;
            }

            if (remainder & highBit) {
                remainder <<= 1u;
                remainder ^= m_truncPoly;
            } else {
                remainder <<= 1u;
            }
        }

        m_table[value] = remainder;
    }
}

Crc8Fast2::Crc8Fast2(const uint8_t *arr, uint32_t numBits, uint32_t poly, uint32_t theLen)
        : Crc8FastBase(arr, numBits, poly, theLen) {
    xInitTable();
}

uint32_t* Crc8Fast2::getTable() { return m_table; }

uint8_t Crc8Fast2::getCRC8() {
    uint8_t crc = 0;
    for (uint32_t j = 0; j < m_len; j++) {
        /* XOR-in next input byte */
        crc ^= m_msg.at(j);
        /* get current CRC value = remainder */
        crc = m_table[crc];
    }
    return crc;
}