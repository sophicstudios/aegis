#include <afth_uuid.h>
#include <aunit.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

namespace afth {

namespace {

bool uuidMatch(std::vector<char> const& bytes, std::string uuid)
{
    uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());
    assert(bytes.size() * 2 == uuid.size());

    for (size_t i = 0; i < bytes.size(); ++i) {
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
        if (lhs != rhs) {
            return false;
        }
    }

    return true;
}

}

class TestUUID : public aunit::TestFixture
{
public:
    TestUUID();

    virtual ~TestUUID();

protected:
    virtual void runTest();
};

AUNIT_REGISTERTEST(TestUUID);

TestUUID::TestUUID()
{}

TestUUID::~TestUUID()
{}

void TestUUID::runTest()
{
    UUID u1;
    std::string str1 = u1.str();
    AUNIT_ASSERT(str1 == "00000000-0000-0000-0000-000000000000");

    std::vector<char> b1 = u1.bytes();
    AUNIT_ASSERT(uuidMatch(b1, str1));

    UUID u2 = UUID::v4();
    std::string str2 = u2.str();
    AUNIT_ASSERT(str2[14] == '4');

    std::vector<char> b2 = u2.bytes();
    AUNIT_ASSERT(uuidMatch(b2, str2));

    AUNIT_ASSERT(u1 == u1);
    AUNIT_ASSERT(u1 <= u1);
    AUNIT_ASSERT(u1 >= u1);

    AUNIT_ASSERT(u2 == u2);
    AUNIT_ASSERT(u2 <= u2);
    AUNIT_ASSERT(u2 >= u2);
    AUNIT_ASSERT(u1 < u2);
    AUNIT_ASSERT(u2 > u1);

    UUID u3 = UUID::v4();
    if (u3 < u2) {
        AUNIT_ASSERT(u2 != u3);
        AUNIT_ASSERT(u2 > u3);
        AUNIT_ASSERT(u3 <= u2);
        AUNIT_ASSERT(!(u2 == u3));
    } else {
        AUNIT_ASSERT(u3 != u2);
        AUNIT_ASSERT(u3 > u2);
        AUNIT_ASSERT(u2 <= u3);
        AUNIT_ASSERT(!(u2 == u3));
    }

    std::stringstream s;
    s << u2;
    AUNIT_ASSERT(s.str() == u2.str());
}

} // namespace
