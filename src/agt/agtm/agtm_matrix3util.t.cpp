#include <agtm_matrix3.h>
#include <agtm_matrix3util.h>
#include <agtm_vector3.h>
#include <afts_comparisonutil.h>
#include <aunit.h>
#include <array>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(std::array<T, 9> const& arr, U v1, U v2, U v3, U v4, U v5, U v6, U v7, U v8, U v9)
{
    return arr[0] == v1 && arr[1] == v2 && arr[2] == v3 &&
           arr[3] == v4 && arr[4] == v5 && arr[5] == v6 &&
           arr[6] == v7 && arr[7] == v8 && arr[8] == v9;
}

template<typename T, typename U>
bool verify(agtm::Matrix3<T> const& m, U v1, U v2, U v3, U v4, U v5, U v6, U v7, U v8, U v9)
{
    std::array<T, 9> arr = agtm::Matrix3Util::toRowMajor(m);
    return verify(arr, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

Describe d("agtm_matrix3util", []
{
    it("Converters In", [&]
    {
        std::array<float, 9> arr{{1, 2, 3, 4, 5, 6, 7, 8, 9}};

        Matrix3<float> m1 = Matrix3Util::fromRowMajor(arr);
        expect(verify(m1, 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        Matrix3<float> m2 = Matrix3Util::fromColMajor(arr);
        expect(verify(m2, 1, 4, 7, 2, 5, 8, 3, 6, 9)).toBeTrue();

        Vector3<float> v1(1, 2, 3);
        Vector3<float> v2(4, 5, 6);
        Vector3<float> v3(7, 8, 9);

        Matrix3<float> m3 = Matrix3Util::fromRowVectors(v1, v2, v3);
        expect(verify(m3, 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        Matrix3<float> m4 = Matrix3Util::fromColVectors(v1, v2, v3);
        expect(verify(m4, 1, 4, 7, 2, 5, 8, 3, 6, 9)).toBeTrue();
    });

    it("Converters Out", [&]
    {
        Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

        std::array<float, 9> arr1 = Matrix3Util::toRowMajor(m1);
        expect(verify(arr1, 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        std::array<float, 9> arr2 = Matrix3Util::toColMajor(m1);
        expect(verify(arr2, 1, 4, 7, 2, 5, 8, 3, 6, 9)).toBeTrue();
    });

    it("Transpose", [&]
    {
        Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

        Matrix3<float> m2 = Matrix3Util::transpose(m1);
        expect(verify(m2, 1, 4, 7, 2, 5, 8, 3, 6, 9)).toBeTrue();
    });

    it("Determinant", [&]
    {
        Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

        float d1 = Matrix3Util::determinant(m1);
        expect(afts::ComparisonUtil::equalULP(d1, 0.0f)).toBeTrue();

        Matrix3<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1);
        float d2 = Matrix3Util::determinant(m2);
        expect(afts::ComparisonUtil::equalULP(d2, 27.0f)).toBeTrue();

        Matrix3<float> m3(9, 1, 2, 3, 4, 5, 6, 7, 8);
        float d3 = Matrix3Util::determinant(m3);
        expect(afts::ComparisonUtil::equalULP(d3, -27.0f)).toBeTrue();
    });
});

} // namespace

