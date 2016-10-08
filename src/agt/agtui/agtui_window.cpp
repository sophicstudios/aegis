#include <agtui_window.h>

namespace agtui {

template<typename T>
void removeHandler(std::string const& id, std::vector<std::pair<std::string, T> >& handlers)
{
    typename std::vector<std::pair<std::string, T> >::iterator it = handlers.begin();
    typename std::vector<std::pair<std::string, T> >::iterator end = handlers.end();

    for (; it != end; ++it) {
        if (id == it->first) {
            handlers.erase(it);
            break;
        }
    }
}

Window::Window()
{}

Window::~Window()
{}

void Window::addResizeEventHandler(std::string const& id, ResizeEventHandler const& handler)
{
    m_resizeHandlers.push_back(std::make_pair(id, handler));

    doAddResizeEventHandler(id, handler);
}

void Window::removeResizeEventHandler(std::string const& id)
{
    removeHandler(id, m_resizeHandlers);

    doRemoveResizeEventHandler(id);
}

void Window::addDrawEventHandler(std::string const& id, DrawEventHandler const& handler)
{
    m_drawHandlers.push_back(std::make_pair(id, handler));

    doAddDrawEventHandler(id, handler);
}

void Window::removeDrawEventHandler(std::string const& id)
{
    removeHandler(id, m_drawHandlers);

    doRemoveDrawEventHandler(id);
}

void Window::addKeyEventHandler(std::string const& id, KeyEventHandler const& handler)
{
    m_keyHandlers.push_back(std::make_pair(id, handler));

    doAddKeyEventHandler(id, handler);
}

void Window::removeKeyEventHandler(std::string const& id)
{
    removeHandler(id, m_keyHandlers);

    doRemoveKeyEventHandler(id);
}

void Window::addMouseEventHandler(std::string const& id, MouseEventHandler const& handler)
{
    m_mouseHandlers.push_back(std::make_pair(id, handler));

    doAddMouseEventHandler(id, handler);
}

void Window::removeMouseEventHandler(std::string const& id)
{
    removeHandler(id, m_mouseHandlers);

    doRemoveMouseEventHandler(id);
}

void Window::addTouchEventHandler(std::string const& id, TouchEventHandler const& handler)
{
    m_touchHandlers.push_back(std::make_pair(id, handler));

    doAddTouchEventHandler(id, handler);
}

void Window::removeTouchEventHandler(std::string const& id)
{
    removeHandler(id, m_touchHandlers);

    doRemoveTouchEventHandler(id);
}

void Window::addChild(Window::WidgetPtr widget)
{
    m_children.push_back(widget);
}

void Window::setSizer(Window::SizerPtr sizer)
{
    m_sizer = sizer;
}

void Window::onResize(agtm::Rect<float> const& bounds)
{
    // calculate the client size?
    // update the size of the sizer
    if (m_sizer)
    {
        m_sizer->size(bounds.size());
    }

    // TOOD: verify the size meets the sizer's constraints
    // and reset the window size to the constraint
}

Window::ResizeHandlers const& Window::resizeHandlers() const
{
    return m_resizeHandlers;
}

Window::DrawHandlers const& Window::drawHandlers() const
{
    return m_drawHandlers;
}

Window::KeyHandlers const& Window::keyHandlers() const
{
    return m_keyHandlers;
}

Window::MouseHandlers const& Window::mouseHandlers() const
{
    return m_mouseHandlers;
}

Window::TouchHandlers const& Window::touchHandlers() const
{
    return m_touchHandlers;
}

void Window::doAddResizeEventHandler(std::string const& id, ResizeEventHandler const& handler)
{
    // Default handler does nothing
}

void Window::doRemoveResizeEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void Window::doAddDrawEventHandler(std::string const& id, DrawEventHandler const& handler)
{
    // Default handler does nothing
}

void Window::doRemoveDrawEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void Window::doAddKeyEventHandler(std::string const& id, KeyEventHandler const& handler)
{
    // Default handler does nothing
}

void Window::doRemoveKeyEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void Window::doAddMouseEventHandler(std::string const& id, MouseEventHandler const& handler)
{
    // Default handler does nothing
}

void Window::doRemoveMouseEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void Window::doAddTouchEventHandler(std::string const& id, TouchEventHandler const& handler)
{
    // Default handler does nothing
}

void Window::doRemoveTouchEventHandler(std::string const& id)
{
    // Default handler does nothing
}

} // namespace
