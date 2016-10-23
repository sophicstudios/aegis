#include <agte_surface.h>
#include <actp_scopedlock.h>
#include <iostream>

namespace agte {

Surface::Surface(RenderingContextPtr renderingContext)
: m_renderingContext(renderingContext)
{
}

Surface::~Surface()
{
}

void Surface::boundsChangedCallback(Surface::BoundsChangedCallback boundsChangedCallback)
{
    m_boundsChangedCallback = boundsChangedCallback;
    m_boundsChangedCallback(bounds());
}

void Surface::onDraw(agtm::Rect<float> const& dirtyRect)
{
}

void Surface::onBounds(agtm::Rect<float> const& bounds)
{
    if (m_boundsChangedCallback)
    {
        m_boundsChangedCallback(bounds);
    }
}

Surface::RenderingContextPtr Surface::renderingContext()
{
    return m_renderingContext;
}

} //namespace
