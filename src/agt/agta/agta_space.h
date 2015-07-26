#ifndef INCLUDED_AGTA_SPACE_H
#define INCLUDED_AGTA_SPACE_H

#include <agta_entity.h>
#include <agtg_camera.h>
#include <afth_uuid.h>
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace agta {

class Space
{
public:
    typedef std::shared_ptr<agta::Entity> EntityPtr;

    Space();

    ~Space();

    afth::UUID const& id() const;
    
    EntityPtr createEntity();

    bool removeEntity(EntityPtr entity);

    bool removeEntity(afth::UUID const& entityId);

private:
    typedef std::vector<bool> EntityList;
    typedef std::map<afth::UUID, size_t> EntityMap;
    typedef std::map<size_t, afth::UUID> ReverseEntityMap;
    typedef std::set<size_t> FreeEntitySet;

    afth::UUID m_id;
    EntityList m_entities;
    EntityMap m_entityMap;
    ReverseEntityMap m_reverseEntityMap;
    FreeEntitySet m_freeEntities;
};

} // namespace

#endif // INCLUDED
