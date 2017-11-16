#include <agtm_matrix3.h>
#include <agtm_matrixutil.h>
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

Describe d("agtm_matrix3", []
{
    it("Construction", [&]
    {
        agtm::Matrix3<float> m1;
        expect(verify(agtm::MatrixUtil::toRowMajor(m1), 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();

        agtm::Matrix3<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9);
        expect(verify(agtm::MatrixUtil::toRowMajor(m2), 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        std::array<float, 9> arr{{2, 3, 4, 5, 6, 7, 8, 9, 1}};
        agtm::Matrix3<float> m3(arr);
        expect(verify(agtm::MatrixUtil::toRowMajor(m3), 2, 3, 4, 5, 6, 7, 8, 9, 1)).toBeTrue();
    });

    it("Assignment", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Matrix3<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1);

        m1 = m2;
        expect(verify(agtm::MatrixUtil::toRowMajor(m1), 2, 3, 4, 5, 6, 7, 8, 9, 1)).toBeTrue();
    });
});

} // namespace
