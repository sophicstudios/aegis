#include <agta_space.h>
#include <vector>
#include <map>
#include <set>

namespace agta {

class Space::Impl
{
public:
    typedef std::vector<bool> EntityList;
    typedef std::map<std::string, uint32_t> EntityMap;
    typedef std::map<uint32_t, std::string> ReverseEntityMap;
    typedef std::set<uint32_t> FreeEntitySet;

    EntityList entities;
    EntityMap entityMap;
    ReverseEntityMap reverseEntityMap;
    FreeEntitySet freeEntities;
};

Space::Space()
{}

Space::~Space()
{}

uint32_t Space::createEntity(std::string const& name)
{
    uint32_t entityId = 0;

    if (!m_impl->freeEntities.empty()) {
        // if there are entries in the free entity list, reuse the first id
        entityId = *(m_impl->freeEntities.begin());

        // remove the id from the free entity list
        m_impl->freeEntities.erase(m_impl->freeEntities.begin());

        // mark the id as active in the active entity list
        m_impl->entities[entityId] = true;
    }
    else {
        // get the next available entity id
        entityId = m_impl->entities.size();

        // add an entry to the active entity list
        m_impl->entities.push_back(true);
    }

    // map the name to the entity id
    m_impl->entityMap.insert(std::make_pair(name, entityId));
    m_impl->reverseEntityMap.insert(std::make_pair(entityId, name));

    // return the allocated entityId
    return entityId;
}

bool Space::deleteEntity(std::string const& name)
{
    // find the entityId in the entity map
    Impl::EntityMap::iterator it = m_impl->entityMap.find(name);
    if (it == m_impl->entityMap.end()) {
        return false;
    }

    m_impl->freeEntities.insert(it->second);
    m_impl->entities[it->second] = false;
    m_impl->reverseEntityMap.erase(it->second);
    m_impl->entityMap.erase(it);

    return true;
}

bool Space::deleteEntity(uint32_t entityId)
{
    // find the name from the entityId
    Impl::ReverseEntityMap::iterator it = m_impl->reverseEntityMap.find(entityId);
    if (it == m_impl->reverseEntityMap.end()) {
        return false;
    }

    m_impl->freeEntities.insert(entityId);
    m_impl->entities[entityId] = false;
    m_impl->entityMap.erase(it->second);
    m_impl->reverseEntityMap.erase(it);

    return true;
}

} // namespace
