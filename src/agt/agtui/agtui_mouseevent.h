#ifndef INCLUDED_AEGIS_AGTUI_MOUSEEVENT_H
#define INCLUDED_AEGIS_AGTUI_MOUSEEVENT_H

#include <agtm_point2d.h>
#include <iosfwd>

namespace agtui {

class MouseEvent
{
    friend std::ostream& operator<<(std::ostream&, MouseEvent const&);
    
public:
    enum Button {
        Button_NONE = 0,
        Button_LEFT = 1,
        Button_1 = 1,
        Button_RIGHT = 2,
        Button_2 = 2,
        Button_MIDDLE,
        Button_3 = 3,
        Button_4 = 4,
        Button_5 = 5,
        Button_6 = 6,
        Button_7 = 7,
        Button_8 = 8,
        Button_9 = 9
    };
    
    enum Type {
        Type_MOUSEDOWN,
        Type_MOUSEUP,
        Type_MOUSEDRAG,
        Type_MOUSEMOVE,
        Type_MOUSEENTER,
        Type_MOUSELEAVE,
        Type_MOUSEDOUBLECLICK
    };
        
    MouseEvent(Type type, Button button, agtm::Point2d<float> const& location);
    
    ~MouseEvent();

    Type type() const;
    
    Button button() const;
    
    agtm::Point2d<float> const& location() const;
    
private:
    Type m_type;
    Button m_button;
    agtm::Point2d<float> m_location;
};

std::ostream& operator<<(std::ostream& os, MouseEvent const& event);

} // namespace

#endif // INCLUDED
