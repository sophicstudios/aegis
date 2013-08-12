#include <aftu_stringutil.h>
#include <aunit.h>

namespace aftu {

class TestStringUtil
    : public aunit::TestFixture
{
public:
    TestStringUtil() {}

    virtual ~TestStringUtil() {}

protected:
    virtual void runTest();

private:
    void testTrimLeft();
    void testTrimRight();
    void testTrim();
    void testTokenize();
};

AUNIT_REGISTERTEST(TestStringUtil);

void TestStringUtil::runTest()
{
    testTrimLeft();
    testTrimRight();
    testTrim();
    testTokenize();
}

void TestStringUtil::testTrimLeft()
{
    std::string s1("xxxmy string");
    std::string s2("my string");

    aftu::StringUtil::trimLeft(&s1, 'x');
    aftu::StringUtil::trimLeft(&s2, 'x');

    AUNIT_ASSERT(s1 == s2);
}

void TestStringUtil::testTrimRight()
{
    std::string s1("my stringxxx");
    std::string s2("my string");

    aftu::StringUtil::trimRight(&s1, 'x');
    aftu::StringUtil::trimRight(&s2, 'x');

    AUNIT_ASSERT(s1 == s2);
}

void TestStringUtil::testTrim()
{
    std::string s1("xxxmy stringxxx");
    std::string s2("my string");

    aftu::StringUtil::trim(&s1, 'x');
    aftu::StringUtil::trim(&s2, 'x');

    AUNIT_ASSERT(s1 == s2);
}

void TestStringUtil::testTokenize()
{
    std::vector<std::string> tokenList1;
    std::vector<std::string> tokenList2;

    std::string s1("0");
    StringUtil::tokenize(&tokenList1, s1);
    AUNIT_ASSERT(tokenList1.size() == 1);
    AUNIT_ASSERT(tokenList1[0] == "0");

    tokenList1.clear();
    
    std::string s2("0 1");
    StringUtil::tokenize(&tokenList1, s2);
    AUNIT_ASSERT(tokenList1.size() == 2);
    AUNIT_ASSERT(tokenList1[0] == "0");
    AUNIT_ASSERT(tokenList1[1] == "1");

    tokenList1.clear();
    
    std::string s3("0;1");
    StringUtil::tokenize(&tokenList1, s3, ';');
    AUNIT_ASSERT(tokenList1.size() == 2);
    AUNIT_ASSERT(tokenList1[0] == "0");
    AUNIT_ASSERT(tokenList1[1] == "1");
    
    tokenList1.clear();

    std::string s4("0;;2");
    StringUtil::tokenize(&tokenList1, s4, ';', true);
    AUNIT_ASSERT(tokenList1.size() == 3);
    AUNIT_ASSERT(tokenList1[0] == "0");
    AUNIT_ASSERT(tokenList1[1] == "");
    AUNIT_ASSERT(tokenList1[2] == "2");
    
    tokenList1.clear();
    
    std::string s5(";1;;3;");
    StringUtil::tokenize(&tokenList1, s5, ';', true);
    AUNIT_ASSERT(tokenList1.size() == 5);
    AUNIT_ASSERT(tokenList1[0] == "");
    AUNIT_ASSERT(tokenList1[1] == "1");
    AUNIT_ASSERT(tokenList1[2] == "");
    AUNIT_ASSERT(tokenList1[3] == "3");
    AUNIT_ASSERT(tokenList1[4] == "");
}

} // namespace
