#include <agtm_matrix3.h>
#include <agtm_matrix3util.h>
#include <agtm_vector3.h>
#include <aunit.h>
#include <array>
#include <iomanip>
#include <sstream>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(agtm::Matrix3<T> const& m, U v1, U v2, U v3, U v4, U v5, U v6, U v7, U v8, U v9)
{
    std::array<T, 9> arr = agtm::Matrix3Util::toRowMajor(m);

    return arr[0] == v1 && arr[1] == v2 && arr[2] == v3 &&
           arr[3] == v4 && arr[4] == v5 && arr[5] == v6 &&
           arr[6] == v7 && arr[7] == v8 && arr[8] == v9;
}

Describe d("agtm_matrix3", []
{
    it("Construction", [&]
    {
        agtm::Matrix3<float> m1;
        expect(verify(m1, 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();

        agtm::Matrix3<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9);
        expect(verify(m2, 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        std::array<std::array<float, 3>, 3> arr{{ {{2, 3, 4}}, {{5, 6, 7}}, {{8, 9, 1}}}};
        agtm::Matrix3<float> m3(arr);
        expect(verify(m3, 2, 3, 4, 5, 6, 7, 8, 9, 1)).toBeTrue();

        agtm::Matrix3<float> m4 = agtm::Matrix3<float>::identity();
        expect(verify(m4, 1, 0, 0, 0, 1, 0, 0, 0, 1)).toBeTrue();
    });

    it("Assignment", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Matrix3<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1);

        m1 = m2;
        expect(verify(m1, 2, 3, 4, 5, 6, 7, 8, 9, 1)).toBeTrue();
    });

    it("Addition", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Matrix3<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9);

        agtm::Matrix3<float> m3 = m1 + m2;
        expect(verify(m3, 2, 4, 6, 8, 10, 12, 14, 16, 18)).toBeTrue();

        m1 += m2;
        expect(verify(m1, 2, 4, 6, 8, 10, 12, 14, 16, 18)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Matrix3<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9);

        agtm::Matrix3<float> m3 = m1 - m2;
        expect(verify(m3, 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();

        m1 -= m2;
        expect(verify(m1, 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Matrix3<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1);

        agtm::Matrix3<float> m3 = m1 * m2;
        expect(verify(m3, 36, 42, 21, 81, 96, 57, 126, 150, 93)).toBeTrue();

        m1 *= m2;
        expect(verify(m1, 36, 42, 21, 81, 96, 57, 126, 150, 93)).toBeTrue();

        agtm::Matrix3<float> m4 = m2 * 3.0f;
        expect(verify(m4, 6, 9, 12, 15, 18, 21, 24, 27, 3)).toBeTrue();

        agtm::Matrix3<float> m5 = 3.0f * m2;
        expect(verify(m5, 6, 9, 12, 15, 18, 21, 24, 27, 3)).toBeTrue();

        m2 *= 3.0f;
        expect(verify(m2, 6, 9, 12, 15, 18, 21, 24, 27, 3)).toBeTrue();

        agtm::Matrix3<float> m6(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Vector3<float> v1(1, 2, 3);

        agtm::Vector3<float> v2 = m6 * v1;
        expect(v2.x() == 14.0f && v2.y() == 32.0f && v2.z() == 50.0f).toBeTrue();

        agtm::Vector3<float> v3 = v1 * m6;
        expect(v3.x() == 30.0f && v3.y() == 36.0f && v3.z() == 42.0f).toBeTrue();
    });

    it("Division", [&]
    {
        agtm::Matrix3<float> m1(3, 6, 9, 12, 15, 18, 21, 24, 27);

        agtm::Matrix3<float> m2 = m1 / 3.0f;
        expect(verify(m2, 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        m1 /= 3.0f;
        expect(verify(m1, 1, 2, 3, 4, 5, 6, 7, 8, 9)).toBeTrue();

        agtm::Matrix3<float> m3(1, 2, 4, 5, 20, 1, 2, 4, 5);

        agtm::Matrix3<float> m4 = 20.0f / m3;
        expect(verify(m4, 20, 10, 5, 4, 1, 20, 10, 5, 4)).toBeTrue();
    });

    it("Comparison", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        agtm::Matrix3<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1);

        expect(m1 == m1).toBeTrue();
        expect(m1 != m2).toBeTrue();
    });

    it("Element Accessors", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

        expect(m1(0, 0) == 1.0f).toBeTrue();
        expect(m1(0, 1) == 2.0f).toBeTrue();
        expect(m1(0, 2) == 3.0f).toBeTrue();
        expect(m1(1, 0) == 4.0f).toBeTrue();
        expect(m1(1, 1) == 5.0f).toBeTrue();
        expect(m1(1, 2) == 6.0f).toBeTrue();
        expect(m1(2, 0) == 7.0f).toBeTrue();
        expect(m1(2, 1) == 8.0f).toBeTrue();
        expect(m1(2, 2) == 9.0f).toBeTrue();

        m1(0, 0) = 2.0f;
        m1(0, 1) = 3.0f;
        m1(0, 2) = 4.0f;
        m1(1, 0) = 5.0f;
        m1(1, 1) = 6.0f;
        m1(1, 2) = 7.0f;
        m1(2, 0) = 8.0f;
        m1(2, 1) = 9.0f;
        m1(2, 2) = 1.0f;

        expect(m1(0, 0) == 2.0f).toBeTrue();
        expect(m1(0, 1) == 3.0f).toBeTrue();
        expect(m1(0, 2) == 4.0f).toBeTrue();
        expect(m1(1, 0) == 5.0f).toBeTrue();
        expect(m1(1, 1) == 6.0f).toBeTrue();
        expect(m1(1, 2) == 7.0f).toBeTrue();
        expect(m1(2, 0) == 8.0f).toBeTrue();
        expect(m1(2, 1) == 9.0f).toBeTrue();
        expect(m1(2, 2) == 1.0f).toBeTrue();
    });

    it("Row/Column Accessors", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

        agtm::Vector3<float> r0 = m1.row(0);
        expect(r0.x() == 1.0f && r0.y() == 2.0f && r0.z() == 3.0f).toBeTrue();

        agtm::Vector3<float> r1 = m1.row(1);
        expect(r1.x() == 4.0f && r1.y() == 5.0f && r1.z() == 6.0f).toBeTrue();

        agtm::Vector3<float> r2 = m1.row(2);
        expect(r2.x() == 7.0f && r2.y() == 8.0f && r2.z() == 9.0f).toBeTrue();

        agtm::Vector3<float> c0 = m1.col(0);
        expect(c0.x() == 1.0f && c0.y() == 4.0f && c0.z() == 7.0f).toBeTrue();

        agtm::Vector3<float> c1 = m1.col(1);
        expect(c1.x() == 2.0f && c1.y() == 5.0f && c1.z() == 8.0f).toBeTrue();

        agtm::Vector3<float> c2 = m1.col(2);
        expect(c2.x() == 3.0f && c2.y() == 6.0f && c2.z() == 9.0f).toBeTrue();
    });

    it("Stream", [&]
    {
        agtm::Matrix3<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 900);

        std::stringstream s1;
        s1 << std::setw(3) << std::fixed << std::setprecision(0) << m1;
        expect(s1.str() == "\n|  1   2   3|\n|  4   5   6|\n|  7   8 900|\n").toBeTrue();

        std::stringstream s2;
        s2 << std::setw(6) << std::fixed << std::setprecision(2) << m1;
        expect(s2.str() == "\n|  1.00   2.00   3.00|\n|  4.00   5.00   6.00|\n|  7.00   8.00 900.00|\n").toBeTrue();
    });
});

} // namespace
