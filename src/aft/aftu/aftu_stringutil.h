#ifndef INCLUDED_AEGIS_AFTU_STRINGUTIL_H
#define INCLUDED_AEGIS_AFTU_STRINGUTIL_H

#include <string>
#include <vector>

namespace aegis {
namespace aftu {

struct StringUtil
{
    /**
     * Removes the specified character from the beginning and end of the
     * supplied string. The removal is done to the original string.
     * \param s The string to trim.
     * \param c The character to remove.
     */
    static void trim(std::string* s, char c = ' ');

    /** Removes the character 'c' from the beginning and end
     * of string 's' and returns the newly trimmed string.
     * The original string is untouched.
     * \param s The string to trim.
     * \param c The character to remove.
     * \result The trimmed string.
     */
    static std::string trimCopy(std::string const& s, char c = ' ');

    /** Removes the character 'c' from the beginning of the
     * string 's' and returns the newly trimmed string.
     * The removal is done to the original string.
     * \param s The string to trim.
     * \param c The character to remove.
     */
    static void trimLeft(std::string* s, char c = ' ');
    
    /**
     * \param s The string to trim.
     * \param c The character to remove.
     * \result The trimmed string.
     */
    static std::string trimLeftCopy(std::string const& s, char c = ' ');

    /**
     * \param s The string to trim.
     * \param c The character to remove.
     */
    static void trimRight(std::string* s, char c = ' ');

    /**
     * \param s The string to trim.
     * \param c The character to remove.
     * \result The trimmed string.
     */
    static std::string trimRightCopy(std::string const& s, char c = ' ');
    
    static void toUpper(std::string* s);
    
    static void toUpperTrim(std::string* s);
    
    static std::string toUpperCopy(std::string const& s);
    
    static std::string toUpperTrimCopy(std::string const& s);
    
    static void toLower(std::string* s);
    
    static void toLowerTrim(std::string* s);
    
    static std::string toLowerCopy(std::string const& s);
    
    static std::string toLowerTrimCopy(std::string const& s);
    
    static void tokenize(
        std::vector<std::string>* tokens,
        std::string const& s,
        char sep = ' ',
        bool keepEmptyTokens = true);
    
    static void tokenize(
        std::vector<std::string>* tokens,
        std::string::const_iterator beg,
        std::string::const_iterator end,
        char sep = ' ',
        bool keepEmptyTokens = true);
    
    static void tokenize(
        std::vector<std::string>* tokens,
        std::string const& s,
        std::string const& seps,
        bool keepEmptyTokens = true);
    
    static void tokenize(
        std::vector<std::string>* tokens,
        std::string::const_iterator beg,
        std::string::const_iterator end,
        std::string const& seps,
        bool keepEmptyTokens = true);
        
};

} // namespace
} // namespace

#endif // INCLUDED
