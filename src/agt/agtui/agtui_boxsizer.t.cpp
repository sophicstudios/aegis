#include <agtui_boxsizer.h>
#include <agtui_widget.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace agtui {

class A : public agtui::Widget
{
public:
    A();

    virtual ~A();

private:
    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    virtual agtm::Size2d<float> doPreferredSize() const;
};

class B : public agtui::Widget
{
public:
    B() {}

    virtual ~B() {}

private:
    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    virtual agtm::Size2d<float> doPreferredSize() const;
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
    agtui::BoxSizer sizer;

}

} // namespace
