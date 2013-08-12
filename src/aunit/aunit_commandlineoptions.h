#ifndef INCLUDED_AEGIS_AUNIT_COMMANDLINEOPTIONS_H
#define INCLUDED_AEGIS_AUNIT_COMMANDLINEOPTIONS_H

#include <iosfwd>
#include <string>
#include <vector>

namespace aunit {

class CommandLineOptions
{
public:
    typedef std::vector<std::string> TestIdList;

    enum ParseResult {
        ParseResult_OK,
        ParseResult_NO_PARAM_SPECIFIED,
        ParseResult_INVALID_PARAM,
        ParseResult_UNEXPECTED_VALUE,
        ParseResult_NO_VALUE_FOUND,
        ParseResult_WRONG_VALUE_TYPE
    };

    CommandLineOptions();

    ~CommandLineOptions();

    ParseResult parse(int argc, char** argv);

    void printUsage(std::ostream& os) const;

    void printErrorAndUsage(std::ostream& os, ParseResult result) const;

    bool help() const;

    TestIdList const& testIdList() const;

private:
    std::string m_arg0;
    bool m_help;
    TestIdList m_testIdList;
};

} // namespace

#endif // INCLUDED
