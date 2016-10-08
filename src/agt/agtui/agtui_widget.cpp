#include <agtui_widget.h>
#include <agtm_size2d.h>
#include <limits>

namespace agtui {

namespace {

void grow(agtm::Size2d<float>& best, agtm::Size2d<float> const& min)
{
    if (min.width() > best.width())
    {
        best.width(min.width());
    }

    if (min.height() > best.height())
    {
        best.height(min.height());
    }
}

void shrink(agtm::Size2d<float>& best, agtm::Size2d<float> const& max)
{
    if (max.width() != Widget::DEFAULT_SIZE.width() && max.width() < best.width())
    {
        best.width(max.width());
    }

    if (max.height() != Widget::DEFAULT_SIZE.height() && max.height() < best.height())
    {
        best.height(max.height());
    }
}

} // namespace

const agtm::Point2d<float> Widget::DEFAULT_POSITION = agtm::Point2d<float>(0.0f, 0.0f);
const agtm::Size2d<float> Widget::DEFAULT_SIZE = agtm::Size2d<float>(-1.0f, -1.0f);

Widget::Widget()
: m_id(afth::UUID::v4()),
  m_bounds(Widget::DEFAULT_POSITION, Widget::DEFAULT_SIZE)
{
}

Widget::Widget(agtm::Rect<float> const& bounds)
: m_id(afth::UUID::v4()),
  m_bounds(bounds)
{
}

Widget::~Widget()
{
}

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
    agtm::Size2d<float> best = doBestSize();

    grow(best, minSize());
    shrink(best, maxSize());

    return best;
}

agtm::Size2d<float> Widget::actualMinSize() const
{
    agtm::Size2d<float> min = minSize();
    if (min.width() == Widget::DEFAULT_SIZE.width() || min.height() == Widget::DEFAULT_SIZE.height())
    {
        agtm::Size2d<float> best = bestSize();
        if (min.width() == Widget::DEFAULT_SIZE.width())
        {
            min.width(best.width());
        }

        if (min.height() == Widget::DEFAULT_SIZE.height())
        {
            min.height(best.height());
        }
    }

    return min;
}

agtm::Size2d<float> Widget::doMinSize() const
{
    return Widget::DEFAULT_SIZE;
}

agtm::Size2d<float> Widget::doMaxSize() const
{
    return Widget::DEFAULT_SIZE;
}

agtm::Size2d<float> Widget::doBestSize() const
{
    return doMinSize();
}

} // namespace
