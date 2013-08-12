#ifndef INCLUDED_AEGIS_AFTU_HEXUTIL_H
#define INCLUDED_AEGIS_AFTU_HEXUTIL_H

#include <inttypes.h>

namespace aftu {

struct HexUtil
{
    // Converts an alphanumeric character matching the
    // regex [0-9a-fA-F] to a numeric value in the range 0-15.
    static uint8_t convertHexChar(char c);
    
    // Converts two characters, each matching the regex [0-9a-fA-F] to
    // a byte value in the range 0-255.
    static uint8_t convertHexByte(char hi, char lo);
};

} // namespace

#endif // INCLUDED
