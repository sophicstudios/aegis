#ifndef INCLUDED_AEGIS_AFTIO_PERMISSIONS_H
#define INCLUDED_AEGIS_AFTIO_PERMISSIONS_H

#include <aftio_permission.h>
#include <iosfwd>

namespace aftio {

class Permissions
{
public:
    /**
     * Creates a Permissions object with user, group and other
     * all set to read, write and execute
     */
    Permissions();
    
    /**
     * Creates a Permissions object with user, group and other
     * set to the supplied values
     */
    Permissions(
        Permission const& user,
        Permission const& group,
        Permission const& other);
    
    /**
     * Creates a Permissions object with user, group and other
     * set to the same specified value
     */
    Permissions(Permission const& all);
    
    /**
     * Creates a Permissions object with user, group and other
     * set based on the value of mask, which is of type mode_t
     */
    Permissions(mode_t mask);

    /**
     * Destructor
     */
    ~Permissions();
    
    Permission const& user() const;

    void setUser(Permission const& perm);
    
    Permission const& group() const;

    void setGroup(Permission const& perm);
    
    Permission const& other() const;

    void setOther(Permission const& perm);

    mode_t mode() const;
    
private:
    Permission m_user;
    Permission m_group;
    Permission m_other;
};

std::ostream& operator<<(std::ostream& os, Permissions const& perm);

} // namespace

#endif // INCLUDED
