#ifndef INCLUDED_AGTUI_WIDGET_H
#define INCLUDED_AGTUI_WIDGET_H

#include <agtm_rect.h>
#include <agtm_point2d.h>
#include <agtm_size2d.h>
#include <afth_uuid.h>

namespace agtui {

class Widget
{
public:
    static const agtm::Point2d<float> DEFAULT_POSITION;
    static const agtm::Point2d<float> DEFAULT_SIZE;

    Widget(agtm::Rect<float> const& bounds)

    virtual ~Widget() = 0;

    afth::UUID const& id() const;

    bool enabled() const;

    void enabled(bool enabled);

    bool visible() const;

    void visible(bool visible);

    agtm::Rect<float> const& bounds() const;
    
    void bounds(agtm::Rect<float> const& bounds);

    agtm::Size2d<float> size() const;

    void size(agtm::Size2d<float> const& size);

    agtm::Point2d<float> position() const;

    void position(agtm::Point2d<float> const& position);
    
    agtm::Size2d<float> minSize() const;

    agtm::Size2d<float> maxSize() const;

    agtm::Size2d<float> bestSize() const;

    agtm::Size2d<float> actualMinSize() const;

private:
    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    virtual agtm::Size2d<float> doBestSize() const;

    afth::UUID m_id;
    bool m_enabled;
    bool m_visible;
    agtm::Rect<float> m_bounds;
};

} // namespace

#endif // INCLUDED
