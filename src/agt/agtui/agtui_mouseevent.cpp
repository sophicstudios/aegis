#include <agtui_mouseevent.h>

namespace agtui {

MouseEvent::MouseEvent(Type type, Button button, agtm::Point2d<float> const& location)
: m_type(type),
  m_button(button),
  m_location(location)
{}

MouseEvent::~MouseEvent()
{}

MouseEvent::Type MouseEvent::type() const
{
    return m_type;
}

MouseEvent::Button MouseEvent::button() const
{
    return m_button;
}

agtm::Point2d<float> const& MouseEvent::location() const
{
    return m_location;
}

} // namespace
