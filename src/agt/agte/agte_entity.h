#ifndef INCLUDED_AEGIS_AGTE_ENTITY_H
#define INCLUDED_AEGIS_AGTE_ENTITY_H

#include <bitset>
#include <string>

namespace agte {

class Space;

class Entity
{
    friend class Space;

    friend bool operator==(Entity const& lhs, Entity const& rhs);
    friend bool operator<(Entity const& lhs, Entity const& rhs);
    friend bool operator>(Entity const& lhs, Entity const& rhs);
    friend bool operator<=(Entity const& lhs, Entity const& rhs);
    friend bool operator>=(Entity const& lhs, Entity const& rhs);

public:
    static const int MAX_COMPONENTS = sizeof(size_t);
    typedef std::bitset<MAX_COMPONENTS> ComponentSet;

    struct Hash
    {
        size_t operator()(Entity const& entity);
    };

    ~Entity();

    size_t id() const;

protected:
    Entity(size_t id);

private:
    Entity();

    size_t m_id;
};

bool operator==(Entity const& lhs, Entity const& rhs);

bool operator<(Entity const& lhs, Entity const& rhs);

bool operator>(Entity const& lhs, Entity const& rhs);

bool operator<=(Entity const& lhs, Entity const& rhs);

bool operator>=(Entity const& lhs, Entity const& rhs);

} // namespace

#endif // INCLUDED
