#ifndef INCLUDED_AEGIS_AUNIT_COMMANDLINEPARSER_H
#define INCLUDED_AEGIS_AUNIT_COMMANDLINEPARSER_H

#include <boost/shared_ptr.hpp>
#include <iosfwd>

namespace aunit {

class TestConfiguration;

struct CommandLineParser
{
    typedef boost::shared_ptr<TestConfiguration> TestConfigurationPtr;

    static TestConfigurationPtr parse(std::ostream& errorStream, int argc, char** argv);
};

} // namespace

#endif // INCLUDED
