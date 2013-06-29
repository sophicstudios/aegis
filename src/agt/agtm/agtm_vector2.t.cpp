#include <agtm_vector2.h>
#include <aunit.h>

namespace aegis {
namespace agtm {

template<typename T>
class TestVector2 : public aunit::TestFixture
{
public:
    TestVector2()
    {}

    virtual ~TestVector2()
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

AUNIT_REGISTERTESTID(TestVector2<float>, TestVector2Float);
AUNIT_REGISTERTESTID(TestVector2<double>, TestVector2Double);

namespace {

template<typename T, typename U>
bool verify(Vector2<T> const& v, U x, U y)
{
    return v.x() == static_cast<T>(x) && v.y() == static_cast<T>(y);
}

} // namespace

template<typename T>
void TestVector2<T>::runTest()
{
    testConstruction();
    testAddition();
    testSubtraction();
    testMultiplication();
    testDivision();
    testLength();
}

template<typename T>
void TestVector2<T>::testConstruction()
{
    Vector2<T> v1;
    AUNIT_ASSERT(verify(v1, 0, 0));
    
    Vector2<T> v2(1, 2);
    AUNIT_ASSERT(verify(v2, 1, 2));
    
    Vector2<T> v3(v2);
    AUNIT_ASSERT(verify(v3, 1, 2));
    AUNIT_ASSERT(v3 == v2);
    
    v3.assign(3, 4);
    AUNIT_ASSERT(verify(v3, 3, 4));
    
    v3 = -v3;
    AUNIT_ASSERT(verify(v3, -3, -4));
}

template<typename T>
void TestVector2<T>::testAddition()
{
    Vector2<T> v1(1, 2);
    Vector2<T> v2(3, 4);
    
    v1 += v2;
    AUNIT_ASSERT(verify(v1, 4, 6));
    
    Vector2<T> v3;
    v3 = v1 + v2;
    AUNIT_ASSERT(verify(v3, 7, 10));
    
    v3 += 1;
    AUNIT_ASSERT(verify(v3, 8, 11));
    
    Vector2<T> v4;
    v4 = v3 + 2;
    AUNIT_ASSERT(verify(v4, 10, 13));
}

template<typename T>
void TestVector2<T>::testSubtraction()
{
    Vector2<T> v1(8, 9);
    Vector2<T> v2(1, 2);
    
    v1 -= v2;
    AUNIT_ASSERT(verify(v1, 7, 7));
    
    Vector2<T> v3;
    v3 = v1 - v2;
    AUNIT_ASSERT(verify(v3, 6, 5));
    
    v3 -= 1;
    AUNIT_ASSERT(verify(v3, 5, 4));
    
    Vector2<T> v4;
    v4 = v3 - 2;
    AUNIT_ASSERT(verify(v4, 3, 2));
}

template<typename T>
void TestVector2<T>::testMultiplication()
{
    Vector2<T> v1(1, 2);
    Vector2<T> v2(2, 3);
    
    v1 *= v2;
    AUNIT_ASSERT(verify(v1, 2, 6));
    
    Vector2<T> v3;
    v3 = v1 * v2;
    AUNIT_ASSERT(verify(v3, 4, 18));
    
    v3 *= 2;
    AUNIT_ASSERT(verify(v3, 8, 36));
    
    Vector2<T> v4;
    v4 = v3 * 2;
    AUNIT_ASSERT(verify(v4, 16, 72));
}

template<typename T>
void TestVector2<T>::testDivision()
{
    Vector2<T> v1(16, 72);
    Vector2<T> v2(2, 3);
    
    v1 /= v2;
    AUNIT_ASSERT(verify(v1, 8, 24));
    
    Vector2<T> v3;
    v3 = v1 / v2;
    AUNIT_ASSERT(verify(v3, 4, 8));
    
    v3 /= 2;
    AUNIT_ASSERT(verify(v3, 2, 4));
    
    Vector2<T> v4;
    v4 = v3 / 2;
    AUNIT_ASSERT(verify(v4, 1, 2));
}

template<typename T>
void TestVector2<T>::testLength()
{
    Vector2<T> v1(3, 4);
    AUNIT_ASSERT(v1.length() == 5);
    AUNIT_ASSERT(v1.lengthSquared() == 25);
}

} // namespace
} // namespace
