#include <aftfs_path.h>
#include <aunit.h>

namespace aftfs {

class TestPath : public aunit::TestFixture
{
public:
    TestPath();
    
    virtual ~TestPath();
    
protected:
    virtual void runTest();
    
private:
    void testConstruction();
};

AUNIT_REGISTERTEST(TestPath);

TestPath::TestPath()
{}

TestPath::~TestPath()
{}

void TestPath::runTest()
{
    testConstruction();
}

void TestPath::testConstruction()
{
    aftfs::Path p1("/usr/local/bin");
    AUNIT_ASSERT(p1.dirname() == "/usr/local");
    AUNIT_ASSERT(p1.basename() == "bin");
    AUNIT_ASSERT(p1.extension().empty());
    AUNIT_ASSERT(p1.isAbsolute() == true);
    
    aftfs::Path p2("/usr/local/bin/");
    AUNIT_ASSERT(p2.dirname() == "/usr/local");
    AUNIT_ASSERT(p2.basename() == "bin");
    AUNIT_ASSERT(p2.extension().empty());
    AUNIT_ASSERT(p2.isAbsolute() == true);
    
    aftfs::Path p4("/usr/local/bin/test.dat");
    AUNIT_ASSERT(p4.dirname() == "/usr/local/bin");
    AUNIT_ASSERT(p4.basename() == "test.dat");
    AUNIT_ASSERT(p4.extension() == "dat");
    AUNIT_ASSERT(p4.isAbsolute() == true);
    
    aftfs::Path p5(".");
    AUNIT_ASSERT(p5.dirname() == ".");
    AUNIT_ASSERT(p5.basename() == ".");
    AUNIT_ASSERT(p5.extension().empty());
    AUNIT_ASSERT(p5.isAbsolute() == false);
    
    aftfs::Path p6("..");
    AUNIT_ASSERT(p6.dirname() == ".");
    AUNIT_ASSERT(p6.basename() == "..");
    AUNIT_ASSERT(p6.extension().empty());
    AUNIT_ASSERT(p6.isAbsolute() == false);
    
    aftfs::Path p7("./.");
    AUNIT_ASSERT(p7.dirname() == ".");
    AUNIT_ASSERT(p7.basename() == ".");
    AUNIT_ASSERT(p7.isAbsolute() == false);
    
    aftfs::Path p8("./..");
}

} // namespace
