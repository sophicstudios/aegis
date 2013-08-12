#include <aftfs_localfilesystem.h>
#include <afts_platform.h>
#include <dirent.h>
#include <iostream>

namespace aftfs {

struct LocalFilesystem::Impl
{
};

LocalFilesystem::LocalFilesystem()
: m_impl(new LocalFilesystem::Impl())
{}

LocalFilesystem::~LocalFilesystem()
{
    delete m_impl;
}

void LocalFilesystem::listDirectory(std::vector<aftfs::DirectoryEntry>& entries)
{
    DIR* dir = NULL;
    struct dirent* entry = NULL;
    struct dirent* entryResult = NULL;
    
    dir = opendir("./");
    if (!dir) {
        return;
    }

    int name_max = pathconf("./", _PC_NAME_MAX);
    if (name_max == -1) { // Limit not defined, or error
        name_max = 255;   // Make a reasonable guess
    }
    int len = offsetof(struct dirent, d_name) + name_max + 1;
    entry = (struct dirent*)malloc(len);
    
    int result = 0;
    do {
        result = readdir_r(dir, entry, &entryResult);
    } while (entryResult != NULL && result == 0);
    
    if (result != 0) {
        std::cerr << "Error reading directory entry" << std::endl;
    }
    
    free(entry);
}

void LocalFilesystem::listDirectory(std::vector<aftfs::DirectoryEntry>& entries, aftfs::Path const& path)
{
}

void LocalFilesystem::listDirectory(std::vector<aftfs::DirectoryEntry>& entries, aftfs::DirectoryEntry const& dir)
{
}

} // namespace
