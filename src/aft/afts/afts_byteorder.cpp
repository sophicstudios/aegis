#include <afts_byteorder.h>

namespace afts {

bool ByteOrder::isBigEndian()
{
    static_assert(sizeof(int) > sizeof(char), "sizeof(int) <= sizeof(char)");
    static int i = 1;
    static char* c = reinterpret_cast<char*>(&i);
    return static_cast<int>(c[0]) == 1 ? true : false;
}

bool ByteOrder::isLittleEndian()
{
    return !isBigEndian();
}

} // namespace
