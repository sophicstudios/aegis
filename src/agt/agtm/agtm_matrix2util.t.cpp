#include <agtm_matrix2.h>
#include <agtm_matrix2util.h>
#include <agtm_vector2.h>
#include <afts_comparisonutil.h>
#include <aunit.h>
#include <array>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(std::array<T, 4> const& arr, U v1, U v2, U v3, U v4)
{
    return arr[0] == v1 && arr[1] == v2 && arr[2] == v3 && arr[3] == v4;
}

template<typename T, typename U>
bool verify(agtm::Matrix2<T> const& m, U v1, U v2, U v3, U v4)
{
    std::array<T, 4> arr = agtm::Matrix2Util::toRowMajor(m);
    return verify(arr, v1, v2, v3, v4);
}

Describe d("agtm_matrix2util", []
{
    it("Converters In", [&]
    {
        std::array<float, 4> arr{{1, 2, 3, 4}};

        Matrix2<float> m1 = Matrix2Util::fromRowMajor(arr);
        expect(verify(m1, 1, 2, 3, 4)).toBeTrue();

        Matrix2<float> m2 = Matrix2Util::fromColMajor(arr);
        expect(verify(m2, 1, 3, 2, 4)).toBeTrue();

        Vector2<float> v1(1, 2);
        Vector2<float> v2(3, 4);

        Matrix2<float> m3 = Matrix2Util::fromRowVectors(v1, v2);
        expect(verify(m3, 1, 2, 3, 4)).toBeTrue();

        Matrix2<float> m4 = Matrix2Util::fromColVectors(v1, v2);
        expect(verify(m4, 1, 3, 2, 4)).toBeTrue();
    });

    it("Converters Out", [&]
    {
        Matrix2<float> m1(1, 2, 3, 4);

        std::array<float, 4> arr1 = Matrix2Util::toRowMajor(m1);
        expect(verify(arr1, 1, 2, 3, 4)).toBeTrue();

        std::array<float, 4> arr2 = Matrix2Util::toColMajor(m1);
        expect(verify(arr2, 1, 3, 2, 4)).toBeTrue();
    });

    it("Transpose", [&]
    {
        Matrix2<float> m1(1, 2, 3, 4);

        Matrix2<float> m2 = Matrix2Util::transpose(m1);
        expect(verify(m2, 1, 3, 2, 4)).toBeTrue();
    });

    it("Determinant", [&]
    {
        Matrix2<float> m1(1, 2, 3, 4);

        float d1 = Matrix2Util::determinant(m1);
        expect(afts::ComparisonUtil::equalULP(d1, -2.0f)).toBeTrue();

        Matrix2<float> m2(3, 4, 1, 2);
        float d2 = Matrix2Util::determinant(m2);
        expect(afts::ComparisonUtil::equalULP(d2, 2.0f)).toBeTrue();

        Matrix2<float> m3(3, 4, 3, 4);
        float d3 = Matrix2Util::determinant(m3);
        expect(afts::ComparisonUtil::equalULP(d3, 0.0f)).toBeTrue();
    });
});

} // namespace
