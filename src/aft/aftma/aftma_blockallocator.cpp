#include <aftma_blockallocator.h>

#include <exception>
#include <memory>

namespace aegis {
namespace aftma {

namespace {

size_t calculateBlockSize(size_t size)
{
    size_t blockSize = 8;
    while (size > blockSize) {
        blockSize <<= 1;
    }
    
    return blockSize;
}

bool hasFreeBlock(uint32_t* freeListBitmap, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
    }
    
    return false;
}

}

BlockAllocator::BlockAllocator()
{}

BlockAllocator::~BlockAllocator()
{
    PoolMap::iterator it, end = m_poolMap.end();
    for (it = m_poolMap.begin(); it != end; ++it) {
        //Pool* pool = it->second;
    }
}

void* BlockAllocator::allocate(size_t size)
{
    size_t blockSize = calculateBlockSize(size);
    PoolMap::iterator it = m_poolMap.find(blockSize);
    if (it == m_poolMap.end()) {
//        it = m_poolMap.insert(std::make_pair(blockSize, 
//    void* block = malloc(m_blockSize * m_blockCount);
    }
    
    return 0;
}

void BlockAllocator::deallocate(void* ptr)
{
}

} // namespace
} // namespace
