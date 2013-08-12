#include <aunit_commandlineoptions.h>
#include <ostream>

namespace aunit {

struct ArgInfo
{
    char const* const shortParam;
    char const* const longParam;
    char const* const description;
};

CommandLineOptions::CommandLineOptions()
: m_help(false)
{}

CommandLineOptions::~CommandLineOptions()
{}

CommandLineOptions::ParseResult CommandLineOptions::parse(int argc, char** argv) 
{
    ParseResult result = ParseResult_OK;

    if (argc == 0) {
        return ParseResult_NO_VALUE_FOUND;
    }

    m_arg0 = argv[0];

    for (int i = 1; i < argc && result == ParseResult_OK; ++i) {
        std::string arg(argv[i]);

        // check for param specifiers
        if (arg.size() > 0 && arg[0] == '-') {
            std::string param;

            // check if it's a long param
            if (arg.size() > 1 && arg[1] == '-') {
                param = arg.substr(2);
            }
            else {
                param = arg.substr(1);
            }

            // If the parameter was empty, return an error
            if (param.empty()) {
                return ParseResult_NO_PARAM_SPECIFIED;
            }

            if (param == "h" || param == "help") {
                m_help = true;
                return ParseResult_OK;
            }
        }
        else {
            m_testIdList.push_back(arg);
        }
    }

    return result;
}

void CommandLineOptions::printUsage(std::ostream& os) const
{
    os << "Program usage:" << std::endl
        << "\t" << m_arg0 << " [-h] [testId[ testId[ ...]]]" << std::endl
        << std::endl
        << "\t" << "-h|--help" << "\t\t" << "Print this help" << std::endl
        << std::endl;
}

void CommandLineOptions::printErrorAndUsage(std::ostream& os, ParseResult result) const
{
    switch (result) {
    case ParseResult_OK:
        os << "OK" << std::endl << std::endl;
        break;
    case ParseResult_NO_PARAM_SPECIFIED:
        os << "No parameter specified" << std::endl << std::endl;
        break;
    case ParseResult_INVALID_PARAM:
        os << "Invalid parameter" << std::endl << std::endl;
        break;
    case ParseResult_UNEXPECTED_VALUE:
        os << "Unexpected value found" << std::endl << std::endl;
        break;
    case ParseResult_NO_VALUE_FOUND:
        os << "No value found" << std::endl << std::endl;
        break;
    case ParseResult_WRONG_VALUE_TYPE:
        os << "Value is the wrong type" << std::endl << std::endl;
        break;
    }

    printUsage(os);
}

bool CommandLineOptions::help() const {
    return m_help;
}

CommandLineOptions::TestIdList const& CommandLineOptions::testIdList() const
{
    return m_testIdList;
}

} // namespace
