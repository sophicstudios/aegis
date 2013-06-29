#ifndef INCLUDED_AEGIS_AFTFS_FILESYSTEM_H
#define INCLUDED_AEGIS_AFTFS_FILESYSTEM_H

#include <aftfs_path.h>
#include <aftfs_directoryentry.h>

namespace aegis {
namespace aftfs {

class FileSystem
{
public:
    enum Status {
        Status_OK,
        Status_UNKNOWN
    };
    
    ~FileSystem();

    static bool setCurrentWorkingDirectory(aftfs::Path const& path);
    
    static aftfs::Path currentWorkingDirectory();
    
    void listDirectory(std::vector<DirectoryEntry>& entries);
    
    void listDirectory(std::vector<DirectoryEntry>& entries, aftfs::Path const& path);
    
    void listDirectory(std::vector<DirectoryEntry>& entries, DirectoryEntry const& dir);
    
private:
    FileSystem();
};

} // namespace
} // namespace

#endif // INCLUDED
