#ifndef INCLUDED_AEGIS_AFTFS_DIRECTORYENTRY_H
#define INCLUDED_AEGIS_AFTFS_DIRECTORYENTRY_H

#include <aftfs_path.h>
#include <aftio_permissions.h>

namespace aegis {
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
    
   virtual  ~DirectoryEntry();
    
    virtual std::string name() = 0;
    
    virtual aftfs::Path path() = 0;
    
    virtual aftio::Permissions permissions() = 0;
    
    virtual Type type() const = 0;
    
    virtual bool isFile() const = 0;
    
    virtual bool isDirectory() const = 0;
    
    virtual bool isLink() const = 0;

    virtual bool setName(std::string const& name) = 0;
    
    virtual bool setPermissions(aftio::Permissions const& permissions) = 0;
    
// remove - accept void, return bool (success)
// move - accept Path (destination
// copy - accept Path object (destination)

private:
    Type m_type;
};

} // namespace
} // namespace

#endif // INCLUDED
