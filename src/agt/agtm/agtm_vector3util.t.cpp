#include <agtm_vector3.h>
#include <agtm_vector3util.h>
#include <afts_comparisonutil.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace agtm;

Describe d("agtm_vector3util", []
{
    it("Magnitude", [&]
    {
        Vector3<double> v2(2, 3, 6);
        expect(Vector3Util::magnitude(v2)).toEqual(7);
    });

    it("Normalize", [&]
    {
        Vector3<double> v2(3, 4, 5);
        Vector3<double> v2n = Vector3Util::normalize(v2);
        expect(afts::ComparisonUtil::equalULP(Vector3Util::magnitude(v2n), 1.0)).toBeTrue();
    });

    it("Dot Product", [&]
    {
        Vector3<double> v3(3, 4, 5);
        Vector3<double> v4(5, 1, 4);
        expect(Vector3Util::dot(v3, v4)).toEqual(39);
    });

    it("Cross Product", [&]
    {
        Vector3<double> x(1, 0, 0);
        Vector3<double> y(0, 1, 0);
        Vector3<double> z(0, 0, 1);

        expect(Vector3Util::cross(x, y)).toEqual(z);
        expect(Vector3Util::cross(z, x)).toEqual(y);
        expect(Vector3Util::cross(y, z)).toEqual(x);
    });
});

} // namespace
