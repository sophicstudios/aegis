#ifndef INCLUDED_AGTUI_GLWINDOW_H
#define INCLUDED_AGTUI_GLWINDOW_H

#include <agtui_window.h>
#include <agtg_renderingcontext.h>
#include <memory>

namespace agtui {

class DisplayTimer;

class GLWindow : public agtui::Window
{
public:
    typedef std::shared_ptr<DisplayTimer> DisplayTimerPtr;
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    GLWindow();
    
    virtual ~GLWindow() = 0;

    virtual DisplayTimerPtr displayTimer() = 0;
    
    virtual RenderingContextPtr renderingContext() = 0;
};

} // namespace

#endif // INCLUDED
