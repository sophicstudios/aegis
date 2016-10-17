#include <agtui_glview.h>

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

GLView::GLView()
{}

GLView::~GLView()
{}

void GLView::addResizeEventHandler(std::string const& id, ResizeEventHandler const& handler)
{
    m_resizeHandlers.push_back(std::make_pair(id, handler));

    doAddResizeEventHandler(id, handler);
}

void GLView::removeResizeEventHandler(std::string const& id)
{
    removeHandler(id, m_resizeHandlers);

    doRemoveResizeEventHandler(id);
}

void GLView::addDrawEventHandler(std::string const& id, DrawEventHandler const& handler)
{
    m_drawHandlers.push_back(std::make_pair(id, handler));

    doAddDrawEventHandler(id, handler);
}

void GLView::removeDrawEventHandler(std::string const& id)
{
    removeHandler(id, m_drawHandlers);

    doRemoveDrawEventHandler(id);
}

void GLView::addKeyEventHandler(std::string const& id, KeyEventHandler const& handler)
{
    m_keyHandlers.push_back(std::make_pair(id, handler));

    doAddKeyEventHandler(id, handler);
}

void GLView::removeKeyEventHandler(std::string const& id)
{
    removeHandler(id, m_keyHandlers);

    doRemoveKeyEventHandler(id);
}

void GLView::addMouseEventHandler(std::string const& id, MouseEventHandler const& handler)
{
    m_mouseHandlers.push_back(std::make_pair(id, handler));

    doAddMouseEventHandler(id, handler);
}

void GLView::removeMouseEventHandler(std::string const& id)
{
    removeHandler(id, m_mouseHandlers);

    doRemoveMouseEventHandler(id);
}

void GLView::addTouchEventHandler(std::string const& id, TouchEventHandler const& handler)
{
    m_touchHandlers.push_back(std::make_pair(id, handler));

    doAddTouchEventHandler(id, handler);
}

void GLView::removeTouchEventHandler(std::string const& id)
{
    removeHandler(id, m_touchHandlers);

    doRemoveTouchEventHandler(id);
}

void GLView::addChild(GLView::WidgetPtr widget)
{
    m_children.push_back(widget);
}

void GLView::setSizer(GLView::SizerPtr sizer)
{
    m_sizer = sizer;
}

void GLView::onResize(agtm::Rect<float> const& bounds)
{
    // calculate the client size?
    // update the size of the sizer
    if (m_sizer)
    {
        m_sizer->size(bounds.size());
    }

    // TOOD: verify the size meets the sizer's constraints
    // and reset the GLView size to the constraint
}

GLView::ResizeHandlers const& GLView::resizeHandlers() const
{
    return m_resizeHandlers;
}

GLView::DrawHandlers const& GLView::drawHandlers() const
{
    return m_drawHandlers;
}

GLView::KeyHandlers const& GLView::keyHandlers() const
{
    return m_keyHandlers;
}

GLView::MouseHandlers const& GLView::mouseHandlers() const
{
    return m_mouseHandlers;
}

GLView::TouchHandlers const& GLView::touchHandlers() const
{
    return m_touchHandlers;
}

void GLView::doAddResizeEventHandler(std::string const& id, ResizeEventHandler const& handler)
{
    // Default handler does nothing
}

void GLView::doRemoveResizeEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void GLView::doAddDrawEventHandler(std::string const& id, DrawEventHandler const& handler)
{
    // Default handler does nothing
}

void GLView::doRemoveDrawEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void GLView::doAddKeyEventHandler(std::string const& id, KeyEventHandler const& handler)
{
    // Default handler does nothing
}

void GLView::doRemoveKeyEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void GLView::doAddMouseEventHandler(std::string const& id, MouseEventHandler const& handler)
{
    // Default handler does nothing
}

void GLView::doRemoveMouseEventHandler(std::string const& id)
{
    // Default handler does nothing
}

void GLView::doAddTouchEventHandler(std::string const& id, TouchEventHandler const& handler)
{
    // Default handler does nothing
}

void GLView::doRemoveTouchEventHandler(std::string const& id)
{
    // Default handler does nothing
}

} // namespace
