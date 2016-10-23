#include <agte_surface.h>
#include <actp_scopedlock.h>
#include <iostream>

namespace agte {

Surface::Surface(RenderingContextPtr renderingContext)
: m_renderingContext(renderingContext),
  m_dirty(true);
{
}

Surface::~Surface()
{
}

bool Surface::dirty() const
{
    return m_dirty;
}

void Surface::onDraw(agtm::Rect<float> const& dirtyRect)
{
}

void Surface::onBounds(agtm::Rect<float> const& bounds)
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);
    std::cout << "new bounds: " << bounds << std::endl;
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
