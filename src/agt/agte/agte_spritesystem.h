#ifndef INCLUDED_AEGIS_AGTE_SPRITESYSTEM_H
#define INCLUDED_AEGIS_AGTE_SPRITESYSTEM_H

#include <agte_pool.h>
#include <agte_engine.h>
#include <agte_space.h>
#include <agte_system.h>
#include <agta_assetpool.h>
#include <agta_material.h>
#include <agtc_spriteanimationcomponent.h>
#include <memory>

namespace agte {

class SpriteSystem : public System
{
public:
    typedef std::shared_ptr<agte::Space> SpacePtr;
    typedef std::shared_ptr<agte::Pool<agtc::SpriteAnimationComponent> > SpriteAnimationComponentPoolPtr;

    SpriteSystem();
    
    SpriteSystem(int updatePriority);

    virtual ~SpriteSystem();

    void addSpriteAnimationComponents(SpacePtr space, SpriteAnimationComponentPoolPtr components);

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);

    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    virtual void doPostUpdate(agte::Engine::Context& context);

private:
    typedef std::map<afth::UUID, SpriteAnimationComponentPoolPtr> SpaceSpriteAnimationComponentsMap;

    Space::Entity::ComponentSet m_componentSet;
    SpaceSpriteAnimationComponentsMap m_spaceSpriteAnimationComponentsMap;
};

} // namespace

#endif // INCLUDED
