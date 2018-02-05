#include <agte_space.h>
#include <vector>
#include <map>
#include <set>

namespace agte {

Space::EntityView::Iterator::Iterator()
: m_entities(nullptr),
  m_componentSet(nullptr)
{}

Space::EntityView::Iterator::Iterator(Space::EntityInfoList* entities,
                                      Entity::ComponentSet const* componentSet,
                                      Space::EntityInfoList::iterator iter)
: m_entities(entities),
  m_componentSet(componentSet),
  m_iter(iter)
{}

Space::EntityView::Iterator::Iterator(Space::EntityView::Iterator const& rhs)
: m_entities(rhs.m_entities),
  m_componentSet(rhs.m_componentSet),
  m_iter(rhs.m_iter)
{}

Space::EntityView::Iterator::~Iterator()
{}

Space::EntityView::Iterator& Space::EntityView::Iterator::operator=(Space::EntityView::Iterator const& rhs)
{
    m_entities = rhs.m_entities;
    m_componentSet = rhs.m_componentSet;
    m_iter = rhs.m_iter;

    return *this;
}

Space::EntityView::Iterator& Space::EntityView::Iterator::operator++()
{
    ++m_iter;
    while (m_iter != m_entities->end() && (m_iter->components & *m_componentSet) != *m_componentSet)
    {
        ++m_iter;
    }

    return *this;
}

Space::EntityView::Iterator Space::EntityView::Iterator::operator++(int)
{
    Space::EntityInfoList::iterator iter = m_iter;
    ++m_iter;
    while (m_iter != m_entities->end() && (m_iter->components & *m_componentSet) != *m_componentSet)
    {
        ++m_iter;
    }

    return Iterator(m_entities, m_componentSet, iter);
}

Entity& Space::EntityView::Iterator::operator*()
{
    return m_iter->entity;
}

bool Space::EntityView::Iterator::operator==(Space::EntityView::Iterator const& rhs) const
{
    return m_iter == rhs.m_iter;
}

bool Space::EntityView::Iterator::operator!=(Space::EntityView::Iterator const& rhs) const
{
    return m_iter != rhs.m_iter;
}

Space::EntityView::EntityView(Space::EntityInfoList& entities,
                              Entity::ComponentSet const& componentSet)
: m_entities(entities),
  m_componentSet(componentSet)
{}

Space::EntityView::~EntityView()
{}

Space::EntityView::Iterator Space::EntityView::begin() const
{
    Space::EntityInfoList::iterator iter = m_entities.begin();
    
    while ((iter->components & m_componentSet) != m_componentSet && iter != m_entities.end())
    {
        ++iter;
    }

    return Iterator(&m_entities, &m_componentSet, iter);
}

Space::EntityView::Iterator Space::EntityView::end() const
{
    return Iterator(&m_entities, &m_componentSet, m_entities.end());
}

Space::Space()
: m_id(afth::UUID::v4())
{}

Space::~Space()
{}

afth::UUID const& Space::id() const
{
    return m_id;
}

Entity Space::createEntity()
{
    size_t entityId = -1;

    // if free entities, use one of those
    if (!m_freeEntityIds.empty())
    {
        entityId = m_freeEntityIds.back();
        m_freeEntityIds.pop_back();

        Entity entity(entityId);

        EntityInfo& entityInfo = m_entities[entityId];
        entityInfo.entity = entity;
        entityInfo.active = true;
        entityInfo.components = Entity::ComponentSet();

        return entity;
    }
    else
    {
        entityId = m_entities.size();

        Entity entity(entityId);

        EntityInfo entityInfo;
        entityInfo.entity = entity;
        entityInfo.active = true;
        entityInfo.components = Entity::ComponentSet();
        m_entities.push_back(entityInfo);

        return entity;
    }
}

void Space::destroyEntity(Entity entity)
{
    size_t entityId = entity.id();
    EntityInfo& entityInfo = m_entities[entityId];
    entityInfo.active = false;
    m_freeEntityIds.push_back(entityId);
}

void Space::addComponentToEntity(Entity entity, size_t componentType)
{
    EntityInfo& entityInfo = m_entities[entity.id()];
    entityInfo.components.set(componentType);
}

void Space::removeComponentFromEntity(Entity entity, size_t componentType)
{
    EntityInfo& entityInfo = m_entities[entity.id()];
    entityInfo.components.reset(componentType);
}

Space::EntityView Space::getEntitiesForComponents(Entity::ComponentSet const& components)
{
    return Space::EntityView(m_entities, components);
}

} // namespace
