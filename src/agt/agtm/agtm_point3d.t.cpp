#include <agtm_point3d.h>
#include <afts_comparisonutil.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace agtm;

namespace {

struct TestValues
{
    static float xOrigin;
    static float yOrigin;
    static float zOrigin;
    
    static float x;
    static float y;
    static float z;
};

float TestValues::xOrigin = 0.0f;
float TestValues::yOrigin = 0.0f;
float TestValues::zOrigin = 0.0f;

float TestValues::x = 1.1f;
float TestValues::y = 2.2f;
float TestValues::z = 3.3f;

template<typename T>
void assertEqual(agtm::Point3d<T> const& p, T x, T y, T z)
{
    expect(afts::ComparisonUtil::equalULP(p.x(), x, 5)).toBeTrue();
    expect(afts::ComparisonUtil::equalULP(p.y(), y, 5)).toBeTrue();
    expect(afts::ComparisonUtil::equalULP(p.z(), z, 5)).toBeTrue();
}

} // namespace

Describe d("agtm_point3d", []
{
    it("Construction", [&]
    {
        // Default construction
        agtm::Point3d<float> p1;
        assertEqual(p1, TestValues::xOrigin, TestValues::yOrigin, TestValues::zOrigin);
        
        // Construction with individual x, y and z components
        agtm::Point3d<float> p2(TestValues::x, TestValues::y, TestValues::z);
        assertEqual(p2, TestValues::x, TestValues::y, TestValues::z);
        
        // Construction with 3-element array
        float arr[3];
        arr[0] = TestValues::x;
        arr[1] = TestValues::y;
        arr[2] = TestValues::z;

        agtm::Point3d<float> p3(arr);
        assertEqual(p3, arr[0], arr[1], arr[2]);
    });

    it("Assignment", [&]
    {
        agtm::Point3d<float> p1(TestValues::x, TestValues::y, TestValues::z);
        agtm::Point3d<float> p2;
        
        // Basic assignment
        p2 = p1;
        assertEqual(p1, p2.x(), p2.y(), p2.z());
    });

    it("Multiplication", [&]
    {
        // unary operator *=
        agtm::Point3d<float> p1(TestValues::x, TestValues::y, TestValues::z);
        p1 *= 2.0;
        assertEqual(p1, TestValues::x * 6 / 3, TestValues::y * 6 / 3, TestValues::z * 6 / 3);
        
        // binary operator*
        agtm::Point3d<float> p2 = p1 * 3.0;
        assertEqual(p2, TestValues::x * 6, TestValues::y * 6, TestValues::z * 6);
    });

    it("Division", [&]
    {
        const float xInit = TestValues::x * 12;
        const float yInit = TestValues::y * 12;
        const float zInit = TestValues::z * 12;
        
        // unary operator/=
        agtm::Point3d<float> p1(xInit, yInit, zInit);
        p1 /= 3;
        assertEqual(p1, xInit / 3, yInit / 3, zInit / 3);
        
        // binary operator/
        agtm::Point3d<float> p2 = p1 / 4;
        assertEqual(p2, xInit / 12, yInit / 12, zInit / 12);
    });
});

} // namespace
