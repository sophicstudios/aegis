#ifndef INCLUDED_AEGIS_AFTS_ASSERT_H
#define INCLUDED_AEGIS_AFTS_ASSERT_H

#include <afts_compiler.h>
#include <boost/function.hpp>

/**
 * Native C assert in both release and debug builds.
 */
#define AFTS_ASSERT(x) \
    afts::AssertUtil::assertFunc(x, #x, __LINE__, __FILE__);

/**
 * Native C assert, but only for debug builds.
 */
#if defined(AFTS_DEBUG)
#define AFTS_ASSERT_DEBUG(x) \
    afts::AssertUtil::assertFunc(x, #x, __LINE__, __FILE__);
#else
#define AFTS_ASSERT_DEBUG(x)
#endif

namespace afts {

struct AssertUtil
{
    typedef boost::function<void (bool, const char*, int, const char*)> AssertFunc;
    
    static void assignAssertFunc(AssertFunc const& f);
    
    static void assertFunc(bool value, char const* msg, int line, char const* file);
};

} // namespace

#endif // INCLUDED
