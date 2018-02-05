#ifndef INCLUDED_AEGIS_AGTE_PLATFORM_H
#define INCLUDED_AEGIS_AGTE_PLATFORM_H

#include <agtui_glview.h>
#include <aftfs_filesystem.h>
#include <memory>

namespace agte {

class Platform
{
public:
    typedef std::shared_ptr<aftfs::FileSystem> FilesystemPtr;
    typedef std::shared_ptr<agtui::GLView> GLViewPtr;

    Platform(FilesystemPtr filesystem, GLViewPtr glView);

    ~Platform();

    FilesystemPtr filesystem() const;

    GLViewPtr glView() const;

private:
    FilesystemPtr m_filesystem;
    GLViewPtr m_glView;
};

} // namespace

#endif // INCLUDED
