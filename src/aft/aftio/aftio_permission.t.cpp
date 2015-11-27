#include <aftio_permission.h>
#include <aunit.h>

namespace aftio {

using namespace aunit;

describe("aftio_permission", []
{
    it("Default Construction", [&]
    {
        Permission p;

        expect(p.read()).toBeTrue();
        expect(p.write()).toBeTrue();
        expect(p.execute()).toBeTrue();
    });

    it("Enum Construction", [&]
    {
        Permission p1(Permission::Type_READ);

        expect(p1.read()).toBeTrue();
        expect(p1.write()).non().toBeTrue();
        expect(p1.execute()).non().toBeTrue();

        Permission p2(Permission::Type_READ | Permission::Type_WRITE);

        expect(p2.read()).toBeTrue();
        expect(p2.write()).toBeTrue();
        expect(p2.execute()).non().toBeTrue();
    });

    it("R/W/E Construction", [&]
    {
        Permission p1(Permission::Read(true), Permission::Write(true), Permission::Execute(false));

        expect(p1.read()).toBeTrue();
        expect(p1.write()).toBeTrue();
        expect(p1.execute()).non().toBeTrue();
    });

    it("|= operator (R/W/E)", [&]
    {
        Permission p;
        Permission::Read read(false);
        Permission::Write write(false);
        Permission::Execute execute(false);

        p |= read;

        expect(p.read()).non().toBeTrue();

        p |= write;

        expect(p.write()).non().toBeTrue();

        p |= execute;

        expect(p.execute()).non().toBeTrue();

        read = Permission::Read(true);
        write = Permission::Write(true);
        execute = Permission::Execute(true);

        p |= read;

        expect(p.read()).toBeTrue();

        p |= write;

        expect(p.write()).toBeTrue();

        p |= execute;

        expect(p.execute()).toBeTrue();
    });

    it("|= operator (Permission)", [&]
    {
        Permission p1(false, false, false);
        Permission p2(true, true, true);

        p1 |= p2;

        expect(p1.read()).toBeTrue();
        expect(p1.write()).toBeTrue();
        expect(p1.execute()).toBeTrue();

    });

    it("&= operator (R/W/E)", [&]
    {
        Permission p;
        Permission::Read read(true);
        Permission::Write write(true);
        Permission::Execute execute(true);

        p &= read;

        expect(p.read()).non().toBeTrue();

        p &= write;

        expect(p.write()).non().toBeTrue();

        p &= execute;

        expect(p.execute()).non().toBeTrue();

        p.read(true);
        p.write(true);
        p.execute(true);

        p &= read;

        expect(p.read()).toBeTrue();

        p &= write;

        expect(p.write()).toBeTrue();

        p &= execute;

        expect(p.execute()).toBeTrue();
    });

    it("&= operator (Permission)", [&]
    {
        Permission p1(false, true, false);
        Permission p2(true, false, true);

        p1 &= p2;

        expect(p1.read()).non().toBeTrue();
        expect(p1.write()).non().toBeTrue();
        expect(p1.execute()).non().toBeTrue();
    });

    it("| operator", [&]
    {
        Permission p1(true, false, false);
        Permission p2(false, true, false);

        Permission p3 = p1 | p2;

        expect(p3.read()).toBeTrue();
        expect(p3.write()).toBeTrue();
        expect(p3.execute()).non().toBeTrue();
    });

    it("& operator", [&]
    {
        Permission p1(true, false, false);
        Permission p2(true, true, true);

        Permission p3 = p1 & p2;

        expect(p3.read()).toBeTrue();
        expect(p3.write()).non().toBeTrue();
        expect(p3.execute()).non().toBeTrue();
    });
});

} // namespace
