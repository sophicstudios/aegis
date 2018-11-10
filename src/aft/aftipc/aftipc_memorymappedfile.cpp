#include <aftipc_memorymappedfile.h>
#include <aftipc_resultcode.h>
#include <aftu_exception.h>
#include <afts_platform.h>
#include <cerrno>
#include <sstream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace aftipc {

namespace {

int createOrOpen(
    std::string const& filename,
    size_t size,
    int oflag,
    aftio::Permissions const& permissions)
{
    int fd = open(filename.c_str(), oflag, permissions.mode());
    if (-1 == fd) {
        aftipc::ResultCode result = aftipc::ResultUtil::fromErrno(errno);
        
        std::stringstream s;
        s << "open failed ["
            << " result: " << result
            << " ]";
            
        throw aftu::Exception(s.str());
    }
    
    if (size > 0) {
        int truncResult = ftruncate(fd, size);
        if (0 != truncResult) {
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

int openOnly(
    std::string const& filename,
    int oflag)
{
    int fd = open(filename.c_str(), oflag);
    if (-1 == fd) {
        aftipc::ResultCode result = aftipc::ResultUtil::fromErrno(errno);
        
        std::stringstream s;
        s << "open failed ["
            << " result: " << result
            << " ]";
            
        throw aftu::Exception(s.str());
    }
    
    return fd;
}

} // namespace

MemoryMappedFile::MemoryMappedFile(
    aftio::OpenFlags::CreateOnly openFlag,
    aftio::AccessFlags::ReadWrite accessFlag,
    std::string const& filename,
    size_t size,
    aftio::Permissions const& permissions)
: m_permissions(permissions)
, m_filename(filename)
{
    int oflag = O_RDWR | O_CREAT | O_EXCL;
    
    if (0 == size) {
        oflag |= O_TRUNC;
    }
    
    m_fd = createOrOpen(m_filename, size, oflag, permissions);
}

MemoryMappedFile::MemoryMappedFile(
    aftio::OpenFlags::CreateOnly openFlag,
    aftio::AccessFlags::ReadOnly accessFlag,
    std::string const& filename,
    size_t size,
    aftio::Permissions const& permissions)
: m_permissions(permissions)
, m_filename(filename)
{
    int oflag = O_RDONLY | O_CREAT | O_EXCL;
    
    if (0 == size) {
        oflag |= O_TRUNC;
    }
    
    m_fd = createOrOpen(m_filename, size, oflag, permissions);
}

MemoryMappedFile::MemoryMappedFile(
    aftio::OpenFlags::CreateOrOpen openFlag,
    aftio::AccessFlags::ReadWrite accessFlag,
    std::string const& filename,
    size_t size,
    aftio::Permissions const& permissions)
: m_permissions(permissions)
, m_filename(filename)
{
    int oflag = O_RDWR | O_CREAT;
    
    if (0 == size) {
        oflag |= O_TRUNC;
    }
    
    m_fd = createOrOpen(m_filename, size, oflag, permissions);
}

MemoryMappedFile::MemoryMappedFile(
    aftio::OpenFlags::CreateOrOpen openFlag,
    aftio::AccessFlags::ReadOnly accessFlag,
    std::string const& filename,
    size_t size,
    aftio::Permissions const& permissions)
: m_filename(filename)
{
    int oflag = O_RDONLY | O_CREAT;

    if (0 == size) {
        oflag |= O_TRUNC;
    }

    m_fd = createOrOpen(m_filename, size, oflag, permissions);
}
    
MemoryMappedFile::MemoryMappedFile(
    aftio::AccessFlags::ReadWrite accessFlag,
    std::string const& filename)
: m_permissions(aftio::Permission(true, true, false)) // read, write, non-exec
, m_filename(filename)
{
    int oflag = O_RDWR;
    
    m_fd = openOnly(m_filename, oflag);
}
    
MemoryMappedFile::MemoryMappedFile(
    aftio::AccessFlags::ReadOnly accessFlag,
    std::string const& filename)
: m_permissions(aftio::Permission(true, false, false)) // read, non-write, non-exec
, m_filename(filename)
{
    int oflag = O_RDONLY;

    m_fd = openOnly(m_filename, oflag);
}
    
MemoryMappedFile::~MemoryMappedFile()
{
    close(m_fd);
    unlink(m_filename.c_str());
}

ResultCode MemoryMappedFile::map(
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
        // assume 4K pagesize
        pagesize = 4096;
    }
    
    off_t pageOffset = (offset / pagesize) * pagesize;
    size_t actualLength = static_cast<size_t>(offset + length);
    
    
    int prot = 0;
    if (m_permissions.user().read()) {
        prot |= PROT_READ;
    }

    if (m_permissions.user().write()) {
        prot |= PROT_WRITE;
    }

    if (m_permissions.user().execute()) {
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

ResultCode MemoryMappedFile::unmap(
    aftipc::Mappable::MappedRegionInfo* regionInfo)
{
    int result = munmap(regionInfo->baseAddress, regionInfo->size);
    if (result != 0) {
        return aftipc::ResultUtil::fromErrno(errno);
    }

    return aftipc::ResultCode_SUCCESS;
}

} // namespace
