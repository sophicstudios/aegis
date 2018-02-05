#include <agtm_vector3.h>
#include <aunit.h>
#include <iomanip>
#include <sstream>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(Vector3<T> const& v, U x, U y, U z)
{
    return v.x() == static_cast<T>(x)
        && v.y() == static_cast<T>(y)
        && v.z() == static_cast<T>(z);
}

Describe d("agtm_vector3", []
{
    std::array<double, 3> arr = {{1, 2, 3}};

    it("Construction", [&]
    {
        Vector3<double> v1;
        expect(verify(v1, 0, 0, 0)).toBeTrue();
        
        Vector3<double> v2(1, 2, 3);
        expect(verify(v2, 1, 2, 3)).toBeTrue();
        
        Vector3<double> v3(v2);
        expect(verify(v3, 1, 2, 3)).toBeTrue();

        Vector3<double> v4(arr);
        expect(verify(v4, 1, 2, 3)).toBeTrue();
    });

    it("Assignment", [&]
    {
        Vector3<double> v1(3, 4, 5);

        Vector3<double> v2;
        v2 = v1;
        expect(verify(v2, 3, 4, 5)).toBeTrue();

        Vector3<double> v3;
        v3 = arr;
        expect(verify(v3, 1, 2, 3)).toBeTrue();
    });

    it("Addition", [&]
    {
        Vector3<double> v1(1, 2, 3);
        Vector3<double> v2(3, 4, 5);
        
        v1 += v2;
        expect(verify(v1, 4, 6, 8)).toBeTrue();
        
        Vector3<double> v3;
        v3 = v1 + v2;
        expect(verify(v3, 7, 10, 13)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Vector3<double> v1(8, 9, 10);
        Vector3<double> v2(1, 2, 3);
        
        v1 -= v2;
        expect(verify(v1, 7, 7, 7)).toBeTrue();
        
        Vector3<double> v3;
        v3 = v1 - v2;
        expect(verify(v3, 6, 5, 4)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        Vector3<double> v1(1, 2, 3);

        v1 *= 2;
        expect(verify(v1, 2, 4, 6)).toBeTrue();
        
        Vector3<double> v2;
        v2 = v1 * 2.0;
        expect(verify(v2, 4, 8, 12)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector3<double> v1(4, 8, 12);

        v1 /= 2;
        expect(verify(v1, 2, 4, 6)).toBeTrue();
        
        Vector3<double> v2;
        v2 = v1 / 2.0;
        expect(verify(v2, 1, 2, 3)).toBeTrue();
    });

    it("Negation", [&]
    {
        Vector3<double> v1(1, 2, 3);

        Vector3<double> v2 = -v1;
        expect(verify(v2, -1, -2, -3)).toBeTrue();
    });

    it("Comparison", [&]
    {
        Vector3<double> v1(1, 2, 3);
        Vector3<double> v2(1, 2, 3);
        Vector3<double> v3(2, 3, 4);

        expect(v1 == v2).toBeTrue();
        expect(v1 != v3).toBeTrue();
    });

    it("Stream", [&]
    {
        Vector3<double> v1(1, 2, 300);

        std::stringstream s1;
        s1 << std::setw(0) << std::fixed << std::setprecision(0) << v1;
        expect(s1.str() == "[1 2 300]");

        std::stringstream s2;
        s2 << std::setw(3) << std::fixed << std::setprecision(0) << v1;
        expect(s2.str() == "[  1   2 300]");

        std::stringstream s3;
        s3 << std::setw(6) << std::fixed << std::setprecision(2) << v1;
        expect(s3.str() == "[  1.00   2.00 300.00]");
    });
});

} // namespace
