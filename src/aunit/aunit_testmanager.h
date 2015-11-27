#ifndef INCLUDED_AEGIS_AUNIT_TESTMANAGER_H
#define INCLUDED_AEGIS_AUNIT_TESTMANAGER_H

#include <string>
#include <vector>

namespace aunit {

class Reporter;
class TestResult;
class TestRegistry;
class FixtureRegistry;

class TestManager
{
public:
    enum Result {
        Result_OK,
        Result_TEST_NOT_FOUND,
        Result_UNKNOWN_ERROR
    };
    
    TestManager();
    
    ~TestManager();

    std::vector<std::string> testNames() const;

    /**
     * @deprecated
     */
    void runAllTests(Reporter& testReporter) const;

    /**
     * @deprecated
     */
    Result runTest(std::string const& testName, Reporter& reporter) const;

    void run(Reporter& reporter);

    //void run(std::string const& name, Reporter& reporter);

private:
    TestRegistry& m_testRegistry;
    FixtureRegistry& m_fixtureRegistry;
};

} // namespace

#endif // INCLUDED
