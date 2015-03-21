#include <agta_platform.h>

namespace agta {

Platform::Platform(FilesystemPtr filesystem, DisplayTimerPtr displayTimer)
: m_filesystem(filesystem),
  m_displayTimer(displayTimer)
{}

Platform::~Platform()
{}

Platform::FilesystemPtr Platform::filesystem() const
{
    return m_filesystem;
}

Platform::DisplayTimerPtr Platform::displayTimer() const
{
    return m_displayTimer;
}

} // namespace
