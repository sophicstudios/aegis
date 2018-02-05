#include <agtm_vector2.h>
#include <aunit.h>
#include <iomanip>
#include <sstream>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(Vector2<T> const& v, U x, U y)
{
    return v.x() == static_cast<T>(x) && v.y() == static_cast<T>(y);
}

Describe d("agtm_vector2", []
{
    std::array<double, 2> arr = {{1, 2}};

    it("Construction", [&]
    {
        Vector2<double> v1;
        expect(verify(v1, 0, 0)).toBeTrue();
        
        Vector2<double> v2(1, 2);
        expect(verify(v2, 1, 2)).toBeTrue();
        
        Vector2<double> v3(v2);
        expect(verify(v3, 1, 2)).toBeTrue();

        Vector2<double> v4(arr);
        expect(verify(v4, 1, 2)).toBeTrue();
    });

    it("Assignment", [&]
    {
        Vector2<double> v1(3, 4);

        Vector2<double> v2;
        v2 = v1;
        expect(verify(v2, 3, 4)).toBeTrue();

        Vector2<double> v3;
        v3 = arr;
        expect(verify(v3, 1, 2)).toBeTrue();
    });

    it("Addition", [&]
    {
        Vector2<double> v1(1, 2);
        Vector2<double> v2(3, 4);
        
        v1 += v2;
        expect(verify(v1, 4, 6)).toBeTrue();
        
        Vector2<double> v3;
        v3 = v1 + v2;
        expect(verify(v3, 7, 10)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Vector2<double> v1(8, 9);
        Vector2<double> v2(1, 2);
        
        v1 -= v2;
        expect(verify(v1, 7, 7)).toBeTrue();
        
        Vector2<double> v3;
        v3 = v1 - v2;
        expect(verify(v3, 6, 5)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        Vector2<double> v1(1, 2);

        v1 *= 2;
        expect(verify(v1, 2, 4)).toBeTrue();
        
        Vector2<double> v2;
        v2 = v1 * 2.0;
        expect(verify(v2, 4, 8)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector2<double> v1(4, 8);

        v1 /= 2;
        expect(verify(v1, 2, 4)).toBeTrue();
        
        Vector2<double> v2;
        v2 = v1 / 2.0;
        expect(verify(v2, 1, 2)).toBeTrue();
    });

    it("Negation", [&]
    {
        Vector2<double> v1(1, 2);

        Vector2<double> v2 = -v1;
        expect(verify(v2, -1, -2)).toBeTrue();
    });

    it("Comparison", [&]
    {
        Vector2<double> v1(1, 2);
        Vector2<double> v2(1, 2);
        Vector2<double> v3(2, 3);

        expect(v1 == v2).toBeTrue();
        expect(v1 != v3).toBeTrue();
    });

    it("Stream", [&]
    {
        Vector2<double> v1(1, 200);

        std::stringstream s1;
        s1 << std::setw(0) << std::fixed << std::setprecision(0) << v1;
        expect(s1.str() == "[1 200]");

        std::stringstream s2;
        s2 << std::setw(3) << std::fixed << std::setprecision(0) << v1;
        expect(s2.str() == "[  1 200]");

        std::stringstream s3;
        s3 << std::setw(6) << std::fixed << std::setprecision(2) << v1;
        expect(s3.str() == "[  1.00 200.00]");
    });
});

} // namespace
