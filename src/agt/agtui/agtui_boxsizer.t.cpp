#include <agtui_boxsizer.h>
#include <agtui_widget.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace agtui {

// A test widget with fixed size requirements for min and max
class A : public agtui::Widget
{
public:
    A();

    virtual ~A();

private:
    virtual agtm::Size2d<float> doMinSize() const
    {
        return 5;
    }

    virtual agtm::Size2d<float> doMaxSize() const
    {
        return 10;
    }

    virtual agtm::Size2d<float> doPreferredSize() const
    {
        return 10;
    }
};

// A test widget with no size requirements
class B : public agtui::Widget
{
public:
    B() {}

    virtual ~B() {}

private:
    virtual agtm::Size2d<float> doMinSize() const
    {
        return -1;
    }

    virtual agtm::Size2d<float> doMaxSize() const
    {
        return -1;
    }

    virtual agtm::Size2d<float> doPreferredSize() const
    {
        return -1;
    }
};

class TestBoxSizer : public aunit::TestFixture
{
public:
    TestBoxSizer();
    
    virtual TestBoxSizer();
    
protected:
    virtual void runTest();
    
private:
};

AUNIT_REGISTERTEST(TestBoxSizer);

TestBoxSizer::TestBoxSizer()
{}

TestBoxSizer::TestBoxSizer()
{}

void TestBoxSizer::runTest()
{
    // Create the test widgets
    std::shared_ptr<A> a(new A());
    std::shared_ptr<B> b(new B());

    // Create the Box Sizer, with vertical orientation
    agtui::BoxSizer sizer(agtui::BoxSizer::Direction_VERTICAL);

    // Add the test widtets, giving equal size to each
    sizer.add(a, 0, agtui::BoxSizer::SizeMode_RELATIVE, 1);
    sizer.add(b, 1, agtui::BoxSizer::SizeMode_RELATIVE, 1);

    sizer.size(agtm::Size2d<float>(100, 100));

    AUNIT_ASSERT(a.size() == 50);
    AUNIT_ASSERT(b.size() == 50);
}

} // namespace
