#include <agte_spritesystem.h>
#include <agtc_componenthandle.h>
#include <agtc_spriteanimationcomponent.h>
#include <agtc_visual2dcomponent.h>

namespace agte {

namespace {

void initComponentSet(Space::Entity::ComponentSet& componentSet)
{
    componentSet.set(agtc::ComponentHandle<agtc::SpriteAnimationComponent>::typeId());
    componentSet.set(agtc::ComponentHandle<agtc::Visual2dComponent>::typeId());
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

void SpriteSystem::doPreUpdate(agte::Engine::Context& context)
{
}

void SpriteSystem::doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    // get all entities with sprite animation components
    Space::EntityView entityView = space->entitiesForComponents(m_componentSet);

    Space::EntityView::Iterator it = entityView.begin();
    Space::EntityView::Iterator end = entityView.end();
    for (; it != end; ++it)
    {
        agtc::SpriteAnimationComponent& spriteAnimation = it->get<agtc::SpriteAnimationComponent>();

        spriteAnimation.update(context.elapsedSeconds());

        agtc::Visual2dComponent& visual = it->get<agtc::Visual2dComponent>();
        float offsetX = visual.spriteSize().width() * spriteAnimation.currentFrame();
        float offsetY = visual.spriteOffset().y();
        visual.spriteOffset(agtm::Vector2<float>(offsetX, offsetY));
    }
}

void SpriteSystem::doPostUpdate(agte::Engine::Context& context)
{
}

} // namespace
