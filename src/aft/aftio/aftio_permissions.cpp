#include <aftio_permissions.h>
#include <sys/stat.h>
#include <ostream>

namespace aegis {
namespace aftio {

Permissions::Permissions()
: m_user(true, true, false),
  m_group(true, true, false),
  m_other(true, true, false)
{}

Permissions::Permissions(
    Permission const& user,
    Permission const& group,
    Permission const& other)
: m_user(user),
  m_group(group),
  m_other(other)
{}

Permissions::Permissions(Permission const& all)
: m_user(all),
  m_group(all),
  m_other(all)
{}

Permissions::Permissions(mode_t mask)
: m_user(mask & S_IRUSR, mask & S_IWUSR, mask & S_IXUSR),
  m_group(mask & S_IRGRP, mask & S_IWGRP, mask & S_IXGRP),
  m_other(mask & S_IROTH, mask & S_IWOTH, mask & S_IXOTH)
{}

Permissions::~Permissions()
{}

Permission const& Permissions::user() const
{
    return m_user;
}

void Permissions::setUser(Permission const& perm)
{
    m_user = perm;
}

Permission const& Permissions::group() const
{
    return m_group;
}

void Permissions::setGroup(Permission const& perm)
{
    m_group = perm;
}

Permission const& Permissions::other() const
{
    return m_other;
}

void Permissions::setOther(Permission const& perm)
{
    m_other = perm;
}

mode_t Permissions::mode() const
{
    mode_t mode = 0;

    if (m_user.hasRead()) {
        mode |= S_IRUSR;
    }
    
    if (m_user.hasWrite()) {
        mode |= S_IWUSR;
    }
    
    if (m_user.hasExecute()) {
        mode |= S_IXUSR;
    }
    
    if (m_group.hasRead()) {
        mode |= S_IRGRP;
    }
    
    if (m_group.hasWrite()) {
        mode |= S_IWGRP;
    }
    
    if (m_group.hasExecute()) {
        mode |= S_IXGRP;
    }
    
    if (m_other.hasRead()) {
        mode |= S_IROTH;
    }
    
    if (m_other.hasWrite()) {
        mode |= S_IWOTH;
    }
    
    if (m_other.hasExecute()) {
        mode |= S_IXOTH;
    }
    
    return mode;
}

std::ostream& operator<<(std::ostream& os, Permissions const& perm)
{
    os << "["
        << " u: " << perm.user()
        << " g: " << perm.group()
        << " o: " << perm.other()
        << " ]";
    
    return os;
}

} // namespace
} // namespace
