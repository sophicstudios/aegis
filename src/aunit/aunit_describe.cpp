#include <aunit_describe.h>
#include <aunit_fixture.h>
#include <aunit_fixtureregistry.h>
#include <iostream>

namespace aunit {

Describe::Describe(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line)
{
    // Get the FixtureRegistry singleton
    FixtureRegistry& registry = FixtureRegistry::instance();

    // Create an instance of the Describe object for the func
    std::shared_ptr<Fixture> fixture(new Fixture(name, func, filename, line));

    // register it with the TestRegistry
    registry.registerFixture(name, fixture);
}

Describe::~Describe()
{}

void doBeforeEach(std::function<void ()> const& func, std::string const& filename, int line)
{
    // Get the current running fixture
    Fixture* instance = Fixture::instance();
    if (instance) {
        // Register the before func with the fixture
        instance->doBeforeEach(func, filename, line);
    }
}

void doAfterEach(std::function<void ()> const& func, std::string const& filename, int line)
{
    // Get the current running fixture
    Fixture* instance = Fixture::instance();
    if (instance) {
        // Register the after func with the fixture
        instance->doAfterEach(func, filename, line);
    }
}

void doIt(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line)
{
    Fixture* instance = Fixture::instance();
    if (instance) {
        instance->doIt(name, func, filename, line);
    }
}

} // namespace
