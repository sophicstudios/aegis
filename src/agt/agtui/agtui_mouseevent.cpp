#include <agtui_mouseevent.h>
#include <ostream>
namespace agtui {

namespace {
    const char* typeToString(MouseEvent::Type type)
    {
        switch (type) {
        case MouseEvent::Type_MOUSEDOWN: return "MOUSEDOWN";
        case MouseEvent::Type_MOUSEUP: return "MOUSEUP";
        case MouseEvent::Type_MOUSEMOVE: return "MOUSEMOVE";
        case MouseEvent::Type_MOUSEDRAG: return "MOUSEDRAG";
        case MouseEvent::Type_MOUSEENTER: return "MOUSEENTER";
        case MouseEvent::Type_MOUSELEAVE: return "MOUSELEAVE";
        case MouseEvent::Type_MOUSEDOUBLECLICK: return "MOUSEDOUBLECLICK";
        default: return "UNKNOWN";
        }
    }
    
    const char* buttonToString(MouseEvent::Button button)
    {
        switch (button) {
        case MouseEvent::Button_NONE: return "Button_NONE";
        case MouseEvent::Button_1: return "Button_1";
        case MouseEvent::Button_2: return "Button_2";
        case MouseEvent::Button_3: return "Button_3";
        case MouseEvent::Button_4: return "Button_4";
        case MouseEvent::Button_5: return "Button_5";
        case MouseEvent::Button_6: return "Button_6";
        case MouseEvent::Button_7: return "Button_7";
        case MouseEvent::Button_8: return "Button_8";
        case MouseEvent::Button_9: return "Button_9";
        default: return "UNKNOWN";
        }
    }
}

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

std::ostream& operator<<(std::ostream& os, MouseEvent const& event)
{
    os << "["
        << " location: " << event.m_location
        << " type: " << typeToString(event.m_type)
        << " button: " << buttonToString(event.m_button)
        << " ]";
    
    return os;
}

} // namespace
