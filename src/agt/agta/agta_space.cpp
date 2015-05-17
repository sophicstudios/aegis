#include <agta_space.h>
#include <vector>
#include <map>
#include <set>

namespace agta {

Space::Space()
{}

Space::~Space()
{}

size_t Space::id() const
{
    return 0;
}

agta::Entity Space::createEntity(std::string const& name)
{
    size_t entityId = 0;

    if (!m_freeEntities.empty()) {
        // if there are entries in the free entity list, reuse the first id
        entityId = *(m_freeEntities.begin());

        // remove the id from the free entity list
        m_freeEntities.erase(m_freeEntities.begin());

        // mark the id as active in the active entity list
        m_entities[entityId] = true;
    }
    else {
        // get the next available entity id
        entityId = m_entities.size();

        // add an entry to the active entity list
        m_entities.push_back(true);
    }

    // map the name to the entity id
    m_entityMap.insert(std::make_pair(name, entityId));
    m_reverseEntityMap.insert(std::make_pair(entityId, name));

    // return the allocated entityId
    return agta::Entity(entityId, name);
}

bool Space::removeEntity(std::string const& name)
{
    // find the entityId in the entity map
    EntityMap::iterator it = m_entityMap.find(name);
    if (it == m_entityMap.end()) {
        return false;
    }

    m_freeEntities.insert(it->second);
    m_entities[it->second] = false;
    m_reverseEntityMap.erase(it->second);
    m_entityMap.erase(it);

    return true;
}

bool Space::removeEntity(size_t entityId)
{
    // find the name from the entityId
    ReverseEntityMap::iterator it = m_reverseEntityMap.find(entityId);
    if (it == m_reverseEntityMap.end()) {
        return false;
    }

    m_freeEntities.insert(entityId);
    m_entities[entityId] = false;
    m_entityMap.erase(it->second);
    m_reverseEntityMap.erase(it);

    return true;
}

void Space::addCamera(CameraPtr camera)
{
    m_cameras.push_back(camera);
}

Space::CameraList const& Space::cameras() const
{
    return m_cameras;
}

} // namespace
