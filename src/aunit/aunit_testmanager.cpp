#include <aunit_testmanager.h>
#include <aunit_fixtureregistry.h>
#include <aunit_describe.h>
#include <aunit_fixture.h>

namespace aunit {

TestManager::TestManager()
: m_fixtureRegistry(FixtureRegistry::instance())
{}

TestManager::~TestManager()
{}

TestManager::Result TestManager::run(Reporter& reporter)
{
    bool hasErrors = false;
    FixtureRegistry::iterator it = m_fixtureRegistry.begin();
    FixtureRegistry::iterator end = m_fixtureRegistry.end();
    for (; it != end; ++it) {
        if (!it->second->run(reporter))
        {
            hasErrors = true;
        }
    }

    if (hasErrors)
    {
        return Result_ERROR;
    }

    return Result_OK;
}

} // namespace
