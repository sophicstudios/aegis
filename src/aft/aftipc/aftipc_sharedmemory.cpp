#include <aftipc_sharedmemory.h>
#include <afts_platform.h>
#include <aftu_exception.h>
#include <cerrno>
#include <sstream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace aegis {
namespace aftipc {

namespace {

std::string normalizeKey(std::string const& key)
{
    if (key[0] != '/') {
        return std::string("/") + key;
    }
    else {
        return key;
    }
}

int openOrCreate(int oflag, std::string const& key, size_t size, aftio::Permissions const& perm)
{
    std::string normalizedKey = normalizeKey(key);

    int fd = shm_open(normalizedKey.c_str(), oflag, perm.mode());
    if (-1 == fd) {
        aftipc::ResultCode result = aftipc::ResultUtil::fromErrno(errno);

        std::stringstream s;
        s << "shm_open failed ["
            << " result: " << result
            << " ]";

        throw aftu::Exception(s.str());
    }
    
    if (size > 0) {
        int truncResult = ftruncate(fd, size);
        if (truncResult != 0) {
            close(fd);
            
            aftipc::ResultCode result = aftipc::ResultUtil::fromErrno(errno);

            std::stringstream s;
            s << "ftruncate failed ["
                << " result: " << result
                << " ]";

            throw aftu::Exception(s.str());
        }
    }
    
    return fd;
}

int openOnly(int oflag, std::string const& key, aftio::Permissions const& perm)
{
    std::string normalizedKey = normalizeKey(key);

    int fd = shm_open(normalizedKey.c_str(), oflag, perm.mode());
    if (-1 == fd) {
        aftipc::ResultCode result = aftipc::ResultUtil::fromErrno(errno);

        std::stringstream s;
        s << "shm_open failed ["
            << " result: " << result
            << " ]";

        throw aftu::Exception(s.str());
    }

    return fd;
}

} // namespace

ResultCode SharedMemory::destroy(std::string const& key)
{
    std::string normalizedKey = normalizeKey(key);
    
    int result = shm_unlink(normalizedKey.c_str());
    if (result != 0) {
        return aftipc::ResultUtil::fromErrno(errno);
    }
    
    return aftipc::ResultCode_SUCCESS;
}

SharedMemory::SharedMemory(
    aftio::OpenFlags::CreateOnly openFlag,
    aftio::AccessFlags::ReadWrite accessFlag,
    std::string const& key,
    size_t size,
    aftio::Permissions perm)
: m_permissions(perm)
{
    int oflag = O_CREAT | O_EXCL | O_RDWR;

    if (size == 0) {
        oflag |= O_TRUNC;
    }
    
    m_fd = openOrCreate(oflag, key, size, perm);
}

SharedMemory::SharedMemory(
    aftio::OpenFlags::CreateOnly openFlag,
    aftio::AccessFlags::ReadOnly accessFlag,
    std::string const& key,
    size_t size,
    aftio::Permissions perm)
: m_permissions(perm)
{
    int oflag = O_CREAT | O_EXCL | O_RDONLY;
    
    if (size == 0) {
        oflag |= O_TRUNC;
    }
    
    m_fd = openOrCreate(oflag, key, size, perm);
}

SharedMemory::SharedMemory(
    aftio::OpenFlags::CreateOrOpen openFlag,
    aftio::AccessFlags::ReadWrite accessFlag,
    std::string const& key,
    size_t size,
    aftio::Permissions perm)
: m_permissions(perm)
{
    int oflag = O_CREAT | O_RDWR;
    
    if (size == 0) {
        oflag |= O_TRUNC;
    }
    
    m_fd = openOrCreate(oflag, key, size, perm);
}
    
SharedMemory::SharedMemory(
    aftio::OpenFlags::CreateOrOpen openFlag,
    aftio::AccessFlags::ReadOnly accessFlag,
    std::string const& key,
    size_t size,
    aftio::Permissions perm)
: m_permissions(perm)
{
    int oflag = O_CREAT | O_RDONLY;
    
    m_fd = openOrCreate(oflag, key, size, perm);
}

SharedMemory::SharedMemory(
    aftio::AccessFlags::ReadWrite accessMode,
    std::string const& key)
: m_permissions(aftio::Permission(true, true, false)) // read, write, non-exec
{
    int oflag = O_RDWR;
    
    m_fd = openOnly(oflag, key, m_permissions);
}

SharedMemory::SharedMemory(
    aftio::AccessFlags::ReadOnly accessMode,
    std::string const& key)
: m_permissions(aftio::Permission(true, false, false)) // read, non-write, non-exec
{
    int oflag = O_RDONLY;
    
    m_fd = openOnly(oflag, key, m_permissions);
}

SharedMemory::~SharedMemory()
{
    close(m_fd);
}

aftipc::ResultCode SharedMemory::map(
    aftipc::Mappable::MappedRegionInfo* regionInfo,
    off_t offset,
    size_t length)
{
    // first, we have to calculate the correct offset to use when
    // mapping the shared memory segment. This must be a multiple of the
    // page size, so we calculate which page this offset is in and use
    // the page start address as the real offset for mapping
    long pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize == -1) {
        // assume 4K
        pagesize = 4096;
    }

    long pageOffset = (offset / pagesize) * pagesize;
    size_t actualLength = static_cast<size_t>(offset + length);
    
    
    int prot = 0;
    if (m_permissions.user().hasRead()) {
        prot |= PROT_READ;
    }

    if (m_permissions.user().hasWrite()) {
        prot |= PROT_WRITE;
    }

    if (m_permissions.user().hasExecute()) {
        // Mac OSX doesn't support PROT_EXEC flag
        #ifndef AFTS_OS_MACOS
        prot |= PROT_EXEC;
        #endif
    }
    
    int flags = MAP_SHARED;

    void* addr = mmap(
        NULL,           // let the system determine the mapping address
        actualLength,   // the length of the area to map
        prot,           // protection flags
        flags,          // private or shared
        m_fd,           // file descriptor opened with shm_open
        pageOffset);    // the offset to start mapping from

    if (addr == MAP_FAILED) {
        return aftipc::ResultUtil::fromErrno(errno);
    }
    
    regionInfo->baseAddress = addr;
    regionInfo->size = actualLength;
    regionInfo->offset = offset;
    
    return aftipc::ResultCode_SUCCESS;
}

aftipc::ResultCode SharedMemory::unmap(
    aftipc::Mappable::MappedRegionInfo* regionInfo)
{
    int result = munmap(regionInfo->baseAddress, regionInfo->size);
    if (result != 0) {
        return aftipc::ResultUtil::fromErrno(errno);
    }

    return aftipc::ResultCode_SUCCESS;
}

} // namespace
} // namespace
