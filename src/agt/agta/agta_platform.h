#ifndef INCLUDED_AGTA_PLATFORM_H
#define INCLUDED_AGTA_PLATFORM_H

#include <aftfs_filesystem.h>
#include <agtui_window.h>
#include <memory>

namespace agta {

class Platform
{
public:
    typedef std::shared_ptr<aftfs::Filesystem> FilesystemPtr;
    typedef std::shared_ptr<agtui::Window> WindowPtr;

    Platform(FilesystemPtr filesystem, WindowPtr window);

    ~Platform();

    FilesystemPtr filesystem() const;

    WindowPtr window() const;

private:
    FilesystemPtr m_filesystem;
    WindowPtr m_window;
};

} // namespace

#endif // INCLUDED
