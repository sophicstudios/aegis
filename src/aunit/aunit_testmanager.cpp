#include <aunit_testmanager.h>
#include <aunit_testfixture.h>
#include <aunit_testregistry.h>
#include <aunit_fixtureregistry.h>
#include <aunit_describe.h>
#include <aunit_fixture.h>

namespace aunit {

TestManager::TestManager()
: m_testRegistry(TestRegistry::instance()),
  m_fixtureRegistry(FixtureRegistry::instance())
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

void TestManager::run(Reporter& reporter)
{
    FixtureRegistry::iterator it = m_fixtureRegistry.begin();
    FixtureRegistry::iterator end = m_fixtureRegistry.end();
    for (; it != end; ++it) {
        it->second->run(reporter);
    }
}

} // namespace
