#include <aunit_describe.h>
#include <aunit_fixture.h>
#include <aunit_fixtureregistry.h>

namespace aunit {

Describe::Describe(std::string const& name, std::function<void ()> const& func)
{
    // Get the FixtureRegistry singleton
    FixtureRegistry& registry = FixtureRegistry::instance();

    // Create an instance of the Describe object for the func
    std::shared_ptr<Fixture> fixture(new Fixture(name, func, "", -1));

    // register it with the TestRegistry
    registry.registerFixture(name, fixture);
}

Describe::~Describe()
{}

void beforeEach(std::function<void ()> const& func)
{
    // Get the current running fixture
    Fixture* instance = Fixture::instance();
    if (instance) {
        // Register the before func with the fixture
        instance->doBeforeEach(func, "", -1);
    }
}

void afterEach(std::function<void ()> const& func)
{
    // Get the current running fixture
    Fixture* instance = Fixture::instance();
    if (instance) {
        // Register the after func with the fixture
        instance->doAfterEach(func, "", -1);
    }
}

void it(std::string const& name, std::function<void ()> const& func)
{
    Fixture* instance = Fixture::instance();
    if (instance) {
        instance->doIt(name, func, "", -1);
    }
}

} // namespace
