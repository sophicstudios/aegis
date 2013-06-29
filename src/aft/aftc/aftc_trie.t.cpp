#include <aftc_trie.h>
#include <aunit.h>

namespace aegis {
namespace aftc {

class TestTrie : public aunit::TestFixture
{
public:
    TestTrie();

    virtual ~TestTrie();

protected:
    virtual void runTest();

private:
    void testConstruction();
    void testInsert();
    void testErase();
    void testFind();
    void testIterator();
    void testPrint();
};

AUNIT_REGISTERTEST(TestTrie);

TestTrie::TestTrie()
{}

TestTrie::~TestTrie()
{}

void TestTrie::runTest()
{
    testConstruction();
    testInsert();
    testErase();
    testFind();
    testIterator();
    testPrint();
}

void TestTrie::testConstruction()
{
    Trie<float> t;
    AUNIT_ASSERT(true == t.empty());
    AUNIT_ASSERT(0 == t.size());
    AUNIT_ASSERT(t.begin() == t.end());
}

void TestTrie::testInsert()
{
}

void TestTrie::testErase()
{
}

void TestTrie::testFind()
{
}

void TestTrie::testIterator()
{
}

void TestTrie::testPrint()
{
}
    
} // namespace
} // namespace
