#ifndef INCLUDED_AGTA_ENTITY_H
#define INCLUDED_AGTA_ENTITY_H

#include <afth_uuid.h>
#include <string>

namespace agta {

class Entity
{
public:
    Entity();

    Entity(afth::UUID const& id);

    ~Entity();

    afth::UUID const& id() const;

private:
    Entity();

    afth::UUID m_id;
};

} // namespace

#endif // INCLUDED
