#ifndef INCLUDED_AGTUI_GLVIEW_H
#define INCLUDED_AGTUI_GLVIEW_H

#include <agtui_widget.h>
#include <agtg_renderingcontext.h>
#include <memory>

namespace agtui {

class GLView : public agtui::Widget
{
public:
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    GLView(RenderingContextPtr renderingContext);

    virtual ~GLView();

protected:
    RenderingContextPtr m_renderingContext;
};

} // namespace

#endif // INCLUDED
