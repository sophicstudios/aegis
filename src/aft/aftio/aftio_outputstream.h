#ifndef INCLUDED_AEGIS_AFTIO_OUTPUTSTREAM_H
#define INCLUDED_AEGIS_AFTIO_OUTPUTSTREAM_H

#include <vector>
#include <cstddef>
#include <stdint.h>

namespace aftio {

class OutputStream
{
public:
    OutputStream();
    
    virtual ~OutputStream() = 0;

    size_t write(int8_t);
    
    size_t write(int8_t const* const buffer, size_t count);
    
    size_t write(std::vector<int8_t> const& buffer, size_t count);
    
private:
    virtual size_t writeImpl(int8_t b) = 0;
    
    virtual size_t writeImpl(int8_t const* const buffer, size_t count) = 0;
    
    virtual size_t writeImpl(std::vector<int8_t> const& buffer, size_t count) = 0;
};

} // namespace

#endif // INCLUDED
