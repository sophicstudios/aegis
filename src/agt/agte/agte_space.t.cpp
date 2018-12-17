#include <agte_space.h>
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

bool operator==(Dummy const& d1, Dummy const& d2) {
    return d1.value == d2.value;
}

Describe d("agte_space", [] {
    it("Constructor", [&] {
        agte::Space space;
        expect(space.id()).toEqual(space.id());
    });

    it("Create Entity", [&] {
        agte::Space space;
        agte::Space::Entity e = space.createEntity();
    });

    it("Assign Component", [&] {
        agte::Space space;
        agte::Space::Entity e = space.createEntity();

        Dummy d;
        d.value = 1;
        d.d = 1.1;
        d.f = 1.2f;
        d.c = 'a';

        e.assign(d);

        Dummy d1 = e.get<Dummy>();
        expect(d1 == d).toBeTrue();
    });
});

} // namespace
} // namespace

