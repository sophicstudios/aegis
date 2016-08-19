#include <agtui_window.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace {

using namespace aunit;
using namespace agtui;

class DummyWindow : public agtui::Window
{
public:
    DummyWindow()
    {}

    virtual ~DummyWindow()
    {}

    virtual void show()
    {}

    virtual void hide()
    {}

    virtual agtm::Rect<float> bounds() const
    {
        return agtm::Rect<float>::fromXYWidthHeight(0.0f, 0.0f, 1.0f, 1.0f);
    }

    agtui::Window::ResizeHandlers const& getResizeHandlers() const
    {
        return resizeHandlers();
    }
};

void resizeHandler(agtm::Rect<float> const& bounds)
{}

Describe d("agtui_window", []
{
    it("Resize Handler", [&]
    {
        DummyWindow w;

        w.addResizeEventHandler("resize", resizeHandler);

        expect(w.getResizeHandlers().size()).toEqual(1);

        w.removeResizeEventHandler("resize");

        expect(w.getResizeHandlers().size()).toEqual(0);
    });
});

} // namespace
