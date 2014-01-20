#ifndef INCLUDED_AEGIS_AFTIO_WRITER_H
#define INCLUDED_AEGIS_AFTIO_WRITER_H

#include <vector>
#include <cstddef>
#include <stdint.h>

namespace aftio {

class Writer
{
public:
    Writer();
    
    virtual ~Writer() = 0;

    virtual size_t write(char const* const buffer, size_t bytes) = 0;
    
    virtual size_t write(std::vector<char> const& buffer, size_t bytes) = 0;
    
    virtual off_t getPosition() = 0;

    virtual void setPosition(off_t position) = 0;
};

} // namespace

#endif // INCLUDED
