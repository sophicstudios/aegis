#include <aata_commandlineparser.h>
#include <boost/algorithm/string.hpp>
#include <sstream>

namespace aegis {
namespace aata {

namespace {

} // namespace

CommandLineParser::CommandLineParser()
{}

CommandLineParser::~CommandLineParser()
{}

bool CommandLineParser::addOption(
    std::string const& shortTag,
    std::string const& longTag,
    std::string const& identifier,
    std::string const& helpMessage)
{
    // verify that we have some sort of identifier
    if (shortTag.empty() && longTag.empty() && identifier.empty()) {
        return false;
    }
    
    // verify if any of the identifiers already exist
    bool shortTagExists = !shortTag.empty()
        && m_shortTagOptionMap.find(shortTag) != m_shortTagOptionMap.end();
    
    bool longTagExists = !longTag.empty()
        && m_longTagOptionMap.find(longTag) != m_longTagOptionMap.end();
        
    bool identifierExists = !identifier.empty()
        && m_identifierOptionMap.find(identifier) != m_identifierOptionMap.end();
        
    if (shortTagExists || longTagExists || identifierExists) {
        return false;
    }

    // create a new option definition object
    OptionDefPtr optionDef(new OptionDef());
    optionDef->shortTag = shortTag;
    optionDef->longTag = longTag;
    optionDef->identifier = identifier;
    optionDef->helpMessage = helpMessage;

    // map the short tag to the option definition
    if (!shortTag.empty()) {
        m_shortTagOptionMap.insert(std::make_pair(shortTag, optionDef));
    }

    // map the long tag to the option definition    
    if (!longTag.empty()) {
        m_longTagOptionMap.insert(std::make_pair(longTag, optionDef));
    }
    
    // map the identifier to the option definition
    if (!identifier.empty()) {
        m_identifierOptionMap.insert(std::make_pair(identifier, optionDef));
    }
    
    return true;
}

CommandLineParser::ParseResult CommandLineParser::parse(int argc, char const** const argv)
{
    std::stringstream errorStream;
    
    if (argc < 1) {
        return ParseResult_EMPTY_ARGUMENT_LIST;
    }
    
    int i = 0;
    // first argument is assumed to be the program name
    m_command = argv[i];
    ++i;
    
    while (i < argc) {
        std::string arg(argv[i]);
        boost::algorithm::trim(arg);
        
        if (arg.empty()) {
            errorStream << "Empty argument at position " << i << std::endl;
            m_errorMessage = errorStream.str();
            return ParseResult_EMPTY_ARGUMENT;
        }
        
        if (arg[0] == '-') {
            // short or long tag
            if (arg.size() == 1) {
                errorStream << "Badly formatted option '" << arg << "' at position " << i << std::endl;
                return ParseResult_BAD_OPTION_FORMAT;
            }

            if (arg[1] == '-') {
                if (arg.size() == 2) {
                    errorStream << "Badly formatted option '" << arg << "' at position " << i << std::endl;
                    return ParseResult_BAD_OPTION_FORMAT;
                }

                // long tag. remaining characters are the tag name
                std::string tagName = arg.substr(2);
                
                OptionMap::iterator it = m_longTagOptionMap.find(tagName);
                if (it == m_longTagOptionMap.end()) {
                    errorStream << "Unknown option '" << tagName << "' at position " << i << std::endl;
                    return ParseResult_OTHER_ERROR;
                }
                
                /*
                if (it->second->type == CommandLineValue::Type_BOOL) {
                    // a flag option. Set the value to true
                }
                else {
                    // a normal option, parse the next token for the value
                    ++i;
                    
                    if (i >= argc) {
                        errorStream << "Missing option value for '" << tagName << "'" << std::endl;
                        return ParseResult_MISSIONG_OPTION_VALUE;
                    }
                }
                */
            }
            else {
                // short tag. At this point there are a couple of possibilities:
                // 1) tag followed by whitespace, i.e. '-a '
                // 2) tag followed by non-whitespace, i.e. '-abc'
                //    a) if 'a' is a flag, then 'b' is another tag
                //    b) "bc" is the tag value
                
                // grab the tag and check what type it is
            }
        }
        else {
            // tag argument or position option
        }
    }
    
    return ParseResult_OK;
}

CommandLineParser::ParseResult CommandLineParser::parse(char const* args)
{
    return ParseResult_OTHER_ERROR;
}

void CommandLineParser::printHelp(std::ostream& os) const
{
}

std::string const& CommandLineParser::command() const
{
    return m_command;
}

std::string CommandLineParser::getString(std::string const& id, std::string& value) const
{
    return std::string();
}

} // namespace
} // namespace
