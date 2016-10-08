#include <agta_platform.h>

namespace agta {

Platform::Platform(FilesystemPtr filesystem, WindowPtr window)
: m_filesystem(filesystem),
  m_window(window)
{}

Platform::~Platform()
{}

Platform::FilesystemPtr Platform::filesystem() const
{
    return m_filesystem;
}

Platform::WindowPtr Platform::window() const
{
    return m_window;
}

} // namespace
