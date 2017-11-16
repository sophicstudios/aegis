#include <agtm_vector4.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(Vector4<T> const& vec, U x, U y, U z, U w)
{
    return vec.x() == static_cast<T>(x)
        && vec.y() == static_cast<T>(y)
        && vec.z() == static_cast<T>(z)
        && vec.w() == static_cast<T>(w);
}

Describe d("agtm_vector4", []
{
    std::array<double, 4> arr = {{1, 2, 3, 4}};

    it("Construction", [&]
    {
        Vector4<double> v1;
        expect(verify(v1, 0, 0, 0, 1)).toBeTrue();
        
        Vector4<double> v2(1, 2, 3, 4);
        expect(verify(v2, 1, 2, 3, 4)).toBeTrue();
        
        Vector4<double> v3(v2);
        expect(verify(v3, 1, 2, 3, 4)).toBeTrue();
        expect(v3).toEqual(v2);
    });

    it("Assignment", [&]
    {
        Vector4<double> v1(3, 4, 5, 6);

        Vector4<double> v2;
        v2 = v1;
        expect(verify(v2, 3, 4, 5, 6)).toBeTrue();

        Vector4<double> v3;
        v3 = arr;
        expect(verify(v3, 1, 2, 3, 4)).toBeTrue();
    });

    it("Addition", [&]
    {
        Vector4<double> v1(1, 2, 3, 4);
        Vector4<double> v2(3, 4, 5, 6);
        
        v1 += v2;
        expect(verify(v1, 4, 6, 8, 10)).toBeTrue();
        
        Vector4<double> v3;
        v3 = v1 + v2;
        expect(verify(v3, 7, 10, 13, 16)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Vector4<double> v1(8, 9, 10, 11);
        Vector4<double> v2(1, 2, 3, 4);
        
        v1 -= v2;
        expect(verify(v1, 7, 7, 7, 7)).toBeTrue();
        
        Vector4<double> v3;
        v3 = v1 - v2;
        expect(verify(v3, 6, 5, 4, 3)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        Vector4<double> v1(1, 2, 3, 4);

        v1 *= 2;
        expect(verify(v1, 2, 4, 6, 8)).toBeTrue();
        
        Vector4<double> v2;
        v2 = v1 * 2.0;
        expect(verify(v2, 4, 8, 12, 16)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector4<double> v1(4, 8, 12, 16);

        v1 /= 2;
        expect(verify(v1, 2, 4, 6, 8)).toBeTrue();
        
        Vector4<double> v2;
        v2 = v1 / 2.0;
        expect(verify(v2, 1, 2, 3, 4)).toBeTrue();
    });
});

} // namespace
