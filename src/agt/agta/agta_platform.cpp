#include <agta_platform.h>

namespace agta {

Platform::Platform(FilesystemPtr filesystem, GLWindowPtr glWindow)
: m_filesystem(filesystem),
  m_glWindow(glWindow)
{}

Platform::~Platform()
{}

Platform::FilesystemPtr Platform::filesystem() const
{
    return m_filesystem;
}

Platform::GLWindowPtr Platform::glWindow() const
{
    return m_glWindow;
}

} // namespace
