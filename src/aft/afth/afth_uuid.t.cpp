#include <afth_uuid.h>
#include <aunit.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <cassert>

namespace {

using namespace aunit;
using namespace afth;

namespace {

bool uuidMatch(std::vector<char> const& bytes, std::string uuid)
{
    uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());
    assert(bytes.size() * 2 == uuid.size());

    for (size_t i = 0; i < bytes.size(); ++i)
    {
        // convert the byte to a string
        std::stringstream s;
        s << std::hex << std::nouppercase << std::setfill('0');
        s << std::setw(2) << (static_cast<uint32_t>(bytes[i]) & 0xff);
        std::string lhs = s.str();

        // grab two characters to form the equivalent from the uuid string
        std::string rhs;
        rhs += uuid[i*2];
        rhs += uuid[(i*2)+1];

        // compare
        if (lhs != rhs)
        {
            return false;
        }
    }

    return true;
}

} // namespace

Describe d("afth_uuid", []
{
    const char* zeroUUID = "00000000-0000-0000-0000-000000000000";

    it("Default construction", [&]
    {
        UUID uuid;
        std::string str = uuid.str();

        expect(str).toEqual(zeroUUID);
    });

    it("Version 4 construction", [&]
    {
        UUID uuid = UUID::v4();
        std::string str = uuid.str();

        expect(str[14]).toEqual('4');
        expect(uuidMatch(uuid.bytes(), str)).toEqual(true);
    });

    it("bytes", [&]
    {
        UUID uuid = UUID::v4();
        std::string str = uuid.str();

        expect(uuidMatch(uuid.bytes(), str)).toEqual(true);
    });

    it("equality operators", [&]
    {
        UUID u1 = UUID::v4();
        UUID u2 = UUID::v4();

        expect(u1 == u1).toEqual(true);
        expect(u2 == u2).toEqual(true);
        expect(u1 != u2).toEqual(true);
    });

    it("lt operator", [&]
    {
        UUID u1;
        UUID u2 = UUID::v4();

        expect(u1 < u2).toEqual(true);
        expect(u2 < u1).toEqual(false);
    });

    it("gt operator", [&]
    {
        UUID u1;
        UUID u2 = UUID::v4();

        expect(u2 > u1).toEqual(true);
        expect(u1 > u2).toEqual(false);
    });

    it("lt/eq operator", [&]
    {
        UUID u1;
        UUID u2 = UUID::v4();
        UUID u3 = UUID::v4();

        expect(u1 <= u2).toEqual(true);
        expect(u1 <= u1).toEqual(true);
        expect(u2 <= u1).toEqual(false);
    });

    it("gt/eq operator", [&]
    {
        UUID u1;
        UUID u2 = UUID::v4();
        UUID u3 = UUID::v4();

        expect(u2 >= u1).toEqual(true);
        expect(u1 >= u1).toEqual(true);
        expect(u1 >= u2).toEqual(false);
    });

    it("str operator", [&]
    {
        UUID uuid = UUID::v4();
        std::stringstream s;
        s << uuid;
        expect(s.str()).toEqual(uuid.str());
    });
});

} // namespace
