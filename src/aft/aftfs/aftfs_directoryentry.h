#ifndef INCLUDED_AEGIS_AFTFS_DIRECTORYENTRY_H
#define INCLUDED_AEGIS_AFTFS_DIRECTORYENTRY_H

#include <aftio_permissions.h>
#include <aftu_url.h>

namespace aftfs {

class DirectoryEntry
{
public:
    enum Type {
        Type_DIRECTORY,
        Type_FILE,
        Type_LINK,
        Type_UNKNOWN
    };

    DirectoryEntry();
    
    virtual ~DirectoryEntry();
    
    virtual aftu::URL url() = 0;
    
    virtual aftio::Permissions permissions() = 0;
    
    virtual Type type() const = 0;
    
    virtual bool isFile() const = 0;
    
    virtual bool isDirectory() const = 0;
    
    virtual bool isLink() const = 0;
    
    virtual size_t size() const = 0;
};

} // namespace

#endif // INCLUDED
