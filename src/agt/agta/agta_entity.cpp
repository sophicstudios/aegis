#include <agta_entity.h>

namespace agta {

Entity::Entity(uint32_t id, std::string const& name)
: m_id(id),
  m_name(name)
{}

Entity::~Entity()
{}

uint32_t Entity::id() const
{
    return m_id;
}

std::string const& Entity::name() const
{
    return m_name;
}

} // namespace
