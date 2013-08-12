#ifndef INCLUDED_AEGIS_AFTIO_INPUTSTREAM_H
#define INCLUDED_AEGIS_AFTIO_INPUTSTREAM_H

#include <vector>
#include <cstddef>
#include <stdint.h>

namespace aftio {

class InputStream
{
public:
    InputStream();
    
    virtual ~InputStream() = 0;
    
    size_t read(int8_t byte);
    
    size_t read(int8_t* buffer, size_t count);
    
    size_t read(std::vector<int8_t>& buffer, size_t count);

    void seek(size_t location);
    
private:    
    virtual size_t readImpl(int8_t byte) = 0;
    
    virtual size_t readImpl(int8_t* buffer, size_t count) = 0;
    
    virtual size_t readImpl(std::vector<int8_t>& buffer, size_t count) = 0;
    
    virtual void seekImpl(size_t location) = 0;
};

} // namespace

#endif // INCLUDED
