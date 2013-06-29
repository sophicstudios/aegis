#ifndef INCLUDE_AEGIS_AATA_COMMANDLINE_H
#define INCLUDE_AEGIS_AATA_COMMANDLINE_H

#include <string>
#include <vector>

namespace aegis {
namespace aata {

class CommandLine
{
public:
    /**
     * Default constructor
     */
    CommandLine();
    
    /**
     * Constructor that takes the number of arguments and an array of
     * null terminated strings representing the arguments, as specified
     * in the C/C++ standards. The program name is the first argument.
     */
    CommandLine(int argc, char const* const argv[]);
    
    /**
     * Construct a CommandLine object from a string representing the
     * program command, and a string containing the rest of the command
     * line.
     */
    CommandLine(char const* const programName, char const* const arguments);
    
    /**
     * Construct a CommandLine object from a string that contains both
     * the program name and all the arguments on the command line.
     */
    CommandLine(char const* const commandLine);
    
    /**
     * Destructor
     */
    ~CommandLine();
    
    /**
     * The program program name, including any path information.
     */
    std::string const& programName() const;
    
    /**
     * The list of arguments.
     */
    std::vector<std::string> const& argumentList() const;
    
    /**
     * Determines whether the exact string 'arg' is present in the
     * argument list. Returns -1 if no argument exists, otherwise returns
     * the position of the argument in the list.
     */
    int hasArgument(std::string const& argument) const;

    /** 
     * Determines whether the string 'arg' is present in the argument list
     * by doing a caseless comparison. Returns -1 if no argument exists,
     * otherwise returns the position of the argument in the list.
     */
    int hasArgumentCaseInsensitive(std::string const& argument) const;
    
private:
    typedef std::vector<std::string> ArgumentList;
    
    std::string m_programName;
    ArgumentList m_argumentList;
};

} // namespace
} // namespace

#endif // INCLUDE
