#ifndef INCLUDED_AEGIS_AFTIPC_MAPPABLE_H
#define INCLUDED_AEGIS_AFTIPC_MAPPABLE_H

#include <aftipc_resultcode.h>

namespace aftipc {

class Mappable
{
public:
    struct MappedRegionInfo
    {
        void* baseAddress;
        size_t size;
        off_t offset;        
    };
    
    /**
     * Constructor
     */
    Mappable();
    
    /**
     * Destructor
     */
    virtual ~Mappable() = 0;
    
    virtual aftipc::ResultCode map(MappedRegionInfo* regionInfo,
                                   off_t offset,
                                   size_t length) = 0;
    
    virtual aftipc::ResultCode unmap(MappedRegionInfo* regionInfo) = 0;
};

} // namespace

#endif // INCLUDED
