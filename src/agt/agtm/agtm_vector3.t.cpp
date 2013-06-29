#include <agtm_vector3.h>
#include <aunit.h>

namespace aegis {
namespace agtm {

template<typename T>
class TestVector3 : public aunit::TestFixture
{
public:
    TestVector3()
    {}

    virtual ~TestVector3()
    {}

protected:
    virtual void runTest();
    
private:
    void testConstruction();
    void testAddition();
    void testSubtraction();
    void testMultiplication();
    void testDivision();
    void testLength();
};

AUNIT_REGISTERTESTID(TestVector3<float>, TestVector3Float);
AUNIT_REGISTERTESTID(TestVector3<double>, TestVector3Double);

namespace {

template<typename T, typename U>
bool verify(Vector3<T> const& v, U x, U y, U z)
{
    return v.x() == static_cast<T>(x)
        && v.y() == static_cast<T>(y)
        && v.z() == static_cast<T>(z);
}

} // namespace

template<typename T>
void TestVector3<T>::runTest()
{
    testConstruction();
    testAddition();
    testSubtraction();
    testMultiplication();
    testDivision();
    testLength();
}

template<typename T>
void TestVector3<T>::testConstruction()
{
    Vector3<T> v1;
    AUNIT_ASSERT(verify(v1, 0, 0, 0));
    
    Vector3<T> v2(1, 2, 3);
    AUNIT_ASSERT(verify(v2, 1, 2, 3));
    
    Vector3<T> v3(v2);
    AUNIT_ASSERT(verify(v3, 1, 2, 3));
    AUNIT_ASSERT(v3 == v2);
    
    v3.assign(3, 4, 5);
    AUNIT_ASSERT(verify(v3, 3, 4, 5));
    
    v3 = -v3;
    AUNIT_ASSERT(verify(v3, -3, -4, -5));
}

template<typename T>
void TestVector3<T>::testAddition()
{
    Vector3<T> v1(1, 2, 3);
    Vector3<T> v2(3, 4, 5);
    
    v1 += v2;
    AUNIT_ASSERT(verify(v1, 4, 6, 8));
    
    Vector3<T> v3;
    v3 = v1 + v2;
    AUNIT_ASSERT(verify(v3, 7, 10, 13));
    
    v3 += 1;
    AUNIT_ASSERT(verify(v3, 8, 11, 14));
    
    Vector3<T> v4;
    v4 = v3 + 2;
    AUNIT_ASSERT(verify(v4, 10, 13, 16));
}

template<typename T>
void TestVector3<T>::testSubtraction()
{
    Vector3<T> v1(8, 9, 10);
    Vector3<T> v2(1, 2, 3);
    
    v1 -= v2;
    AUNIT_ASSERT(verify(v1, 7, 7, 7));
    
    Vector3<T> v3;
    v3 = v1 - v2;
    AUNIT_ASSERT(verify(v3, 6, 5, 4));
    
    v3 -= 1;
    AUNIT_ASSERT(verify(v3, 5, 4, 3));
    
    Vector3<T> v4;
    v4 = v3 - 2;
    AUNIT_ASSERT(verify(v4, 3, 2, 1));
}

template<typename T>
void TestVector3<T>::testMultiplication()
{
    Vector3<T> v1(1, 2, 3);
    Vector3<T> v2(2, 3, 4);
    
    v1 *= v2;
    AUNIT_ASSERT(verify(v1, 2, 6, 12));
    
    Vector3<T> v3;
    v3 = v1 * v2;
    AUNIT_ASSERT(verify(v3, 4, 18, 48));
    
    v3 *= 2;
    AUNIT_ASSERT(verify(v3, 8, 36, 96));
    
    Vector3<T> v4;
    v4 = v3 * 2;
    AUNIT_ASSERT(verify(v4, 16, 72, 192));
}

template<typename T>
void TestVector3<T>::testDivision()
{
    Vector3<T> v1(16, 72, 192);
    Vector3<T> v2(2, 3, 4);
    
    v1 /= v2;
    AUNIT_ASSERT(verify(v1, 8, 24, 48));
    
    Vector3<T> v3;
    v3 = v1 / v2;
    AUNIT_ASSERT(verify(v3, 4, 8, 12));
    
    v3 /= 2;
    AUNIT_ASSERT(verify(v3, 2, 4, 6));
    
    Vector3<T> v4;
    v4 = v3 / 2;
    AUNIT_ASSERT(verify(v4, 1, 2, 3));
}

template<typename T>
void TestVector3<T>::testLength()
{
    Vector3<T> v1(2, 3, 6);
    AUNIT_ASSERT(v1.length() == 7);
    AUNIT_ASSERT(v1.lengthSquared() == 49);
}

} // namespace
} // namespace
