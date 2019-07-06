//
// Created by WANG Zhenxiang Pharrell on 2019-07-06.
//

#ifndef CRC_CRC8_H
#define CRC_CRC8_H

#include <iostream>
#include <string>

/**
 * An implementation of a CRC-8 algorithm for solely one byte input data
 *
 * @param msg, the one byte message to be transmitted
 * @return the CRC value (i.e., the ``checksum``)
 * */

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


#endif //CRC_CRC8_H
