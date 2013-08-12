#ifndef INCLUDED_AEGIS_AFTIPC_MEMORYMAPPEDFILE_H
#define INCLUDED_AEGIS_AFTIPC_MEMORYMAPPEDFILE_H

#include <aftipc_mappable.h>
#include <aftipc_resultcode.h>
#include <aftio_flags.h>
#include <aftio_permissions.h>
#include <string>

namespace aftipc {

class MemoryMappedFile : public aftipc::Mappable
{
public:
    static aftipc::ResultCode destroy(std::string const& path);
    
    MemoryMappedFile(
        aftio::OpenFlags::CreateOnly openFlag,
        aftio::AccessFlags::ReadWrite accessFlag,
        std::string const& path,
        size_t size,
        aftio::Permissions const& permissions = aftio::Permissions());

    MemoryMappedFile(
        aftio::OpenFlags::CreateOnly openFlag,
        aftio::AccessFlags::ReadOnly accessFlag,
        std::string const& path,
        size_t size,
        aftio::Permissions const& permissions = aftio::Permissions());
    
    MemoryMappedFile(
        aftio::OpenFlags::CreateOrOpen openFlag,
        aftio::AccessFlags::ReadWrite accessFlag,
        std::string const& path,
        size_t size,
        aftio::Permissions const& permissions = aftio::Permissions());
    
    MemoryMappedFile(
        aftio::OpenFlags::CreateOrOpen openFlag,
        aftio::AccessFlags::ReadOnly accessFlag,
        std::string const& path,
        size_t size,
        aftio::Permissions const& permissions = aftio::Permissions());
        
    MemoryMappedFile(
        aftio::AccessFlags::ReadWrite accessFlag,
        std::string const& path);
        
    MemoryMappedFile(
        aftio::AccessFlags::ReadOnly accessFlag,
        std::string const& path);
        
    ~MemoryMappedFile();

    virtual aftipc::ResultCode map(
        aftipc::Mappable::MappedRegionInfo* regionInfo,
        off_t offset,
        size_t length);

    virtual aftipc::ResultCode unmap(
        aftipc::Mappable::MappedRegionInfo* regionInfo);

private:
    int m_fd;
    aftio::Permissions m_permissions;
};

} // namespace

#endif // INCLUDED
