#include <agta_space.h>
#include <vector>
#include <map>
#include <set>

namespace agta {

Space::Space()
: m_uuid(afth::UUID::v4())
{}

Space::~Space()
{}

afth::UUID const& Space::id() const
{
    return m_uuid;
}

Space::EntityPtr Space::createEntity()
{
    size_t entityLoc = 0;
    afth::UUID uuid = afth::UUID::v4();
    EntityPtr entity(new agta::Entity(uuid));

    if (!m_freeEntities.empty()) {
        // if there are entries in the free entity list, reuse the first available location
        entityLoc = *(m_freeEntities.begin());

        // remove the location from the free entity list
        m_freeEntities.erase(m_freeEntities.begin());

        // mark the location as active in the active entity list
        m_entities[entityLoc] = true;
    }
    else {
        // get the next available entity id
        entityLoc = m_entities.size();

        // add an entry to the active entity list
        m_entities.push_back(true);
    }

    // map the name to the entity id
    m_entityMap.insert(std::make_pair(uuid, entityLoc));
    m_reverseEntityMap.insert(std::make_pair(entityLoc, uuid));

    // return the allocated entityId
    return entity;
}

bool Space::removeEntity(EntityPtr entity)
{
    return removeEntity(entity->id());
}

bool Space::removeEntity(afth::UUID const& uuid)
{
    // find the entityId in the entity map
    EntityMap::iterator it = m_entityMap.find(uuid);
    if (it == m_entityMap.end()) {
        return false;
    }

    m_freeEntities.insert(it->second);
    m_entities[it->second] = false;
    m_reverseEntityMap.erase(it->second);
    m_entityMap.erase(it);

    return true;
}

} // namespace
