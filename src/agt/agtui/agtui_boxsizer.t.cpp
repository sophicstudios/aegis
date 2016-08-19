#include <agtui_boxsizer.h>
#include <agtui_widget.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace {

using namespace aunit;
using namespace agtui;

// A test widget with fixed size requirements for min and max
class A : public agtui::Widget
{
public:
    A() {};

    virtual ~A() {};

private:
    virtual agtm::Size2d<float> doMinSize() const
    {
        return agtm::Size2d<float>(5, 5);
    }

    virtual agtm::Size2d<float> doMaxSize() const
    {
        return agtm::Size2d<float>(10, 10);
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
        return agtm::Size2d<float>(-1, -1);
    }

    virtual agtm::Size2d<float> doMaxSize() const
    {
        return agtm::Size2d<float>(-1, -1);
    }
};

Describe d("agtui_boxsizer", []
{
    it("size", [&]
    {
        // Create the test widgets
        std::shared_ptr<A> a(new A());
        std::shared_ptr<B> b(new B());

        // Create the Box Sizer, with vertical orientation
        agtui::BoxSizer sizer(agtui::BoxSizer::Direction_VERTICAL);

        // Add the test widtets, giving equal size to each
        sizer.insert(a, 0, BoxSizer::Flags().sizeMode(BoxSizer::SizeMode_RELATIVE).size(1));
        sizer.insert(b, 1, BoxSizer::Flags().sizeMode(BoxSizer::SizeMode_RELATIVE).size(1));

        sizer.size(agtm::Size2d<float>(100, 100));

        expect(a->size()).toEqual(agtm::Size2d<float>(10, 50));
        expect(b->size()).toEqual(agtm::Size2d<float>(100, 50));
    });
});

} // namespace
