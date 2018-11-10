#include <agte_space.h>
#include <vector>
#include <map>
#include <set>

namespace agte {

Space::EntityView::Iterator::Iterator()
: _entities(nullptr),
  _componentSet(nullptr)
{}

Space::EntityView::Iterator::Iterator(Space::EntityInfoList* entities,
                                      Entity::ComponentSet const* componentSet,
                                      Space::EntityInfoList::iterator iter)
: _entities(entities),
  _componentSet(componentSet),
  _iter(iter)
{}

Space::EntityView::Iterator::Iterator(Space::EntityView::Iterator const& rhs)
: _entities(rhs._entities),
  _componentSet(rhs._componentSet),
  _iter(rhs._iter)
{}

Space::EntityView::Iterator::~Iterator()
{}

Space::EntityView::Iterator& Space::EntityView::Iterator::operator=(Space::EntityView::Iterator const& rhs)
{
    _entities = rhs._entities;
    _componentSet = rhs._componentSet;
    _iter = rhs._iter;

    return *this;
}

Space::EntityView::Iterator& Space::EntityView::Iterator::operator++()
{
    ++_iter;
    while (_iter != _entities->end() && (_iter->components & *_componentSet) != *_componentSet)
    {
        ++_iter;
    }

    return *this;
}

Space::EntityView::Iterator Space::EntityView::Iterator::operator++(int)
{
    Space::EntityInfoList::iterator iter = _iter;
    ++_iter;
    while (_iter != _entities->end() && (_iter->components & *_componentSet) != *_componentSet)
    {
        ++_iter;
    }

    return Iterator(_entities, _componentSet, iter);
}

Entity& Space::EntityView::Iterator::operator*()
{
    return _iter->entity;
}

bool Space::EntityView::Iterator::operator==(Space::EntityView::Iterator const& rhs) const
{
    return _iter == rhs._iter;
}

bool Space::EntityView::Iterator::operator!=(Space::EntityView::Iterator const& rhs) const
{
    return _iter != rhs._iter;
}

Space::EntityView::EntityView(Space::EntityInfoList& entities,
                              Entity::ComponentSet const& componentSet)
: _entities(entities),
  _componentSet(componentSet)
{}

Space::EntityView::~EntityView()
{}

Space::EntityView::Iterator Space::EntityView::begin() const
{
    Space::EntityInfoList::iterator iter = _entities.begin();
    
    while ((iter->components & _componentSet) != _componentSet && iter != _entities.end())
    {
        ++iter;
    }

    return Iterator(&_entities, &_componentSet, iter);
}

Space::EntityView::Iterator Space::EntityView::end() const
{
    return Iterator(&_entities, &_componentSet, _entities.end());
}

Space::Space()
: _id(afth::UUID::v4())
{}

Space::~Space()
{}

afth::UUID const& Space::id() const
{
    return _id;
}

Entity Space::createEntity()
{
    size_t entityId = -1;

    // if free entities, use one of those
    if (!_freeEntityIds.empty())
    {
        entityId = _freeEntityIds.back();
        _freeEntityIds.pop_back();

        Entity entity(this, entityId);

        EntityInfo& entityInfo = _entities[entityId];
        entityInfo.entity = entity;
        entityInfo.active = true;
        entityInfo.components = Entity::ComponentSet();

        return entityInfo.entity;
    }
    else
    {
        entityId = _entities.size();

        Entity entity(this, entityId);

        EntityInfo entityInfo;
        entityInfo.entity = entity;
        entityInfo.active = true;
        entityInfo.components = Entity::ComponentSet();
        _entities.push_back(entityInfo);

        return _entities[entityId].entity;
    }
}

void Space::destroyEntity(Entity entity)
{
    size_t entityId = entity.id();
    EntityInfo& entityInfo = _entities[entityId];
    entityInfo.active = false;
    // TODO: Destroy all associated components
    _freeEntityIds.push_back(entityId);
}

Space::EntityView Space::entitiesForComponents(Entity::ComponentSet const& components)
{
    return Space::EntityView(_entities, components);
}


} // namespace
