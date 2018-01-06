#include <agtm_vector2.h>
#include <agtm_vector2util.h>
#include <afts_comparisonutil.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace agtm;

Describe d("agtm_vector2util", []
{
    it("Magnitude", [&]
    {
        Vector2<double> v1(3, 4);
        expect(Vector2Util::magnitude(v1)).toEqual(5);
    });

    it("Normalize", [&]
    {
        Vector2<double> v1(3, 4);
        Vector2<double> v1n = Vector2Util::normalize(v1);
        expect(afts::ComparisonUtil::equalULP(Vector2Util::magnitude(v1n), 1.0)).toBeTrue();
    });

    it("Dot Product", [&]
    {
        Vector2<double> v1(3, 4);
        Vector2<double> v2(5, 2);
        expect(Vector2Util::dot(v1, v2)).toEqual(23);
    });
});

} // namespace
