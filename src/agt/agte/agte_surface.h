#ifndef INCLUDED_AGTE_SURFACE_H
#define INCLUDED_AGTE_SURFACE_H

#include <agtui_widget.h>
#include <agtg_renderingcontext.h>

namespace agte {

class Surface : public agtui::Widget
{
public:
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    Surface(RenderingContextPtr renderingContext);

    virtual ~Surface();

private:
    RenderingContextPtr m_renderingContext;
};

} // namespace

#endif // INCLUDED
