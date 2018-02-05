#ifndef INCLUDED_AEGIS_AUNIT_FIXTUREREGISTRY_H
#define INCLUDED_AEGIS_AUNIT_FIXTUREREGISTRY_H

#include <memory>
#include <string>
#include <map>

namespace aunit {

class Fixture;

class FixtureRegistry
{
public:
    typedef std::shared_ptr<Fixture> FixturePtr;
    typedef std::map<std::string, FixturePtr> FixtureMap;
    typedef FixtureMap::iterator iterator;

    static FixtureRegistry& instance();

    ~FixtureRegistry();

    void registerFixture(std::string const& name, FixturePtr fixture);
    
    iterator begin();

    iterator end();

private:
    FixtureRegistry();
    FixtureRegistry(FixtureRegistry const&);
    FixtureRegistry& operator=(FixtureRegistry const&);

    static FixtureRegistry* m_instance;

    FixtureMap m_fixtureMap;
};

} // namespace

#endif // INCLUDED
