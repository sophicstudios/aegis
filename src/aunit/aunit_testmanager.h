#ifndef INCLUDED_AEGIS_AUNIT_TESTMANAGER_H
#define INCLUDED_AEGIS_AUNIT_TESTMANAGER_H

#include <string>
#include <vector>

namespace aunit {

class Reporter;
class FixtureRegistry;

class TestManager
{
public:
    enum Result {
        Result_OK = 0,
        Result_ERROR,
        Result_TEST_NOT_FOUND
    };
    
    TestManager();
    
    ~TestManager();

    Result run(Reporter& reporter);

private:
    FixtureRegistry& m_fixtureRegistry;
};

} // namespace

#endif // INCLUDED
