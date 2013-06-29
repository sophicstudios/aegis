#include <aunit_commandlineparser.h>
#include <aunit_testconfiguration.h>
#include <ostream>
#include <string>

namespace aegis {
namespace aunit {

namespace {

enum CommandLineParserResult {
    CommandLineParserResult_OK,
    CommandLineParserResult_NO_PARAM_SPECIFIED,
    CommandLineParserResult_INVALID_PARAM,
    CommandLineParserResult_UNEXPECTED_VALUE,
    CommandLineParserResult_NO_VALUE_FOUND,
    CommandLineParserResult_WRONG_VALUE_TYPE,
    CommandLineParserResult_WRONG_NUMBER_OF_ARGUMENTS
};

void printUsage(std::ostream& os, std::string const& arg0)
{
    os << "Program usage:" << std::endl
        << "\t" << arg0 << " [-h] [testId[ testId[ ...]]]" << std::endl
        << std::endl
        << "\t" << "-h|--help" << "\t\t" << "Print this help" << std::endl
        << std::endl;
}

void printErrorAndUsage(std::ostream& os, CommandLineParserResult result, std::string const& arg0)
{
    os << "Error: ";

    switch (result)
    {
    case CommandLineParserResult_OK:
        os << "OK" << std::endl << std::endl;
        break;
    case CommandLineParserResult_NO_PARAM_SPECIFIED:
        os << "No parameter specified" << std::endl << std::endl;
        break;
    case CommandLineParserResult_INVALID_PARAM:
        os << "Invalid parameter" << std::endl << std::endl;
        break;
    case CommandLineParserResult_UNEXPECTED_VALUE:
        os << "Unexpected value found" << std::endl << std::endl;
        break;
    case CommandLineParserResult_NO_VALUE_FOUND:
        os << "No value found" << std::endl << std::endl;
        break;
    case CommandLineParserResult_WRONG_VALUE_TYPE:
        os << "Value is the wrong type" << std::endl << std::endl;
        break;
    case CommandLineParserResult_WRONG_NUMBER_OF_ARGUMENTS:
        os << "Wrong number of arguments" << std::endl << std::endl;
    }

    printUsage(os, arg0);
}

} // namespace

CommandLineParser::TestConfigurationPtr CommandLineParser::parse(std::ostream& errorStream, int argc, char** argv)
{
    TestConfigurationPtr testConfiguration = TestConfigurationPtr(new aunit::TestConfiguration());
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);

        // check for param specifiers
        if (arg.size() > 0 && arg[0] == '-')
        {
            std::string param;

            // check if it's a long param
            if (arg.size() > 1 && arg[1] == '-')
            {
                param = arg.substr(2);
            }
            else
            {
                param = arg.substr(1);
            }

            // If the parameter was empty, return an error
            if (param.empty())
            {
                printErrorAndUsage(errorStream, CommandLineParserResult_NO_PARAM_SPECIFIED, argv[0]);
                return TestConfigurationPtr();
            }

            if (param == "h" || param == "help")
            {
                printUsage(errorStream, argv[0]);
                return TestConfigurationPtr();
            }
        }
        else
        {
            testConfiguration->addTestId(arg);
        }
    }

    return testConfiguration;
}

} // namespace
} // namespace
