#include <aftfs_localfilesystem.h>
#include <afts_assert.h>
#include <afts_platform.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <cerrno>

namespace aftfs {

namespace {

class PosixDirectoryEntry : public DirectoryEntry
{
public:
    explicit PosixDirectoryEntry(aftu::URL const& url, struct stat const& info);
    
    virtual ~PosixDirectoryEntry();
    
    virtual aftu::URL url();
    
    virtual aftio::Permissions permissions();
    
    virtual Type type() const;
    
    virtual bool isFile() const;
    
    virtual bool isDirectory() const;
    
    virtual bool isLink() const;
    
    virtual size_t size() const;
    
private:
    aftu::URL m_url;
    struct stat m_info;
};

class PosixFileReader : public aftio::Reader
{
public:
    PosixFileReader(FILE* fileHandle);
    
    virtual ~PosixFileReader();
    
    virtual aftio::Reader::Status read(char* buffer, size_t bytes, size_t* actualBytes);
    
    virtual aftio::Reader::Status read(std::vector<char>& buffer, size_t bytes, size_t* actualBytes);

    virtual aftio::Reader::Status reset();
    
    virtual bool eof(aftio::Reader::Status* status = NULL);
    
    virtual aftio::Reader::Status position(off_t position);
    
    virtual off_t position(aftio::Reader::Status* status = NULL);

private:
    FILE* m_fileHandle;
};

long getPathMaxLength(std::string const& path)
{
    long name_max = 255;//pathconf(path.c_str(), _PC_NAME_MAX);

    if (name_max == -1) // limit not defined, or error
    {
        name_max = 1024;
    }
    
    return name_max;
}

std::string getCWD(long name_max)
{
    char* buffer = (char*)malloc(name_max);
    char* result = getcwd(buffer, name_max);
    while (result == NULL && errno == ERANGE)
    {
        free(buffer);
        name_max *= 2;
        buffer = (char*)malloc(name_max);
        result = getcwd(buffer, name_max);
    }
    
    if (result)
    {
        return std::string(buffer);
    }
    else
    {
        return std::string("");
    }
}

} // namespace

struct LocalFilesystem::Impl
{
};

LocalFilesystem::LocalFilesystem()
: m_impl(new LocalFilesystem::Impl())
{
}

LocalFilesystem::~LocalFilesystem()
{
    delete m_impl;
}

aftu::URL LocalFilesystem::getCurrentDirectory(Filesystem::Status* status)
{
    long name_max = getPathMaxLength(".");
    std::string dir = getCWD(name_max);
    return aftu::URL(std::string("file://") + dir);
}

Filesystem::Status LocalFilesystem::setCurrentDirectory(aftu::URL const& url)
{
    std::string path = url.path();
    int result = chdir(path.c_str());
    return result == 0 ? Filesystem::Status_OK : Filesystem::Status_ERROR;
}

Filesystem::Status LocalFilesystem::listCurrentDirectory(std::vector<aftu::URL>& results)
{
    long name_max = getPathMaxLength(".");

    long len = offsetof(struct dirent, d_name) + name_max + 1;

    std::string currentDirectory = getCWD(name_max);
    
    std::string baseUrl;

    if (currentDirectory.empty())
    {
        baseUrl = ".";
    }
    else
    {
        baseUrl = std::string("file://") + currentDirectory;
    }
    
    DIR* dir = opendir(currentDirectory.c_str());
    if (!dir)
    {
        return Filesystem::Status_DIRECTORY_NOT_FOUND;
    }

    struct dirent* entry = (struct dirent*)malloc(len);
    
    int result = 0;
    struct dirent* entryResult;

    do
    {
        entryResult = NULL;
        result = readdir_r(dir, entry, &entryResult);
        results.push_back(aftu::URL(baseUrl + "/" + std::string(entry->d_name, entry->d_namlen)));
    }
    while (entryResult != NULL && result == 0);
    
    if (result != 0)
    {
        return Filesystem::Status_ERROR;
    }
    
    free(entry);
    
    return Filesystem::Status_OK;
}

Filesystem::Status LocalFilesystem::listDirectory(std::vector<aftu::URL>& results, aftu::URL const& url)
{
    DIR* dir = NULL;
    struct dirent* entry = NULL;
    struct dirent* entryResult = NULL;
    
    std::string path = url.path();
    dir = opendir(path.empty() ? "/" : path.c_str());

    if (!dir)
    {
        return Filesystem::Status_DIRECTORY_NOT_FOUND;
    }

    long name_max = getPathMaxLength(path);
    long len = offsetof(struct dirent, d_name) + name_max + 1;
    entry = (struct dirent*)malloc(len);
    
    int result = 0;

    while ((result = readdir_r(dir, entry, &entryResult) == 0) && entryResult != NULL)
    {
        results.push_back(aftu::URL(url.canonical() + std::string(entry->d_name, entry->d_namlen)));
    }
    
    if (result != 0)
    {
        return Filesystem::Status_ERROR;
    }
    
    free(entry);
    
    return Filesystem::Status_OK;
}

Filesystem::DirectoryEntryPtr LocalFilesystem::directoryEntry(aftu::URL const& url, Filesystem::Status* status)
{
    std::string path = url.path();

    if (path.empty())
    {
        path = "/";
    }
    
    struct stat info;
    std::memset(&info, 0, sizeof(struct stat));
    
    stat(path.c_str(), &info);

    return Filesystem::DirectoryEntryPtr(new PosixDirectoryEntry(url, info));
}

Filesystem::FileReaderPtr LocalFilesystem::openFileReader(aftu::URL const& url, Filesystem::Status* status)
{
    std::string path = url.path();
    FILE* fileHandle = fopen(path.c_str(), "r");

    if (!fileHandle)
    {
        if (status)
        {
            *status = Filesystem::Status_FILE_NOT_FOUND;
        }

        return Filesystem::FileReaderPtr();
    }
    
    return Filesystem::FileReaderPtr(new PosixFileReader(fileHandle));
}

PosixDirectoryEntry::PosixDirectoryEntry(aftu::URL const& url, struct stat const& info)
: m_url(url)
{
    std::memcpy(&m_info, &info, sizeof(struct stat));
}
    
PosixDirectoryEntry::~PosixDirectoryEntry()
{
}

aftu::URL PosixDirectoryEntry::url()
{
    return m_url;
}
    
aftio::Permissions PosixDirectoryEntry::permissions()
{
    return aftio::Permissions();
}
    
DirectoryEntry::Type PosixDirectoryEntry::type() const
{
    return DirectoryEntry::Type_UNKNOWN;
}
    
bool PosixDirectoryEntry::isFile() const
{
    return S_ISREG(m_info.st_mode);
}
    
bool PosixDirectoryEntry::isDirectory() const
{
    return S_ISDIR(m_info.st_mode);
}
    
bool PosixDirectoryEntry::isLink() const
{
    return S_ISLNK(m_info.st_mode);
}

size_t PosixDirectoryEntry::size() const
{
    return static_cast<size_t>(m_info.st_size);
}

PosixFileReader::PosixFileReader(FILE* fileHandle)
: m_fileHandle(fileHandle)
{}

PosixFileReader::~PosixFileReader()
{
    if (m_fileHandle)
    {
        fclose(m_fileHandle);
    }
}

aftio::Reader::Status PosixFileReader::read(char* buffer, size_t bytes, size_t* actualBytes)
{
    size_t bytesRead = fread(buffer, sizeof(char), bytes, m_fileHandle);

    if (actualBytes)
    {
        *actualBytes = bytesRead;
    }
    
    aftio::Reader::Status status = aftio::Reader::Status_OK;

    if (bytesRead < bytes)
    {
        if (feof(m_fileHandle) > 0)
        {
            status = aftio::Reader::Status_EOF;
        }
        else if (ferror(m_fileHandle) > 0)
        {
            status = aftio::Reader::Status_ERROR;
        }
    }
    
    return status;
}

aftio::Reader::Status PosixFileReader::read(std::vector<char>& buffer, size_t bytes, size_t* actualBytes)
{
    size_t originalSize = buffer.size();
    buffer.resize(originalSize + bytes);
    size_t bytesRead = fread(&buffer[buffer.size()], sizeof(char), bytes, m_fileHandle);
    
    if (actualBytes)
    {
        *actualBytes = bytesRead;
    }
    
    aftio::Reader::Status status = aftio::Reader::Status_OK;
    
    if (bytesRead < bytes)
    {
        if (feof(m_fileHandle) > 0)
        {
            status = aftio::Reader::Status_EOF;
        }
        else if (ferror(m_fileHandle) > 0)
        {
            status = aftio::Reader::Status_ERROR;
        }

        buffer.resize(originalSize + bytesRead);
    }
    
    return status;
}

aftio::Reader::Status PosixFileReader::reset()
{
    clearerr(m_fileHandle);
    return aftio::Reader::Status_OK;
}

bool PosixFileReader::eof(aftio::Reader::Status* status)
{
    bool result = feof(m_fileHandle) > 0 ? true : false;

    if (status)
    {
        *status = aftio::Reader::Status_OK;
    }
    
    return result;
}

aftio::Reader::Status PosixFileReader::position(off_t position)
{
    aftio::Reader::Status status = aftio::Reader::Status_OK;

    int result = fseeko(m_fileHandle, position, 0);

    if (result != 0)
    {
        status = aftio::Reader::Status_ERROR;
    }
    
    return status;
}

off_t PosixFileReader::position(aftio::Reader::Status* status)
{
    off_t result = ftello(m_fileHandle);

    if (result < 0)
    {
        if (status)
        {
            *status = aftio::Reader::Status_ERROR;
        }

        return 0;
    }
    else
    {
        if (status)
        {
            *status = aftio::Reader::Status_OK;
        }

        return result;
    }
}

} // namespace
