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
    std::array<int, 3> arr = {1, 2, 3};

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    it("Construction", [&]
    {
        Vector3<int> v1;
        expect(verify(v1, 0, 0, 0)).toBeTrue();
        
        Vector3<int> v2(1, 2, 3);
        expect(verify(v2, 1, 2, 3)).toBeTrue();
        
        Vector3<int> v3(v2);
        expect(verify(v3, 1, 2, 3)).toBeTrue();

        Vector3<int> v4(arr);
        expect(verify(v4, 1, 2, 3)).toBeTrue();

        Vector3<int> v5(vec);
        expect(verify(v5, 1, 2, 3)).toBeTrue();
    });

    it("Assignment", [&]
    {
        Vector3<int> v1;
        v1.assign(3, 4, 5);
        expect(verify(v1, 3, 4, 5)).toBeTrue();

        Vector3<int> v2;
        v2 = v1;
        expect(verify(v2, 3, 4, 5)).toBeTrue();

        Vector3<int> v3;
        v3 = arr;
        expect(verify(v3, 1, 2, 3)).toBeTrue();

        Vector3<int> v4;
        v4 = vec;
        expect(verify(v4, 1, 2, 3)).toBeTrue();
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

        v1 *= 2;

        expect(verify(v1, 2, 4, 6)).toBeTrue();
        
        Vector3<int> v2;
        v2 = v1 * 2;

        expect(verify(v2, 4, 8, 12)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector3<int> v1(4, 8, 12);

        v1 /= 2;

        expect(verify(v1, 2, 4, 6)).toBeTrue();
        
        Vector3<int> v2;
        v2 = v1 / 2;

        expect(verify(v2, 1, 2, 3)).toBeTrue();
    });

    it("Length", [&]
    {
        Vector3<int> v1(2, 3, 6);

        expect(v1.length()).toEqual(7);
        expect(v1.lengthSquared()).toEqual(49);
    });
});

} // namespace
