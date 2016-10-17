#include <agte_platform.h>

namespace agte {

Platform::Platform(FilesystemPtr filesystem, GLViewPtr glView)
: m_filesystem(filesystem),
  m_glView(glView)
{}

Platform::~Platform()
{}

Platform::FilesystemPtr Platform::filesystem() const
{
    return m_filesystem;
}

Platform::GLViewPtr Platform::glView() const
{
    return m_glView;
}

} // namespace
