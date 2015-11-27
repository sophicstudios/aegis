#ifndef INCLUDED_AEGIS_AUNIT_COMMANDLINEPARSER_H
#define INCLUDED_AEGIS_AUNIT_COMMANDLINEPARSER_H

#include <memory>
#include <iosfwd>

namespace aunit {

class TestConfiguration;

struct CommandLineParser
{
    typedef std::shared_ptr<TestConfiguration> TestConfigurationPtr;

    static TestConfigurationPtr parse(std::ostream& errorStream, int argc, char** argv);
};

} // namespace

#endif // INCLUDED
