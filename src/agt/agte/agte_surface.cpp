#include <agte_surface.h>
#include <actp_scopedlock.h>

namespace agte {

Surface::Surface(RenderingContextPtr renderingContext)
: m_renderingContext(renderingContext)
{
}

Surface::~Surface()
{
}

void Surface::onDraw(agtm::Rect<float> const& dirtyRect)
{
}

void Surface::onBounds(agtm::Rect<float> const& bounds)
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);
    m_viewport = bounds;
}

agtm::Rect<float> Surface::viewport()
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);
    return agtm::Rect<float>(m_viewport);
}

Surface::RenderingContextPtr Surface::renderingContext()
{
    return m_renderingContext;
}

} //namespace
