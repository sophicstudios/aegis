#include <agta_entity.h>

namespace agta {

Entity::Entity()
: m_id(afth::UUID::v4())
{}

Entity::Entity(afth::UUID const& id)
: m_id(id)
{}

Entity::~Entity()
{}

afth::UUID const& Entity::id() const
{
    return m_id;
}

} // namespace
