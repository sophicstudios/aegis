#include <aunit_reporter.h>

namespace aunit {

Reporter::Reporter()
{}

Reporter::~Reporter()
{
}

void Reporter::setFixture(std::string const& name)
{
    onSetFixture(name);
}

void Reporter::addResult(TestResult const& result)
{
}

void Reporter::addResult(std::string const& name, bool success, std::string const& filename, int line)
{
    onAddResult(name, success, filename, line);
}

void Reporter::onSetFixture(std::string const& name)
{
}

void Reporter::onAddResult(std::string const& name, bool success, std::string const& filename, int line)
{
}

} // namespace
