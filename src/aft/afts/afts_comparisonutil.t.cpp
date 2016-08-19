#include <afts_comparisonutil.h>
#include <aunit.h>
#include <cstring>
#include <limits>

namespace {

using namespace aunit;
using namespace afts;

Describe d("afts_comparisonutil", []
{
    it("float ULP", [&]
    {
        float f1;
        float f2;
        
        int i = 0x00000001;
        f1 = *(reinterpret_cast<float*>(&i));
        i = 0x80000001;
        f2 = *(reinterpret_cast<float*>(&i));

        expect(afts::ComparisonUtil::equalULP(f1, f2)).toBeTrue();
        expect(afts::ComparisonUtil::equalULP(f1, f2, 5)).toBeTrue();
        
        f1 = 0.0f + std::numeric_limits<float>::epsilon();
        f2 = 0.0f - std::numeric_limits<float>::epsilon();

        expect(afts::ComparisonUtil::equalULP(f1, f2)).toBeTrue();
        expect(afts::ComparisonUtil::equalULP(f1, f2, 5)).toBeTrue();
        
        f1 = .0000000001f;
        f2 = -.0000000001f;

        expect(afts::ComparisonUtil::equalULP(f1, f2)).toBeTrue();
        expect(afts::ComparisonUtil::equalULP(f1, f2, 5)).toBeTrue();
    });

    it("double ULP", [&]
    {
        double d1;
        double d2;

        d1 = 0.0;
        d2 = 0.0;
        *((long long*)&d2) += 1;
        
        expect(afts::ComparisonUtil::equalULP(d1, d2)).toBeTrue();
        expect(afts::ComparisonUtil::equalULP(d1, d2, 5)).toBeTrue();
    });
});

} // namespace
