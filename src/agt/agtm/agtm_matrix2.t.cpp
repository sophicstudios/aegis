#include <agtm_matrix2.h>
#include <agtm_matrix2util.h>
#include <agtm_vector2.h>
#include <aunit.h>
#include <array>
#include <iomanip>
#include <sstream>

namespace {

using namespace aunit;
using namespace agtm;

template<typename T, typename U>
bool verify(agtm::Matrix2<T> const& m, U v1, U v2, U v3, U v4)
{
    std::array<T, 4> arr = agtm::Matrix2Util::toRowMajor(m);

    return arr[0] == v1 && arr[1] == v2 && arr[2] == v3 && arr[3] == v4;
}

Describe d("agtm_matrix2", []
{
    it("Construction", [&]
    {
        agtm::Matrix2<float> m1;
        expect(verify(m1, 0, 0, 0, 0)).toBeTrue();

        agtm::Matrix2<float> m2(1, 2, 3, 4);
        expect(verify(m2, 1, 2, 3, 4)).toBeTrue();

        std::array<std::array<float, 2>, 2> arr{{ {{5, 6}}, {{7, 8}} }};
        agtm::Matrix2<float> m3(arr);
        expect(verify(m3, 5, 6, 7, 8)).toBeTrue();

        agtm::Matrix2<float> m4 = agtm::Matrix2<float>::identity();
        expect(verify(m4, 1, 0, 0, 1)).toBeTrue();
    });

    it("Assignment", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);
        agtm::Matrix2<float> m2(5, 6, 7, 8);

        m1 = m2;
        expect(verify(m1, 5, 6, 7, 8)).toBeTrue();
    });

    it("Addition", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);
        agtm::Matrix2<float> m2(1, 2, 3, 4);

        agtm::Matrix2<float> m3 = m1 + m2;
        expect(verify(m3, 2, 4, 6, 8)).toBeTrue();

        m1 += m2;
        expect(verify(m1, 2, 4, 6, 8)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);
        agtm::Matrix2<float> m2(1, 2, 3, 4);

        agtm::Matrix2<float> m3 = m1 - m2;
        expect(verify(m3, 0, 0, 0, 0)).toBeTrue();

        m1 -= m2;
        expect(verify(m1, 0, 0, 0, 0)).toBeTrue();
    });

    it("Multiplication", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);
        agtm::Matrix2<float> m2(2, 3, 4, 5);

        agtm::Matrix2<float> m3 = m1 * m2;
        expect(verify(m3, 10, 13, 22, 29)).toBeTrue();

        m1 *= m2;
        expect(verify(m1, 10, 13, 22, 29)).toBeTrue();

        agtm::Matrix2<float> m4 = m2 * 3.0f;
        expect(verify(m4, 6, 9, 12, 15)).toBeTrue();

        agtm::Matrix2<float> m5 = 3.0f * m2;
        expect(verify(m5, 6, 9, 12, 15)).toBeTrue();

        m2 *= 3.0f;
        expect(verify(m2, 6, 9, 12, 15)).toBeTrue();

        agtm::Matrix2<float> m6(1, 2, 3, 4);
        agtm::Vector2<float> v1(1, 2);

        agtm::Vector2<float> v2 = m6 * v1;
        expect(v2.x() == 5.0f && v2.y() == 11.0f).toBeTrue();

        agtm::Vector2<float> v3 = v1 * m6;
        expect(v3.x() == 7.0f && v3.y() == 10.0f).toBeTrue();
    });

    it("Division", [&]
    {
        agtm::Matrix2<float> m1(6, 9, 12, 15);

        agtm::Matrix2<float> m2 = m1 / 3.0f;
        expect(verify(m2, 2, 3, 4, 5)).toBeTrue();

        m1 /= 3.0f;
        expect(verify(m1, 2, 3, 4, 5)).toBeTrue();

        agtm::Matrix2<float> m3(2, 4, 5, 20);

        agtm::Matrix2<float> m4 = 20.0f / m3;
        expect(verify(m4, 10, 5, 4, 1)).toBeTrue();
    });

    it("Comparison", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);
        agtm::Matrix2<float> m2(2, 3, 4, 5);

        expect(m1 == m1).toBeTrue();
        expect(m1 != m2).toBeTrue();
    });

    it("Element Accessors", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);

        expect(m1(0, 0) == 1.0f).toBeTrue();
        expect(m1(0, 1) == 2.0f).toBeTrue();
        expect(m1(1, 0) == 3.0f).toBeTrue();
        expect(m1(1, 1) == 4.0f).toBeTrue();

        m1(0, 0) = 2.0f;
        m1(0, 1) = 3.0f;
        m1(1, 0) = 4.0f;
        m1(1, 1) = 5.0f;

        expect(m1(0, 0) == 2.0f).toBeTrue();
        expect(m1(0, 1) == 3.0f).toBeTrue();
        expect(m1(1, 0) == 4.0f).toBeTrue();
        expect(m1(1, 1) == 5.0f).toBeTrue();
    });

    it("Row/Column Accessors", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 4);

        agtm::Vector2<float> r0 = m1.row(0);
        expect(r0.x() == 1.0f && r0.y() == 2.0f).toBeTrue();

        agtm::Vector2<float> r1 = m1.row(1);
        expect(r1.x() == 3.0f && r1.y() == 4.0f).toBeTrue();

        agtm::Vector2<float> c0 = m1.col(0);
        expect(c0.x() == 1.0f && c0.y() == 3.0f).toBeTrue();

        agtm::Vector2<float> c1 = m1.col(1);
        expect(c1.x() == 2.0f && c1.y() == 4.0f).toBeTrue();
    });

    it("Stream", [&]
    {
        agtm::Matrix2<float> m1(1, 2, 3, 400);

        std::ostringstream s;
        std::ios::fmtflags flags = s.flags();
        bool boolalpha = flags & std::ios::boolalpha;
        bool showbase = flags & std::ios::showbase;
        bool showpoint = flags & std::ios::showpoint;
        bool showpos = flags & std::ios::showpos;
        bool skipws = flags & std::ios::skipws;
        bool unitbuf = flags & std::ios::unitbuf;
        bool uppercase = flags & std::ios::uppercase;
        bool hex = flags & std::ios::hex;
        bool dec = flags & std::ios::dec;
        bool oct = flags & std::ios::oct;
        bool fixed = flags & std::ios::fixed;
        bool scientific = flags & std::ios::scientific;
        bool left = flags & std::ios::left;
        bool right = flags & std::ios::right;
        bool internal = flags & std::ios::internal;

        s << std::setw(3);
        size_t w = s.width();

        s << "val:" << 5 << "\n";
        w = s.width();

        expect(s.str() == "\n|  1   2|\n|  3 400|\n").toBeTrue();
    });
});

} // namespace
