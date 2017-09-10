#ifndef INCLUDED_AEGIS_AFTFS_LOCALFILESYSTEM_H
#define INCLUDED_AEGIS_AFTFS_LOCALFILESYSTEM_H

#include <aftfs_filesystem.h>
#include <aftfs_directoryentry.h>
#include <aftu_url.h>

namespace aftfs {

class LocalFileSystem : public FileSystem
{
public:    
    LocalFileSystem();

    virtual ~LocalFileSystem();
    
    virtual aftu::URL getCurrentDirectory(FileSystem::Status* status = NULL);
    
    virtual FileSystem::Status setCurrentDirectory(aftu::URL const& url);
    
    virtual FileSystem::Status listCurrentDirectory(std::vector<aftu::URL>& results);
    
    virtual FileSystem::Status listDirectory(std::vector<aftu::URL>& results, aftu::URL const& path);
    
    virtual FileSystem::DirectoryEntryPtr directoryEntry(aftu::URL const& url, FileSystem::Status* status = NULL);
    
    virtual FileSystem::FileReaderPtr openFileReader(aftu::URL const& url, FileSystem::Status* status = NULL);

private:
    struct Impl;
    Impl* m_impl;
};

} // namespace

#endif // INCLUDED
