#include <agtui_widget.h>

namespace agtui {

Widget::Widget()
: m_id(0),
  m_bounds(agtm::make_point(0, 0), agtm::make_size(0, 0))
{}

Widget::Widget(int id)
: m_id(id),
  m_bounds(agtm::make_point(0, 0), agtm::make_size(0, 0))
{}

Widget::Widget(agtm::Rect<int> const& bounds)
: m_id(0),
  m_bounds(bounds)
{}

Widget::Widget(int id, agtm::Rect<int> const& bounds)
: m_id(id),
  m_bounds(bounds)
{}

Widget::~Widget()
{}

int Widget::id()
{
    return m_id;
}

void Widget::enable()
{
    m_enabled = true;
}

void Widget::disable()
{
    m_enabled = false;
}

bool Widget::isEnabled() const
{
    return m_enabled;
}

void Widget::position(agtm::Point2d<int> const& position)
{
    m_bounds.origin(position);
}

agtm::Point2d<int> Widget::position() const
{
    return m_bounds.origin();
}

int Widget::x() const
{
    return m_bounds.origin().x();
}
    
void Widget::x(int x)
{
    m_bounds.origin(agtm::make_point(x, m_bounds.origin().y()));
}
    
int Widget::y() const
{
    return m_bounds.origin().y();
}
    
void Widget::y(int y)
{
    m_bounds.origin(agtm::make_point(m_bounds.origin().x(), y));
}

agtm::Size2d<int> Widget::size() const
{
    return m_bounds.size();
}

void Widget::size(agtm::Size2d<int> const& size)
{
    m_bounds.size(size);
}

int Widget::width() const
{
    return m_bounds.size().width();
}
    
void Widget::width(int width)
{
    m_bounds.size(agtm::make_size(width, m_bounds.size().height()));
}
    
int Widget::height() const
{
    return m_bounds.size().height();
}
    
void Widget::height(int height)
{
    m_bounds.size(agtm::make_size(m_bounds.size().width(), height));
}
    
agtm::Rect<int> const& Widget::bounds() const
{
    return m_bounds;
}
    
void Widget::bounds(agtm::Rect<int> const& bounds)
{
    m_bounds = bounds;
}

} // namespace
