#ifndef INCLUDED_AEGIS_AGTUI_WIDGET_H
#define INCLUDED_AEGIS_AGTUI_WIDGET_H

#include <agtm_rect.h>
#include <agtm_vector2.h>
#include <agtm_size2d.h>
#include <afth_uuid.h>

namespace agtui {

class Widget
{
public:
    static const agtm::Vector2<float> DEFAULT_POSITION;
    static const agtm::Size2d<float> DEFAULT_SIZE;

    Widget();
    
    Widget(agtm::Rect<float> const& bounds);

    virtual ~Widget() = 0;

    afth::UUID const& id() const;

    void draw(agtm::Rect<float> const& dirtyRect);

    bool enabled() const;

    void enabled(bool enabled);

    bool visible() const;

    void visible(bool visible);

    agtm::Rect<float> const& bounds() const;
    
    void bounds(agtm::Rect<float> const& bounds);

    agtm::Size2d<float> size() const;

    void size(agtm::Size2d<float> const& size);

    agtm::Vector2<float> position() const;

    void position(agtm::Vector2<float> const& position);
    
    agtm::Size2d<float> minSize() const;

    agtm::Size2d<float> maxSize() const;

    agtm::Size2d<float> bestSize() const;

    agtm::Size2d<float> actualMinSize() const;

private:
    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    virtual agtm::Size2d<float> doBestSize() const;

    virtual void onDraw(agtm::Rect<float> const& dirtyRect);

    virtual void onBounds(agtm::Rect<float> const& bounds);

    afth::UUID m_id;
    bool m_enabled;
    bool m_visible;
    agtm::Rect<float> m_bounds;
};

} // namespace

#endif // INCLUDED
