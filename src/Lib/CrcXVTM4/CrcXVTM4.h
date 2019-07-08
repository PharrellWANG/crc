//
// Created by WANG Zhenxiang Pharrell on 2019-07-08.
//

#ifndef CRC_CRCXVTM4_H
#define CRC_CRCXVTM4_H

#include <iostream>

class CrcXVTM4 {
public:
    CrcXVTM4(uint32_t bits, uint32_t truncPoly);

    ~CrcXVTM4();

public:
    void processData(unsigned char *curData, uint32_t dataLength);

    void reset() { m_remainder = 0; }

    uint32_t getCRC() { return m_remainder & m_finalResultMask; }
    uint32_t getCRCNoMask() { return m_remainder; }

private:
    void xInitTable();

private:
    uint32_t m_remainder;
    uint32_t m_truncPoly;
    uint32_t m_bits;
    uint32_t m_table[256];
    uint32_t m_finalResultMask;
};


#endif //CRC_CRCXVTM4_H
