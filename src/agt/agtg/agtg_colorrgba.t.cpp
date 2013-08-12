#include <agtg_colorrgba.h>
#include <aunit.h>

namespace agtg {

class TestColorRGBA : public aunit::TestFixture
{
public:
    TestColorRGBA() {}

    virtual ~TestColorRGBA() {}

protected:
    virtual void runTest();
    
private:
    void testConstruction();
};

AUNIT_REGISTERTEST(TestColorRGBA);

void TestColorRGBA::runTest()
{
    testConstruction();
}

void TestColorRGBA::testConstruction()
{
    agtg::ColorRGBA<double> white(0xffffffff);
    AUNIT_ASSERT(white.red() == 1.0);
    AUNIT_ASSERT(white.green() == 1.0);
    AUNIT_ASSERT(white.blue() == 1.0);
    AUNIT_ASSERT(white.alpha() == 1.0);

    agtg::ColorRGBA<double> red(255, 0, 0);
    AUNIT_ASSERT(red.red() == 1.0);
    AUNIT_ASSERT(red.green() == 0.0);
    AUNIT_ASSERT(red.blue() == 0.0);
    AUNIT_ASSERT(red.alpha() == 1.0);

    agtg::ColorRGBA<double> darkGreenHalfAlpha(0, .5, 0, 0.5);
    AUNIT_ASSERT(darkGreenHalfAlpha.red() == 0.0);
    AUNIT_ASSERT(darkGreenHalfAlpha.green() == 0.5);
    AUNIT_ASSERT(darkGreenHalfAlpha.blue() == 0.0);
    AUNIT_ASSERT(darkGreenHalfAlpha.alpha() == 0.5);
}

} // namespace
