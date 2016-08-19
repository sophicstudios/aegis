#include <agtm_vector3.h>
#include <aunit.h>

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
    it("Construction", [&]
    {
        Vector3<int> v1;

        expect(verify(v1, 0, 0, 0)).toBeTrue();
        
        Vector3<int> v2(1, 2, 3);

        expect(verify(v2, 1, 2, 3)).toBeTrue();
        
        Vector3<int> v3(v2);

        expect(verify(v3, 1, 2, 3)).toBeTrue();
        expect(v3).toEqual(v2);
        
        v3.assign(3, 4, 5);

        expect(verify(v3, 3, 4, 5)).toBeTrue();
        
        v3 = -v3;

        expect(verify(v3, -3, -4, -5)).toBeTrue();
    });

    it("Addition", [&]
    {
        Vector3<int> v1(1, 2, 3);
        Vector3<int> v2(3, 4, 5);
        
        v1 += v2;

        expect(verify(v1, 4, 6, 8)).toBeTrue();
        
        Vector3<int> v3;
        v3 = v1 + v2;

        expect(verify(v3, 7, 10, 13)).toBeTrue();
        
        v3 += 1;

        expect(verify(v3, 8, 11, 14)).toBeTrue();
        
        Vector3<int> v4;
        v4 = v3 + 2;

        expect(verify(v4, 10, 13, 16)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Vector3<int> v1(8, 9, 10);
        Vector3<int> v2(1, 2, 3);
        
        v1 -= v2;

        expect(verify(v1, 7, 7, 7)).toBeTrue();
        
        Vector3<int> v3;
        v3 = v1 - v2;

        expect(verify(v3, 6, 5, 4)).toBeTrue();
        
        v3 -= 1;

        expect(verify(v3, 5, 4, 3)).toBeTrue();
        
        Vector3<int> v4;
        v4 = v3 - 2;

        expect(verify(v4, 3, 2, 1)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        Vector3<int> v1(1, 2, 3);
        Vector3<int> v2(2, 3, 4);
        
        v1 *= v2;

        expect(verify(v1, 2, 6, 12)).toBeTrue();
        
        Vector3<int> v3;
        v3 = v1 * v2;

        expect(verify(v3, 4, 18, 48)).toBeTrue();
        
        v3 *= 2;

        expect(verify(v3, 8, 36, 96)).toBeTrue();
        
        Vector3<int> v4;
        v4 = v3 * 2;

        expect(verify(v4, 16, 72, 192)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector3<int> v1(16, 72, 192);
        Vector3<int> v2(2, 3, 4);
        
        v1 /= v2;

        expect(verify(v1, 8, 24, 48)).toBeTrue();
        
        Vector3<int> v3;
        v3 = v1 / v2;

        expect(verify(v3, 4, 8, 12)).toBeTrue();
        
        v3 /= 2;

        expect(verify(v3, 2, 4, 6)).toBeTrue();
        
        Vector3<int> v4;
        v4 = v3 / 2;

        expect(verify(v4, 1, 2, 3)).toBeTrue();
    });

    it("Length", [&]
    {
        Vector3<int> v1(2, 3, 6);

        expect(v1.length()).toEqual(7);
        expect(v1.lengthSquared()).toEqual(49);
    });
});

} // namespace
