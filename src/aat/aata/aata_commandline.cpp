#include <aata_commandline.h>
#include <aftu_stringutil.h>
#include <boost/algorithm/string/compare.hpp>

namespace aegis {
namespace aata {

namespace {

struct IsEqualCaseInsensitive
{
    IsEqualCaseInsensitive(std::string const& str)
    : m_str(str)
    {}
    
    bool operator()(std::string const& val)
    {
        return m_iequal(val, m_str);
    }

    std::string const& m_str;
    boost::algorithm::is_iequal m_iequal;
};

} // namespace

CommandLine::CommandLine()
{}

CommandLine::CommandLine(int argc, char const* const argv[])
{
    if (argc > 0) {
        m_programName = argv[0];
        
        for (int i = 1; i < argc; ++i) {
            m_argumentList.push_back(argv[i]);
        }
    }
}

CommandLine::CommandLine(
    char const* const programName,
    char const* const arguments)
: m_programName(programName)
{
    aftu::StringUtil::tokenize(m_argumentList, arguments, ' ', false);
}

CommandLine::CommandLine(char const* const commandLine)
{
    aftu::StringUtil::tokenize(m_argumentList, commandLine, ' ', false);

    if (m_argumentList.size() > 0) {
        m_programName = m_argumentList[0];
        m_argumentList.erase(m_argumentList.begin());
    }
}

CommandLine::~CommandLine()
{}

std::string const& CommandLine::programName() const
{
    return m_programName;
}

std::vector<std::string> const& CommandLine::argumentList() const
{
    return m_argumentList;
}

int CommandLine::hasArgument(std::string const& argument) const
{
    ArgumentList::const_iterator it = std::find(
        m_argumentList.begin(),
        m_argumentList.end(),
        argument);
    
    return (
        it == m_argumentList.end()
        ? -1
        : (it - m_argumentList.begin())
    );
}

int CommandLine::hasArgumentCaseInsensitive(std::string const& argument) const
{
    ArgumentList::const_iterator it = std::find_if(
        m_argumentList.begin(),
        m_argumentList.end(),
        IsEqualCaseInsensitive(argument));
    
    return (
        it == m_argumentList.end()
        ? -1
        : (it - m_argumentList.begin())
    );
}

} // namespace
} // namespace
