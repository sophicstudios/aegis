#include <afth_crc32.h>
#include <aunit.h>
#include <cstring>
#include <iostream>

namespace afth {

using namespace aunit;

describe("Test CRC32", []
{
    char const string1[] = "The quick brown fox jumps over the lazy dog";
    char const string2[] = "The quick brown fox jumps over the lazy dog.";

    unsigned int crc1;
    unsigned int crc2;
    unsigned int crc3;

    beforeEach([&]
    {
        crc1 = Crc32::compute(string1, std::strlen(string1));
        crc2 = Crc32::compute(string2, std::strlen(string2));
        crc3 = Crc32::compute(string1, std::strlen(string1));
    });

    afterEach([&]
    {
        crc1 = 0;
        crc2 = 0;
        crc3 = 0;
    });

    it("crc equality", [&]
    {
        expect(crc1).toEqual(crc3);
        expect(crc1).non().toEqual(crc2);
    });

    it("equal/not equal operators", [&]
    {
        expect(crc1 == crc2).toEqual(false);
        expect(crc1 != crc2).toEqual(true);
        expect(crc1 == crc3).toEqual(true);
        expect(crc1 != crc3).toEqual(false);
    });
});

} // namespace
