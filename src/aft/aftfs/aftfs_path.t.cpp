#include <aftfs_path.h>
#include <aunit.h>

namespace aftfs {

using namespace aunit;

describe("aftfs_path", []
{
    it("Constructor - directory with no ending slash", [&]
    {
        aftfs::Path p("/usr/local/bin");

        expect(p.dirname()).toEqual("/usr/local");
        expect(p.basename()).toEqual("bin");
        expect(p.extension().empty()).toBeTrue();
        expect(p.isAbsolute()).toBeTrue();
    });

    it("Constructor - directory with ending slash", [&]
    {
        aftfs::Path p("/usr/local/bin/");

        expect(p.dirname()).toEqual("/usr/local");
        expect(p.basename()).toEqual("bin");
        expect(p.extension().empty()).toBeTrue();
        expect(p.isAbsolute()).toBeTrue();
    });

    it("Constructor - file with extension", [&]
    {
        aftfs::Path p("/usr/local/bin/test.dat");

        expect(p.dirname()).toEqual("/usr/local/bin");
        expect(p.basename()).toEqual("test.dat");
        expect(p.extension()).toEqual("dat");
        expect(p.isAbsolute()).toBeTrue();
    });

    it("Constructor - current directory ('.') with no slash", [&]
    {
        aftfs::Path p(".");

        expect(p.dirname()).toEqual(".");
        expect(p.basename()).toEqual(".");
        expect(p.extension().empty()).toBeTrue();
        expect(p.isAbsolute()).non().toBeTrue();
    });

    it("Constructor - one directory level up ('..') with no slash", [&]
    {
        aftfs::Path p("..");

        expect(p.dirname()).toEqual(".");
        expect(p.basename()).toEqual("..");
        expect(p.extension().empty()).toBeTrue();
        expect(p.isAbsolute()).non().toBeTrue();
    });

    it("Constructor - current directory ('./.') with slash", [&]
    {
        aftfs::Path p("./.");

        expect(p.dirname()).toEqual(".");
        expect(p.basename()).toEqual(".");
        expect(p.extension().empty()).toBeTrue();
        expect(p.isAbsolute()).non().toBeTrue();
    });

    it("Constructor - one directory level up ('./..') with slash", [&]
    {
        aftfs::Path p("./..");

        expect(p.dirname()).toEqual(".");
        expect(p.basename()).toEqual("..");
        expect(p.extension().empty()).toBeTrue();
        expect(p.isAbsolute()).non().toBeTrue();
    });
});

} // namespace
