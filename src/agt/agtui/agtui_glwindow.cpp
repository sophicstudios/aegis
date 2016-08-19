#include <agtui_glwindow.h>

namespace agtui {

GLWindow::GLWindow(
    GLWindow::RenderingContextPtr renderingContext,
    GLWindow::DisplayTimerPtr displayTimer)
: m_renderingContext(renderingContext),
  m_displayTimer(displayTimer)
{}

GLWindow::~GLWindow()
{}

GLWindow::DisplayTimerPtr GLWindow::displayTimer() const
{
    return m_displayTimer;
}

GLWindow::RenderingContextPtr GLWindow::renderingContext() const
{
    return m_renderingContext;
}

} // namespace
