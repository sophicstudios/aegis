#ifndef INCLUDED_AEGIS_AFTIO_READER_H
#define INCLUDED_AEGIS_AFTIO_READER_H

namespace aegis {
namespace aftio {

class Reader
{
public:
    Reader();
    
    virtual ~Reader() = 0;
    
    virtual int read(char* buffer, size_t bytes) = 0;
};

} // namespace
} // namespace

#endif // INCLUDED