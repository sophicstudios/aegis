#include <agtm_matrix4.h>
#include <agtm_matrix4util.h>
#include <agtm_vector4.h>
#include <afts_comparisonutil.h>
#include <aunit.h>
#include <array>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(std::array<T, 16> const& arr, U v1, U v2, U v3, U v4, U v5, U v6, U v7, U v8, U v9, U v10, U v11, U v12, U v13, U v14, U v15, U v16)
{
    return arr[0] == v1 && arr[1] == v2 && arr[2] == v3 && arr[3] == v4 &&
           arr[4] == v5 && arr[5] == v6 && arr[6] == v7 && arr[7] == v8 &&
           arr[8] == v9 && arr[9] == v10 && arr[10] == v11 && arr[11] == v12 &&
           arr[12] == v13 && arr[13] == v14 && arr[14] == v15 && arr[15] == v16;
}

template<typename T, typename U>
bool verify(agtm::Matrix4<T> const& m, U v1, U v2, U v3, U v4, U v5, U v6, U v7, U v8, U v9, U v10, U v11, U v12, U v13, U v14, U v15, U v16)
{
    std::array<T, 16> arr = agtm::Matrix4Util::toRowMajor(m);
    return verify(arr, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
}

Describe d("agtm_matrix4util", []
{
    it("Converters In", [&]
    {
        std::array<float, 16> arr{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};

        Matrix4<float> m1 = Matrix4Util::fromRowMajor(arr);
        expect(verify(m1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)).toBeTrue();

        Matrix4<float> m2 = Matrix4Util::fromColMajor(arr);
        expect(verify(m2, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16)).toBeTrue();

        Vector4<float> v1(1, 2, 3, 4);
        Vector4<float> v2(5, 6, 7, 8);
        Vector4<float> v3(9, 10, 11, 12);
        Vector4<float> v4(13, 14, 15, 16);

        Matrix4<float> m3 = Matrix4Util::fromRowVectors(v1, v2, v3, v4);
        expect(verify(m3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)).toBeTrue();

        Matrix4<float> m4 = Matrix4Util::fromColVectors(v1, v2, v3, v4);
        expect(verify(m4, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16)).toBeTrue();
    });

    it("Converters Out", [&]
    {
        Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        std::array<float, 16> arr1 = Matrix4Util::toRowMajor(m1);
        expect(verify(arr1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)).toBeTrue();

        std::array<float, 16> arr2 = Matrix4Util::toColMajor(m1);
        expect(verify(arr2, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16)).toBeTrue();
    });

    it("Transpose", [&]
    {
        Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        Matrix4<float> m2 = Matrix4Util::transpose(m1);
        expect(verify(m2, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16)).toBeTrue();
    });

    it("Determinant", [&]
    {
        Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        float d1 = Matrix4Util::determinant(m1);
        expect(afts::ComparisonUtil::equalULP(d1, 0.0f)).toBeTrue();

        Matrix4<float> m2(16, 14, 13, 15, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 11, 12);
        float d2 = Matrix4Util::determinant(m2);
        expect(afts::ComparisonUtil::equalULP(d2, 128.0f)).toBeTrue();

        Matrix4<float> m3(16, 14, 13, 15, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2);
        float d3 = Matrix4Util::determinant(m3);
        expect(afts::ComparisonUtil::equalULP(d3, -192.0f)).toBeTrue();
    });
});

} // namespace


