#ifndef INCLUDED_AEGIS_AFTFS_POSIXPATH_H
#define INCLUDED_AEGIS_AFTFS_POSIXPATH_H

#include <aftfs_path.h>

namespace aftfs {

class PosixPath : public aftfs::Path
{
public:
    PosixPath();
    
    PosixPath(std::string const& pathname);

private:
    std::string m_pathname;
};

} // namespace

#endif // INCLUDED
