#ifndef INCLUDED_AEGIS_AFTFS_LOCALFILESYSTEM_H
#define INCLUDED_AEGIS_AFTFS_LOCALFILESYSTEM_H

#include <aftfs_filesystem.h>
#include <aftfs_directoryentry.h>
#include <aftfs_path.h>
#include <vector>

namespace aftfs {

class LocalFilesystem
{
public:
    LocalFilesystem();

    virtual ~LocalFilesystem();
    
    virtual void listDirectory(std::vector<aftfs::DirectoryEntry>& entries);
    
    virtual void listDirectory(std::vector<aftfs::DirectoryEntry>& entries, aftfs::Path const& path);
    
    virtual void listDirectory(std::vector<aftfs::DirectoryEntry>& entries, aftfs::DirectoryEntry const& dir);

private:
    class Impl;
    Impl* m_impl;
};

} // namespace

#endif // INCLUDED
