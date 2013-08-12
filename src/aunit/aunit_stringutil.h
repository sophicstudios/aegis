#ifndef INCLUDED_AEGIS_AUNIT_STRINGUTIL_H
#define INCLUDED_AEGIS_AUNIT_STRINGUTIL_H

#include <string>

namespace aunit {

struct StringUtil
{
    static void trim(std::string& str, char c = ' ');

    static void trimLeft(std::string& str, char c = ' ');

    static void trimRight(std::string& str, char c = ' ');
};

} // namespace

#endif // INCLUDED
