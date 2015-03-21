#ifndef INCLUDED_AGTA_ENTITY_H
#define INCLUDED_AGTA_ENTITY_H

#include <string>

namespace agta {

class Entity
{
public:
    Entity(uint32_t id, std::string const& name);

    ~Entity();

    uint32_t id() const;

    std::string const& name() const;

private:
    Entity();

    uint32_t m_id;
    std::string m_name;
};

} // namespace

#endif // INCLUDED
