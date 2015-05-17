#ifndef INCLUDED_AGTA_SPACE_H
#define INCLUDED_AGTA_SPACE_H

#include <agta_entity.h>
#include <agtg_camera.h>
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
    typedef std::shared_ptr<agtg::Camera> CameraPtr;
    typedef std::vector<CameraPtr> CameraList;

    Space();

    ~Space();

    size_t id() const;
    
    agta::Entity createEntity(std::string const& name);

    bool removeEntity(std::string const& name);

    bool removeEntity(size_t entityId);

    void addCamera(CameraPtr camera);

    CameraList const& cameras() const;
    
private:
    typedef std::vector<bool> EntityList;
    typedef std::map<std::string, size_t> EntityMap;
    typedef std::map<size_t, std::string> ReverseEntityMap;
    typedef std::set<size_t> FreeEntitySet;

    EntityList m_entities;
    EntityMap m_entityMap;
    ReverseEntityMap m_reverseEntityMap;
    FreeEntitySet m_freeEntities;
    CameraList m_cameras;
};

} // namespace

#endif // INCLUDED
