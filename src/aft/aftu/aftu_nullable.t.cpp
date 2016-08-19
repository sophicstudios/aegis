#include <aftu_nullable.h>
#include <aunit.h>
#include <string>

namespace {

using namespace aunit;
using namespace aftu;

Describe d("aftu_nullable", []
{
    it("Default Construction", [&]
    {
        aftu::Nullable<std::string> nullable;

        expect(nullable.isNull()).toBeTrue();
    });

    it("Value Construction", [&]
    {
        std::string myString("myString");
        aftu::Nullable<std::string> nullable(myString);

        expect(nullable.isNull()).non().toBeTrue();
        expect(nullable.value()).toEqual(myString);
    });

    it("makeNull", [&]
    {
        std::string myString("myString");
        aftu::Nullable<std::string> nullable(myString);

        nullable.makeNull();

        expect(nullable.isNull()).toBeTrue();
    });
});

} // namespace
