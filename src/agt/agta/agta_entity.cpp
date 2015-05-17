#include <agta_entity.h>

namespace agta {

Entity::Entity(size_t id, std::string const& name)
: m_id(id),
  m_name(name)
{}

Entity::~Entity()
{}

size_t Entity::id() const
{
    return m_id;
}

std::string const& Entity::name() const
{
    return m_name;
}

} // namespace
