#ifndef INCLUDED_AEGIS_AFTFS_READONLYFILEHANDLE_H
#define INCLUDED_AEGIS_AFTFS_READONLYFILEHANDLE_H

#include <aftio_outputstream.h>
#include <tr1/memory>

namespace aftfs {

class ReadOnlyFileHandle
{
public:
    ReadOnlyFileHandle();
    
    ~ReadOnlyFileHandle();
    
    bool isValid() const;

    void close();

    int read(char* buffer, size_t bytes);
    
private:
    struct ReadOnlyFileHandleImpl* m_impl;
};

} // namespace

#endif // INCLUDED_AEGIS_AFTFS_FILEHANDLE_H
