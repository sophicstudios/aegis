#ifndef INCLUDED_AGTA_PLATFORM_H
#define INCLUDED_AGTA_PLATFORM_H

#include <aftfs_filesystem.h>
#include <agta_displaytimer.h>
#include <memory>

namespace agta {

class Platform
{
public:
    typedef std::shared_ptr<aftfs::Filesystem> FilesystemPtr;
    typedef std::shared_ptr<agta::DisplayTimer> DisplayTimerPtr;

    Platform(FilesystemPtr filesystem, DisplayTimerPtr displayTimer);

    ~Platform();

    FilesystemPtr filesystem() const;

    DisplayTimerPtr displayTimer() const;

private:
    FilesystemPtr m_filesystem;
    DisplayTimerPtr m_displayTimer;
};

} // namespace

#endif // INCLUDED
