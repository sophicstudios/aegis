#ifndef INCLUDED_AEGIS_AFTIO_READER_H
#define INCLUDED_AEGIS_AFTIO_READER_H

#include <vector>
#include <cstddef>
#include <stdint.h>

namespace aftio {

class Reader
{
public:
    enum Status {
        Status_OK,
        Status_EOF,
        Status_ERROR
    };
    
    Reader();
    
    virtual ~Reader() = 0;
    
    virtual Status read(char* buffer, size_t bytes, size_t* actualBytes) = 0;
    
    virtual Status read(std::vector<char>& buffer, size_t bytes, size_t* actualBytes) = 0;

    virtual Status reset() = 0;
    
    virtual bool eof(Status* status = NULL) = 0;
    
    virtual Status position(off_t position) = 0;

    virtual off_t position(Status* status = NULL) = 0;
};

} // namespace

#endif // INCLUDED
