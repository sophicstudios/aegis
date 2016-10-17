#include <agte_space.h>
#include <vector>
#include <map>
#include <set>

namespace agte {

Space::EntityView::Iterator::Iterator()
: m_entities(nullptr),
  m_componentSet(nullptr),
  m_index(std::numeric_limits<size_t>::max())
{}

Space::EntityView::Iterator::Iterator(Space::EntityInfoList* entities,
                                      Entity::ComponentSet const* componentSet,
                                      size_t index)
: m_entities(entities),
  m_componentSet(componentSet),
  m_index(index)
{}

Space::EntityView::Iterator::Iterator(Space::EntityView::Iterator const& rhs)
: m_entities(rhs.m_entities),
  m_componentSet(rhs.m_componentSet),
  m_index(rhs.m_index)
{}

Space::EntityView::Iterator::~Iterator()
{}

Space::EntityView::Iterator& Space::EntityView::Iterator::operator=(Space::EntityView::Iterator const& rhs)
{
    m_entities = rhs.m_entities;
    m_componentSet = rhs.m_componentSet;
    m_index = rhs.m_index;

    return *this;
}

Space::EntityView::Iterator& Space::EntityView::Iterator::operator++()
{
    while (((*m_entities)[++m_index].components & *m_componentSet) != *m_componentSet) {}
    return *this;
}

Space::EntityView::Iterator Space::EntityView::Iterator::operator++(int)
{
    size_t index = m_index;
    while (((*m_entities)[++m_index].components & *m_componentSet) != *m_componentSet) {}
    return Iterator(m_entities, m_componentSet, index);
}

Entity& Space::EntityView::Iterator::operator*()
{
    return (*m_entities)[m_index].entity;
}

bool Space::EntityView::Iterator::operator==(Space::EntityView::Iterator const& rhs) const
{
    return m_index == rhs.m_index;
}

bool Space::EntityView::Iterator::operator!=(Space::EntityView::Iterator const& rhs) const
{
    return m_index != rhs.m_index;
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
    size_t index = 0;
    while ((m_entities[index].components & m_componentSet) != m_componentSet)
    {
        ++index;
    }

    return Iterator(&m_entities, &m_componentSet, index);
}

Space::EntityView::Iterator Space::EntityView::end() const
{
    return Iterator(&m_entities, &m_componentSet, m_entities.size());
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
        entityId = m_freeEntityIds[m_freeEntityIds.size() - 1];
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
