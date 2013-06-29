#include <afts_byteorder.h>
#include <boost/static_assert.hpp>

namespace aegis {
namespace afts {

bool ByteOrder::isBigEndian()
{
    BOOST_STATIC_ASSERT(sizeof(int) > sizeof(char));
    static int i = 1;
    static char* c = reinterpret_cast<char*>(&i);
    return static_cast<int>(c[0]) == 1 ? true : false;
}

bool ByteOrder::isLittleEndian()
{
    return !isBigEndian();
}

} // namespace
} // namespace
