#include <aunit_testmanager.h>
#include <aunit_testfixture.h>

namespace aegis {
namespace aunit {

TestManager::TestManager(TestRegistry& testRegistry)
: m_testRegistry(testRegistry)
{}

TestManager::~TestManager()
{}

void TestManager::runAllTests(Reporter& reporter) const
{
    TestRegistry::const_iterator it, end = m_testRegistry.end();
    for (it = m_testRegistry.begin(); it != end; ++it) {
        TestRegistry::TestFixturePtr test = (*it)();
        test->run(reporter);
    }
}

TestManager::Result TestManager::runTest(std::string const& testName, Reporter& reporter) const
{
    TestRegistry::const_iterator it = m_testRegistry.find(testName);
    if (it != m_testRegistry.end()) {
        TestRegistry::TestFixturePtr test = (*it)();
        test->run(reporter);
        return TestManager::Result_OK;
    }
    else {
        return TestManager::Result_TEST_NOT_FOUND;
    }
}

} // namespace
} // namespace
