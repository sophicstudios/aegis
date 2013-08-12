#ifndef INCLUDED_AEGIS_AFTH_CRC32_H
#define INCLUDED_AEGIS_AFTH_CRC32_H

#include <cstddef>
#include <stdint.h>

namespace afth {

struct Crc32
{
    static uint32_t compute(char const* const buffer, size_t length, uint32_t priorCrc32 = 0);
};

} // namespace

#endif // INCLUDED
