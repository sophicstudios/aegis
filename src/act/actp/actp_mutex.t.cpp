#include <actp_mutex.h>
#include <aunit.h>

namespace aegis {
namespace actp {

class TestMutex : public aunit::TestFixture
{
public:
    TestMutex() {}

    virtual ~TestMutex() {}

protected:
    virtual void runTest();
};

AUNIT_REGISTER_TEST(TestMutex);

void TestMutex::runTest()
{
    actp::Mutex m;
    m.lock();
    m.unlock();
}

} // namespace
} // namespace
