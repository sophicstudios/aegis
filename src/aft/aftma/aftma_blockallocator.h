#ifndef INCLUDED_AEGIS_AFTMA_BLOCKALLOCATOR_H
#define INCLUDED_AEGIS_AFTMA_BLOCKALLOCATOR_H

#include <aftma_allocator.h>
#include <map>

namespace aftma {

class BlockAllocator
    : public aftma::Allocator
{
public:
    BlockAllocator();
    
    virtual ~BlockAllocator();
    
    virtual void* allocate(size_t size);
    
    virtual void deallocate(void* ptr);
    
private:
    struct Pool
    {
        void* startPool;
        void* endPool;
        size_t size;
        uint32_t* freeListBitmap;
        size_t bitmapLength;
    };

    typedef std::map<size_t, Pool*> PoolMap;
    PoolMap m_poolMap;
};

} // namespace

#endif // INCLUDED
