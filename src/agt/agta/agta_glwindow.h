#ifndef INCLUDED_AGTA_GLWINDOW_H
#define INCLUDED_AGTA_GLWINDOW_H

#include <aftt_datetime.h>
#include <agtg_renderingcontext.h>
#include <agtm_rect.h>
#include <agtui_mouseevent.h>
#include <agtui_touchevent.h>
#include <functional>
#include <memory>

namespace agta {

class DisplayTimer;

class GLWindow
{
public:
    typedef std::function<void (agtm::Rect<float> const&)> ResizeEventHandler;
    typedef std::function<void ()> KeyEventHandler;
    typedef std::function<void (agtui::MouseEvent const&)> MouseEventHandler;
    typedef std::function<void (agtui::TouchEvent const&)> TouchEventHandler;

    GLWindow();
    
    virtual ~GLWindow() = 0;

    virtual void show() = 0;
    
    virtual void hide() = 0;

    virtual DisplayTimer& displayTimer() = 0;
    
    virtual agtm::Rect<float> bounds() = 0;
    
    virtual agtg::RenderingContext& context() = 0;
    
    virtual void registerResizeEventHandler(ResizeEventHandler const& handler) = 0;
    
    virtual void registerKeyEventHandler(KeyEventHandler const& handler) = 0;
    
    virtual void registerMouseEventHandler(MouseEventHandler const& handler) = 0;
    
    virtual void registerTouchEventHandler(TouchEventHandler const& handler) = 0;
};

} // namespace

#endif // INCLUDED
