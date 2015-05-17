#ifndef INCLUDED_AGTA_WINDOWEVENTSYSTEM_H
#define INCLUDED_AGTA_WINDOWEVENTSYSTEM_H

#include <agta_engine.h>
#include <agta_system.h>
#include <agtm_rect.h>
#include <agtui_window.h>
#include <actp_mutex.h>
#include <functional>
#include <memory>

namespace agta {

class WindowEventSystem : public agta::System
{
public:
    WindowEventSystem(std::shared_ptr<agtui::Window> const& window);

    virtual ~WindowEventSystem();

    void addResizeEventHandler(std::string const& id, agtui::Window::ResizeEventHandler const& handler);

    void removeResizeEventHandler(std::string const& id);

protected:
    virtual void doPreUpdate(agta::Engine::Context& context);
    virtual void doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context);
    virtual void doPostUpdate(agta::Engine::Context& context);

private:
    WindowEventSystem();

    typedef std::vector<agtm::Rect<float> > PendingResizeRects;
    typedef std::vector<std::pair<std::string, agtui::Window::ResizeEventHandler> > ResizeHandlers;

    void onResize(agtm::Rect<float> const& rect);

    std::shared_ptr<agtui::Window> m_window;
    PendingResizeRects m_pendingResizeRects;
    ResizeHandlers m_resizeHandlers;
    actp::Mutex m_mutex;
};

} // namespace

#endif // INCLUDED
