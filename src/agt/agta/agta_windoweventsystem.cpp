#include <agta_windoweventsystem.h>
#include <actp_scopedlock.h>
#include <functional>

namespace agta {

namespace {

void callResizeHandlers(agta::Engine::Context& context,
                        std::vector<std::pair<std::string, agtui::Window::ResizeEventHandler> > const& resizeHandlers,
                        agtm::Rect<float> const& rect)
{
    std::vector<std::pair<std::string, agtui::Window::ResizeEventHandler> >::const_iterator it = resizeHandlers.begin();
    std::vector<std::pair<std::string, agtui::Window::ResizeEventHandler> >::const_iterator end = resizeHandlers.end();
    for (; it != end; ++it) {
        it->second(rect);
    }
}

} // namespace

WindowEventSystem::WindowEventSystem(std::shared_ptr<agtui::Window> const& window)
: System(0),
  m_window(window)
{
    m_pendingResizeRects.reserve(10);
    m_window->addResizeEventHandler("WindowEventSystem", std::bind(&WindowEventSystem::onResize, this, std::placeholders::_1));
}

WindowEventSystem::~WindowEventSystem()
{
    m_window->removeResizeEventHandler("WindowEventSystem");
}

void WindowEventSystem::addResizeEventHandler(std::string const& id, agtui::Window::ResizeEventHandler const& handler)
{
    m_resizeHandlers.push_back(std::make_pair(id, handler));
}

void WindowEventSystem::removeResizeEventHandler(std::string const& id)
{
    ResizeHandlers::iterator it = m_resizeHandlers.begin();
    ResizeHandlers::iterator end = m_resizeHandlers.end();

    for (; it != end; ++it) {
        if (id == it->first) {
            m_resizeHandlers.erase(it);
            break;
        }
    }
}

void WindowEventSystem::doPreUpdate(agta::Engine::Context& context)
{
    // go through all queued events and send them to the listeners
    actp::ScopedLock<actp::Mutex> lock(m_mutex);

    PendingResizeRects::iterator it = m_pendingResizeRects.begin();
    PendingResizeRects::iterator end = m_pendingResizeRects.end();
    for (; it != end; ++it) {
        callResizeHandlers(context, m_resizeHandlers, *it);
    }
}

void WindowEventSystem::doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context)
{}

void WindowEventSystem::doPostUpdate(agta::Engine::Context& context)
{}

void WindowEventSystem::onResize(agtm::Rect<float> const& rect)
{
    // queue up the resize events for later
    actp::ScopedLock<actp::Mutex> lock(m_mutex);
    m_pendingResizeRects.push_back(rect);
}

} // namespace
