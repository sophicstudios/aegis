#include <aftipc_mappedregion.h>
#include <aftipc_mappable.h>
#include <aftipc_resultcode.h>
#include <exception>
#include <iostream>

namespace aegis {
namespace aftipc {

MappedRegion::MappedRegion(aftipc::Mappable& mappable, off_t offset, size_t length)
: m_data(0),
  m_mappable(mappable)
{
    aftipc::ResultCode result = mappable.map(&m_regionInfo, offset, length);
    if (result != aftipc::ResultCode_SUCCESS) {
        throw std::exception();
    }
    
    m_data = reinterpret_cast<char*>(m_regionInfo.baseAddress) + m_regionInfo.offset;
    m_dataLength = m_regionInfo.size -
        (reinterpret_cast<char*>(m_data) - reinterpret_cast<char*>(m_regionInfo.baseAddress));
}

MappedRegion::~MappedRegion()
{
    aftipc::ResultCode result = m_mappable.unmap(&m_regionInfo);
    if (result != aftipc::ResultCode_SUCCESS) {
        std::cerr << "Error unmapping region ["
            << " result: " << result
            << " ]" << std::endl;
    }
}

aftipc::ResultCode MappedRegion::remap(off_t offset, size_t length)
{
    aftipc::ResultCode result = m_mappable.unmap(&m_regionInfo);
    if (result != aftipc::ResultCode_SUCCESS) {
        return result;
    }
    
    result = m_mappable.map(&m_regionInfo, offset, length);
    if (result != aftipc::ResultCode_SUCCESS) {
        return result;
    }
    
    m_data = reinterpret_cast<char*>(m_regionInfo.baseAddress) + m_regionInfo.offset;
    
    m_dataLength = m_regionInfo.size -
        (reinterpret_cast<char*>(m_data) - reinterpret_cast<char*>(m_regionInfo.baseAddress));
        
    return result;
}

size_t MappedRegion::size() const
{
    return m_dataLength;
}

void* MappedRegion::data(off_t offset)
{
    return reinterpret_cast<char*>(m_data) + offset;
}

} // namespace
} // namespace
