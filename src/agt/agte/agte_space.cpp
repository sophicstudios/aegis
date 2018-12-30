#include <agte_space.h>
#include <vector>
#include <map>
#include <set>

namespace agte {

Space::Entity::Entity() {}

Space::Entity::Entity(Space* space, size_t id)
: _space(space)
, _id(id)
{
}

Space::Entity::~Entity() {}

size_t Space::Entity::id() const
{
    return _id;
}

std::string const& Space::Entity::name() const
{
    return _name;
}

void Space::Entity::name(std::string const& name)
{
    _name = name;
}

size_t Space::Entity::Hash::operator()(Space::Entity const& entity)
{
    return std::hash<size_t>()(entity._id);
}

bool operator==(Space::Entity const& lhs, Space::Entity const& rhs)
{
    return lhs._id == rhs._id;
}

bool operator<(Space::Entity const& lhs, Space::Entity const& rhs)
{
    return lhs._id < rhs._id;
}

bool operator>(Space::Entity const& lhs, Space::Entity const& rhs)
{
    return lhs._id > rhs._id;
}

bool operator<=(Space::Entity const& lhs, Space::Entity const& rhs)
{
    return lhs._id <= rhs._id;
}

bool operator>=(Space::Entity const& lhs, Space::Entity const& rhs)
{
    return lhs._id >= rhs._id;
}

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

Space::Entity& Space::EntityView::Iterator::operator*()
{
    return _iter->entity;
}

Space::Entity* Space::EntityView::Iterator::operator->()
{
    return &(_iter->entity);
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
    // if no components are set, return the end iterator
    if (!_componentSet.any()) {
        return end();
    }

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

Space::Entity Space::createEntity()
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

void Space::destroyEntity(Space::Entity entity)
{
    size_t entityId = entity.id();
    EntityInfo& entityInfo = _entities[entityId];
    entityInfo.active = false;
    // TODO: Destroy all associated components
    _freeEntityIds.push_back(entityId);
}

Space::EntityView Space::entitiesForComponents(Space::Entity::ComponentSet const& components)
{
    return Space::EntityView(_entities, components);
}


} // namespace
