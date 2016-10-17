#include <agte_entity.h>
#include <functional>

namespace agte {

Entity::Entity()
{}

Entity::Entity(size_t id)
: m_id(id)
{}

Entity::~Entity()
{}

size_t Entity::id() const
{
    return m_id;
}

size_t Entity::Hash::operator()(Entity const& entity)
{
    return std::hash<size_t>()(entity.m_id);
}

bool operator==(Entity const& lhs, Entity const& rhs)
{
    return lhs.m_id == rhs.m_id;
}

bool operator<(Entity const& lhs, Entity const& rhs)
{
    return lhs.m_id < rhs.m_id;
}

bool operator>(Entity const& lhs, Entity const& rhs)
{
    return lhs.m_id > rhs.m_id;
}

bool operator<=(Entity const& lhs, Entity const& rhs)
{
    return lhs.m_id <= rhs.m_id;
}

bool operator>=(Entity const& lhs, Entity const& rhs)
{
    return lhs.m_id >= rhs.m_id;
}

} // namespace
