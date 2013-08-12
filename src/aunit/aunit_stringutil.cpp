#include <aunit_stringutil.h>

namespace aunit {

void StringUtil::trim(std::string& str, char c)
{
    StringUtil::trimRight(str, c);
    StringUtil::trimLeft(str, c);
}

void StringUtil::trimLeft(std::string& str, char c)
{
    std::string::size_type pos = str.find_first_not_of(c);
    if (pos != std::string::npos) { // found a non-'c' character
        str.erase(0, pos);
    }
    else {
        str.erase(str.begin(), str.end());
    }
}

void StringUtil::trimRight(std::string& str, char c)
{
    std::string::size_type pos = str.find_last_not_of(c);
    if (pos != std::string::npos) { // found a non-'c' character
        str.erase(pos + 1);
    }
    else {
        str.erase(str.begin(), str.end());
    }
}

} // namespace
