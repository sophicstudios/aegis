#ifndef INCLUDED_AGTE_SURFACE_H
#define INCLUDED_AGTE_SURFACE_H

#include <agtui_widget.h>
#include <agtg_renderingcontext.h>
#include <agtm_rect.h>
#include <actp_mutex.h>
#include <functional>


namespace agte {

class Surface : public agtui::Widget
{
public:
    typedef std::function<void (agtm::Rect<float> const&)> BoundsChangedCallback;
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    Surface(RenderingContextPtr renderingContext);

    virtual ~Surface();

    agtm::Rect<float> viewport();

    RenderingContextPtr renderingContext();

    void boundsChangedCallback(BoundsChangedCallback callback);

protected:
    virtual void onDraw(agtm::Rect<float> const& dirtyRect);

    virtual void onBounds(agtm::Rect<float> const& bounds);

private:
    RenderingContextPtr m_renderingContext;
    BoundsChangedCallback m_boundsChangedCallback;
};

} // namespace

#endif // INCLUDED
