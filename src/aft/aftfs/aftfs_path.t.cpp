#include <aftfs_path.h>
#include <aunit.h>

namespace aegis {
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
    AUNIT_ASSERT(p1.nativePathString() == "/usr/local/bin");
    AUNIT_ASSERT(p1.dirname() == "/usr/local");
    AUNIT_ASSERT(p1.basename() == "bin");
    AUNIT_ASSERT(p1.extension().empty());
    
    aftfs::Path p2("/usr//local/bin");
    AUNIT_ASSERT(p2.nativePathString() == "/usr/local/bin");
    AUNIT_ASSERT(p2.dirname() == "/usr/local");
    AUNIT_ASSERT(p2.basename() == "bin");
    AUNIT_ASSERT(p2.extension().empty());
    
    aftfs::Path p3("file:///usr/local/bin");
    aftfs::Path p4("/usr/local/bin/test.dat");
    
}

} // namespace
} // namespace
