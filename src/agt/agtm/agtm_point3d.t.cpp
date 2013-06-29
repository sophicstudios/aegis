#include <agtm_point3d.h>
#include <afts_comparisonutil.h>
#include <aunit.h>

using namespace aegis;

namespace aegis {
namespace agtm {

template<typename T>
class TestPoint3d : public aunit::TestFixture
{
public:
    struct TestValues
    {
        static T xOrigin;
        static T yOrigin;
        static T zOrigin;
        
        static T x;
        static T y;
        static T z;
        
        static T xNeg;
        static T yNeg;
        static T zNeg;
    };

    TestPoint3d() {}
    
    virtual ~TestPoint3d() {};
    
protected:
    virtual void runTest();
    
private:
    void assertEqual(agtm::Point3d<T> const& p, T x, T y, T z);
    void testConstruction();
    void testAssignment();
    void testMultiplication();
    void testDivision();
    void testAddition();
    void testSubtraction();
};

template<typename T> T TestPoint3d<T>::TestValues::xOrigin = static_cast<T>(0);
template<typename T> T TestPoint3d<T>::TestValues::yOrigin = static_cast<T>(0);
template<typename T> T TestPoint3d<T>::TestValues::zOrigin = static_cast<T>(0);
template<typename T> T TestPoint3d<T>::TestValues::x = static_cast<T>(1.1);
template<typename T> T TestPoint3d<T>::TestValues::y = static_cast<T>(2.2);
template<typename T> T TestPoint3d<T>::TestValues::z = static_cast<T>(3.3);
template<typename T> T TestPoint3d<T>::TestValues::xNeg = static_cast<T>(-1.1);
template<typename T> T TestPoint3d<T>::TestValues::yNeg = static_cast<T>(-2.2);
template<typename T> T TestPoint3d<T>::TestValues::zNeg = static_cast<T>(-3.3);

template<typename T>
void TestPoint3d<T>::runTest()
{
    testConstruction();
    testAssignment();
    testMultiplication();
    testDivision();
    testAddition();
    testSubtraction();
}

template<typename T>
void TestPoint3d<T>::assertEqual(agtm::Point3d<T> const& p, T x, T y, T z)
{
    AUNIT_ASSERT(afts::ComparisonUtil::equalULP(p.x(), x, 5)
        && afts::ComparisonUtil::equalULP(p.y(), y, 5)
        && afts::ComparisonUtil::equalULP(p.z(), z, 5));
}

template<typename T>
void TestPoint3d<T>::testConstruction()
{
    // Default construction
    agtm::Point3d<T> p1;
    assertEqual(p1, TestValues::xOrigin, TestValues::yOrigin, TestValues::zOrigin);
    
    // Construction with individual x, y and z components
    agtm::Point3d<T> p2(TestValues::x, TestValues::y, TestValues::z);
    assertEqual(p2, TestValues::x, TestValues::y, TestValues::z);
    
    // Construction with 3-element array
    T arr[3];
    arr[0] = TestValues::x;
    arr[1] = TestValues::y;
    arr[2] = TestValues::z;

    agtm::Point3d<T> p3(arr);
    assertEqual(p3, arr[0], arr[1], arr[2]);
}

template<typename T>
void TestPoint3d<T>::testAssignment()
{
    agtm::Point3d<T> p1(TestValues::x, TestValues::y, TestValues::z);
    agtm::Point3d<T> p2;
    
    // Basic assignment
    p2 = p1;
    assertEqual(p1, p2.x(), p2.y(), p2.z());
}

template<typename T>
void TestPoint3d<T>::testMultiplication()
{    
    // unary operator *=
    agtm::Point3d<T> p1(TestValues::x, TestValues::y, TestValues::z);
    p1 *= 2.0;
    assertEqual(p1, TestValues::x * 6 / 3, TestValues::y * 6 / 3, TestValues::z * 6 / 3);
    
    // binary operator*
    agtm::Point3d<T> p2 = p1 * 3.0;
    assertEqual(p2, TestValues::x * 6, TestValues::y * 6, TestValues::z * 6);
}

template<typename T>
void TestPoint3d<T>::testDivision()
{
    const T xInit = TestValues::x * 12;
    const T yInit = TestValues::y * 12;
    const T zInit = TestValues::z * 12;
    
    // unary operator/=
    agtm::Point3d<T> p1(xInit, yInit, zInit);
    p1 /= 3;
    assertEqual(p1, xInit / 3, yInit / 3, zInit / 3);
    
    // binary operator/
    agtm::Point3d<T> p2 = p1 / 4;
    assertEqual(p2, xInit / 12, yInit / 12, zInit / 12);
}

template<typename T>
void TestPoint3d<T>::testAddition()
{
}

template<typename T>
void TestPoint3d<T>::testSubtraction()
{
}

} // namespace
} // namespace
