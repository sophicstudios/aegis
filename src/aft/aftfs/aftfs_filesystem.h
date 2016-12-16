#ifndef INCLUDED_AEGIS_AFTFS_FILESYSTEM_H
#define INCLUDED_AEGIS_AFTFS_FILESYSTEM_H

#include <aftfs_directoryentry.h>
#include <aftio_reader.h>
#include <aftu_url.h>
#include <memory>
#include <vector>

namespace aftfs {

class FileSystem
{
public:
    typedef std::shared_ptr<aftfs::DirectoryEntry> DirectoryEntryPtr;
    typedef std::shared_ptr<aftio::Reader> FileReaderPtr;
    
    enum Status {
        Status_OK,
        Status_ERROR,
        Status_DIRECTORY_NOT_FOUND,
        Status_FILE_NOT_FOUND,
        Status_UNKNOWN
    };
    
    FileSystem();

    virtual ~FileSystem();
    
    virtual aftu::URL getCurrentDirectory(Status* status = NULL) = 0;
    
    virtual Status setCurrentDirectory(aftu::URL const& url) = 0;
    
    virtual Status listCurrentDirectory(std::vector<aftu::URL>& results) = 0;
    
    virtual Status listDirectory(std::vector<aftu::URL>& results, aftu::URL const& url) = 0;
    
    virtual DirectoryEntryPtr directoryEntry(aftu::URL const& url, Status* status = NULL) = 0;
    
    virtual FileReaderPtr openFileReader(aftu::URL const& url, Status* status = NULL) = 0;
};

} // namespace

#endif // INCLUDED
