#include <aftu_stringutil.h>
#include <afts_assert.h>
#include <cctype>

namespace aftu {

void StringUtil::trim(std::string* s, char c)
{
    if (s->empty()) {
        return;
    }

    StringUtil::trimRight(s, c);
    StringUtil::trimLeft(s, c);
}

std::string StringUtil::trimCopy(std::string const& s, char c)
{
    if (s.empty()) {
        return std::string();
    }

    std::string::size_type start = s.find_first_not_of(c);
    if (start != std::string::npos) {
        std::string::size_type end = s.find_last_not_of(c);
        return std::string(s.begin() + start, s.begin() + end);
    }
    else {
        return std::string();
    }
}

void StringUtil::trimLeft(std::string* s, char c)
{
    if (s->empty()) {
        return;
    }

    std::string::size_type pos = s->find_first_not_of(c);
    if (pos != std::string::npos) { // found a non-'c' character
        s->erase(0, pos);
    }
    else {
        s->erase(s->begin(), s->end());
    }
}

std::string StringUtil::trimLeftCopy(std::string const& s, char c)
{
    if (s.empty()) {
        return std::string();
    }

    std::string::size_type pos = s.find_first_not_of(c);
    if (pos != std::string::npos) {
        return std::string(s.begin() + pos, s.end());
    }
    else {
        return std::string();
    }
}

void StringUtil::trimRight(std::string* s, char c)
{
    if (s->empty()) {
        return;
    }

    std::string::size_type pos = s->find_last_not_of(c);
    if (pos != std::string::npos) { // found a non-'c' character
        s->erase(pos + 1);
    }
    else {
        s->erase(s->begin(), s->end());
    }
}

std::string StringUtil::trimRightCopy(std::string const& s, char c)
{
    if (s.empty()) {
        return std::string();
    }

    std::string::size_type pos = s.find_last_not_of(c);
    if (pos != std::string::npos) {
        return std::string(s.begin(), s.begin() + pos + 1);
    }
    else {
        return std::string();
    }
}

void StringUtil::toUpper(std::string* s)
{
    std::string::iterator it, end = s->end();
    for (it = s->begin(); it != end; ++it) {
        *it = std::toupper(*it);
    }
}

std::string StringUtil::toUpperCopy(std::string const& s)
{
    std::string result;
    result.reserve(s.size());
    
    std::string::const_iterator it, end = s.end();
    for (it = s.begin(); it != end; ++it) {
        result += std::toupper(*it);
    }
    
    return result;
}

void StringUtil::toLower(std::string* s)
{
    std::string::iterator it, end = s->end();
    for (it = s->begin(); it != end; ++it) {
        *it = std::tolower(*it);
    }
}

std::string StringUtil::toLowerCopy(std::string const& s)
{
    std::string result;
    result.reserve(s.size());
    
    std::string::const_iterator it, end = s.end();
    for (it = s.begin(); it != end; ++it) {
        result += std::tolower(*it);
    }
    
    return result;
}

void StringUtil::tokenize(
    std::vector<std::string>* tokens,
    std::string const& s,
    char sep,
    bool keepEmptyTokens)
{
    StringUtil::tokenize(tokens, s.begin(), s.end(), sep, keepEmptyTokens);
}

void StringUtil::tokenize(
    std::vector<std::string>* tokens,
    std::string::const_iterator beg,
    std::string::const_iterator end,
    char sep,
    bool keepEmptyTokens)
{
    AFTS_ASSERT(tokens);
    
    std::string::const_iterator it1, it2;

    // start with both iterators at the beginning
    it1 = it2 = beg;

    // skip any sep characters at the beginning
    while (*it1 == sep && it1 != end) {
        if (keepEmptyTokens) {
            tokens->push_back(std::string());
        }

        ++it1;
        ++it2;
    }
    
    // loop through the rest of the characters in the string
    while (it2 != end) {
        if (*it2 != sep) {
            ++it2;
        }
        else {
            tokens->push_back(std::string(it1, it2));
            it1 = it2;

            ++it1;
            ++it2;

            while (*it1 == sep && it1 != end) {
                if (keepEmptyTokens) {
                    tokens->push_back(std::string());
                }
                
                ++it1;
                ++it2;
            }
        }
    }
    
    if (it1 != it2 || keepEmptyTokens) {
        tokens->push_back(std::string(it1, it2));
    }
}

void StringUtil::tokenize(
    std::vector<std::string>* tokens,
    std::string const& s,
    std::string const& seps,
    bool keepEmptyTokens)
{
    StringUtil::tokenize(tokens, s.begin(), s.end(), seps, keepEmptyTokens);
}

bool isSep(char c, std::string const& seps)
{
    std::string::const_iterator it, end = seps.end();
    for (it = seps.begin(); it != end; ++it) {
        if (*it == c) {
            return true;
        }
    }
    
    return false;
}

void StringUtil::tokenize(
    std::vector<std::string>* tokens,
    std::string::const_iterator beg,
    std::string::const_iterator end,
    std::string const& seps,
    bool keepEmptyTokens)
{
    AFTS_ASSERT(tokens);
    
    std::string::const_iterator it1, it2;
    
    it1 = it2 = beg;
    
    while (isSep(*it1, seps) && it1 != end) {
        if (keepEmptyTokens) {
            tokens->push_back(std::string());
        }
        
        ++it1;
        ++it2;
    }
    
    while (it2 != end) {
        if (isSep(*it2, seps)) {
            tokens->push_back(std::string(it1, it2));
            it1 = it2;
            
            ++it1;
            ++it2;
            
            while (isSep(*it1, seps) && it1 != end) {
                if (keepEmptyTokens) {
                    tokens->push_back(std::string());
                }
                
                ++it1;
                ++it2;
            }
        }
        else {
            ++it2;
        }
    }
    
    if (it1 != it2 || keepEmptyTokens) {
        tokens->push_back(std::string(it1, it2));
    }
}

} // namespace
