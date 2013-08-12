#ifndef INCLUDED_AEGIS_AFTS_BYTEORDER_H
#define INCLUDED_AEGIS_AFTS_BYTEORDER_H

#include <netinet/in.h>

namespace afts {

struct ByteOrder
{
    static bool isBigEndian();

    static bool isLittleEndian();
    
    template<typename T>
    T hostToNetwork(T value);

    template<typename T>
    T networkToHost(T value);
    
    template<typename T>
    T swapByteOrder(T value);
};

template<>
inline int16_t ByteOrder::hostToNetwork(int16_t value)
{
    return htons(value);
}

template<>
inline int16_t ByteOrder::networkToHost(int16_t value)
{
    return ntohs(value);
}

template<>
inline int32_t ByteOrder::hostToNetwork(int32_t value)
{
    return htonl(value);
}

template<>
inline int32_t ByteOrder::networkToHost(int32_t value)
{
    return ntohl(value);
}

} // namespace

#endif // INCLUDED
