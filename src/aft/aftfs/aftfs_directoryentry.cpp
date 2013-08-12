#include <aftfs_directoryentry.h>

namespace aftfs {

DirectoryEntry::DirectoryEntry()
{
}

DirectoryEntry::~DirectoryEntry()
{
}

std::string DirectoryEntry::name()
{
    return std::string();
}

aftfs::Path DirectoryEntry::path()
{
    return aftfs::Path("./");
}

aftio::Permissions DirectoryEntry::permissions()
{
    return aftio::Permissions();
}

DirectoryEntry::Type DirectoryEntry::type() const
{
    return Type_UNKNOWN;
}

bool DirectoryEntry::isFile() const
{
    return false;
}

bool DirectoryEntry::isDirectory() const
{
    return false;
}

bool DirectoryEntry::isLink() const
{
    return false;
}

bool DirectoryEntry::setName(std::string const& name)
{
    return false;
}

bool DirectoryEntry::setPermissions(aftio::Permissions const& permissions)
{
    return false;
}

} // namespace
