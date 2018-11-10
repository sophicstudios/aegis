#include <agte_entity.h>
#include <functional>

namespace agte {

Entity::Entity() {}

Entity::Entity(Space* space, size_t id)
: _space(space)
, _id(id)
{
}

Entity::~Entity() {}

size_t Entity::id() const
{
    return _id;
}

std::string const& Entity::name() const
{
    return _name;
}

void Entity::name(std::string const& name)
{
    _name = name;
}

size_t Entity::Hash::operator()(Entity const& entity)
{
    return std::hash<size_t>()(entity._id);
}

bool operator==(Entity const& lhs, Entity const& rhs)
{
    return lhs._id == rhs._id;
}

bool operator<(Entity const& lhs, Entity const& rhs)
{
    return lhs._id < rhs._id;
}

bool operator>(Entity const& lhs, Entity const& rhs)
{
    return lhs._id > rhs._id;
}

bool operator<=(Entity const& lhs, Entity const& rhs)
{
    return lhs._id <= rhs._id;
}

bool operator>=(Entity const& lhs, Entity const& rhs)
{
    return lhs._id >= rhs._id;
}

} // namespace agte
