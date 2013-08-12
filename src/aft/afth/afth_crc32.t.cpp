#include <afth_crc32.h>
#include <aunit.h>
#include <cstring>

namespace afth {

class TestCrc32 : public aunit::TestFixture
{
public:
    TestCrc32();

    virtual ~TestCrc32();

protected:
    virtual void runTest();
};

AUNIT_REGISTERTEST(TestCrc32);

TestCrc32::TestCrc32()
{}

TestCrc32::~TestCrc32()
{}

void TestCrc32::runTest()
{
    char const string1[] = "The quick brown fox jumps over the lazy dog";
    char const string2[] = "The quick brown fox jumps over the lazy dog.";

    unsigned int crc1 = Crc32::compute(string1, std::strlen(string1));
    unsigned int crc2 = Crc32::compute(string2, std::strlen(string2));

    AUNIT_ASSERT(crc1 != crc2);

    unsigned int crc3 = Crc32::compute(string1, std::strlen(string1));

    AUNIT_ASSERT(crc1 == crc3);
}

} // namespace
