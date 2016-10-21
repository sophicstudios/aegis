#ifndef INCLUDED_AGTE_SURFACE_H
#define INCLUDED_AGTE_SURFACE_H

#include <agtui_widget.h>
#include <agtg_renderingcontext.h>
#include <agtm_rect.h>
#include <actp_mutex.h>

namespace agte {

class Surface : public agtui::Widget
{
public:
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    Surface(RenderingContextPtr renderingContext);

    virtual ~Surface();

    agtm::Rect<float> viewport();

    RenderingContextPtr renderingContext();

protected:
    virtual void onDraw(agtm::Rect<float> const& dirtyRect);

    virtual void onBounds(agtm::Rect<float> const& bounds);

private:
    actp::Mutex m_mutex;
    RenderingContextPtr m_renderingContext;
    agtm::Rect<float> m_viewport;
};

} // namespace

#endif // INCLUDED
