#include <aunit_testfixture.h>
#include <aunit_reporter.h>

namespace aegis {
namespace aunit {

TestFixture::TestFixture()
{}

TestFixture::~TestFixture()
{}

void TestFixture::run(Reporter& reporter)
{
    m_reporter = &reporter;
    setup();
    runTest();
    tearDown();
}

void TestFixture::setup()
{}

void TestFixture::tearDown()
{}

Reporter& TestFixture::reporter()
{
    return *m_reporter;
}

} // namespace
} // namespace
