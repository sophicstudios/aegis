#include <agtm_matrix2.h>
#include <agtm_matrixutil.h>
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

Describe d("agtm_matrix2", []
{
    it("Construction", [&]
    {
        agtm::Matrix2<float> m1;
        expect(verify(agtm::MatrixUtil::toRowMajor(m1), 0, 0, 0, 0)).toBeTrue();

        agtm::Matrix2<float> m2(1, 2, 3, 4);
        expect(verify(agtm::MatrixUtil::toRowMajor(m2), 1, 2, 3, 4)).toBeTrue();

        std::array<float, 4> arr{{5, 6, 7, 8}};
        agtm::Matrix2<float> m3(arr);
        expect(verify(agtm::MatrixUtil::toRowMajor(m3), 5, 6, 7, 8)).toBeTrue();
    });

    it("Assignment", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);
        agtm::Matrix2<float> m2(5, 6, 7, 8);

        m1 = m2;
        expect(verify(agtm::MatrixUtil::toRowMajor(m1), 5, 6, 7, 8)).toBeTrue();
    });
});

} // namespace
