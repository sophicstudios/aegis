#include <agte_pool.h>
#include <aunit.h>

namespace agte {
namespace {

using namespace aunit;

struct Dummy {
    size_t value;
    double d;
    float f;
    char c;
};

Describe d("agte_pool", [] {
    it("Constructor", [&] {
        agte::Pool<Dummy> pool;
        expect(pool.capacity()).toEqual(0);
    });

    it("reserve", [&] {
        agte::Pool<Dummy, 10> pool;
        pool.reserve(1);
        expect(pool.capacity()).toEqual(10);

        pool.reserve(11);
        expect(pool.capacity()).toEqual(20);
    });

    it("get", [&] {
        agte::Pool<Dummy> pool;
        pool.resize(10);

        Dummy* ptr1 = static_cast<Dummy*>(pool.at(0));
        expect(ptr1 != nullptr).toBeTrue();

        Dummy* ptr2 = static_cast<Dummy*>(pool.at(5));
        size_t s1 = sizeof(Dummy) * (ptr2 - ptr1);
        size_t s2 = sizeof(Dummy) * 5;
        expect(s1 == s2).toBeTrue();
    });
});

} // namespace
} // namespace

