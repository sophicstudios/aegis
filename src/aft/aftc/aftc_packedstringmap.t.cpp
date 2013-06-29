#include <aftc_packedstringmap.h>
#include <aunit.h>

namespace aegis {
namespace aftc {

class TestPackedStringMap : public aunit::TestFixture
{
public:
    TestPackedStringMap();

    virtual ~TestPackedStringMap();

protected:
    virtual void runTest();

private:
    void testConstruction();
    void testInsert();
    void testErase();
    void testFind();
    void testLowerBound();
    void testUpperBound();
    void testIterator();
    void testPrint();
};

AUNIT_REGISTERTEST(TestPackedStringMap);

TestPackedStringMap::TestPackedStringMap()
{}

TestPackedStringMap::~TestPackedStringMap()
{}

void TestPackedStringMap::runTest()
{
    testConstruction();
    testInsert();
    testErase();
    testFind();
    testLowerBound();
    testUpperBound();
    //testIterator();
    //testPrint();
}

void TestPackedStringMap::testConstruction()
{
    PackedStringMap<int> m;
    AUNIT_ASSERT(m.empty() == true);
    AUNIT_ASSERT(m.size() == 0);
    AUNIT_ASSERT(m.begin() == m.end());
}

void TestPackedStringMap::testInsert()
{
    PackedStringMap<int> m;
    typedef std::pair<PackedStringMap<int>::iterator, bool> Result;

    Result r1 = m.insert(std::make_pair("test1", 1));
    AUNIT_ASSERT(m.empty() == false);
    AUNIT_ASSERT(m.size() == 1);
    AUNIT_ASSERT(r1.first != m.end());
    AUNIT_ASSERT(r1.second == true);
    AUNIT_ASSERT(*(r1.first) == 1);
    
    Result r2 = m.insert(std::make_pair("test20", 20));
    AUNIT_ASSERT(m.empty() == false);
    AUNIT_ASSERT(m.size() == 2);
    AUNIT_ASSERT(r2.first != m.end());
    AUNIT_ASSERT(r2.second == true);
    AUNIT_ASSERT(*(r2.first) == 20);
    
    Result r3 = m.insert(std::make_pair("test1", 3));
    AUNIT_ASSERT(m.empty() == false);
    AUNIT_ASSERT(m.size() == 2);
    AUNIT_ASSERT(r3.first != m.end());
    AUNIT_ASSERT(r3.first == m.begin());
    AUNIT_ASSERT(r3.first == r1.first);
    AUNIT_ASSERT(*(r3.first) == 1);
    
    Result r4 = m.insert(std::make_pair("test0", 0));
    AUNIT_ASSERT(m.empty() == false);
    AUNIT_ASSERT(m.size() == 3);
    AUNIT_ASSERT(r4.first != m.end());
    AUNIT_ASSERT(r4.second == true);
    AUNIT_ASSERT(*(r4.first) == 0);
    
    Result r5 = m.insert(std::make_pair("test2", 2));
    AUNIT_ASSERT(m.empty() == false);
    AUNIT_ASSERT(m.size() == 4);
    AUNIT_ASSERT(r5.first != m.end());
    AUNIT_ASSERT(r5.second == true);
    AUNIT_ASSERT(*(r5.first) == 2);    
}

void TestPackedStringMap::testErase()
{
    PackedStringMap<int> m;
    m.insert(std::make_pair("test0", 0));
    m.insert(std::make_pair("test1", 1));
    m.insert(std::make_pair("test12345", 12345));
    m.insert(std::make_pair("test20", 20));
    m.insert(std::make_pair("test333", 333));
    
    AUNIT_ASSERT(m.size() == 5);
    
    bool r1 = m.erase("test1");
    AUNIT_ASSERT(r1 == true);
    AUNIT_ASSERT(m.size() == 4);
    AUNIT_ASSERT(*(m.begin()) == 0);

    bool r2 = m.erase("test333");
    AUNIT_ASSERT(r2 == true);
    AUNIT_ASSERT(m.size() == 3);
    AUNIT_ASSERT(*(m.begin()) == 0);

    bool r3 = m.erase("test0");
    AUNIT_ASSERT(r3 == true);
    AUNIT_ASSERT(m.size() == 2);
    AUNIT_ASSERT(*(m.begin()) == 12345);

    bool r4 = m.erase("notfound");
    AUNIT_ASSERT(r4 == false);
    AUNIT_ASSERT(m.size() == 2);

    bool r5 = m.erase("test20");
    AUNIT_ASSERT(r5 == true);
    AUNIT_ASSERT(m.size() == 1);
    
    bool r6 = m.erase("test12345");
    AUNIT_ASSERT(r6 == true);
    AUNIT_ASSERT(m.size() == 0);
    AUNIT_ASSERT(m.begin() == m.end());
}

void TestPackedStringMap::testFind()
{
    PackedStringMap<int> m;
    m.insert(std::make_pair("test1", 1));
    m.insert(std::make_pair("test20", 20));
    m.insert(std::make_pair("test333", 333));
    m.insert(std::make_pair("mytest12345", 12345));
    
    PackedStringMap<int>::iterator it = m.find("mytest12345");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(it == m.begin());
    AUNIT_ASSERT(*it == 12345);

    it = m.find("test1");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(*it == 1);
    
    it = m.find("test20");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(*it == 20);
    
    it = m.find("test333");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(*it == 333);
        
    it = m.find("notfound");
    AUNIT_ASSERT(it == m.end());
}

void TestPackedStringMap::testLowerBound()
{
    PackedStringMap<int> m;
    m.insert(std::make_pair("test1", 1));
    m.insert(std::make_pair("test12345", 12345));
    m.insert(std::make_pair("test20", 20));
    m.insert(std::make_pair("test333", 333));
    
    PackedStringMap<int>::iterator it = m.lowerBound("test1");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(it == m.begin());
    AUNIT_ASSERT(*it == 1);
    
    it = m.lowerBound("test20");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(*it == 20);
}

void TestPackedStringMap::testUpperBound()
{
    PackedStringMap<int> m;
    m.insert(std::make_pair("test1", 1));
    m.insert(std::make_pair("test12345", 12345));
    m.insert(std::make_pair("test20", 20));
    m.insert(std::make_pair("test333", 333));

    PackedStringMap<int>::iterator it = m.upperBound("test1");
    AUNIT_ASSERT(it != m.end());
    AUNIT_ASSERT(*it == 12345);
    
    it = m.upperBound("test333");
    AUNIT_ASSERT(it == m.end());
}

void TestPackedStringMap::testIterator()
{
    PackedStringMap<int> m;
    m.insert(std::make_pair("test1", 1));
    m.insert(std::make_pair("test20", 20));
    m.insert(std::make_pair("test333", 333));
    
    PackedStringMap<int>::iterator it;
    it = m.begin();

    AUNIT_ASSERT(*it == 1);

    PackedStringMap<int>::iterator end;
    end = m.end();

    AUNIT_ASSERT(it != end);
    
    PackedStringMap<int>::iterator it1 = ++it;
    AUNIT_ASSERT(*it == 20);
    AUNIT_ASSERT(*it1 == 20);
    AUNIT_ASSERT(it1 == it);
    AUNIT_ASSERT(it != end);
    
    PackedStringMap<int>::iterator it2 = it++;
    AUNIT_ASSERT(*it == 333);
    AUNIT_ASSERT(*it2 == 20);
    AUNIT_ASSERT(it != it2);
    AUNIT_ASSERT(it != end);
    
    ++it;
    AUNIT_ASSERT(it == end);
    
    PackedStringMap<int>::iterator it3 = it--;
    AUNIT_ASSERT(*it == 333);
    AUNIT_ASSERT(it3 == end);
    AUNIT_ASSERT(it != it3);
    AUNIT_ASSERT(it != end);
    
    PackedStringMap<int>::iterator it4 = --it;
    AUNIT_ASSERT(*it == 20);
    AUNIT_ASSERT(*it4 == 20);
    AUNIT_ASSERT(it == it4);
    AUNIT_ASSERT(it != end);
    
    --it;
    AUNIT_ASSERT(it == m.begin());
    AUNIT_ASSERT(*it == 1);
}

void TestPackedStringMap::testPrint()
{
}

} // namespace
} // namespace
