#ifndef INCLUDED_AEGIS_AFTIPC_MAPPEDREGION_H
#define INCLUDED_AEGIS_AFTIPC_MAPPEDREGION_H

#include <aftipc_mappable.h>
#include <aftipc_resultcode.h>
#include <cstdlib>

namespace aegis {
namespace aftipc {

class MappedRegion
{
public:
    MappedRegion(aftipc::Mappable& mappable, off_t offset, size_t length);
    
    ~MappedRegion();

    aftipc::ResultCode remap(off_t offset, size_t length);
    
    size_t size() const;
    
    void* data(off_t offset = 0);
    
private:
    MappedRegion(MappedRegion const&);
    MappedRegion& operator=(MappedRegion const&);
    
    aftipc::Mappable& m_mappable;
    aftipc::Mappable::MappedRegionInfo m_regionInfo;
    void* m_data;
    size_t m_dataLength;
};

} // namespace
} // namespace

#endif // INCLUDED
