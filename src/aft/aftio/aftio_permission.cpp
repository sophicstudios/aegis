#include <aftio_permission.h>
#include <aftu_exception.h>

namespace aegis {
namespace aftio {

Permission::Permission()
: m_read(true), m_write(true), m_execute(true)
{}

Permission::Permission(int typeFlags)
: m_read(typeFlags & Permission::Type_READ),
  m_write(typeFlags & Permission::Type_WRITE),
  m_execute(typeFlags & Permission::Type_EXECUTE)
{}

Permission::Permission(std::string const& flagString) throw (aftu::Exception)
: m_read(false),
  m_write(false),
  m_execute(false)
{
    if (flagString.size() > 3) {
        throw aftu::Exception() << "Invalid permission flag string ["
            << " flagString: '" << flagString << "'"
            << " ]";
    }

    std::string::const_iterator it, end = flagString.end();
    for (it = flagString.begin(); it != end; ++it) {
        if (*it == 'r') {
            m_read = true;
        }
        else if (*it == 'w') {
            m_write = true;
        }
        else if (*it == 'x') {
            m_execute = true;
        }
        else {
            throw aftu::Exception() << "Invalid permission flag character ["
                << " character: '" << *it << "'"
                << " flagString: '" << flagString << "'"
                << " ]";
        }
    }
}

Permission::Permission(Permission const& rhs)
: m_read(rhs.m_read),
  m_write(rhs.m_write),
  m_execute(rhs.m_execute)
{}

Permission::Permission(bool read, bool write, bool execute)
: m_read(read),
  m_write(write),
  m_execute(execute)
{}

Permission::~Permission()
{}

Permission& Permission::operator=(Permission const& rhs)
{
    m_read = rhs.m_read;
    m_write = rhs.m_write;
    m_execute = rhs.m_execute;
    
    return *this;
}

Permission& Permission::operator+=(Permission const& rhs)
{
    if (rhs.m_read) {
        m_read = true;
    }
    
    if (rhs.m_write) {
        m_write = true;
    }
    
    if (rhs.m_execute) {
        m_execute = true;
    }
    
    return *this;
}

Permission& Permission::operator-=(Permission const& rhs)
{
    if (rhs.m_read) {
        m_read = false;
    }
    
    if (rhs.m_write) {
        m_write = false;
    }
    
    if (rhs.m_execute) {
        m_execute = false;
    }
    
    return *this;
}

bool Permission::hasRead() const
{
    return m_read;
}

void Permission::setRead(bool value)
{
    m_read = value;
}

bool Permission::hasWrite() const
{
    return m_write;
}

void Permission::setWrite(bool value)
{
    m_write = value;
}

bool Permission::hasExecute() const
{
    return m_execute;
}

void Permission::setExecute(bool value)
{
    m_execute = value;
}

std::ostream& operator<<(std::ostream& os, Permission const& perm)
{
    os << "["
        << (perm.hasRead() ? "+r" : "-r")
        << (perm.hasWrite() ? "+w" : "-w")
        << (perm.hasExecute() ? "+x" : "-x")
        << "]";
    
    return os;
}

} // namespace
} // namespace
