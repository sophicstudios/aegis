#ifndef INCLUDED_AEGIS_AUNIT_TESTMANAGER_H
#define INCLUDED_AEGIS_AUNIT_TESTMANAGER_H

#include <aunit_testregistry.h>

namespace aegis {
namespace aunit {

class Reporter;
class TestResult;

class TestManager
{
public:
    enum Result {
        Result_OK,
        Result_TEST_NOT_FOUND,
        Result_UNKNOWN_ERROR
    };
    
    TestManager(TestRegistry& testRegistry = TestRegistry::instance());
    
    ~TestManager();

    std::vector<std::string> testNames() const;
    
    void runAllTests(Reporter& testReporter) const;
    
    Result runTest(std::string const& testName, Reporter& reporter) const;
        
private:
    TestRegistry& m_testRegistry;
};

} // namespace
} // namespace

#endif // INCLUDED
