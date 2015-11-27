#include <aftio_permission.h>
#include <aftu_exception.h>

namespace aftio {

Permission::Read::Read(bool read)
: m_read(read)
{}

Permission::Read::~Read()
{}

Permission::Read::operator bool() const
{
    return m_read;
}

Permission::Write::Write(bool write)
: m_write(write)
{}

Permission::Write::~Write()
{}

Permission::Write::operator bool() const
{
    return m_write;
}

Permission::Execute::Execute(bool execute)
: m_execute(execute)
{}

Permission::Execute::~Execute()
{}

Permission::Execute::operator bool() const
{
    return m_execute;
}

Permission::Permission()
: m_read(false), m_write(false), m_execute(false)
{}

Permission::Permission(int typeFlags)
: m_read(typeFlags & Permission::Type_READ),
  m_write(typeFlags & Permission::Type_WRITE),
  m_execute(typeFlags & Permission::Type_EXECUTE)
{}

Permission::Permission(Permission const& rhs)
: m_read(rhs.m_read),
  m_write(rhs.m_write),
  m_execute(rhs.m_execute)
{}

Permission::Permission(Read read, Write write, Execute execute)
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

Permission& Permission::operator|=(Read read)
{
    m_read |= read;

    return *this;
}

Permission& Permission::operator|=(Write write)
{
    m_write |= write;

    return *this;
}

Permission& Permission::operator|=(Execute execute)
{
    m_execute |= execute;

    return *this;
}

Permission& Permission::operator|=(Permission const& permission)
{
    m_read |= permission.read();
    m_write |= permission.write();
    m_execute |= permission.execute();

    return *this;
}

Permission& Permission::operator&=(Read read)
{
    m_read &= read;

    return *this;
}

Permission& Permission::operator&=(Write write)
{
    m_write &= write;

    return *this;
}

Permission& Permission::operator&=(Execute execute)
{
    m_execute &= execute;

    return *this;
}

Permission& Permission::operator&=(Permission const& permission)
{
    m_read &= permission.read();
    m_write &= permission.write();
    m_execute &= permission.execute();

    return *this;
}

Permission::Read Permission::read() const
{
    return m_read;
}

void Permission::read(Permission::Read value)
{
    m_read = value;
}

Permission::Write Permission::write() const
{
    return m_write;
}

void Permission::write(Permission::Write value)
{
    m_write = value;
}

Permission::Execute Permission::execute() const
{
    return m_execute;
}

void Permission::execute(Permission::Execute value)
{
    m_execute = value;
}

std::ostream& operator<<(std::ostream& os, Permission const& perm)
{
    os << "["
        << (perm.read() ? "+r" : "-r")
        << (perm.write() ? "+w" : "-w")
        << (perm.execute() ? "+x" : "-x")
        << "]";
    
    return os;
}

Permission operator|(Permission const& lhs, Permission const& rhs)
{
    return Permission(lhs.read() || rhs.read(), lhs.write() || rhs.write(), lhs.execute() || rhs.execute());
}

Permission operator&(Permission const& lhs, Permission const& rhs)
{
    return Permission(lhs.read() && rhs.read(), lhs.write() && rhs.write(), lhs.execute() && rhs.execute());
}

} // namespace
