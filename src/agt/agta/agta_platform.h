#ifndef INCLUDED_AGTA_PLATFORM_H
#define INCLUDED_AGTA_PLATFORM_H

#include <aftfs_filesystem.h>
#include <agta_glwindow.h>
#include <memory>

namespace agta {

class Platform
{
public:
    typedef std::shared_ptr<aftfs::Filesystem> FilesystemPtr;
    typedef std::shared_ptr<agta::GLWindow> GLWindowPtr;

    Platform(FilesystemPtr filesystem, GLWindowPtr glWindow);

    ~Platform();

    FilesystemPtr filesystem() const;

    GLWindowPtr glWindow() const;

private:
    FilesystemPtr m_filesystem;
    GLWindowPtr m_glWindow;
};

} // namespace

#endif // INCLUDED
