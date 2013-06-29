#include <aftu_hexutil.h>

namespace aegis {
namespace aftu {

uint8_t HexUtil::convertHexChar(char c)
{
    switch (c) {
        case 'F':
        case 'E':
        case 'D':
        case 'C':
        case 'B':
        case 'A':
            return (c - 'A') + 10;
        case 'f':
        case 'e':
        case 'd':
        case 'c':
        case 'b':
        case 'a':
            return (c - 'a') + 10;
        case '9':
        case '8':
        case '7':
        case '6':
        case '5':
        case '4':
        case '3':
        case '2':
        case '1':
            return (c - '0');
        default:
            return 0;
    }
}

uint8_t HexUtil::convertHexByte(char hi, char lo)
{
    return (HexUtil::convertHexChar(hi) << 4) | HexUtil::convertHexChar(lo);
}

} // namespace
} // namespace
