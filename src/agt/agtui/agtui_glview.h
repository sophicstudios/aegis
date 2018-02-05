#ifndef INCLUDED_AEGIS_AGTUI_WINDOW_H
#define INCLUDED_AEGIS_AGTUI_WINDOW_H

#include <agtui_displaytimer.h>
#include <agtui_mouseevent.h>
#include <agtui_sizer.h>
#include <agtui_touchevent.h>
#include <agtui_widget.h>
#include <agtg_renderingcontext.h>
#include <agtm_rect.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace agtui {

class GLView
{
public:
    typedef std::shared_ptr<agtui::Widget> WidgetPtr;
    typedef std::shared_ptr<agtui::Sizer> SizerPtr;
    typedef std::function<void (agtm::Rect<float> const&)> ResizeEventHandler;
    typedef std::function<void ()> DrawEventHandler;
    typedef std::function<void ()> KeyEventHandler;
    typedef std::function<void (agtui::MouseEvent const&)> MouseEventHandler;
    typedef std::function<void (agtui::TouchEvent const&)> TouchEventHandler;
    typedef std::shared_ptr<agtui::DisplayTimer> DisplayTimerPtr;
    typedef std::shared_ptr<agtg::RenderingContext> RenderingContextPtr;

    GLView();
    
    virtual ~GLView() = 0;

    virtual agtm::Rect<float> bounds() const = 0;
    
    void addResizeEventHandler(std::string const& id, ResizeEventHandler const& handler);

    void removeResizeEventHandler(std::string const& id);

    void addDrawEventHandler(std::string const& id, DrawEventHandler const& handler);

    void removeDrawEventHandler(std::string const& id);

    void addKeyEventHandler(std::string const& id, KeyEventHandler const& handler);

    void removeKeyEventHandler(std::string const& id);

    void addMouseEventHandler(std::string const& id, MouseEventHandler const& handler);

    void removeMouseEventHandler(std::string const& id);

    void addTouchEventHandler(std::string const& id, TouchEventHandler const& handler);

    void removeTouchEventHandler(std::string const& id);

    void addChild(WidgetPtr widget);

    void setSizer(SizerPtr sizer);

    virtual DisplayTimerPtr displayTimer() const = 0;
    
    virtual RenderingContextPtr renderingContext() const = 0;

protected:
    typedef std::vector<std::pair<std::string, ResizeEventHandler> > ResizeHandlers;
    typedef std::vector<std::pair<std::string, DrawEventHandler> > DrawHandlers;
    typedef std::vector<std::pair<std::string, KeyEventHandler> > KeyHandlers;
    typedef std::vector<std::pair<std::string, MouseEventHandler> > MouseHandlers;
    typedef std::vector<std::pair<std::string, TouchEventHandler> > TouchHandlers;

    void onResize(agtm::Rect<float> const& bounds);

    void onDraw(agtm::Rect<float> const& dirtyRect);

    ResizeHandlers const& resizeHandlers() const;

    DrawHandlers const& drawHandlers() const;

    KeyHandlers const& keyHandlers() const;

    MouseHandlers const& mouseHandlers() const;

    TouchHandlers const& touchHandlers() const;

    virtual void doAddResizeEventHandler(std::string const& id, ResizeEventHandler const& handler);

    virtual void doRemoveResizeEventHandler(std::string const& id);

    virtual void doAddDrawEventHandler(std::string const& id, DrawEventHandler const& handler);

    virtual void doRemoveDrawEventHandler(std::string const& id);

    virtual void doAddKeyEventHandler(std::string const& id, KeyEventHandler const& handler);

    virtual void doRemoveKeyEventHandler(std::string const& id);

    virtual void doAddMouseEventHandler(std::string const& id, MouseEventHandler const& handler);

    virtual void doRemoveMouseEventHandler(std::string const& id);

    virtual void doAddTouchEventHandler(std::string const& id, TouchEventHandler const& handler);

    virtual void doRemoveTouchEventHandler(std::string const& id);

private:
    typedef std::vector<WidgetPtr> Children;

    ResizeHandlers m_resizeHandlers;
    DrawHandlers m_drawHandlers;
    KeyHandlers m_keyHandlers;
    MouseHandlers m_mouseHandlers;
    TouchHandlers m_touchHandlers;
    RenderingContextPtr m_renderingContext;
    DisplayTimerPtr m_displayTimer;
    SizerPtr m_sizer;
    Children m_children;
};

} // namespace

#endif // INCLUDED
