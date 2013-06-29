#include <aata_commandline.h>
#include <aunit.h>

namespace aegis {
namespace aata {

class TestCommandLine : public aunit::TestFixture
{
public:
    TestCommandLine();
    
    virtual ~TestCommandLine();
    
protected:
    virtual void runTest();

private:
    void testConstruction();
};

AUNIT_REGISTERTEST(TestCommandLine);

TestCommandLine::TestCommandLine()
{}

TestCommandLine::~TestCommandLine()
{}

void TestCommandLine::runTest()
{
    testConstruction();
}

void TestCommandLine::testConstruction()
{
    int argc1 = 1;
    char const* const argv1[] = {"test1"};
    
    aata::CommandLine test1(argc1, argv1);
    AUNIT_ASSERT(test1.programName() == "test1");
    
    int argc2 = 2;
    char const* const argv2[] = {"test2", "arg1"};
    
    aata::CommandLine test2(argc2, argv2);
    AUNIT_ASSERT(test2.programName() == "test2");
    AUNIT_ASSERT(test2.hasArgument("arg1") == true);
    //AUNIT_ASSERT(test2.hasArgumentCaseInsensitive("ARG1") == true);
}

} // namespace
} // namespace
