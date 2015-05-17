#include <agtui_window.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace agtui {

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

class TestWindow : public aunit::TestFixture
{
public:
    TestWindow();
    
    virtual ~TestWindow();
    
protected:
    virtual void runTest();
    
private:
};

AUNIT_REGISTERTEST(TestWindow);

TestWindow::TestWindow()
{}

TestWindow::~TestWindow()
{}

void TestWindow::runTest()
{
    DummyWindow w;

    w.addResizeEventHandler("resize", resizeHandler);
    AUNIT_ASSERT(w.getResizeHandlers().size() == 1);

    w.removeResizeEventHandler("resize");
    AUNIT_ASSERT(w.getResizeHandlers().size() == 0);
}

} // namespace
