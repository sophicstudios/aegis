#include <agtm_matrix4.h>
#include <agtm_matrix4util.h>
#include <agtm_vector4.h>
#include <aunit.h>
#include <array>
#include <iomanip>
#include <sstream>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(agtm::Matrix4<T> const& m, U v1, U v2, U v3, U v4, U v5, U v6, U v7, U v8, U v9, U v10, U v11, U v12, U v13, U v14, U v15, U v16)
{
    std::array<T, 16> arr = agtm::Matrix4Util::toRowMajor(m);

    return arr[0]  == v1  && arr[1]  == v2  && arr[2]  == v3  && arr[3]  == v4  &&
           arr[4]  == v5  && arr[5]  == v6  && arr[6]  == v7  && arr[7]  == v8  &&
           arr[8]  == v9  && arr[9]  == v10 && arr[10] == v11 && arr[11] == v12 &&
           arr[12] == v13 && arr[13] == v14 && arr[14] == v15 && arr[15] == v16;
}

Describe d("agtm_matrix4", []
{
    it("Construction", [&]
    {
        agtm::Matrix4<float> m1;
        expect(verify(m1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();

        agtm::Matrix4<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        expect(verify(m2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)).toBeTrue();

        std::array<std::array<float, 4>, 4> arr{{ {{2, 3, 4, 5}}, {{6, 7, 8, 9}}, {{10, 11, 12, 13}}, {{14, 15, 16, 17}} }};
        agtm::Matrix4<float> m3(arr);
        expect(verify(m3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17)).toBeTrue();

        agtm::Matrix4<float> m4 = agtm::Matrix4<float>::identity();
        expect(verify(m4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)).toBeTrue();
    });

    it("Assignment", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        agtm::Matrix4<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);

        m1 = m2;
        expect(verify(m1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17)).toBeTrue();
    });

    it("Addition", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);
        agtm::Matrix4<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);

        agtm::Matrix4<float> m3 = m1 + m2;
        expect(verify(m3, 2, 4, 6, 8, 10, 12, 14, 16, 18, 2, 4, 6, 8, 10, 12, 14)).toBeTrue();

        m1 += m2;
        expect(verify(m1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 2, 4, 6, 8, 10, 12, 14)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);
        agtm::Matrix4<float> m2(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);

        agtm::Matrix4<float> m3 = m1 - m2;
        expect(verify(m3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();

        m1 -= m2;
        expect(verify(m1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);
        agtm::Matrix4<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8);

        agtm::Matrix4<float> m3 = m1 * m2;
        expect(verify(m3, 37, 47, 57, 67, 93, 119, 145, 171, 41, 56, 71, 86, 79, 101, 123, 145)).toBeTrue();

        m1 *= m2;
        expect(verify(m1, 37, 47, 57, 67, 93, 119, 145, 171, 41, 56, 71, 86, 79, 101, 123, 145)).toBeTrue();

        agtm::Matrix4<float> m4 = m2 * 3.0f;
        expect(verify(m4, 6, 9, 12, 15, 18, 21, 24, 27, 3, 6, 9, 12, 15, 18, 21, 24)).toBeTrue();

        agtm::Matrix4<float> m5 = 3.0f * m2;
        expect(verify(m5, 6, 9, 12, 15, 18, 21, 24, 27, 3, 6, 9, 12, 15, 18, 21, 24)).toBeTrue();

        m2 *= 3.0f;
        expect(verify(m2, 6, 9, 12, 15, 18, 21, 24, 27, 3, 6, 9, 12, 15, 18, 21, 24)).toBeTrue();

        agtm::Matrix4<float> m6(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);
        agtm::Vector4<float> v1(1, 2, 3, 4);

        agtm::Vector4<float> v2 = m6 * v1;
        expect(v2.x() == 30.0f && v2.y() == 70.0f && v2.z() == 29.0f && v2.w() == 60.0f).toBeTrue();

        agtm::Vector4<float> v3 = v1 * m6;
        expect(v3.x() == 54.0f && v3.y() == 37.0f && v3.z() == 47.0f && v3.w() == 57.0f).toBeTrue();
    });

    it("Division", [&]
    {
        agtm::Matrix4<float> m1(3, 6, 9, 12, 15, 18, 21, 24, 27, 3, 6, 9, 12, 15, 18, 21);

        agtm::Matrix4<float> m2 = m1 / 3.0f;
        expect(verify(m2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7)).toBeTrue();

        m1 /= 3.0f;
        expect(verify(m1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7)).toBeTrue();

        agtm::Matrix4<float> m3(1, 2, 4, 5, 1, 2, 4, 5, 1, 2, 4, 5, 1, 2, 4, 5);

        agtm::Matrix4<float> m4 = 20.0f / m3;
        expect(verify(m4, 20, 10, 5, 4, 20, 10, 5, 4, 20, 10, 5, 4, 20, 10, 5, 4)).toBeTrue();
    });

    it("Comparison", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);
        agtm::Matrix4<float> m2(2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8);

        expect(m1 == m1).toBeTrue();
        expect(m1 != m2).toBeTrue();
    });

    it("Element Accessors", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);

        expect(m1(0, 0) == 1.0f).toBeTrue();
        expect(m1(0, 1) == 2.0f).toBeTrue();
        expect(m1(0, 2) == 3.0f).toBeTrue();
        expect(m1(0, 3) == 4.0f).toBeTrue();
        expect(m1(1, 0) == 5.0f).toBeTrue();
        expect(m1(1, 1) == 6.0f).toBeTrue();
        expect(m1(1, 2) == 7.0f).toBeTrue();
        expect(m1(1, 3) == 8.0f).toBeTrue();
        expect(m1(2, 0) == 9.0f).toBeTrue();
        expect(m1(2, 1) == 1.0f).toBeTrue();
        expect(m1(2, 2) == 2.0f).toBeTrue();
        expect(m1(2, 3) == 3.0f).toBeTrue();
        expect(m1(3, 0) == 4.0f).toBeTrue();
        expect(m1(3, 1) == 5.0f).toBeTrue();
        expect(m1(3, 2) == 6.0f).toBeTrue();
        expect(m1(3, 3) == 7.0f).toBeTrue();

        m1(0, 0) = 2.0f;
        m1(0, 1) = 3.0f;
        m1(0, 2) = 4.0f;
        m1(0, 3) = 5.0f;
        m1(1, 0) = 6.0f;
        m1(1, 1) = 7.0f;
        m1(1, 2) = 8.0f;
        m1(1, 3) = 9.0f;
        m1(2, 0) = 1.0f;
        m1(2, 1) = 2.0f;
        m1(2, 2) = 3.0f;
        m1(2, 3) = 4.0f;
        m1(3, 0) = 5.0f;
        m1(3, 1) = 6.0f;
        m1(3, 2) = 7.0f;
        m1(3, 3) = 8.0f;

        expect(m1(0, 0) == 2.0f).toBeTrue();
        expect(m1(0, 1) == 3.0f).toBeTrue();
        expect(m1(0, 2) == 4.0f).toBeTrue();
        expect(m1(0, 3) == 5.0f).toBeTrue();
        expect(m1(1, 0) == 6.0f).toBeTrue();
        expect(m1(1, 1) == 7.0f).toBeTrue();
        expect(m1(1, 2) == 8.0f).toBeTrue();
        expect(m1(1, 3) == 9.0f).toBeTrue();
        expect(m1(2, 0) == 1.0f).toBeTrue();
        expect(m1(2, 1) == 2.0f).toBeTrue();
        expect(m1(2, 2) == 3.0f).toBeTrue();
        expect(m1(2, 3) == 4.0f).toBeTrue();
        expect(m1(3, 0) == 5.0f).toBeTrue();
        expect(m1(3, 1) == 6.0f).toBeTrue();
        expect(m1(3, 2) == 7.0f).toBeTrue();
        expect(m1(3, 3) == 8.0f).toBeTrue();
    });

    it("Row/Column Accessors", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);

        agtm::Vector4<float> r0 = m1.row(0);
        expect(r0.x() == 1.0f && r0.y() == 2.0f && r0.z() == 3.0f && r0.w() == 4.0f).toBeTrue();

        agtm::Vector4<float> r1 = m1.row(1);
        expect(r1.x() == 5.0f && r1.y() == 6.0f && r1.z() == 7.0f && r1.w() == 8.0f).toBeTrue();

        agtm::Vector4<float> r2 = m1.row(2);
        expect(r2.x() == 9.0f && r2.y() == 1.0f && r2.z() == 2.0f && r2.w() == 3.0f).toBeTrue();

        agtm::Vector4<float> r3 = m1.row(3);
        expect(r3.x() == 4.0f && r3.y() == 5.0f && r3.z() == 6.0f && r3.w() == 7.0f).toBeTrue();

        agtm::Vector4<float> c0 = m1.col(0);
        expect(c0.x() == 1.0f && c0.y() == 5.0f && c0.z() == 9.0f && c0.w() == 4.0f).toBeTrue();

        agtm::Vector4<float> c1 = m1.col(1);
        expect(c1.x() == 2.0f && c1.y() == 6.0f && c1.z() == 1.0f && c1.w() == 5.0f).toBeTrue();

        agtm::Vector4<float> c2 = m1.col(2);
        expect(c2.x() == 3.0f && c2.y() == 7.0f && c2.z() == 2.0f && c2.w() == 6.0f).toBeTrue();

        agtm::Vector4<float> c3 = m1.col(3);
        expect(c3.x() == 4.0f && c3.y() == 8.0f && c3.z() == 3.0f && c3.w() == 7.0f).toBeTrue();
    });

    it("Stream", [&]
    {
        agtm::Matrix4<float> m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 160);

        std::stringstream s1;
        s1 << std::setw(3) << std::fixed << std::setprecision(0) << m1;
        expect(s1.str() == "\n|  1   2   3   4|\n|  5   6   7   8|\n|  9  10  11  12|\n| 13  14  15 160|\n").toBeTrue();

        std::stringstream s2;
        s2 << std::setw(6) << std::fixed << std::setprecision(2) << m1;
        expect(s2.str() == "\n|  1.00   2.00   3.00   4.00|\n|  5.00   6.00   7.00   8.00|\n|  9.00  10.00  11.00  12.00|\n| 13.00  14.00  15.00 160.00|\n").toBeTrue();
    });
});

} // namespace
