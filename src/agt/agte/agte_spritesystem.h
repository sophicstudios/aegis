#ifndef INCLUDED_AEGIS_AGTE_SPRITESYSTEM_H
#define INCLUDED_AEGIS_AGTE_SPRITESYSTEM_H

#include <agte_pool.h>
#include <agte_engine.h>
#include <agte_space.h>
#include <agte_system.h>
#include <memory>

namespace agte {

class SpriteSystem : public System
{
public:
    typedef std::shared_ptr<agte::Space> SpacePtr;

    SpriteSystem();
    
    SpriteSystem(int updatePriority);

    virtual ~SpriteSystem();

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);

    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    virtual void doPostUpdate(agte::Engine::Context& context);

private:
    Space::Entity::ComponentSet m_componentSet;
};

} // namespace

#endif // INCLUDED
