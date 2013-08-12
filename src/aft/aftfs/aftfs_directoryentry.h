#ifndef INCLUDED_AEGIS_AFTFS_DIRECTORYENTRY_H
#define INCLUDED_AEGIS_AFTFS_DIRECTORYENTRY_H

#include <aftfs_path.h>
#include <aftio_permissions.h>

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
    
    ~DirectoryEntry();
    
    std::string name();
    
    aftfs::Path path();
    
    aftio::Permissions permissions();
    
    Type type() const;
    
    bool isFile() const;
    
    bool isDirectory() const;
    
    bool isLink() const;

    bool setName(std::string const& name);
    
    bool setPermissions(aftio::Permissions const& permissions);
    
// remove - accept void, return bool (success)
// move - accept Path (destination
// copy - accept Path object (destination)

private:
    Type m_type;
};

} // namespace

#endif // INCLUDED
