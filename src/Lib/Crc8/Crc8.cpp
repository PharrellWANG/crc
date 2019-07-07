//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#include "Crc8.h"

/*
 * Ref: http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
 *
 * CRC-8 Shift Register Example: Input data = 0xC2 = b11000010 (with 8 zero bits appended: b11000010 00000000), Polynomial = b100011101
 *
 * *********************************************************************************************************************************
 * PHARRELL NOTE:
 * 1. the MSB of the 9-bit Generator Polynomial has been discarded in the code since it doesnt matter.
 * 2. in the code we dont really need to append zeros to the msg, since when we left shit the msg, zeros are automatically appended.
 * *********************************************************************************************************************************
 *
 * 1. CRC-8 register initialized with 0.
 *          --- --- --- --- --- --- --- ---
 *         | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  <-- b1100001000000000
 *          --- --- --- --- --- --- --- ---
 *
 * 2. Left-Shift register by one position. MSB is 0, so nothing do happen, shift in next byte of input stream.
 *          --- --- --- --- --- --- --- ---
 *         | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |  <-- b100001000000000
 *          --- --- --- --- --- --- --- ---
 *
 * 3. Repeat those steps. All steps are left out until there is a 1 in the MSB (nothing interesting happens), then the state looks like:
 *          --- --- --- --- --- --- --- ---
 *         | 1 | 1 | 0 | 0 | 0 | 0 | 1 | 0 |  <-- b00000000
 *          --- --- --- --- --- --- --- ---
 *
 * 4. Left-Shift register. MSB 1 pops out:
 *          --- --- --- --- --- --- --- ---
 *    1 <- | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |  <-- b0000000
 *          --- --- --- --- --- --- --- ---
 *   So XOR the CRC register (with popped out MSB) b110000100 with polynomial b100011101 = b010011001 = 0x99. The MSB is discarded, so the new CRC register value is 010011001:
 *          --- --- --- --- --- --- --- ---
 *         | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 1 |  <-- b0000000
 *          --- --- --- --- --- --- --- ---
 *
 * 5. Left-Shift register. MSB 1 pops out: b100110010 ^ b100011101 = b000101111 = 0x2F:
 *          --- --- --- --- --- --- --- ---
 *         | 0 | 0 | 1 | 0 | 1 | 1 | 1 | 1 |  <-- b000000
 *          --- --- --- --- --- --- --- ---
 *
 * 6. Left-shift register until a 1 is in the MSB position:
 *          --- --- --- --- --- --- --- ---
 *         | 1 | 0 | 1 | 1 | 1 | 1 | 0 | 0 |   <-- b0000
 *          --- --- --- --- --- --- --- ---
 *
 * 7. Left-Shift register. MSB 1 pops out: b101111000 ^ b100011101 = b001100101 = 0x65:
 *          --- --- --- --- --- --- --- ---
 *         | 0 | 1 | 1 | 0 | 0 | 1 | 0 | 1 |   <-- b000
 *          --- --- --- --- --- --- --- ---
 *
 * 8. Left-shift register until a 1 is in the MSB position:
 *          --- --- --- --- --- --- --- ---
 *         | 1 | 1 | 0 | 0 | 1 | 0 | 1 | 0 |   <-- b00
 *          --- --- --- --- --- --- --- ---
 *
 * 9. Left-Shift register. MSB 1 pops out: b110010100 ^ b100011101 = b010001001 = 0x89:
 *          --- --- --- --- --- --- --- ---
 *         | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |   <-- b0
 *          --- --- --- --- --- --- --- ---
 *
 * 10. Left-Shift register. MSB 1 pops out: b10001001 ^ b100011101 = b000001111 = 0x0F:
 *          --- --- --- --- --- --- --- ---
 *         | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 1 |   <-- <empty>
 *          --- --- --- --- --- --- --- ---
 *
 * All input bits are processed, the algorithm stops. The shift register contains now the CRC value which is 0x0F.
 */
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