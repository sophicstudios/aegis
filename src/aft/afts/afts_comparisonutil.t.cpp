#include <afts_comparisonutil.h>
#include <aunit.h>
#include <cstring>
#include <limits>

namespace afts {

class TestComparisonUtil : public aunit::TestFixture
{
public:
    TestComparisonUtil() {}

    virtual ~TestComparisonUtil() {}

protected:
    virtual void runTest();
    
private:
    void testFloatULP();
    void testDoubleULP();
};

AUNIT_REGISTERTEST(TestComparisonUtil);

void TestComparisonUtil::runTest()
{
    testFloatULP();
    testDoubleULP();
}

void TestComparisonUtil::testFloatULP()
{
    float f1, f2;
    
    int i = 0x00000001;
    f1 = *(reinterpret_cast<float*>(&i));
    i = 0x80000001;
    f2 = *(reinterpret_cast<float*>(&i));
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(f1, f2));
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(f1, f2, 5));
    
    f1 = 0.0f + std::numeric_limits<float>::epsilon();
    f2 = 0.0f - std::numeric_limits<float>::epsilon();
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(f1, f2));
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(f1, f2, 5));
    
    f1 = .0000000001f;
    f2 = -.0000000001f;
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(f1, f2));
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(f1, f2, 5));
}

void TestComparisonUtil::testDoubleULP()
{
    double d1, d2;
    d1 = 0.0;
    d2 = 0.0;
    *((long long*)&d2) += 1;
    
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(d1, d2));
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(d1, d2, 5));
}

} // namespace
