#ifndef INCLUDED_AGTA_COMPONENTENTITYMAP_H
#define INCLUDED_AGTA_COMPONENTENTITYMAP_H

#include <agta_entity.h>
#include <agta_space.h>
#include <vector>

namespace agta {

class ComponentEntityMap
{
public:
    typedef std::vector<Entity> EntityList;

    ComponentEntityMap();

    virtual ~ComponentEntityMap();

    virtual void addEntity(Space const& space, Entity& entity);

    virtual EntityList const& entities(Space const& space) const;

private:
    typedef 
    EntityList m_entityList;
};

} // namespace

#endif // INCLUDED
