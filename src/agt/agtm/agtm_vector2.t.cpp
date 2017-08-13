#include <agtm_vector2.h>
#include <aunit.h>

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
    std::array<int, 2> arr = {1, 2};

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    it("Construction", [&]
    {
        Vector2<int> v1;
        expect(verify(v1, 0, 0)).toBeTrue();
        
        Vector2<int> v2(1, 2);
        expect(verify(v2, 1, 2)).toBeTrue();
        
        Vector2<int> v3(v2);
        expect(verify(v3, 1, 2)).toBeTrue();

        Vector2<int> v4(arr);
        expect(verify(v4, 1, 2)).toBeTrue();

        Vector2<int> v5(vec);
        expect(verify(v5, 1, 2)).toBeTrue();
    });

    it("Assignment", [&]
    {
        Vector2<int> v1;
        v1.assign(3, 4);
        expect(verify(v1, 3, 4)).toBeTrue();

        Vector2<int> v2;
        v2 = v1;
        expect(verify(v2, 3, 4)).toBeTrue();

        Vector2<int> v3;
        v3 = arr;
        expect(verify(v3, 1, 2)).toBeTrue();

        Vector2<int> v4;
        v4 = vec;
        expect(verify(v4, 1, 2)).toBeTrue();
    });

    it("Addition", [&]
    {
        Vector2<int> v1(1, 2);
        Vector2<int> v2(3, 4);
        
        v1 += v2;
        expect(verify(v1, 4, 6)).toBeTrue();
        
        Vector2<int> v3;
        v3 = v1 + v2;
        expect(verify(v3, 7, 10)).toBeTrue();
        
        v3 += 1;
        expect(verify(v3, 8, 11)).toBeTrue();
        
        Vector2<int> v4;
        v4 = v3 + 2;
        expect(verify(v4, 10, 13)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Vector2<int> v1(8, 9);
        Vector2<int> v2(1, 2);
        
        v1 -= v2;
        expect(verify(v1, 7, 7)).toBeTrue();
        
        Vector2<int> v3;
        v3 = v1 - v2;
        expect(verify(v3, 6, 5)).toBeTrue();
        
        v3 -= 1;
        expect(verify(v3, 5, 4)).toBeTrue();
        
        Vector2<int> v4;
        v4 = v3 - 2;
        expect(verify(v4, 3, 2)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        Vector2<int> v1(1, 2);

        v1 *= 2;
        expect(verify(v1, 2, 4)).toBeTrue();
        
        Vector2<int> v2;
        v2 = v1 * 2;
        expect(verify(v2, 4, 8)).toBeTrue();
    });

    it("Division", [&]
    {
        Vector2<int> v1(4, 8);

        v1 /= 2;
        expect(verify(v1, 2, 4)).toBeTrue();
        
        Vector2<int> v2;
        v2 = v1 / 2;
        expect(verify(v2, 1, 2)).toBeTrue();
    });

    it("Length", [&]
    {
        Vector2<int> v1(3, 4);
        expect(v1.length()).toEqual(5);
        expect(v1.lengthSquared()).toEqual(25);
    });
});

} // namespace
