#include <agtm_vector4.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T>
bool verify(Vector4<T> const& vec, T x, T y, T z, T w)
{
    return vec.x() == x
        && vec.y() == y
        && vec.z() == z
        && vec.w() == w;
}

Describe d("agtm_vector4", []
{
    std::array<int, 4> arr = {1, 2, 3, 4};

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    it("Construction", [&]
    {
        Vector4<int> v1;

        expect(verify(v1, 0, 0, 0, 0)).toBeTrue();
        
        Vector4<int> v2(1, 2, 3, 4);

        expect(verify(v2, 1, 2, 3, 4)).toBeTrue();
        
        Vector4<int> v3(v2);

        expect(verify(v3, 1, 2, 3, 4)).toBeTrue();
        expect(v3).toEqual(v2);
    });

    it("Assignment", [&]
    {
        Vector4<int> v1;
        v1.assign(3, 4, 5, 6);
        expect(verify(v1, 3, 4, 5, 6)).toBeTrue();

        Vector4<int> v2;
        v2 = v1;
        expect(verify(v2, 3, 4, 5, 6)).toBeTrue();

        Vector4<int> v3;
        v3 = arr;
        expect(verify(v3, 1, 2, 3, 4)).toBeTrue();

        Vector4<int> v4;
        v4 = vec;
        expect(verify(v4, 1, 2, 3, 4)).toBeTrue();

    });

    it("Addition", [&]
    {
        Vector4<int> v1(1, 2, 3, 4);
        Vector4<int> v2(3, 4, 5, 6);
        
        v1 += v2;

        expect(verify(v1, 4, 6, 8, 10)).toBeTrue();
        
        Vector4<int> v3;
        v3 = v1 + v2;

        expect(verify(v3, 7, 10, 13, 16)).toBeTrue();
        
        v3 += 1;

        expect(verify(v3, 8, 11, 14, 17)).toBeTrue();
        
        Vector4<int> v4;
        v4 = v3 + 2;

        expect(verify(v4, 10, 13, 16, 19)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Vector4<int> v1(8, 9, 10, 11);
        Vector4<int> v2(1, 2, 3, 4);
        
        v1 -= v2;

        expect(verify(v1, 7, 7, 7, 7)).toBeTrue();
        
        Vector4<int> v3;
        v3 = v1 - v2;

        expect(verify(v3, 6, 5, 4, 3)).toBeTrue();
        
        v3 -= 1;

        expect(verify(v3, 5, 4, 3, 2)).toBeTrue();
        
        Vector4<int> v4;
        v4 = v3 - 2;

        expect(verify(v4, 3, 2, 1, 0)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        Vector4<int> v1(1, 2, 3, 4);

        v1 *= 2;

        expect(verify(v1, 2, 4, 6, 8)).toBeTrue();
        
        Vector4<int> v2;
        v2 = v1 * 2;

        expect(verify(v2, 4, 8, 12, 16)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector4<int> v1(4, 8, 12, 16);

        v1 /= 2;

        expect(verify(v1, 2, 4, 6, 8)).toBeTrue();
        
        Vector4<int> v2;
        v2 = v1 / 2;

        expect(verify(v2, 1, 2, 3, 4)).toBeTrue();
    });
});

} // namespace
