#include <aunit_fixtureregistry.h>

namespace aunit {

FixtureRegistry* FixtureRegistry::m_instance = nullptr;

FixtureRegistry& FixtureRegistry::instance()
{
    if (!m_instance) {
        m_instance = new FixtureRegistry();
    }

    return *m_instance;
}

FixtureRegistry::FixtureRegistry()
{}

FixtureRegistry::~FixtureRegistry()
{}

void FixtureRegistry::registerFixture(std::string const& name, FixturePtr fixture)
{
    m_fixtureMap.insert(std::make_pair(name, fixture));
}

FixtureRegistry::iterator FixtureRegistry::begin()
{
    return m_fixtureMap.begin();
}

FixtureRegistry::iterator FixtureRegistry::end()
{
    return m_fixtureMap.end();
}

} // namespace
