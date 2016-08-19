#ifndef INCLUDED_AGTUI_GLWINDOW_H
#define INCLUDED_AGTUI_GLWINDOW_H

#include <agtui_window.h>
#include <agtui_displaytimer.h>
#include <agtg_renderingcontext.h>
#include <memory>

namespace agtui {

class GLWindow : public agtui::Window
{
public:
    typedef std::shared_ptr<agtui::DisplayTimer> DisplayTimerPtr;
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    GLWindow(RenderingContextPtr renderingContext, DisplayTimerPtr displayTimer);
    
    virtual ~GLWindow() = 0;

    DisplayTimerPtr displayTimer() const;
    
    RenderingContextPtr renderingContext() const;

protected:
    RenderingContextPtr m_renderingContext;
    DisplayTimerPtr m_displayTimer;
};

} // namespace

#endif // INCLUDED
