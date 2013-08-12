#ifndef INCLUDED_AEGIS_AFTIPC_SHAREDMEMORY_H
#define INCLUDED_AEGIS_AFTIPC_SHAREDMEMORY_H

#include <aftipc_mappable.h>
#include <aftio_flags.h>
#include <aftio_permissions.h>
#include <string>

namespace aftipc {

class SharedMemory : public aftipc::Mappable
{
public:
    static aftipc::ResultCode destroy(std::string const& key);
    
    /**
     * Creates a Posix shared memory object
     */
    SharedMemory(
        aftio::OpenFlags::CreateOnly openFlag,
        aftio::AccessFlags::ReadWrite accessFlag,
        std::string const& key,
        size_t size,
        aftio::Permissions perm = aftio::Permissions());

    SharedMemory(
        aftio::OpenFlags::CreateOnly openFlag,
        aftio::AccessFlags::ReadOnly accessFlag,
        std::string const& key,
        size_t size,
        aftio::Permissions perm = aftio::Permissions());
    
    SharedMemory(
        aftio::OpenFlags::CreateOrOpen openFlag,
        aftio::AccessFlags::ReadWrite accessFlag,
        std::string const& key,
        size_t size,
        aftio::Permissions perm = aftio::Permissions());
        
    SharedMemory(
        aftio::OpenFlags::CreateOrOpen openFlag,
        aftio::AccessFlags::ReadOnly accessFlag,
        std::string const& key,
        size_t size,
        aftio::Permissions perm = aftio::Permissions());
    
    SharedMemory(
        aftio::AccessFlags::ReadWrite accessFlag,
        std::string const& key);
    
    SharedMemory(
        aftio::AccessFlags::ReadOnly accessFlag,
        std::string const& key);

    virtual ~SharedMemory();

    virtual aftipc::ResultCode map(
        aftipc::Mappable::MappedRegionInfo* regionInfo,
        off_t offset,
        size_t length);

    virtual aftipc::ResultCode unmap(
        aftipc::Mappable::MappedRegionInfo* regionInfo);
    
private:
    SharedMemory(SharedMemory const&);
    SharedMemory& operator=(SharedMemory const&);
    
    int m_fd;
    aftio::Permissions m_permissions;
};

} // namespace

#endif // INCLUDED
