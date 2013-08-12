#ifndef INCLUDED_AEGIS_AFTFS_FILESYSTEM_H
#define INCLUDED_AEGIS_AFTFS_FILESYSTEM_H

#include <aftfs_path.h>
#include <aftfs_directoryentry.h>

namespace aftfs {

class Filesystem
{
public:
    enum Status {
        Status_OK,
        Status_UNKNOWN
    };
    
    Filesystem();

    virtual ~Filesystem();
    
    virtual void listDirectory(std::vector<DirectoryEntry>& entries) = 0;
    
    virtual void listDirectory(std::vector<DirectoryEntry>& entries, aftfs::Path const& path) = 0;
    
    virtual void listDirectory(std::vector<DirectoryEntry>& entries, DirectoryEntry const& dir) = 0;
};

} // namespace

#endif // INCLUDED
