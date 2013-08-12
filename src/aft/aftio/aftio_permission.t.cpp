#include <aftio_permission.h>
#include <aunit.h>

namespace aftio {

class TestPermission : public aunit::TestFixture
{
public:
    TestPermission() {}

    virtual ~TestPermission() {}

protected:
    virtual void runTest();
    
private:
    void testConstruction();
    void testOperators();
};

AUNIT_REGISTERTEST(TestPermission);

void TestPermission::runTest()
{
    testConstruction();
    testOperators();
}

void TestPermission::testConstruction()
{
    Permission p1;
    AUNIT_ASSERT(p1.hasRead() && p1.hasWrite() && p1.hasExecute());
    
    Permission p2(Permission::Type_READ | Permission::Type_WRITE);
    AUNIT_ASSERT(p2.hasRead() && p2.hasWrite() && !p2.hasExecute());
    
    Permission p3(Permission::Type_EXECUTE);
    AUNIT_ASSERT(!p3.hasRead() && !p3.hasWrite() && p3.hasExecute());
    
    Permission p4("r");
    AUNIT_ASSERT(p4.hasRead() && !p4.hasWrite() && !p4.hasExecute());
    
    Permission p5("rw");
    AUNIT_ASSERT(p5.hasRead() && p5.hasWrite() && !p5.hasExecute());
}

void TestPermission::testOperators()
{
    Permission p(false, false, false);
    Permission pRead(Permission::Type_READ);
    Permission pWrite(Permission::Type_WRITE);
    Permission pExec(Permission::Type_EXECUTE);
    
    p += pRead;
    AUNIT_ASSERT(p.hasRead() && !p.hasWrite() && !p.hasExecute());
    
    p += pWrite;
    AUNIT_ASSERT(p.hasRead() && p.hasWrite() && !p.hasExecute());
    
    p += pExec;
    AUNIT_ASSERT(p.hasRead() && p.hasWrite() && p.hasExecute());
    
    p -= pRead;
    AUNIT_ASSERT(!p.hasRead() && p.hasWrite() && p.hasExecute());
    
    p -= pWrite;
    AUNIT_ASSERT(!p.hasRead() && !p.hasWrite() && p.hasExecute());
    
    p -= pExec;
    AUNIT_ASSERT(!p.hasRead() && !p.hasWrite() && !p.hasExecute());
}

} // namespace
