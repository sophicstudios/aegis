#include <agte_spritesystem.h>

namespace agte {

namespace {

void initComponentSet(Entity::ComponentSet& componentSet)
{
    //componentSet.set(agte::ComponentPool<agtc::SpriteAnimationComponent>::type());
}

} // namespace

SpriteSystem::SpriteSystem()
{
    initComponentSet(m_componentSet);
}

SpriteSystem::SpriteSystem(int updatePriority)
: System(updatePriority)
{
    initComponentSet(m_componentSet);
}

SpriteSystem::~SpriteSystem()
{}

void SpriteSystem::addSpriteAnimationComponents(SpacePtr space, SpriteAnimationComponentPoolPtr components)
{
    m_spaceSpriteAnimationComponentsMap.insert(std::make_pair(space->id(), components));
}

void SpriteSystem::doPreUpdate(agte::Engine::Context& context)
{
}

void SpriteSystem::doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    // get the SpriteAnimation components for the space
    SpaceSpriteAnimationComponentsMap::iterator spriteAnimationIter = m_spaceSpriteAnimationComponentsMap.find(space->id());
    if (spriteAnimationIter == m_spaceSpriteAnimationComponentsMap.end())
    {
        return;
    }
    SpriteAnimationComponentPoolPtr spriteAnimationComponents = spriteAnimationIter->second;

    // get all entities with sprite animation components
    Space::EntityView entityView = space->entitiesForComponents(m_componentSet);

    Space::EntityView::Iterator it = entityView.begin();
    Space::EntityView::Iterator end = entityView.end();
    for (; it != end; ++it)
    {
        //agtc::SpriteAnimationComponent& spriteAnimation = spriteAnimationComponents->componentForEntity(*it);

        //spriteAnimation.update(context.elapsedSeconds());
    }
}

void SpriteSystem::doPostUpdate(agte::Engine::Context& context)
{
}

} // namespace
