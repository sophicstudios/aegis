#include <agtui_widget.h>
#include <limits>

namespace agtui {

Widget::Widget()
: m_id(afth::UUID::v4())
{}

Widget::Widget(afth::UUID const& id)
: m_id(id)
{}

Widget::~Widget()
{}

afth::UUID const& Widget::id() const
{
    return m_id;
}

bool Widget::enabled() const
{
    return m_enabled;
}

void Widget::enabled(bool enabled)
{
    m_enabled = enabled;
}

bool Widget::visible() const
{
    return m_visible;
}

void Widget::visible(bool visible)
{
    m_visible = visible;
}

agtm::Rect<float> const& Widget::bounds() const
{
    return m_bounds;
}
    
void Widget::bounds(agtm::Rect<float> const& bounds)
{
    m_bounds = bounds;
}

agtm::Size2d<float> Widget::size() const
{
    return m_bounds.size();
}

void Widget::size(agtm::Size2d<float> const& size)
{
    m_bounds.size(size);
}

agtm::Point2d<float> Widget::position() const
{
    return m_bounds.origin();
}

void Widget::position(agtm::Point2d<float> const& position)
{
    m_bounds.origin(position);
}

agtm::Size2d<float> Widget::minSize() const
{
    return doMinSize();
}

agtm::Size2d<float> Widget::maxSize() const
{
    return doMaxSize();
}

agtm::Size2d<float> Widget::bestSize() const
{
    return doBestSize();
}

agtm::Size2d<float> Widget::doMinSize() const
{
    return agtm::Size2d<float>(0.0f, 0.0f);
}

agtm::Size2d<float> Widget::doMaxSize() const
{
    return agtm::Size2d<float>(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
}

agtm::Size2d<float> Widget::doPreferredSize() const
{
    return agtm::Size2d<float>(20.f, 20.0f);
}

} // namespace
