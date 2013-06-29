#include <aata_commandlineparser.h>
#include <aunit.h>

namespace aegis {
namespace aata {

class TestCommandLineParser : public aunit::TestFixture
{
public:
    TestCommandLineParser() {}

    virtual ~TestCommandLineParser() {}

protected:
    virtual void runTest();

private:
    void testConstruction();
    void testNoArgs();
    void testSingleFlag();
    void testSingleOption();
    void testSingleNonOption();
    void testSingleOptionValidation();
};

AUNIT_REGISTERTEST(TestCommandLineParser);

void TestCommandLineParser::runTest()
{
    testNoArgs();
    testSingleFlag();
    testSingleOption();
    testSingleNonOption();
    testSingleOptionValidation();
}

void TestCommandLineParser::testNoArgs()
{
    const char* argv[] = {"command"};
    int argc = 1;
    
    CommandLineParser parser;
    
    AUNIT_ASSERT(parser.parse(argc, argv));

    AUNIT_ASSERT(parser.command() == "command");
}

void TestCommandLineParser::testSingleFlag()
{
    // initialize the flag to false;
    bool flag = false;

    // Set up the flag definition
    CommandLineParser parser;
    parser.addOptionDef("f", "flag", "flag", "Help for flag", &flag, CommandLine::Occurrence_OPTIONAL);

    // test 1: short flag present in commandline
    const char* argv1[] = {"command", "-f"};
    int argc1 = 2;

    AUNIT_ASSERT(parser.parse(argc1, argv1));
    AUNIT_ASSERT(flag == true);
    
    flag = false;
    parser.get("flag", flag);
    AUNIT_ASSERT(flag == true);

    // test 2: long flag present in commandline
    const char* argv2[] = {"command", "--flag"};
    int argc2 = 2;
    flag = false;

    AUNIT_ASSERT(parser.parse(argc2, argv2));
    AUNIT_ASSERT(flag == true);
    
    // test 3: flag not present in commandline
    conat char* argv3[] = {"command"};
    int argc3 = 1;
    flag = true;
    
    AUNIT_ASSERT(parser.parse(argc3, argv3));
    AUNIT_ASSERT(flag == false);
}

void TestCommandLineParser::testMultipleFlags()
{
    bool flag1, flag2, flag3;
    flag1 = flag2 = flag3 = false;
    
    CommandLineParser parser;
    parser.addOptionDef(
        "1",
        "flag1",
        "Help for flag1",
        CommandLineValue(&flag1),
        CommandLineValue::Occurrence_REQUIRED);
   
    parser.addOptionDef(
        "2",
        "flag2",
        "Help for flag2",
        CommandLineValue(&flag2, false),
        CommandLineValue::Occurrence_OPTIONAL);
    
    parser.addOptionDef(
        "3",
        "flag3",
        "Help for flag3",
        CommandLineValue(&flag3, false),
        CommandLineValue::Occurrence_HIDDEN);
    
    const char* argv1[] = {"command", "-1", "-2", "-3"};
    int argc1 = 4;
    
    AUNIT_ASSERT(parser.parse(argc1, argv1) == true);
    AUNIT_ASSERT(flag1 == true);
    AUNIT_ASSERT(flag2 == true);
    AUNIT_ASSERT(flag3 == true);
    
    const char* argv2[] = {"command", "-123"};
    int argc2 = 2;
    flag1 = flag2 = flag3 = false;
    
    AUNIT_ASSERT(parser.parse(argc2, argv2) == true);
    AUNIT_ASSERT(flag1 == true);
    AUNIT_ASSERT(flag2 == true);
    AUNIT_ASSERT(flag3 == true);
    
    const char* argv3[] = {"command", "-1"};
    int argc3 = 2;
    flag1 = false;
    flag2 = flag3 = true;
    
    AUNIT_ASSERT(parser.parse(argc3, argv3) == true);
    AUNIT_ASSERT(flag1 == true);
    AUNIT_ASSERT(flag2 == false); // uses default false
    AUNIT_ASSERT(flag3 == false); // uses default false
    
    const char* argv4[] = {"command", "--flag1", "--flag2", "--flag3"};
    int argc4 = 4;
    flag1 = flag2 = flag3 = false;
    
    AUNIT_ASSERT(parser.parse(argc4, argv4) == true);
    AUNIT_ASSERT(flag1 == true);
    AUNIT_ASSERT(flag2 == true);
    AUNIT_ASSERT(flag3 == true);
}

void TestCommandLineParser::testSingleOption()
{
}

void TestCommandLineParser::testMultipleOptions()
{
}

void TestCommandLineParser::testSingleNonOption()
{
}

void TestCommandLineParser::testMultipleNonOptions()
{
}

void TestCommandLineParser::testSingleOptionValidation()
{
}

} // namespace
} // namespace
