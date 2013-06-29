#ifndef INCLUDED_AEGIS_AFTMA_ALLOCATOR_H
#define INCLUDED_AEGIS_AFTMA_ALLOCATOR_H

#include <cstdlib>

namespace aegis {
namespace aftma {

class Allocator
{
public:
    Allocator();
    
    virtual ~Allocator();
    
    virtual void* allocate(std::size_t size) = 0;
    
    virtual void deallocate(void* ptr) = 0;
};

} // namespace
} // namespace

#endif // INCLUDED
