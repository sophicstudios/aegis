#include <agtm_vectorutil.h>
#include <afts_comparisonutil.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace agtm;

Describe d("agtm_vectorutil", []
{
    it("Magnitude", [&]
    {
        Vector2<double> v1(3, 4);
        expect(VectorUtil::magnitude(v1)).toEqual(5);

        Vector3<double> v2(2, 3, 6);
        expect(VectorUtil::magnitude(v2)).toEqual(7);
    });

    it("Normalize", [&]
    {
        Vector2<double> v1(3, 4);
        Vector2<double> v1n = VectorUtil::normalize(v1);
        expect(afts::ComparisonUtil::equalULP(VectorUtil::magnitude(v1n), 1.0)).toBeTrue();

        Vector3<double> v2(3, 4, 5);
        Vector3<double> v2n = VectorUtil::normalize(v2);
        expect(afts::ComparisonUtil::equalULP(VectorUtil::magnitude(v2n), 1.0)).toBeTrue();
    });

    it("Dot Product", [&]
    {
        Vector2<double> v1(3, 4);
        Vector2<double> v2(5, 2);
        expect(VectorUtil::dot(v1, v2)).toEqual(23);

        Vector3<double> v3(3, 4, 5);
        Vector3<double> v4(5, 1, 4);
        expect(VectorUtil::dot(v3, v4)).toEqual(39);
    });

    it("Cross Product", [&]
    {
        Vector3<double> x(1, 0, 0);
        Vector3<double> y(0, 1, 0);
        Vector3<double> z(0, 0, 1);

        expect(VectorUtil::cross(x, y)).toEqual(z);
        expect(VectorUtil::cross(z, x)).toEqual(y);
        expect(VectorUtil::cross(y, z)).toEqual(x);
    });
});

} // namespace
