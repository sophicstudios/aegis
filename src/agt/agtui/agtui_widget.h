#ifndef INCLUDED_AGTUI_WIDGET_H
#define INCLUDED_AGTUI_WIDGET_H

#include <agtm_rect.h>
#include <agtm_point2d.h>
#include <agtm_size2d.h>

namespace agtui {

class Widget
{
public:
    Widget();
    
    Widget(int id);
    
    Widget(agtm::Rect<int> const& bounds);
    
    Widget(int id, agtm::Rect<int> const& bounds);
    
    virtual ~Widget() = 0;
    
    int id();
    
    void enable();
    
    void disable();
    
    bool isEnabled() const;
    
    agtm::Rect<int> const& bounds() const;
    
    void bounds(agtm::Rect<int> const& bounds);

    void position(agtm::Point2d<int> const& position);
    
    agtm::Point2d<int> position() const;

    int x() const;
    
    void x(int x);
    
    int y() const;
    
    void y(int y);
    
    agtm::Size2d<int> size() const;

    void size(agtm::Size2d<int> const& size);
    
    int width() const;
    
    void width(int width);
    
    int height() const;
    
    void height(int height);
    
private:
    int m_id;
    bool m_enabled;
    agtm::Rect<int> m_bounds;
};

} // namespace

#endif // INCLUDED
