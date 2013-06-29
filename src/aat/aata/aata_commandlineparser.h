#ifndef INCLUDE_AEGIS_AATA_COMMANDLINEOPTIONS_H
#define INCLUDE_AEGIS_AATA_COMMANDLINEOPTIONS_H

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <vector>

namespace aegis {
namespace aata {

struct CommandLineGroupDef
{
    char groupId[64];
    char description[1024];
};

struct CommandLineOptionDef
{
    char group[64];
    char shortTag[2];
    char longTag[64];
    char description[1024];
    CommandLineValue::Type type;
};

class CommandLineParser
{
public:
    enum ParseResult {
        ParseResult_OK,
        ParseResult_EMPTY_ARGUMENT_LIST,
        ParseResult_EMPTY_ARGUMENT,
        ParseResult_BAD_OPTION_FORMAT,
        ParseResult_OTHER_ERROR
    };

    CommandLineParser();
    
    ~CommandLineParser();

    bool addOptionGroup(
        std::string const& id,
        std::string const& title,
        std::string const& helpMessage);
        
    bool addOptionDef(
        std::string const& shortTag,
        std::string const& longTag,
        std::string const& id,
        std::string const& helpMessage);
    
    ParseResult parse(int argc, char const** const argv);
    
    ParseResult parse(char const* args);
    
    void printHelp(std::ostream& os) const;
        
    std::string const& command() const;
    
    std::string getString(std::string const& id, std::string& value) const;
    
private:    
    struct OptionDef
    {
        std::string shortTag;
        std::string longTag;
        std::string identifier;
        std::string helpMessage;
        //CommandLineValue::Type type;
    };
    
    typedef boost::shared_ptr<OptionDef> OptionDefPtr;

    struct OptionGroup
    {
        std::string identifier;
        std::string description;
        std::string helpMessage;
        std::vector<OptionDefPtr> groupOptionDefList;
    };

    std::string m_command;

    typedef std::map<std::string, OptionDefPtr> OptionMap;

    std::string m_errorMessage;
    
    OptionMap m_shortTagOptionMap;
    OptionMap m_longTagOptionMap;
    OptionMap m_identifierOptionMap;
};

} // namespace
} // namespace

#endif // INCLUDE
