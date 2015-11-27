#ifndef INCLUDED_AEGIS_AFTFS_LOCALFILESYSTEM_H
#define INCLUDED_AEGIS_AFTFS_LOCALFILESYSTEM_H

#include <aftfs_filesystem.h>
#include <aftfs_directoryentry.h>
#include <aftu_url.h>

namespace aftfs {

class LocalFilesystem : public Filesystem
{
public:    
    LocalFilesystem();

    virtual ~LocalFilesystem();
    
    virtual aftu::URL getCurrentDirectory(Filesystem::Status* status = NULL);
    
    virtual Filesystem::Status setCurrentDirectory(aftu::URL const& url);
    
    virtual Filesystem::Status listCurrentDirectory(std::vector<aftu::URL>& results);
    
    virtual Filesystem::Status listDirectory(std::vector<aftu::URL>& results, aftu::URL const& path);
    
    virtual Filesystem::DirectoryEntryPtr directoryEntry(aftu::URL const& url, Filesystem::Status* status = NULL);
    
    virtual Filesystem::FileReaderPtr openFileReader(aftu::URL const& url, Filesystem::Status* status = NULL);

private:
    class Impl;
    Impl* m_impl;
};

} // namespace

#endif // INCLUDED
