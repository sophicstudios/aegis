#include <aftt_datetimeinterval.h>
#include <aunit.h>

namespace aftt {

class TestDatetimeInterval : public aunit::TestFixture
{
public:
    TestDatetimeInterval() {}
    virtual ~TestDatetimeInterval() {}
    
protected:
    virtual void runTest();

private:
    void testConstruction();
    void testAssignment();
    void testAddition();
    void testSubtraction();
};

AUNIT_REGISTERTEST(TestDatetimeInterval);

void TestDatetimeInterval::runTest()
{
    testConstruction();
    testAssignment();
    testAddition();
    testSubtraction();
}

void TestDatetimeInterval::testConstruction()
{
}

void TestDatetimeInterval::testAssignment()
{
}

void TestDatetimeInterval::testAddition()
{
}

void TestDatetimeInterval::testSubtraction()
{
}

} // namespace

