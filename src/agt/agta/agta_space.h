#ifndef INCLUDED_AGTA_WORLD_H
#define INCLUDED_AGTA_WORLD_H

#include <cstdint>

namespace agta {

class World
{
public:
    World(uint32_t maxEntities);

    ~World();

    uint32_t createEntity();

    uint32_t deleteEntity(uint32_t entityId);

private:
};

} // namespace

#endif // INCLUDED
