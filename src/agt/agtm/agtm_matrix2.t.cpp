#include <agtm_matrix2.h>
#include <aunit.h>

namespace aegis {
namespace agtm {

template<typename T>
class TestMatrix2 : public aunit::TestFixture
{
public:
    TestMatrix2()
    {}

    virtual ~TestMatrix2()
    {}

protected:
    virtual void runTest();
    
private:
    void testConstruction();
    void testAddition();
    void testSubtraction();
    void testMultiplication();
    void testDeterminant();
};

AUNIT_REGISTERTESTID(TestMatrix2<float>, TestMatrix2Float);
AUNIT_REGISTERTESTID(TestMatrix2<double>, TestMatrix2Double);

template<typename T>
void TestMatrix2<T>::runTest()
{
    testConstruction();
    testAddition();
    testSubtraction();
    testMultiplication();
    testDeterminant();
}

template<typename T>
void TestMatrix2<T>::testConstruction()
{
}

template<typename T>
void TestMatrix2<T>::testAddition()
{
}

template<typename T>
void TestMatrix2<T>::testSubtraction()
{
}

template<typename T>
void TestMatrix2<T>::testMultiplication()
{
}

template<typename T>
void TestMatrix2<T>::testDeterminant()
{
}

} // namespace
} // namespace
